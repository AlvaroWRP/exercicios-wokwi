// Show counter using a single display.

#include "pico/stdlib.h"

const int PINS[] = {0, 1, 2, 3, 4, 5, 6};
const int DIGITS[10][7] = {
    {1, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 0, 0, 0, 0},
    {1, 1, 0, 1, 1, 0, 1},
    {1, 1, 1, 1, 0, 0, 1},
    {0, 1, 1, 0, 0, 1, 1},
    {1, 0, 1, 1, 0, 1, 1},
    {1, 0, 1, 1, 1, 1, 1},
    {1, 1, 1, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 0, 0, 1, 1},
};

void display_digit(int digit)
{
    for (int i = 0; i < 7; i++)
    {
        gpio_put(PINS[i], DIGITS[digit][i]);
    }
}

int main()
{
    for (int i = 0; i < 7; i++)
    {
        gpio_init(PINS[i]);
        gpio_set_dir(PINS[i], GPIO_OUT);
    }
    int digit = 0;

    while (1)
    {
        display_digit(digit);
        sleep_ms(1000);
        digit++;

        if (digit > 9)
        {
            digit = 0;
        }
    }
    return 0;
}
