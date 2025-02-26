#include "pico/stdlib.h"
#include <stdio.h>

#define BUZZER_PIN_1 21   // Pino para o primeiro buzzer
#define BUZZER_PIN_2 10   // Pino para o segundo buzzer
#define BUTTON_PIN 5      // Pino para o botão
#define LED_RED_PIN 13    // Pino para o LED vermelho
#define LED_GREEN_PIN 11  // Pino para o LED verde

const int TEMPO_ESPERA = 10000;

int main() {
    // Inicializa os pinos dos buzzers como saída
    gpio_init(BUZZER_PIN_1);
    gpio_set_dir(BUZZER_PIN_1, GPIO_OUT);
    
    gpio_init(BUZZER_PIN_2);
    gpio_set_dir(BUZZER_PIN_2, GPIO_OUT);

    // Inicializa os pinos dos LEDs
    gpio_init(LED_RED_PIN);
    gpio_set_dir(LED_RED_PIN, GPIO_OUT);

    gpio_init(LED_GREEN_PIN);
    gpio_set_dir(LED_GREEN_PIN, GPIO_OUT);

    // Inicializa o pino do botão como entrada com pull-up
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);  // Ativa o resistor pull-up para garantir um estado estável

    while (1) {
        // Fase 1: LED vermelho ligado
        gpio_put(LED_RED_PIN, 1);  // Liga o LED vermelho
        gpio_put(LED_GREEN_PIN, 0); // Desliga o LED verde
        gpio_put(BUZZER_PIN_1, 0);  // Desliga o buzzer 1
        gpio_put(BUZZER_PIN_2, 0);  // Desliga o buzzer 2
        
        // Espera 10 segundos
        sleep_ms(TEMPO_ESPERA);

        // Fase 2: Desliga o LED vermelho, liga o LED verde e os buzzers
        gpio_put(LED_RED_PIN, 0);   // Desliga o LED vermelho
        gpio_put(LED_GREEN_PIN, 1); // Liga o LED verde
        gpio_put(BUZZER_PIN_1, 1);  // Liga o buzzer 1
        gpio_put(BUZZER_PIN_2, 1);  // Liga o buzzer 2

        // Aguarda o botão ser pressionado para voltar ao ciclo
        while (gpio_get(BUTTON_PIN) == 1) {
            // Espera até o botão ser pressionado
        }

        // Espera até o botão ser liberado (evita múltiplos acionamentos)
        while (gpio_get(BUTTON_PIN) == 0) {
            // Espera o botão ser solto
        }

        // O ciclo reinicia, com o LED vermelho ligado novamente
    }

    return 0;
}
