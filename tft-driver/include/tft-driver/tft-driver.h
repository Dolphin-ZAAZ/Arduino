#ifndef TFT_DRIVER_H
#define TFT_DRIVER_H

#define DATA_PIN_0 8
#define DATA_PIN_1 9
#define DATA_PIN_2 2
#define DATA_PIN_3 3
#define DATA_PIN_4 4
#define DATA_PIN_5 5
#define DATA_PIN_6 6
#define DATA_PIN_7 7

#define READ_ENABLED A0
#define WRITE_ENABLED A1
#define REGISTER_SELECT A2
#define CHIP_SELECT A3
#define RESET A4

class TftDriver {
    public:
        TftDriver();
};

#endif

//latch read
//latch write
//write command
//write data
//read data
