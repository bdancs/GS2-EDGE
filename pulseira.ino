#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 m_p_u;

#define PULSE_PER_BEAT    1           // Número de pulsos por batimento cardíaco
#define INTERRUPT_PIN     5           // Pino de interrupção
#define SAMPLING_INTERVAL 1000        // Intervalo de amostragem em milissegundos
#define TEMPERATURE_THRESHOLD 38.0    // Limiar de temperatura para o alerta em °C

volatile uint16_t pulse;              // Variável que será incrementada na interrupção
uint16_t count;                       // Variável para armazenar o valor atual de pulse

float heartRate;                      // Frequência cardíaca calculada a partir de count

portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;  // Mutex para garantir acesso seguro a pulse

void IRAM_ATTR HeartRateInterrupt() {
  portENTER_CRITICAL_ISR(&mux);  //Entra em uma seção crítica de interrupção
  pulse++;  //Incrementa a variável pulse de maneira segura
  portEXIT_CRITICAL_ISR(&mux);   //Sai da seção crítica de interrupção
}

void setup() {
  Serial.begin(115200);
  while (!Serial)
    delay(20);

  Serial.println("Inicializando o MPU6050...");
  
  Wire.begin(21, 23); // Inicializa a comunicação I2C com SDA na porta 21 e SCL na porta 23

  if (!m_p_u.begin()) {
    Serial.println("Falha ao iniciar o sensor MPU6050. Verifique a conexão e endereço do sensor.");
    while (1) {
      delay(20);
    }
  }

  Serial.println("MPU6050 inicializado com sucesso!");

  pinMode(INTERRUPT_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), HeartRateInterrupt, RISING);  // Configura a interrupção no pino
}

void loop() {
  HeartRate();  //Chama a função principal

  sensors_event_t acc, gcc, temp;
  m_p_u.getEvent(&acc, &gcc, &temp);

  Serial.println("\n===== Frequência Cardíaca =====");
  Serial.println("Frequência Cardíaca: " + String(heartRate, 2) + " BPM");

  Serial.println("\n===== Temperatura =====");
  Serial.println("\nTemperatura: " + String(temp.temperature) + " °C");

  //Verifica possível queda com um limiar aleatório entre 1.0 e 10.0
  checkPossibleFall(acc, random(10) + 1);

  //Verifica se a temperatura ultrapassa 38°C
  checkTemperatureAlert(temp.temperature, TEMPERATURE_THRESHOLD);

  delay(5000);
}

void HeartRate() {
  static unsigned long startTime;
  if (millis() - startTime < SAMPLING_INTERVAL) return;   //Intervalo de mostragem
  startTime = millis();

  portENTER_CRITICAL(&mux);  //Entra em uma seção crítica
  count = pulse;  //Salva o valor atual de pulse e zera pulse
  pulse = 0;
  portEXIT_CRITICAL(&mux);   //Sai da seção crítica

  //Ajuste na fórmula para mapear a faixa de 0 Hz a 220 Hz para a frequência cardíaca em BPM
  heartRate = map(count, 0, 220, 0, 220);  //Mapeia a contagem para a faixa desejada

  //Verifica se a frequência cardíaca atingiu 0
  if (heartRate == 0) {
    //Alerta de frequência cardíaca zero
    Serial.println("\n===== Alerta de Frequência Cardíaca =====");
    Serial.println("ALERTA! Frequência cardíaca atingiu 0 BPM. Chamando a equipe de socorros.");
  }
}

void checkPossibleFall(sensors_event_t accel, float fallThreshold) {
  //Calcula a magnitude da aceleração
  float magnitude = sqrt(accel.acceleration.x * accel.acceleration.x + 
                         accel.acceleration.y * accel.acceleration.y + 
                         accel.acceleration.z * accel.acceleration.z);

  //Se a magnitude da aceleração estiver abaixo do limiar, considere como uma possível queda
  if (magnitude < fallThreshold) {
    //Código para alerta ou chamada de socorro
    Serial.println("\n===== Queda =====");
    Serial.println("Possível queda detectada! Chamando a equipe de socorros");
  }
}

void checkTemperatureAlert(float temperature, float tempThreshold) {
  //Verifica se a temperatura ultrapassa 38°C
  if (temperature > tempThreshold) {
    //Alerta de febre
    Serial.println("\n===== Febre =====");
    Serial.println("ALERTA! A temperatura ultrapassou " + String(tempThreshold) + " °C.");
  }
}
