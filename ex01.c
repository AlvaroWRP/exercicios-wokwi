// Turn LED on using a button.

#include "pico/stdlib.h"

#define LED_PIN 11
#define BUTTON_PIN 5

int main()
{
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

    while (1)
    {
        if (!gpio_get(BUTTON_PIN))
        {
            gpio_put(LED_PIN, 1);
        }
        else
        {
            gpio_put(LED_PIN, 0);
        }
        sleep_ms(100);
    }
}
