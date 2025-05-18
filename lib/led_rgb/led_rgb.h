#ifndef LED_RGB_H
#define LED_RGB_H

#include "stdint.h"
#include "driver/ledc.h"
#include "driver/gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LEDC_RESOLUTION     LEDC_TIMER_12_BIT
#define LEDC_MAX_VALUE      ((1 << LEDC_RESOLUTION) - 1)

/**
 * @brief Estrutura representando o estado dos canais RGB do LED.
 *        Cada canal varia de 0 a 4095, definindo a intensidade da cor.
 */
typedef struct {
    uint16_t red;   /**< Intensidade do canal vermelho (0 a 4095) >*/
    uint16_t green; /**< Intensidade do canal verde (0 a 4095) >*/
    uint16_t blue;  /**< Intensidade do canal azul (0 a 4095) >*/
} led_rgb_t;

/**
 * @brief Inicializa os pinos do LED RGB, configurando os canais de cor.
 * @param rPin Pino do canal vermelho.
 * @param gPin Pino do canal verde.
 * @param bPin Pino do canal azul.
 */
void led_rgb_init(gpio_num_t rPin, gpio_num_t gPin, gpio_num_t bPin);

/**
 * @brief Define os canais do LED RGB conforme a estrutura fornecida.
 * @param color Estrutura contendo os valores para cada canal RGB.
 */
void led_rgb_set(led_rgb_t color);

/**
 * @brief Executa uma transição suave de cor no LED RGB ao longo do tempo especificado.
 * @param r Intensidade do canal vermelho.
 * @param g Intensidade do canal verde.
 * @param b Intensidade do canal azul.
 * @param duration_ms Duração da transição em milissegundos.
 */
void fade_color_up(uint16_t r, uint16_t g, uint16_t b, int duration_ms);
void fade_color_down(uint16_t r, uint16_t g, uint16_t b, int duration_ms);
/**
 * @brief Cria uma estrutura de cor RGB com os valores fornecidos.
 * @param r Intensidade do canal vermelho.
 * @param g Intensidade do canal verde.
 * @param b Intensidade do canal azul.
 * @return Estrutura `led_rgb_t` representando a cor definida.
 */
led_rgb_t led_rgb_color(uint16_t r, uint16_t g, uint16_t b);

/**
 * @brief Retorna a estrutura de cor RGB correspondente ao vermelho puro.
 * @return Estrutura `led_rgb_t` com o canal vermelho ativo.
 */
led_rgb_t led_rgb_red();

/**
 * @brief Retorna a estrutura de cor RGB correspondente ao verde puro.
 * @return Estrutura `led_rgb_t` com o canal verde ativo.
 */
led_rgb_t led_rgb_green();

/**
 * @brief Retorna a estrutura de cor RGB correspondente ao azul puro.
 * @return Estrutura `led_rgb_t` com o canal azul ativo.
 */
led_rgb_t led_rgb_blue();

/**
 * @brief Retorna a estrutura de cor RGB correspondente ao branco.
 *        Todos os canais são configurados no valor máximo.
 * @return Estrutura `led_rgb_t` com os três canais ativos.
 */
led_rgb_t led_rgb_white();

/**
 * @brief Retorna a estrutura de cor RGB correspondente ao estado desligado.
 *        Todos os canais são configurados no valor mínimo.
 * @return Estrutura `led_rgb_t` com os três canais desativados.
 */
led_rgb_t led_rgb_off();

#ifdef __cplusplus
}
#endif

#endif
