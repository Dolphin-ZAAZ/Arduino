#ifndef TFT_DRIVER_H
#define TFT_DRIVER_H

#include <Arduino.h>
#include "../include/uno-R4-pin-macros.h"
#include "../include/tft-macros.h"

class TftDriver {
    public:
        TftDriver();
        void writePixel(int page, int column, uint16_t color);
    private:
        void latchRead();
        void latchWrite();
        void writeCommand(uint8_t command, uint8_t parameters[], int parameterSize);
        void readCommand(uint8_t command, uint8_t* out_parameters, int parameterSize);
        uint8_t getLowByte(uint16_t value);
        uint8_t getHighByte(uint16_t value);
        void writeData(uint8_t data);
        uint8_t readData();
        void setPageAddress(uint16_t startAddress, uint16_t endAddress);
        void setColumnAddress(uint16_t startAddress, uint16_t endAddress);
        void writeMemory(uint16_t color);
        void sendCommand(uint8_t command);
};

#endif