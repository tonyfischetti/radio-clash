
#pragma once

#include "deebug.hpp"
#include "common.h"

#include <Adafruit_LEDBackpack.h>

#include "TickTockClock.h"

class Amber {
    public:
        Amber(const uint8_t address, TickTockClock&) noexcept;

        void init()                         noexcept;
        void update()                       noexcept;
        void setBrightness(const uint8_t)   noexcept;
        void nextBrightness()               noexcept;

    private:
        Adafruit_7segment seg7;
        TickTockClock& rtc;
        const uint8_t seg_address;
        uint8_t brightness;
};

