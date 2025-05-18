#include "led_rgb.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include <stdbool.h>


#define LEDC_TIMER          LEDC_TIMER_0
#define LEDC_MODE           LEDC_LOW_SPEED_MODE
#define LEDC_FREQ_HZ        5000


#define LEDC_CHANNEL_RED    LEDC_CHANNEL_0
#define LEDC_CHANNEL_GREEN  LEDC_CHANNEL_1
#define LEDC_CHANNEL_BLUE   LEDC_CHANNEL_2

static bool is_initialized = false;

void led_rgb_init(gpio_num_t rPin, gpio_num_t gPin, gpio_num_t bPin) {
    // Configura timer do LEDC
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_MODE,
        .timer_num        = LEDC_TIMER,
        .duty_resolution  = LEDC_RESOLUTION,
        .freq_hz          = LEDC_FREQ_HZ,
    };
    if (ledc_timer_config(&ledc_timer) != ESP_OK) {
        return;
    }

    // Configura canal RED
    ledc_channel_config_t ledc_channel_red = {
        .gpio_num       = rPin,
        .speed_mode     = LEDC_MODE,
        .channel        = LEDC_CHANNEL_RED,
        .intr_type      = LEDC_INTR_DISABLE,
        .timer_sel      = LEDC_TIMER,
        .duty           = 0,
        .hpoint         = 0,
    };
    ledc_channel_config(&ledc_channel_red);

    // Configura canal GREEN
    ledc_channel_config_t ledc_channel_green = {
        .gpio_num       = gPin,
        .speed_mode     = LEDC_MODE,
        .channel        = LEDC_CHANNEL_GREEN,
        .intr_type      = LEDC_INTR_DISABLE,
        .timer_sel      = LEDC_TIMER,
        .duty           = 0,
        .hpoint         = 0,
    };
    ledc_channel_config(&ledc_channel_green);

    // Configura canal BLUE
    ledc_channel_config_t ledc_channel_blue = {
        .gpio_num       = bPin,
        .speed_mode     = LEDC_MODE,
        .channel        = LEDC_CHANNEL_BLUE,
        .intr_type      = LEDC_INTR_DISABLE,
        .timer_sel      = LEDC_TIMER,
        .duty           = 0,
        .hpoint         = 0,
    };
    ledc_channel_config(&ledc_channel_blue);

    is_initialized = true;
}

void led_rgb_set(led_rgb_t color) {
    if (!is_initialized) return;
    
    ledc_set_duty(LEDC_MODE, LEDC_CHANNEL_RED, color.red);
    ledc_update_duty(LEDC_MODE, LEDC_CHANNEL_RED);

    ledc_set_duty(LEDC_MODE, LEDC_CHANNEL_GREEN, color.green);
    ledc_update_duty(LEDC_MODE, LEDC_CHANNEL_GREEN);

    ledc_set_duty(LEDC_MODE, LEDC_CHANNEL_BLUE, color.blue);
    ledc_update_duty(LEDC_MODE, LEDC_CHANNEL_BLUE);
}


led_rgb_t led_rgb_color(uint16_t r, uint16_t g, uint16_t b) {
    if (r > LEDC_MAX_VALUE) r = LEDC_MAX_VALUE;
    if (g > LEDC_MAX_VALUE) g = LEDC_MAX_VALUE;
    if (b > LEDC_MAX_VALUE) b = LEDC_MAX_VALUE;

    led_rgb_t rgb_led = {r, g, b};
    led_rgb_set(rgb_led);
    return rgb_led;
}

void fade_color_up(uint16_t r, uint16_t g, uint16_t b, int duration_ms) {
    const int step = 5;
    int steps = LEDC_MAX_VALUE / step;
    int delay_per_step = duration_ms / steps;

    for (int i = 0; i <= LEDC_MAX_VALUE; i += step) {
        led_rgb_set(led_rgb_color((r * i) / LEDC_MAX_VALUE,
                                  (g * i) / LEDC_MAX_VALUE,
                                  (b * i) / LEDC_MAX_VALUE));
        vTaskDelay(delay_per_step/portTICK_PERIOD_MS);
    }
}

void fade_color_down(uint16_t r, uint16_t g, uint16_t b, int duration_ms) {
    const int step = 5;
    int steps = LEDC_MAX_VALUE / step;
    int delay_per_step = duration_ms / steps;

    for (int i = LEDC_MAX_VALUE; i >= 0; i -= step) {
        led_rgb_set(led_rgb_color((r * i) / LEDC_MAX_VALUE,
                                  (g * i) / LEDC_MAX_VALUE,
                                  (b * i) / LEDC_MAX_VALUE));
        vTaskDelay(delay_per_step/portTICK_PERIOD_MS);
    }
}


led_rgb_t led_rgb_red()    { return led_rgb_color(LEDC_MAX_VALUE, 0, 0); }
led_rgb_t led_rgb_green()  { return led_rgb_color(0, LEDC_MAX_VALUE, 0); }
led_rgb_t led_rgb_blue()   { return led_rgb_color(0, 0, LEDC_MAX_VALUE); }
led_rgb_t led_rgb_white()  { return led_rgb_color(LEDC_MAX_VALUE, LEDC_MAX_VALUE, LEDC_MAX_VALUE); }
led_rgb_t led_rgb_off()    { return led_rgb_color(0, 0, 0); }
