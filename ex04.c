// Read keys from keypad.

#include <stdio.h>
#include "pico/stdlib.h"

#define R1 13
#define R2 12
#define R3 11
#define R4 10

#define C1 5
#define C2 4
#define C3 3
#define C4 2

#define ROWS 4
#define COLUMNS 4

const int ROW_PINS[ROWS] = {13, 12, 11, 10};
const int COLUMN_PINS[COLUMNS] = {5, 4, 3, 2};
const char KEYS[ROWS][COLUMNS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'},
};

void initialize_keypad()
{
    for (int i = 0; i < ROWS; i++)
    {
        gpio_init(ROW_PINS[i]);
        gpio_set_dir(ROW_PINS[i], GPIO_OUT);
        gpio_put(ROW_PINS[i], 0);
    }
    for (int i = 0; i < COLUMNS; i++)
    {
        gpio_init(COLUMN_PINS[i]);
        gpio_set_dir(COLUMN_PINS[i], GPIO_IN);
        gpio_pull_down(COLUMN_PINS[i]);
    }
}

char read_key()
{
    for (int row = 0; row < ROWS; row++)
    {
        gpio_put(ROW_PINS[row], 1);

        for (int column = 0; column < COLUMNS; column++)
        {
            if (gpio_get(COLUMN_PINS[column]))
            {
                gpio_put(ROW_PINS[row], 0);
                return KEYS[row][column];
            }
        }
        gpio_put(ROW_PINS[row], 0);
    }
    return '\0';
}

int main()
{
    stdio_init_all();
    initialize_keypad();

    while (1)
    {
        char key = read_key();

        if (key != '\0')
        {
            printf("Pressed key: %c\n", key);
        }
        sleep_ms(100);
    }
    return 0;
}
