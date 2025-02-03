// Disable traffic light using button.

#include <stdbool.h>
#include "pico/stdlib.h"

#define GREEN 15
#define YELLOW 14
#define RED 13
#define BUTTON 12

bool is_loop_active = false;

void run_loop()
{
    gpio_put(GREEN, 1);
    sleep_ms(5000);
    gpio_put(GREEN, 0);

    gpio_put(YELLOW, 1);
    sleep_ms(2500);
    gpio_put(YELLOW, 0);

    gpio_put(RED, 1);
    sleep_ms(5000);
    gpio_put(RED, 0);
}

void disabled_state()
{
    gpio_put(YELLOW, 1);
    sleep_ms(500);
    gpio_put(YELLOW, 0);
    sleep_ms(500);
}

int main()
{
    gpio_init(GREEN);
    gpio_set_dir(GREEN, GPIO_OUT);

    gpio_init(YELLOW);
    gpio_set_dir(YELLOW, GPIO_OUT);

    gpio_init(RED);
    gpio_set_dir(RED, GPIO_OUT);

    gpio_init(BUTTON);
    gpio_set_dir(BUTTON, GPIO_IN);
    gpio_pull_up(BUTTON);

    while (true)
    {
        if (!is_loop_active)
        {
            disabled_state();
        }
        if (is_loop_active)
        {
            run_loop();
        }
        if (!gpio_get(BUTTON))
        {
            is_loop_active = !is_loop_active;
        }
        sleep_ms(200);
    }
    return 0;
}
