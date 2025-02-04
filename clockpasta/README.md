# Clock-Yuri

Tarefa 1: Temporizador Periódico - Semáforo com LEDs
Aluno: Yuri Silva Reis 
Matrícula: TIC370101506

Este projeto implementa um semáforo utilizando um Raspberry Pi Pico W e três LEDs (vermelho, amarelo e verde). O semáforo alterna entre as cores a cada 3 segundos, simulando o funcionamento de um semáforo real.

Descrição do Código
O código utiliza um temporizador periódico (repeating_timer) para alternar entre os estados do semáforo:

Vermelho: LED vermelho ligado, amarelo e verde desligados.

Amarelo: LED amarelo ligado, vermelho e verde desligados.

Verde: LED verde ligado, vermelho e amarelo desligados.

O temporizador é configurado para chamar uma função de callback a cada 3 segundos, alterando o estado dos LEDs.

Componentes Necessários:

- Raspberry Pi Pico W

- 3 LEDs (vermelho, amarelo, verde)

- 3 resistores de 330 Ω

- Jumpers e protoboard

Configuração dos Pinos:

- LED Vermelho: GPIO 11

- LED Amarelo: GPIO 12

- LED Verde: GPIO 13

Como Executar:

Conecte os LEDs aos pinos GPIO conforme a configuração acima.

Compile e carregue o código no Raspberry Pi Pico W.

O semáforo começará a funcionar automaticamente, alternando entre as cores a cada 3 segundos.

Código Principal:

O código principal está no arquivo main.c e utiliza as seguintes funções:

repeating_timer_callback: Alterna o estado dos LEDs.

add_repeating_timer_ms: Configura o temporizador para chamar a função de callback a cada 3 segundos.

Exemplo de Saída:

No terminal serial, a mensagem "1 segundo" será impressa a cada segundo, enquanto os LEDs alternam entre as cores.