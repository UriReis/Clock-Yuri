#include <stdio.h>
#include "pico/stdlib.h"   
#include "hardware/timer.h" 
#include "hardware/pio.h"
#include "pio.h"

#define PIN_RED 11
#define PIN_Y 12
#define PIN_G 13
bool led_onR = false;
bool led_onY = false;
bool led_onG = false;


bool repeating_timer_callback(struct repeating_timer *t) {
    // Imprime uma mensagem na saída serial indicando que 1 segundo se passou.
    printf("1 segundo passou\n");
    //Liga ou desliga o led.
    led_onR = !led_onR;
    gpio_put(PIN_RED,led_onR);
    // Retorna true para manter o temporizador repetindo. Se retornar false, o temporizador para.
    return true;
}

int main() {
    // Inicializa a comunicação serial, permitindo o uso de funções como printf.
    stdio_init_all();

    // Inicializar o pino GPIO11
    gpio_init(PIN_RED);
    gpio_set_dir(PIN_RED,true);
    gpio_init(PIN_Y);
    gpio_set_dir(PIN_Y,true);
    gpio_init(PIN_G);
    gpio_set_dir(PIN_G,true);


    // Declaração de uma estrutura de temporizador de repetição.
    // Esta estrutura armazenará informações sobre o temporizador configurado.
    struct repeating_timer timer;

    // Configura o temporizador para chamar a função de callback a cada 1 segundo.
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    // Loop infinito que mantém o programa em execução.
    while (true) {
        // Pausa de 10 segundos para reduzir o uso da CPU.
        sleep_ms(10000);
        printf("rotina de repetição\n");
    }
    return 0;
}
