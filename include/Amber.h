
#pragma once

#include "deebug.hpp"
#include "common.h"

#include <Adafruit_LEDBackpack.h>

#include "TickTockClock.h"

class Amber {
    public:
        Amber(const uint8_rc address, TickTockClock&) noexcept;

        void init()                         noexcept;
        void update()                       noexcept;
        void setBrightness(const uint8_rc)   noexcept;
        void nextBrightness()               noexcept;

    private:
        Adafruit_7segment seg7;
        TickTockClock& rtc;
        const uint8_rc seg_address;
        uint8_rc brightness;
};

