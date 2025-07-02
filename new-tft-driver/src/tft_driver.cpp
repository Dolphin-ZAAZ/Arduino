#include "../include/tft-driver.h"

// public

void TftDriver::writePixel(int page, int column, uint16_t color) {
    setPageAddress(page, page);
    setColumnAddress(column, column);
    writeMemory(color);
}

void TftDriver::drawRectangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint16_t color) {
    setPageAddress(y0, y1);
    setColumnAddress(x0, y0);
    writeMemory(color);
    Serial.println("Rectangle drawn");
}

void TftDriver::testFunction() {
    Serial.println("=== TFT Shield Initialization Test ===");
    
    // Proper hardware reset sequence
    digitalWrite(RESET, HIGH);
    delay(5);
    digitalWrite(RESET, LOW);
    delay(15);
    digitalWrite(RESET, HIGH);
    delay(150); // Wait for display to boot
    
    // Try basic initialization commands that most TFT controllers accept
    initializeBasicSequence();
    
    // Now try reading ID
    readDisplayIdsNoDummy();
}

void TftDriver::initializeBasicSequence() {
    Serial.println("Sending basic initialization sequence...");
    
    // Software reset
    writeCommand(0x01, nullptr, 0);
    delay(150);
    
    // Exit sleep mode
    writeCommand(0x11, nullptr, 0);
    delay(150);
    
    // Set pixel format to 16-bit
    uint8_t pixelFormat = 0x55; // 16-bit per pixel
    writeCommand(0x3A, &pixelFormat, 1);
    delay(10);
    
    // Set address mode (normal orientation)
    uint8_t addressMode = 0x00;
    writeCommand(0x36, &addressMode, 1);
    delay(10);
    
    // Display on
    writeCommand(0x29, nullptr, 0);
    delay(50);
    
    Serial.println("Basic initialization complete");
}

void TftDriver::readDisplayIds() {
    Serial.println("=== Reading Display IDs ===");
    
    // Try different ID commands
    uint8_t id1[2], id2[2], id3[2], displayId[4];
    
    Serial.println("Reading ID1 (0xDA):");
    readCommand(0xDA, id1, 2);
    Serial.print("Result: 0x");
    Serial.print(id1[0], HEX);
    Serial.print(" 0x");
    Serial.println(id1[1], HEX);
    
    Serial.println("Reading ID2 (0xDB):");
    readCommand(0xDB, id2, 2);
    Serial.print("Result: 0x");
    Serial.print(id2[0], HEX);
    Serial.print(" 0x");
    Serial.println(id2[1], HEX);
    
    Serial.println("Reading ID3 (0xDC):");
    readCommand(0xDC, id3, 2);
    Serial.print("Result: 0x");
    Serial.print(id3[0], HEX);
    Serial.print(" 0x");
    Serial.println(id3[1], HEX);
    
    Serial.println("Reading Display ID (0x04):");
    readCommand(0x04, displayId, 4);
    Serial.print("Result: ");
    for(int i = 0; i < 4; i++) {
        Serial.print("0x");
        Serial.print(displayId[i], HEX);
        Serial.print(" ");
    }
    Serial.println();
}

void TftDriver::readDisplayIdsNoDummy() {
    Serial.println("=== Reading IDs without dummy bytes ===");
    
    uint8_t id1, id2, id3;
    
    readCommand(0xDA, &id1, 1); // Just 1 byte, no dummy
    readCommand(0xDB, &id2, 1);
    readCommand(0xDC, &id3, 1);
    
    Serial.print("ID1: 0x"); Serial.println(id1, HEX);
    Serial.print("ID2: 0x"); Serial.println(id2, HEX);
    Serial.print("ID3: 0x"); Serial.println(id3, HEX);
}

// private

void TftDriver::writeMemory(uint16_t color) {
    uint8_t highByte = getHighByte(color);
    uint8_t lowByte = getLowByte(color);
    uint8_t parameters[2] = {highByte, lowByte};
    writeCommand(WRITE_MEMORY_START, parameters, 2);
    Serial.println("Memory Written");
}

void TftDriver::setPageAddress(uint16_t startAddress, uint16_t endAddress) {
    uint8_t startHighByte = getHighByte(startAddress);
    uint8_t startLowByte = getLowByte(startAddress);
    uint8_t endHighByte = getHighByte(endAddress);
    uint8_t endLowByte = getLowByte(endAddress);
    uint8_t parameters[4] = {startHighByte, startLowByte, endHighByte, endLowByte};
    writeCommand(SET_PAGE_ADDRESS, parameters, 4);
    Serial.println("Page Address Set");
}

