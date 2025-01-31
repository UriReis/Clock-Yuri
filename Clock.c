#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"



#define PIN_RED 11
#define PIN_Y 12
#define PIN_G 13
bool led_onR = false;
bool led_onY = false;
bool led_onG = false;

int iterador = 0;
bool repeating_timer_callback(struct repeating_timer *t)
{
    switch (iterador)
    {
    case 0:
        gpio_put(PIN_RED, 1); // Vermelho on
        gpio_put(PIN_Y, 0);   // Amarelo off
        gpio_put(PIN_G, 0);   // Verde off
        iterador++;
        break;
    case 1:
        gpio_put(PIN_RED, 0); // Vermelho off
        gpio_put(PIN_Y, 1);   // Amarelo on
        gpio_put(PIN_G, 0);   // Verde off
        iterador++;
        break;
    case 2:
        gpio_put(PIN_RED, 0); // Vermelho off
        gpio_put(PIN_Y, 0);   // Amarelo off
        gpio_put(PIN_G, 1);   // Verde on
        iterador = 0;         // Reinicia o ciclo
        break;
    }
    return true;
}

int main()
{
    // Inicializa a comunicação serial, permitindo o uso de funções como printf.
    stdio_init_all();

    // Inicializar o pino GPIO11
    gpio_init(PIN_RED);
    gpio_set_dir(PIN_RED, true);
    gpio_init(PIN_Y);
    gpio_set_dir(PIN_Y, true);
    gpio_init(PIN_G);
    gpio_set_dir(PIN_G, true);

    // Declaração de uma estrutura de temporizador de repetição.
    // Esta estrutura armazenará informações sobre o temporizador configurado.
    struct repeating_timer timer;

    // Configura o temporizador para chamar a função de callback a cada 1 segundo.
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    // Loop infinito que mantém o programa em execução.
    while (true)
    {
        // Pausa de 1 segundos para reduzir o uso da CPU.
        sleep_ms(1000);
        printf("1 segundo\n");
    }
    return 0;
}
