# Participantes (1ESPG) 
- Bianca Carvalho Dancs Firsoff     - RM551645
- Gabriel Machado Carrara Pimentel  - RM99880

# O que é
<div align="justify">Este projeto foi desenvolvido para monitorar dados vitais - como batimentos cardíacos, temperatura e mobilidade - de pacientes que passarão o período de doença em casa, sem a presença de acompanhantes. Isso facilita o monitoramento e agiliza a resposta da equipe de socorro, com o principal objetivo de prevenir o óbito de pacientes enviados para casa devido à negligência médica.</div>

## De onde surgiu
Durante o período de avaliação, um dos membros da equipe vivenciou a perda de alguém muito importante devido à negligência médica.

# Recursos necessários para a implementação
- ESP32, tornando a conexão por WI-FI entre o sistema operacional e o sensor possível;
- IoT, conecta com o ESP32 e recebe informações;
- Sensor para medir os batimentos cardíacos;
- Acelerômetro, para monitorar a movimentação do paciente, como por exemplo uma queda.

# Protocolo de funcionamento
1. Quando o paciente chega no hospital, ele preenche sua ficha de cadastro, onde coloca se estará acompanhado no período de doença ou não;
2. Após a consulta, o paciente pega a prescrição médica e se dirige até a recepção;
3. Na recepção ele dá sua prescrição para um/uma atendente, que coloca na pulseira o período que ela estará funcionando;
    - O período de funcionamento é determinado pelo tempo que o paciente estará tomando o remédico + 5 dias.
4. O sensor coleta informações sobre o paciente a todo momento;
5. Esses dados são passados para o sistema principal através do ESP32(WI-FI);
6. Caso os batimentos cardiácos e a movimentação estejam normais, nada ocorre;
7. Caso o acelerômetro detecte uma parada brusca, por exemplo indicando uma queda, o sensor irá medir os batimentos cardiácos;
8. Dependendo do que o paciente escolheu quando pegou a pulseira na recepção do posto de saúde/hospital, algum contato de emergência ou o SAMU será acionado;
9. Quando o período de funcionamento da pulseira acabar, o paciente a levará até o posto de saúde ou farmácia mais próxima;
10. As pulseiras serão coletadas, higienizadas e, em seguida, redistribuídas para os postos/hospitais.

## Demonstração do funcionamento (WOKWI)
[Link da demonstração do funcionamento do sistema](https://wokwi.com/projects/382329660081844225)

### Código usado no ESP-32 para a demonstração
[Código do ESP-32](pulseira.ino)

### Vídeo da demonstração :
[YOUTUBE](https://youtu.be/5j3m3gKmQnY)

# OBSERVAÇÃO
Coloquei a pasta zipada com todos os componentes que o WOKWI da só por precaução
