#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "led_rgb.h"

#define PIN_RED    GPIO_NUM_26
#define PIN_GREEN  GPIO_NUM_27
#define PIN_BLUE   GPIO_NUM_14

#define TAG "LED_RGB"

void app_main(void) {
    
    // Inicializa o LED RGB nos pinos definidos
    led_rgb_init(PIN_RED, PIN_GREEN, PIN_BLUE);

    while (1) {
        ESP_LOGI(TAG, "LED: Vermelho fixo");
        led_rgb_red();
        vTaskDelay(pdMS_TO_TICKS(1000));

        ESP_LOGI(TAG, "LED: Verde fixo");
        led_rgb_green();
        vTaskDelay(pdMS_TO_TICKS(1000));

        ESP_LOGI(TAG, "LED: Azul fixo");
        led_rgb_blue();
        vTaskDelay(pdMS_TO_TICKS(1000));
        
        ESP_LOGI(TAG, "LED: Branco fixo");
        led_rgb_white();
        vTaskDelay(pdMS_TO_TICKS(1000));
        led_rgb_set(led_rgb_white());
        vTaskDelay(pdMS_TO_TICKS(500));

        ESP_LOGI(TAG, "LED: Desligado");
        led_rgb_off();
        vTaskDelay(pdMS_TO_TICKS(500));

        ESP_LOGI(TAG, "LED: Fade in Amarelo (10s)");
        fade_color_up(4095, 4095, 0, 5000);
        vTaskDelay(pdMS_TO_TICKS(1000));

        ESP_LOGI(TAG, "LED: Fade out Amarelo (10s)");
        fade_color_down(4095, 4095, 0, 5000);
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}