void TftDriver::setColumnAddress(uint16_t startAddress, uint16_t endAddress) {
    uint8_t startHighByte = getHighByte(startAddress);
    uint8_t startLowByte = getLowByte(startAddress);
    uint8_t endHighByte = getHighByte(endAddress);
    uint8_t endLowByte = getLowByte(endAddress);
    uint8_t parameters[4] = {startHighByte, startLowByte, endHighByte, endLowByte};
    writeCommand(SET_COLUMN_ADDRESS, parameters, 4);
    Serial.println("Column Address Set");
}

void TftDriver::writeCommand(uint8_t command, uint8_t parameters[], int parameterSize) {
    sendCommand(command);
    for (int i = 0; i < parameterSize; i++) {
        writeData(parameters[i]);
    }
    digitalWrite(CHIP_SELECT, HIGH);
    Serial.println("Write Command Executed");
}

void TftDriver::readCommand(uint8_t command, uint8_t* out_parameters, int parameterSize) {
    sendCommand(command);
    setDataPinsAsInputs();
    for (int i = 0; i < parameterSize; i++) {
        out_parameters[i] = readData();
    }
    setDataPinsAsOutputs();
    digitalWrite(CHIP_SELECT, HIGH);
}

void TftDriver::setDataPinsAsInputs() {
    pinMode(DATA_PIN_0, INPUT);
    pinMode(DATA_PIN_1, INPUT);
    pinMode(DATA_PIN_2, INPUT);
    pinMode(DATA_PIN_3, INPUT);
    pinMode(DATA_PIN_4, INPUT);
    pinMode(DATA_PIN_5, INPUT);
    pinMode(DATA_PIN_6, INPUT);
    pinMode(DATA_PIN_7, INPUT);
}

void TftDriver::setDataPinsAsOutputs() {
    pinMode(DATA_PIN_0, OUTPUT);
    pinMode(DATA_PIN_1, OUTPUT);
    pinMode(DATA_PIN_2, OUTPUT);
    pinMode(DATA_PIN_3, OUTPUT);
    pinMode(DATA_PIN_4, OUTPUT);
    pinMode(DATA_PIN_5, OUTPUT);
    pinMode(DATA_PIN_6, OUTPUT);
    pinMode(DATA_PIN_7, OUTPUT);
}


void TftDriver::sendCommand(uint8_t command) {
    digitalWrite(CHIP_SELECT, LOW);
    digitalWrite(REGISTER_SELECT, LOW);
    writeData(command);
    delay(10);
    digitalWrite(REGISTER_SELECT, HIGH);
    Serial.println("Command Sent");
}

void TftDriver::latchWrite() {
    digitalWrite(WRITE_ENABLED, LOW);
    delay(10);
    digitalWrite(WRITE_ENABLED, HIGH);
    Serial.println("Write latched");
}

void TftDriver::latchRead() {
    digitalWrite(READ_ENABLED, LOW);
    delay(10);
    digitalWrite(READ_ENABLED, HIGH);
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

    Serial.println("Data set");
    
    latchWrite();
}

uint8_t TftDriver::readData() {
    uint8_t data = 0;
    
    // Trigger read cycle
    digitalWrite(READ_ENABLED, LOW);
    delayMicroseconds(100); // Allow data setup time
    
    // Read the data
    data |= digitalRead(DATA_PIN_0) << 0;
    data |= digitalRead(DATA_PIN_1) << 1;
    data |= digitalRead(DATA_PIN_2) << 2;
    data |= digitalRead(DATA_PIN_3) << 3;
    data |= digitalRead(DATA_PIN_4) << 4;
    data |= digitalRead(DATA_PIN_5) << 5;
    data |= digitalRead(DATA_PIN_6) << 6;
    data |= digitalRead(DATA_PIN_7) << 7;
    
    digitalWrite(READ_ENABLED, HIGH);
    delayMicroseconds(10); // Recovery time
    
    return data;
}

uint8_t TftDriver::getHighByte(uint16_t value) {
    return (value >> 8);
}

uint8_t TftDriver::getLowByte(uint16_t value) {
    return (value & 0xFF);
}