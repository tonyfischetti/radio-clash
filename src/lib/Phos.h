
#ifndef phos_h
#define phos_h

#include "deebug.hpp"
#include "common.h"

#define USE_IRREMOTE_HPP_AS_PLAIN_INCLUDE
#include <IRremote.hpp>
#include <Adafruit_NeoPixel.h>


class Phos {
    public:
        Phos(const uint8_t, const uint8_t)  noexcept;

        void init()                         noexcept;
        void displayUpdate() noexcept;

    private:
        const uint8_t NUM_NEOPIXELS;
        Adafruit_NeoPixel pixels;

        bool is_engaged_p;
        uint8_t brightness;
};

#endif

