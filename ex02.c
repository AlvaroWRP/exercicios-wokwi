// Control multiple LEDs using two buttons.

#include <stdio.h>
#include "pico/stdlib.h"

#define RED_LED_PIN 15
#define GREEN_LED_PIN 14
#define BLUE_LED_PIN 13

#define BUTTON_A_PIN 3
#define BUTTON_B_PIN 4

void set_leds_state(bool red, bool green, bool blue)
{
    gpio_put(RED_LED_PIN, red);
    gpio_put(GREEN_LED_PIN, green);
    gpio_put(BLUE_LED_PIN, blue);
}

int main()
{
    stdio_init_all();

    gpio_init(RED_LED_PIN);
    gpio_set_dir(RED_LED_PIN, GPIO_OUT);

    gpio_init(GREEN_LED_PIN);
    gpio_set_dir(GREEN_LED_PIN, GPIO_OUT);

    gpio_init(BLUE_LED_PIN);
    gpio_set_dir(BLUE_LED_PIN, GPIO_OUT);

    gpio_init(BUTTON_A_PIN);
    gpio_set_dir(BUTTON_A_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_A_PIN);

    gpio_init(BUTTON_B_PIN);
    gpio_set_dir(BUTTON_B_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_B_PIN);

    while (1)
    {
        printf("Button A: %d, Button B: %d\n", gpio_get(BUTTON_A_PIN), gpio_get(BUTTON_B_PIN));

        if (!gpio_get(BUTTON_A_PIN) && !gpio_get(BUTTON_B_PIN))
        {
            set_leds_state(1, 1, 1);
        }
        else if (!gpio_get(BUTTON_A_PIN))
        {
            set_leds_state(1, 0, 0);
        }
        else if (!gpio_get(BUTTON_B_PIN))
        {
            set_leds_state(0, 1, 0);
        }
        else
        {
            set_leds_state(0, 0, 1);
        }
        sleep_ms(100);
    }
    return 0;
}
