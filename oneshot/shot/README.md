# shot-Yuri

Aluno: Yuri Silva Reis 
Matrícula: TIC370101506

Tarefa 2: Temporizador de Um Disparo (One Shot) - Controle de LEDs com Botão
Este projeto implementa um sistema de temporização para acionamento de LEDs a partir do clique de um botão. Quando o botão é pressionado, três LEDs (azul, vermelho e verde) são ligados e, em seguida, desligados em sequência a cada 3 segundos.

Descrição do Código
O código utiliza um botão para iniciar a sequência de temporização. Quando o botão é pressionado:

Todos os LEDs são ligados.

Após 3 segundos, o LED azul é desligado.

Após mais 3 segundos, o LED vermelho é desligado.

Após mais 3 segundos, o LED verde é desligado.

O botão só pode ser pressionado novamente após todos os LEDs serem desligados.

Componentes Necessários
Raspberry Pi Pico W

3 LEDs (azul, vermelho, verde)

3 resistores de 330 Ω

1 botão (pushbutton)

Jumpers e protoboard

Configuração dos Pinos
LED Azul: GPIO 12

LED Vermelho: GPIO 13

LED Verde: GPIO 11

Botão: GPIO 5

Como Executar
Conecte os LEDs e o botão aos pinos GPIO conforme a configuração acima.

Compile e carregue o código no Raspberry Pi Pico W.

Ao pressionar o botão, os LEDs serão ligados e desligados em sequência.

Código Principal
O código principal está no arquivo main.c e utiliza as seguintes funções:

gpio_irq_handler: Função de interrupção para detectar o pressionamento do botão.

turn_off_callback: Função de callback para desligar os LEDs em sequência.

add_alarm_in_ms: Configura o temporizador para chamar a função de callback após 3 segundos.

Exemplo de Saída
No terminal serial, a mensagem "A: <valor>" será impressa sempre que o botão for pressionado, indicando o número de vezes que o botão foi acionado.