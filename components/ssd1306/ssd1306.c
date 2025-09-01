#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2c.h"
#include "ssd1306/ssd1306.h"

uint8_t ssd1306_buffer[SSD1306_HEIGHT * SSD1306_WIDTH / 8];

void i2c_master_init() {
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ
    };
    i2c_param_config(I2C_MASTER_NUM, &conf);
    i2c_driver_install(
        I2C_MASTER_NUM,
        conf.mode,
        I2C_MASTER_RX_BUF_DISABLE,
        I2C_MASTER_TX_BUF_DISABLE,
        0
    );
}

void ssd1306_init() {
    i2c_master_init();
    const uint8_t init_seq[] = {
        0xAE, // display off
        0xD5, 0x80, // set Dispaly Clock Divide Ratio
        //0xA8, SSD1306_HEIGHT - 1,  // set multiplexer height
        // 0xD3, 0x00, // set Display off set, 0 in this case
        0x40, // Set Display Start Line
        0x8D, 0x14, // Enable Charge Pump ragulator 
        0x20, 0x00, // Set Memory addresing mode, Horizontal in thin Case
        0xA1, // Set sagement re-map
        0xC8, // Set COM output scan diraction
        0xDA, (SSD1306_HEIGHT == 64 ? 0x12 : 0x02), // Set COM pins hardware configration, for 64 in this case
        0x81, 0x22, // Set Contrast Control
        // 0xD9, 0xF1, // Set Pre-Charge Period
        // 0xDB, 0x40, // Set VCOMH Deselect Level, default value in this case 
        0xA4, // Entile display ON
        0xA6, // Normal Display, use 0xA7 for inverse
        0xAF  // Display On, 0xAE for display Off
    };
    for (int i = 0; i < sizeof(init_seq); i++) {
        ssd1306_write_cmd(init_seq[i]);
    }
}

void ssd1306_deinit() {
    ssd1306_write_cmd(0xAE);
    i2c_driver_delete(I2C_MASTER_NUM);
}

void ssd1306_write_cmd(uint8_t cmd) {
    i2c_cmd_handle_t handle = i2c_cmd_link_create();
    i2c_master_start(handle);
    i2c_master_write_byte(handle, (SSD1306_ADDR << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(handle, SSD1306_COMMAND, true);
    i2c_master_write_byte(handle, cmd, true);
    i2c_master_stop(handle);
    i2c_master_cmd_begin(I2C_MASTER_NUM, handle, pdMS_TO_TICKS(1000));
    i2c_cmd_link_delete(handle);
}

void ssd1306_draw_pixel(int x, int y, bool on) {
    if (x < 0 || x >= SSD1306_WIDTH || y < 0 || y >= SSD1306_HEIGHT) return;
    int index = x + (y / 8) * SSD1306_WIDTH;
    if (on)
        ssd1306_buffer[index] |= 1 << (y%8) ;
    else
        ssd1306_buffer[index] &= ~(1 << (y%8)); 
}

void ssd1306_clear() {
    for (int _=0; _<SSD1306_WIDTH*SSD1306_HEIGHT/8; _++)
        ssd1306_buffer[_] = 0x00;
}

void ssd1306_fill() {
    for (int _=0; _<SSD1306_WIDTH*SSD1306_HEIGHT/8; _++)
        ssd1306_buffer[_] = 0xFF;
}

void ssd1306_update_screen(){
    for (int page = 0; page < SSD1306_HEIGHT / 8; page++) {
        ssd1306_write_cmd(0xB0 + page);        // set page address
        ssd1306_write_cmd(0x00);               // set lower column
        ssd1306_write_cmd(0x10);               // set higher column

        i2c_cmd_handle_t handle = i2c_cmd_link_create();
        i2c_master_start(handle);
        i2c_master_write_byte(handle, (SSD1306_ADDR << 1) | I2C_MASTER_WRITE, true);
        i2c_master_write_byte(handle, SSD1306_DATA, true);
        i2c_master_write(handle, &ssd1306_buffer[page * SSD1306_WIDTH], SSD1306_WIDTH, true);
        i2c_master_stop(handle);
        i2c_master_cmd_begin(I2C_MASTER_NUM, handle, pdMS_TO_TICKS(1000));
        i2c_cmd_link_delete(handle);
    }
}

