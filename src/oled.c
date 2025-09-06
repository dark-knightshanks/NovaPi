#include "printf.h"
#include <stdint.h>
#include "peripherals/i2c.h"

#define OLED_I2C_ADDR 0x3C   // SSD1306 default address

// Send one command
void oled_command(uint8_t cmd) {
    uint8_t buf[2];  // Changed from uint32_t to uint8_t
    buf[0] = 0x00;   // Control byte: Co=0, D/C#=0 → command
    buf[1] = cmd;
    i2c_write(OLED_I2C_ADDR, buf, 2);  // Added missing I2C write
}

// Send one data byte
void oled_data(uint8_t data) {
    uint8_t buf[2];  // Changed from uint32_t to uint8_t
    buf[0] = 0x40;   // Control byte: Co=0, D/C#=1 → data
    buf[1] = data;
    i2c_write(OLED_I2C_ADDR, buf, 2);  // Added missing I2C write
}
// OLED initialization
void oled_init(void) {
    delay(10000);

    oled_command(0xAE); // Display OFF
    oled_command(0xD5); // Set Display Clock Divide Ratio
    oled_command(0x80); // Default ratio
    oled_command(0xA8); // Set Multiplex Ratio
    oled_command(0x3F); // 64 lines
    oled_command(0xD3); // Set Display Offset
    oled_command(0x00); // No offset
    oled_command(0x40); // Set Display Start Line
    oled_command(0x8D); // Charge Pump Setting
    oled_command(0x14); // Enable Charge Pump
    oled_command(0x20); // Set Memory Addressing Mode
    oled_command(0x00); // Horizontal Addressing Mode
    oled_command(0xA1); // Set Segment Re-map
    oled_command(0xC8); // Set COM Output Scan Direction
    oled_command(0xDA); // Set COM Pins Hardware Configuration
    oled_command(0x12); // Alternative COM pin config
    oled_command(0x81); // Set Contrast Control
    oled_command(0x7F); // Medium contrast
    oled_command(0xD9); // Set Pre-charge Period
    oled_command(0xF1); // Default pre-charge
    oled_command(0xDB); // Set VCOMH Deselect Level
    oled_command(0x40); // Default VCOMH
    oled_command(0xA4); // Entire Display ON (use RAM content)
    oled_command(0xA6); // Set Normal Display (not inverted)
    oled_command(0xAF); // Display ON

    delay(10000);
    printf("OLED initialized\n");
}

// Clear OLED screen
void oled_clear(void) {
    // Set column address (0 to 127)
    oled_command(0x21);
    oled_command(0x00);
    oled_command(0x7F);

    // Set page address (0 to 7)
    oled_command(0x22);
    oled_command(0x00);
    oled_command(0x07);

    // Clear all pixels
    for (int i = 0; i < 1024; i++) { // 128x64 = 8192 bits = 1024 bytes
        oled_data(0x00);
    }

    printf("OLED cleared\n");
}
