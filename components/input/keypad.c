#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "input/keypad.h"

#define KEY_DEBOUNCE_TIME pdMS_TO_TICKS(20)

#define KEYPAD_ROW_1_GPIO 26
#define KEYPAD_ROW_2_GPIO 25

#define KEYPAD_COL_1_GPIO 33
#define KEYPAD_COL_2_GPIO 32

/*
 * Current implimentatian only spports 4 direction keys in 2x2 formate:
 * -------
 * | ^ v |
 * | < > |
 * -------
 * because of some hardware and technical reasons
 * the planned implimentation is:
 -----------
 |   ^     |
 | < O >   |
 |   v     |
 | 1 2 3 A |
 | 4 5 6 B |
 | 7 8 9 C |
 | 0 F E D |
 -----------
*/

/*
 * Connection for Matrix keypad:
 * 
 * allign switches in a form of grid
 *
 * connect one end af all swtichesd of row 1 to KEYPAD_ROW_1_GPIO
 * connect one end af all swtichesd of row 2 to KEYPAD_ROW_2_GPIO
 * 
 * connect another end of all switches of col 1 to KEYPAD_COL_1_GPIO
 * connect another end of all switches of col 2 to KEYPAD_COL_2_GPIO
 *
 */

const Key KEYMAP[2][2] = {
    { KEY_UP, KEY_DOWN },
    { KEY_LEFT, KEY_RIGHT },
};

const int KEYPAD_ROWS = 2, KEYPAD_COLS = 2;
const int KEYPAD_ROW_GPIOS[] = { KEYPAD_ROW_1_GPIO, KEYPAD_ROW_2_GPIO };
const int KEYPAD_COL_GPIOS[] = { KEYPAD_COL_1_GPIO, KEYPAD_COL_2_GPIO };

void keypad_init() {
    // Rows
    for (int i=0; i<KEYPAD_ROWS; i++) {
        gpio_reset_pin(KEYPAD_ROW_GPIOS[i]);
        gpio_set_direction(KEYPAD_ROW_GPIOS[i], GPIO_MODE_OUTPUT);
    }

    // Cols
    for (int i=0; i<KEYPAD_COLS; i++) {
        gpio_reset_pin(KEYPAD_COL_GPIOS[i]);
        gpio_set_direction(KEYPAD_COL_GPIOS[i], GPIO_MODE_INPUT);
        gpio_set_pull_mode(KEYPAD_COL_GPIOS[i], GPIO_PULLUP_ONLY);
    }
}

Key keypad_read() {
    for (int row = 0; row < KEYPAD_ROWS; row++) {

        for (int i=0; i<KEYPAD_ROWS; i++) {
            if (i==row) {
                gpio_set_level(KEYPAD_ROW_GPIOS[i], 1);
            } else {
                gpio_set_level(KEYPAD_ROW_GPIOS[i], 0);
            }
        }

        vTaskDelay(pdMS_TO_TICKS(5));

        for (int i=0; i<KEYPAD_COLS; i++) {
            if (gpio_get_level(KEYPAD_COL_GPIOS[i]) == 0) {
                vTaskDelay(KEY_DEBOUNCE_TIME);
                if (gpio_get_level(KEYPAD_COL_GPIOS[i]) == 0)
                    return KEYMAP[row][i];
            }
        }

    }
    return KEY_NONE;
}

