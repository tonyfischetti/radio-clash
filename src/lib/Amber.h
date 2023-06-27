
#ifndef amber_h
#define amber_h

#include "deebug.hpp"
#include "common.h"

#include <Adafruit_LEDBackpack.h>

#include "TickTockClock.h"

class Amber {
    public:
        Amber(const uint8_t address, TickTockClock&);

        void init();
        void update();
        void setBrightness(const uint8_t);
        void nextBrightness();

    private:
        Adafruit_7segment seg7;
        TickTockClock& rtc;
        const uint8_t seg_address;
        uint8_t brightness;
};

#endif
