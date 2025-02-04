#include <stdio.h>       
#include "pico/stdlib.h" 
#include "pico/time.h"   // Biblioteca para gerenciamento de temporizadores e alarmes.

// Definição dos pinos GPIO para os LEDs e botão
const uint LED_PING = 11;   // LED verde
const uint LED_PINR = 13;   // LED vermelho
const uint LED_PINB = 12;   // LED azul
const uint BUTTON_PIN = 5;  // Pino do botão

bool controle = false; // Variável de controle para impedir acionamentos simultâneos do botão
static volatile uint iterador = 0; // Variável que controla qual LED será apagado
absolute_time_t turn_off_time; // Variável para armazenar o tempo em que o LED deve ser desligado (não utilizada no código)

// Variável auxiliar usada para depuração
int a = 0;


 // A função é chamada automaticamente após um tempo de 3 segundos e desliga os LEDs um por um.
 
int64_t turn_off_callback(alarm_id_t id, void *user_data)
{
    switch (iterador)
    {
    case 0: // Primeiro estado: desliga o LED azul
        gpio_put(LED_PINB, false);
        iterador++;
        return (3000 * 1000); // Aguarda 3 segundos antes de chamar novamente
        break;
    case 1: // Segundo estado: desliga o LED vermelho
        gpio_put(LED_PINR, false);
        iterador++;
        return (3000 * 1000); // Aguarda 3 segundos antes de chamar novamente
        break;
    case 2: // Terceiro estado: desliga o LED verde e reseta o controle
        gpio_put(LED_PING, false);
        iterador = 0;   // Reinicia o ciclo
        controle = false; // Libera o botão para ser pressionado novamente
        return (0); // Encerra o temporizador
    default:
        break;
    }
}


 // Essa função é chamada automaticamente sempre que o botão for pressionado.
 // Ela verifica se o botão pode ser acionado e inicia a sequência de LEDs.
 
void gpio_irq_handler(uint gpio, uint32_t events)
{
    // Obtém o tempo atual em microssegundos
    uint32_t current_time = to_us_since_boot(get_absolute_time());
    static volatile uint32_t last_timeA = 0; // Armazena o tempo do último acionamento do botão

    // Implementação de debounce: verifica se passaram pelo menos 200 ms desde o último acionamento
    if (current_time - last_timeA > 200000)
    {
        // Se o botão foi pressionado e os LEDs estão desligados, inicia o processo
        if (gpio == BUTTON_PIN && controle == false)
        {
            last_timeA = current_time; // Atualiza o tempo do último acionamento
            gpio_put(LED_PINR, true);  // Liga o LED vermelho
            gpio_put(LED_PING, true);  // Liga o LED verde
            gpio_put(LED_PINB, true);  // Liga o LED azul
            controle = true;           // Impede novas chamadas enquanto o ciclo não termina

            // Inicia o temporizador para desligar os LEDs gradualmente
            add_alarm_in_ms(3000, turn_off_callback, NULL, false);

            printf("A: %d\n", a); // Mensagem de depuração para verificar bouncing
        }
    }
}

int main()
{
    // Inicializa a comunicação serial
    stdio_init_all();

    // Configuração dos pinos dos LEDs como saída
    gpio_init(LED_PINR);
    gpio_set_dir(LED_PINR, GPIO_OUT);
    gpio_init(LED_PING);
    gpio_set_dir(LED_PING, GPIO_OUT);
    gpio_init(LED_PINB);
    gpio_set_dir(LED_PINB, GPIO_OUT);

    // Configuração do pino do botão como entrada com pull-up interno ativado
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

    // Configuração da interrupção para detectar quando o botão é pressionado
    gpio_set_irq_enabled_with_callback(BUTTON_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

    // Loop infinito para manter o programa em execução
    while (true)
    {
        sleep_ms(2000); // Aguarda 2 segundos antes de repetir o loop
    }

    

   
    return 0;
}
