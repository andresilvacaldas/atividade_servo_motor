#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "stdio.h"

// Definição do pino onde o servomotor está conectado
#define SERVO_PIN 12

// Definição da frequência do PWM (50Hz) e do período correspondente (20ms)
#define PWM_FREQUENCY 50  
#define PWM_PERIOD 20000   

// Função para ajustar o ângulo do servomotor através do PWM
void ajustar_servo(uint slice, uint canal, uint largura_pulso) {
    pwm_set_chan_level(slice, canal, largura_pulso);
}

int main() {
    // Inicializa a comunicação serial
    stdio_init_all();

    // Configura o pino do servomotor como saída PWM
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);
    uint slice_pwm = pwm_gpio_to_slice_num(SERVO_PIN);
    uint canal_pwm = pwm_gpio_to_channel(SERVO_PIN);

    // Configura o período do PWM e a taxa de clock
    pwm_set_wrap(slice_pwm, PWM_PERIOD);
    pwm_set_clkdiv(slice_pwm, 125.0);
    pwm_set_enabled(slice_pwm, true);

    // Movimenta o servo para 180 graus e aguarda 5 segundos
    printf("Posicionando em 180 graus...\n");
    ajustar_servo(slice_pwm, canal_pwm, 2400);
    sleep_ms(5000);

    // Movimenta o servo para 90 graus e aguarda 5 segundos
    printf("Posicionando em 90 graus...\n");
    ajustar_servo(slice_pwm, canal_pwm, 1470);
    sleep_ms(5000);

    // Movimenta o servo para 0 graus e aguarda 5 segundos
    printf("Posicionando em 0 graus...\n");
    ajustar_servo(slice_pwm, canal_pwm, 500);
    sleep_ms(5000);
    
    // Inicia o movimento contínuo suave entre 0° e 180°
    printf("Iniciando movimento cíclico entre 0° e 180°...\n");

    while (true) {
        // Movimento do servo de 0° para 180°
        for (uint32_t pulso = 500; pulso <= 2400; pulso += 5) {
            ajustar_servo(slice_pwm, canal_pwm, pulso);
            sleep_ms(10);
        }
        // Movimento do servo de 180° para 0°
        for (uint32_t pulso = 2400; pulso >= 500; pulso -= 5) {
            ajustar_servo(slice_pwm, canal_pwm, pulso);
            sleep_ms(10);
        }
    }
}