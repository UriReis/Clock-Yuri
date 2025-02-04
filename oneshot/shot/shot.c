#include <stdio.h>       // Biblioteca padrão do C.
#include "pico/stdlib.h" // Biblioteca padrão do Raspberry Pi Pico para controle de GPIO, temporização e comunicação serial.
#include "pico/time.h"   // Biblioteca para gerenciamento de temporizadores e alarmes.

const uint LED_PING = 11;
const uint LED_PINR = 13;
const uint LED_PINB = 12;  // Define o pino GPIO 11 para controlar o LED.
const uint BUTTON_PIN = 5; // Define o pino GPIO 5 para ler o estado do botão.

bool controle = false;
static volatile uint iterador = 0;
absolute_time_t turn_off_time; // Variável para armazenar o tempo em que o LED deve ser desligado (não utilizada neste código).

// Função de callback para desligar o LED após o tempo programado.
int a = 0;
int64_t turn_off_callback(alarm_id_t id, void *user_data)
{

    switch (iterador)
    {
    case 0:
        gpio_put(LED_PINB, false);
        iterador++;
        return (3000*1000);
        break;
    case 1:
        gpio_put(LED_PINR, false);
        iterador++;
        return (3000*1000);
        break;
    case 2:
        gpio_put(LED_PING, false);
        iterador = 0;
        controle = false;
        return (0);
    default:
        break;
    }
}

void gpio_irq_handler(uint gpio, uint32_t events)
{
    // Obtém o tempo atual em microssegundos
    uint32_t current_time = to_us_since_boot(get_absolute_time());
    static volatile uint32_t last_timeA = 0; // Armazena o tempo do último evento (em microssegundos)

    // Verifica se passou tempo suficiente desde o último evento

    if (current_time - last_timeA > 200000)
    { // Debouncing de 200m
        if (gpio == BUTTON_PIN && controle == false)
        {

            last_timeA = current_time;
            gpio_put(LED_PINR, true);
            gpio_put(LED_PING, true);
            gpio_put(LED_PINB, true);
            controle = true;
            add_alarm_in_ms(3000, turn_off_callback, NULL, false);

            printf("A: %d\n", a); // Para controle quando se usa o monitor serial para verificar se há bouncing
        }
    }
}

int main()
{

    stdio_init_all();

    gpio_init(LED_PINR);
    gpio_set_dir(LED_PINR, GPIO_OUT);

    gpio_init(LED_PING);
    gpio_set_dir(LED_PING, GPIO_OUT);

    gpio_init(LED_PINB);
    gpio_set_dir(LED_PINB, GPIO_OUT);

    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

    gpio_set_irq_enabled_with_callback(BUTTON_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

    // Loop principal do programa que verifica continuamente o estado do botão.
    while (true)
    {
        // Verifica se o botão foi pressionado (nível baixo no pino) e se o LED não está ativo.
        sleep_ms(2000);
    }

    // Introduz uma pequena pausa de 10 ms para reduzir o uso da CPU.
    // Isso evita que o loop seja executado muito rapidamente e consuma recursos desnecessários.
    sleep_ms(10);

    // Retorno de 0, que nunca será alcançado devido ao loop infinito.
    // Isso é apenas uma boa prática em programas com um ponto de entrada main().
    return 0;
}