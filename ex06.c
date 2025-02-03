// Digital safe system.

#include <stdio.h>
#include <stdbool.h>
#include "pico/stdlib.h"

#define RGB_LED_RED_PIN 27
#define RGB_LED_GREEN_PIN 26
#define RGB_LED_BLUE_PIN 22

#define ROWS_QUANTITY 4
#define COLUMNS_QUANTITY 4

const int ROWS_PINS[ROWS_QUANTITY] = {8, 9, 10, 11};         // R1, R2, R3, R4
const int COLUMNS_PINS[COLUMNS_QUANTITY] = {12, 13, 14, 15}; // C1, C2, C3, C4
const char KEYPAD_KEYS[ROWS_QUANTITY][COLUMNS_QUANTITY] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'},
};

const int DISPLAYS_LETTERS_PINS[] = {0, 1, 2, 3, 4, 5, 6}; // A, B, C, D, E, F, G
const int DISPLAYS_PINS[] = {21, 20, 19, 18};              // DIG1, DIG2, DIG3, DIG4
const int DIGITS[10][7] = {
    {1, 1, 1, 1, 1, 1, 0}, // 0
    {0, 1, 1, 0, 0, 0, 0}, // 1
    {1, 1, 0, 1, 1, 0, 1}, // 2
    {1, 1, 1, 1, 0, 0, 1}, // 3
    {0, 1, 1, 0, 0, 1, 1}, // 4
    {1, 0, 1, 1, 0, 1, 1}, // 5
    {1, 0, 1, 1, 1, 1, 1}, // 6
    {1, 1, 1, 0, 0, 0, 0}, // 7
    {1, 1, 1, 1, 1, 1, 1}, // 8
    {1, 1, 1, 0, 0, 1, 1}, // 9
};

void set_up_rgb_led()
{
    gpio_init(RGB_LED_RED_PIN);
    gpio_set_dir(RGB_LED_RED_PIN, GPIO_OUT);
    gpio_put(RGB_LED_RED_PIN, 0);

    gpio_init(RGB_LED_GREEN_PIN);
    gpio_set_dir(RGB_LED_GREEN_PIN, GPIO_OUT);
    gpio_put(RGB_LED_GREEN_PIN, 0);

    gpio_init(RGB_LED_BLUE_PIN);
    gpio_set_dir(RGB_LED_BLUE_PIN, GPIO_OUT);
    gpio_put(RGB_LED_BLUE_PIN, 0);
}

void set_up_keypad()
{
    for (int i = 0; i < ROWS_QUANTITY; i++)
    {
        gpio_init(ROWS_PINS[i]);
        gpio_set_dir(ROWS_PINS[i], GPIO_OUT);
        gpio_put(ROWS_PINS[i], 0);
    }
    for (int i = 0; i < COLUMNS_QUANTITY; i++)
    {
        gpio_init(COLUMNS_PINS[i]);
        gpio_set_dir(COLUMNS_PINS[i], GPIO_IN);
        gpio_pull_down(COLUMNS_PINS[i]);
    }
}

char read_keypad_key()
{
    for (int row = 0; row < ROWS_QUANTITY; row++)
    {
        gpio_put(ROWS_PINS[row], 1);

        for (int column = 0; column < COLUMNS_QUANTITY; column++)
        {
            if (gpio_get(COLUMNS_PINS[column]))
            {
                gpio_put(ROWS_PINS[row], 0);
                sleep_ms(50);
                return KEYPAD_KEYS[row][column];
            }
        }
        gpio_put(ROWS_PINS[row], 0);
    }
    return 'N';
}

void set_up_displays()
{
    for (int i = 0; i < 7; i++)
    {
        gpio_init(DISPLAYS_LETTERS_PINS[i]);
        gpio_set_dir(DISPLAYS_LETTERS_PINS[i], GPIO_OUT);
    }
    for (int i = 0; i < 4; i++)
    {
        gpio_init(DISPLAYS_PINS[i]);
        gpio_set_dir(DISPLAYS_PINS[i], GPIO_OUT);
        gpio_put(DISPLAYS_PINS[i], 1);
    }
}

void show_digit(int display_index, int digit)
{
    for (int i = 0; i < 4; i++)
    {
        gpio_put(DISPLAYS_PINS[i], 1);
    }
    for (int i = 0; i < 7; i++)
    {
        gpio_put(DISPLAYS_LETTERS_PINS[i], DIGITS[digit][i]);
    }
    gpio_put(DISPLAYS_PINS[display_index], 0);
}

bool compare_passwords(int user_password[], int locker_password[])
{
    for (int i = 0; i < 4; i++)
    {
        if (user_password[i] != locker_password[i])
        {
            return false;
        }
    }
    return true;
}

int main()
{
    stdio_init_all();

    set_up_rgb_led();
    set_up_keypad();
    set_up_displays();

    int tries = 0;
    int display_index = 0;
    int locker_password[] = {1, 2, 3, 4};
    int user_password[4];
    int displays_digits[] = {-1, -1, -1, -1};

    while (true)
    {
        if (tries >= 3)
        {
            tries = 0;

            gpio_put(RGB_LED_RED_PIN, 1);
            sleep_ms(5000);
            gpio_put(RGB_LED_RED_PIN, 0);
        }
        char keypad_key = read_keypad_key();
        bool are_passwords_equal = compare_passwords(user_password, locker_password);

        if (keypad_key == '#')
        {
            if (are_passwords_equal)
            {
                tries = 0;

                gpio_put(RGB_LED_GREEN_PIN, 1);
                sleep_ms(2000);
                gpio_put(RGB_LED_GREEN_PIN, 0);
            }
            else
            {
                tries++;

                gpio_put(RGB_LED_RED_PIN, 1);
                sleep_ms(2000);
                gpio_put(RGB_LED_RED_PIN, 0);
            }
            display_index = 0;

            for (int i = 0; i < 4; i++)
            {
                displays_digits[i] = -1;
            }
        }
        if (keypad_key >= '0' && keypad_key <= '9')
        {
            int digit = keypad_key - '0';

            if (display_index < 4)
            {
                user_password[display_index] = digit;
                displays_digits[display_index] = digit;
                display_index++;
            }
        }
        for (int i = 0; i < 4; i++)
        {
            if (displays_digits[i] != -1)
            {
                show_digit(i, displays_digits[i]);
                sleep_ms(5);
            }
        }
        sleep_ms(100);
    }
    return 0;
}
