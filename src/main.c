#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "led_rgb.h"

#define PIN_RED    GPIO_NUM_26
#define PIN_GREEN  GPIO_NUM_27
#define PIN_BLUE   GPIO_NUM_14

void app_main(void) {
    // Inicializa o LED RGB nos pinos definidos
    led_rgb_init(PIN_RED, PIN_GREEN, PIN_BLUE);

    while (1) {
        printf("LED: Vermelho fixo\n");
        led_rgb_red();
        vTaskDelay(1000/portTICK_PERIOD_MS);

        printf("LED: Fade para Azul\n");
        fade_color_up(0, 0, LEDC_MAX_VALUE, 10000);
        vTaskDelay(500/portTICK_PERIOD_MS);

        printf("LED: Fade para Desligar\n");
        fade_color_down(0, 0, LEDC_MAX_VALUE, 10000);
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}
