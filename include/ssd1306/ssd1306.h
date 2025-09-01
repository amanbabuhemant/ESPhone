#ifndef SSD1306_H
#define SSD1306_H

#include <stdint.h>
#include <stdbool.h>

#define I2C_MASTER_NUM              I2C_NUM_0
#define I2C_MASTER_SDA_IO           21
#define I2C_MASTER_SCL_IO           22
#define I2C_MASTER_FREQ_HZ          100000
#define I2C_MASTER_TX_BUF_DISABLE   0
#define I2C_MASTER_RX_BUF_DISABLE   0

#define SSD1306_WIDTH   128
#define SSD1306_HEIGHT  64
#define SSD1306_ADDR    0x3C
#define SSD1306_COMMAND 0x00
#define SSD1306_DATA    0x40

extern uint8_t ssd1306_buffer[SSD1306_HEIGHT * SSD1306_WIDTH / 8];

void i2c_master_init();

void ssd1306_init();

void ssd1306_deinit();

void ssd1306_write_cmd(uint8_t);

void ssd1306_draw_pixel(int, int, bool);

void ssd1306_clear();

void ssd1306_fill();

void ssd1306_update_screen();

#endif
