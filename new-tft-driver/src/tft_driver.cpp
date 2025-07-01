#include "../include/tft-driver.h"

TftDriver::TftDriver() {

}

void TftDriver::latchRead() {
    digitalWrite(READ_ENABLED, LOW);
    delayMicroseconds(1);
    digitalWrite(READ_ENABLED, HIGH);
}

void TftDriver::latchWrite() {
    digitalWrite(WRITE_ENABLED, LOW);
    delayMicroseconds(1);
    digitalWrite(WRITE_ENABLED, HIGH);
}

uint8_t TftDriver::readData() {
    uint8_t data = 0;

    data |= digitalRead(DATA_PIN_0) << 0; // 0000 0001
    data |= digitalRead(DATA_PIN_1) << 1; // 0000 0010
    data |= digitalRead(DATA_PIN_2) << 2; // 0000 0100
    data |= digitalRead(DATA_PIN_3) << 3; // 0000 1000
    data |= digitalRead(DATA_PIN_4) << 4; // 0001 0000
    data |= digitalRead(DATA_PIN_5) << 5; // 0010 0000
    data |= digitalRead(DATA_PIN_6) << 6; // 0100 0000
    data |= digitalRead(DATA_PIN_7) << 7; // 1000 0000

    return data;
}

void TftDriver::writeData(uint8_t data) {
    digitalWrite(DATA_PIN_0, (data & 0x01) ? HIGH : LOW); // 0000 0001
    digitalWrite(DATA_PIN_1, (data & 0x02) ? HIGH : LOW); // 0000 0010
    digitalWrite(DATA_PIN_2, (data & 0x04) ? HIGH : LOW); // 0000 0100
    digitalWrite(DATA_PIN_3, (data & 0x08) ? HIGH : LOW); // 0000 1000
    digitalWrite(DATA_PIN_4, (data & 0x10) ? HIGH : LOW); // 0001 0000
    digitalWrite(DATA_PIN_5, (data & 0x20) ? HIGH : LOW); // 0010 0000
    digitalWrite(DATA_PIN_6, (data & 0x40) ? HIGH : LOW); // 0100 0000
    digitalWrite(DATA_PIN_7, (data & 0x80) ? HIGH : LOW); // 1000 0000
    
}

uint8_t TftDriver::getHighByte(uint16_t value) {
    return (value >> 8);
}

uint8_t TftDriver::getLowByte(uint16_t value) {
    return (value & 0xFF);
}

void TftDriver::readCommand(uint8_t command, uint8_t* out_parameters, int parameterSize) {
    digitalWrite(CHIP_SELECT, LOW);
    digitalWrite(REGISTER_SELECT, LOW);
    writeData(command);
    latchWrite();
    digitalWrite(REGISTER_SELECT, HIGH);
    for (int i = 0; i < parameterSize; i++) {
        latchRead();
        out_parameters[i] = readData();
    }
    digitalWrite(CHIP_SELECT, HIGH);
}

void TftDriver::writeCommand(uint8_t command, uint8_t parameters[], int parameterSize) {
    digitalWrite(CHIP_SELECT, LOW);
    digitalWrite(REGISTER_SELECT, LOW);
    writeData(command);
    latchWrite();
    digitalWrite(REGISTER_SELECT, HIGH);
    for (int i = 0; i < parameterSize; i++) {
        writeData(parameters[i]);
        latchWrite();
    }
    digitalWrite(CHIP_SELECT, HIGH);
}

void TftDriver::setPageAddress(uint16_t startAddress, uint16_t endAddress) {
    uint8_t startHighByte = getHighByte(startAddress);
    uint8_t startLowByte = getLowByte(startAddress);
    uint8_t endHighByte = getHighByte(endAddress);
    uint8_t endLowByte = getLowByte(endAddress);
    uint8_t parameters[] = {startHighByte, startLowByte, endHighByte, endLowByte};
    writeCommand(SET_PAGE_ADDRESS, parameters, 4);
}

void TftDriver::setColumnAddress(uint16_t startAddress, uint16_t endAddress) {
    uint8_t startHighByte = getHighByte(startAddress);
    uint8_t startLowByte = getLowByte(startAddress);
    uint8_t endHighByte = getHighByte(endAddress);
    uint8_t endLowByte = getLowByte(endAddress);
    uint8_t parameters[] = {startHighByte, startLowByte, endHighByte, endLowByte};
    writeCommand(SET_COLUMN_ADDRESS, parameters, 4);
}