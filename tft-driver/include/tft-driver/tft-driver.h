#ifndef TFT_DRIVER_H
#define TFT_DRIVER_H

// System, Status & Diagnostic Commands
#define NOP                        0x00
#define SOFT_RESET                 0x01
#define GET_DISPLAY_ID             0x04
#define GET_DSI_ERR                0x05
#define READ_DISPLAY_STATUS        0x09
#define GET_DIAGNOSTIC_RESULT      0x0F
#define READ_FIRST_CHECKSUM        0xAA
#define READ_CONTINUE_CHECKSUM     0xAF
#define DEVICE_CODE_READ           0xBF
#define READ_ID1                   0xDA
#define READ_ID2                   0xDB
#define READ_ID3                   0xDC
#define READ_ID4                   0xD3

// Power & Mode Control
#define ENTER_SLEEP_MODE           0x10
#define EXIT_SLEEP_MODE            0x11
#define ENTER_PARTIAL_MODE         0x12
#define ENTER_NORMAL_MODE          0x13
#define EXIT_IDLE_MODE             0x38
#define ENTER_IDLE_MODE            0x39
#define GET_POWER_MODE             0x0A

// Memory, Display & Interface Configuration
#define SET_DISPLAY_OFF            0x28
#define SET_DISPLAY_ON             0x29
#define SET_COLUMN_ADDRESS         0x2A
#define SET_PAGE_ADDRESS           0x2B
#define SET_ADDRESS_MODE           0x36
#define GET_ADDRESS_MODE           0x0B
#define SET_PIXEL_FORMAT           0x3A
#define GET_PIXEL_FORMAT           0x0C
#define INTERFACE_MODE_CONTROL     0xB0
#define DISPLAY_FUNCTION_CONTROL   0xB6

// Memory Access
#define WRITE_MEMORY_START         0x2C
#define WRITE_MEMORY_CONTINUE      0x3C
#define READ_MEMORY_START          0x2E
#define READ_MEMORY_CONTINUE       0x3E

// Display Effects, Scrolling & Tearing
#define EXIT_INVERT_MODE           0x20
#define ENTER_INVERT_MODE          0x21
#define SET_PARTIAL_AREA           0x30
#define SET_SCROLL_AREA            0x33
#define SET_SCROLL_START           0x37
#define DISPLAY_INVERSION_CONTROL  0xB4
#define SET_TEAR_OFF               0x34
#define SET_TEAR_ON                0x35
#define SET_TEAR_SCANLINE          0x44
#define GET_SCANLINE               0x45
#define GET_DISPLAY_MODE           0x0D
#define GET_SIGNAL_MODE            0x0E

// Brightness & Backlight Control
#define SET_DISPLAY_BRIGHTNESS     0x51
#define GET_DISPLAY_BRIGHTNESS     0x52
#define SET_CONTROL_DISPLAY        0x53
#define GET_CONTROL_DISPLAY        0x54
#define SET_CABC_MODE              0x55
#define GET_CABC_MODE              0x56
#define SET_CABC_MIN_BRIGHTNESS    0x5E
#define GET_CABC_MIN_BRIGHTNESS    0x5F

// Advanced Power, Frame Rate, VCOM & Gamma
#define FRAME_RATE_CONTROL_NORMAL  0xB1
#define FRAME_RATE_CONTROL_IDLE    0xB2
#define FRAME_RATE_CONTROL_PARTIAL 0xB3
#define BLANKING_PORCH_CONTROL     0xB5
#define ENTRY_MODE_SET             0xB7
#define POWER_CONTROL_1            0xC0
#define POWER_CONTROL_2            0xC1
#define POWER_CONTROL_3_NORMAL     0xC2
#define POWER_CONTROL_5_PARTIAL    0xC4
#define VCOM_CONTROL_1             0xC5
#define NV_MEMORY_WRITE            0xD0
#define NV_MEMORY_PROTECTION_KEY   0xD1
#define NV_MEMORY_STATUS_READ      0xD2
#define GAMMA_SETTING              0xE0

//Pins
#define DATA_PIN_0                 8
#define DATA_PIN_1                 9
#define DATA_PIN_2                 2
#define DATA_PIN_3                 3
#define DATA_PIN_4                 4
#define DATA_PIN_5                 5
#define DATA_PIN_6                 6
#define DATA_PIN_7                 7

#define READ_ENABLED               A0
#define WRITE_ENABLED              A1
#define REGISTER_SELECT            A2
#define CHIP_SELECT                A3
#define RESET                      A4

class TftDriver {
    public:
        TftDriver();
};

#endif

// //latch read
// //latch write
// //write command
// //write data
// //read data


// // Pin definitions
// #define LCD_CS   10
// #define LCD_RS   9   // Register Select (DC)
// #define LCD_WR   8   // Write Enable
// #define LCD_RD   7   // Read Enable  
// #define LCD_RST  6   // Reset

// // Data bus pins (8-bit example)
// #define LCD_D0   0
// #define LCD_D1   1
// #define LCD_D2   2
// #define LCD_D3   3
// #define LCD_D4   4
// #define LCD_D5   5
// #define LCD_D6   A0
// #define LCD_D7   A1

// void writeCommand(uint8_t cmd) {
//     digitalWrite(LCD_CS, LOW);    // Select display
//     digitalWrite(LCD_RS, LOW);    // Command mode
    
//     // Put command on data bus
//     setDataBus(cmd);
    
//     // Latch command with write pulse
//     digitalWrite(LCD_WR, LOW);    // Start write
//     delayMicroseconds(1);         // Hold time
//     digitalWrite(LCD_WR, HIGH);   // End write - data latched
    
//     digitalWrite(LCD_CS, HIGH);   // Deselect
// }

// void writeData(uint8_t data) {
//     digitalWrite(LCD_CS, LOW);    // Select display
//     digitalWrite(LCD_RS, HIGH);   // Data mode
    
//     // Put data on bus
//     setDataBus(data);
    
//     // Latch data with write pulse
//     digitalWrite(LCD_WR, LOW);
//     delayMicroseconds(1);
//     digitalWrite(LCD_WR, HIGH);   // Data latched here
    
//     digitalWrite(LCD_CS, HIGH);
// }

// void setDataBus(uint8_t value) {
//     // Set each data pin based on bit value
//     digitalWrite(LCD_D0, (value & 0x01) ? HIGH : LOW);
//     digitalWrite(LCD_D1, (value & 0x02) ? HIGH : LOW);
//     digitalWrite(LCD_D2, (value & 0x04) ? HIGH : LOW);
//     digitalWrite(LCD_D3, (value & 0x08) ? HIGH : LOW);
//     digitalWrite(LCD_D4, (value & 0x10) ? HIGH : LOW);
//     digitalWrite(LCD_D5, (value & 0x20) ? HIGH : LOW);
//     digitalWrite(LCD_D6, (value & 0x40) ? HIGH : LOW);
//     digitalWrite(LCD_D7, (value & 0x80) ? HIGH : LOW);
// }

// // Example: Set pixel color at coordinates
// void setPixel(uint16_t x, uint16_t y, uint16_t color) {
//     // Column address command
//     writeCommand(0x2A);           // Set column address
//     writeData(x >> 8);            // X high byte
//     writeData(x & 0xFF);          // X low byte
    
//     // Row address command  
//     writeCommand(0x2B);           // Set row address
//     writeData(y >> 8);            // Y high byte
//     writeData(y & 0xFF);          // Y low byte
    
//     // Write pixel data
//     writeCommand(0x2C);           // Memory write
//     writeData(color >> 8);        // Color high byte
//     writeData(color & 0xFF);      // Color low byte
// }