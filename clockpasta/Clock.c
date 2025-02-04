#include <stdio.h>              
#include "pico/stdlib.h"        
#include "hardware/timer.h"     // Biblioteca para manipulação de temporizadores

// Definição dos pinos GPIO para os LEDs
#define PIN_RED 11  // LED vermelho
#define PIN_Y 12    // LED amarelo
#define PIN_G 13    // LED verde

// Variável global para controlar o estado do semáforo
int iterador = 0;


  
 //Esta função é chamada automaticamente a cada 3 segundos e altera o estado dos LEDs
 //simulando um semáforo: Vermelho → Amarelo → Verde → Vermelho...
 
bool repeating_timer_callback(struct repeating_timer *t)
{
    switch (iterador)
    {
    case 0: // Primeiro estado: LED vermelho aceso
        gpio_put(PIN_RED, 1); // Liga o LED vermelho
        gpio_put(PIN_Y, 0);   // Desliga o LED amarelo
        gpio_put(PIN_G, 0);   // Desliga o LED verde
        iterador++;           // Avança para o próximo estado
        break;
    case 1: // Segundo estado: LED amarelo aceso
        gpio_put(PIN_RED, 0); // Desliga o LED vermelho
        gpio_put(PIN_Y, 1);   // Liga o LED amarelo
        gpio_put(PIN_G, 0);   // Desliga o LED verde
        iterador++;           // Avança para o próximo estado
        break;
    case 2: // Terceiro estado: LED verde aceso
        gpio_put(PIN_RED, 0); // Desliga o LED vermelho
        gpio_put(PIN_Y, 0);   // Desliga o LED amarelo
        gpio_put(PIN_G, 1);   // Liga o LED verde
        iterador = 0;         // Reinicia o ciclo para voltar ao LED vermelho
        break;
    }
    return true; 
}

int main()
{
    // Inicializa a comunicação serial, permitindo o uso de printf para depuração
    stdio_init_all();

    // Configuração dos pinos GPIO como saída
    gpio_init(PIN_RED);
    gpio_set_dir(PIN_RED, GPIO_OUT);
    gpio_init(PIN_Y);
    gpio_set_dir(PIN_Y, GPIO_OUT);
    gpio_init(PIN_G);
    gpio_set_dir(PIN_G, GPIO_OUT);

    // Declaração de um temporizador repetitivo
    struct repeating_timer timer;

    // Configuração do temporizador para chamar a função repeating_timer_callback a cada 3 segundos (3000 ms)
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    // Loop infinito para manter o programa em execução
    while (true)
    {
        // Aguarda 1 segundo e imprime uma mensagem na porta serial
        sleep_ms(1000);
        printf("1 segundo\n");
    }

    return 0; 
}

