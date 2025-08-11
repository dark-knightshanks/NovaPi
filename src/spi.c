#include "printf.h"
#include "peripherals/spi.h"
#include <stdint.h>

// Font array for "HELLO WORLD"
const uint8_t font5x8[][5] = {
    {0x7E, 0x11, 0x11, 0x11, 0x7E}, // H
    {0x7F, 0x49, 0x49, 0x49, 0x36}, // E
    {0x7F, 0x40, 0x40, 0x40, 0x40}, // L
    {0x7F, 0x40, 0x40, 0x40, 0x40}, // L
    {0x3E, 0x41, 0x41, 0x41, 0x3E}, // O
    {0x00, 0x00, 0x00, 0x00, 0x00}, // Space
    {0x1F, 0x20, 0x40, 0x20, 0x1F}, // W
    {0x3E, 0x41, 0x41, 0x41, 0x3E}, // O
    {0x7F, 0x09, 0x19, 0x29, 0x46}, // R
    {0x7F, 0x40, 0x40, 0x40, 0x40}, // L
    {0x7F, 0x02, 0x04, 0x08, 0x7F}, // D
};

// CORRECTED: SPI initialization
void spi_init(void) {
    spi_gpio(); // Configure GPIO pins for SPI
    
    // Set clock divider
    CLK = 1024;
    
    // Clear any pending transfers first
    CS &= ~(1 << 7); // Clear TA (Transfer Active)
    
    // Configure SPI Mode 0: CPOL=0, CPHA=0
    CS &= ~(1 << 3); // Clear CPOL
    CS &= ~(1 << 2); // Clear CPHA
    CS &= ~(3 << 0); // Clear CS bits (use CS0)
    
    // Clear FIFOs after configuration
    CS |= (3 << 4); // Clear TX and RX FIFOs
    
    // Small delay for FIFO clearing
    for(volatile int i = 0; i < 10; i++);
    
    printf("SPI initialized\n");
}

// CORRECTED: SPI write function - Fixed timing issues
void spi_write(uint8_t data) {
    // Start transfer FIRST
    CS |= (1 << 7); // Set TA = 1
    
    // Wait for TX FIFO to have space
    while (!(CS & (1 << 18))); // Wait for TXD bit
    
    // Load data into FIFO
    FIFO = data;
    
    // Wait for transfer to complete
    while (!(CS & (1 << 16))); // Wait for DONE bit
    
    // Small delay before clearing TA
    for(volatile int i = 0; i < 5; i++);
    
    // Clear TA to end transfer
    CS &= ~(1 << 7);
}

// Print "HELLO WORLD" on OLED
void oled_print_hello_world(void) {
    // Set position for "HELLO WORLD" (start at column 20, page 3)
    oled_command(0x21); // Set Column Address
    oled_command(20);   // Start column
    oled_command(127);  // End column
    
    oled_command(0x22); // Set Page Address
    oled_command(3);    // Start page (middle of screen)
    oled_command(3);    // End page
    
    // Print "HELLO WORLD"
    for (int char_index = 0; char_index < 11; char_index++) {
        // Print each character (5 columns)
        for (int col = 0; col < 5; col++) {
            oled_data(font5x8[char_index][col]);
        }
        // Add space between characters
        oled_data(0x00);
    }
    
    printf("Hello World displayed on OLED\n");
}

// Simple SPI test pattern for logic analyzer
void test_spi_pattern(void) {
    printf("Testing SPI with simple pattern\n");
    
    spi_init();
    
    // Send alternating pattern to verify SPI is working
    for (int i = 0; i < 5; i++) {
        printf("Sending 0xAA\n");
        spi_write(0xAA); // 10101010 pattern
        delay(10000);
        
        printf("Sending 0x55\n");
        spi_write(0x55); // 01010101 pattern
        delay(10000);
    }
    
    printf("SPI pattern test complete\n");
}

// Main OLED test function
void test_oled_hello_world(void) {
    printf("Starting OLED Hello World test\n");
    
    // Initialize SPI
    spi_init();
    
    // Initialize OLED
    oled_init();
    
    // Clear screen
    oled_clear();
    
    // Display "HELLO WORLD"
    oled_print_hello_world();
    
    printf("OLED Hello World test complete\n");
} 