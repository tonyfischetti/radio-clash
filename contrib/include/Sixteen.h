
#include <stdint.h>
#include <Arduino.h>
#include <Wire.h>

#include <LiquidCrystal_I2C.h>

#ifndef sixteen_h
#define sixteen_h


// TODO: should this handle timeouts and blinking?!

class Sixteen {
    public:
        Sixteen(const uint8_t address);
        LiquidCrystal_I2C lcd;
        void clearLine0();
        void clearLine1();
        void init();
        void update();
        char line0[17];
        char line1[17];
    private:
        char actual_line0[17];
        char actual_line1[17];
};

#endif
