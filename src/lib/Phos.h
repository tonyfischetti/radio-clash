
#pragma once

#include "deebug.hpp"
#include "common.h"

#define USE_IRREMOTE_HPP_AS_PLAIN_INCLUDE
#include <IRremote.hpp>
#include <Adafruit_NeoPixel.h>
#include <elapsedMillis.h>



// enum class uint8_t : uint8_t { RED, GREEN, BLUE, WHITE };
// Nah, I have to use them as array indices and don't want to
// use `static_cast`
static constexpr uint8_t RED_INDEX   {0};
static constexpr uint8_t GREEN_INDEX {1};
static constexpr uint8_t BLUE_INDEX  {2};
static constexpr uint8_t WHITE_INDEX {3};

static constexpr uint8_t max_brightnesses[4] {255, 255, 255, 255};

static constexpr bool UP         {true};
static constexpr bool DOWN      {false};
static constexpr bool INCREMENT  {true};
static constexpr bool DECREMENT {false};
static constexpr bool ON         {true};
static constexpr bool OFF       {false};



class Phos {
    public:
        Phos(const uint8_t, const uint8_t)    noexcept;

        void init()                           noexcept;
        void displayUpdate()                  noexcept;
        void setPixelColor(const uint8_t)     noexcept;
        void displayRGBwColors()              noexcept;
        void turnOffPixels()                  noexcept;
        void displayExactColor(const uint8_t,
                               const uint8_t,
                               const uint8_t,
                               const uint8_t) noexcept;
        void displayDot(const uint8_t,
                        const bool,
                        const bool)           noexcept;
        bool roomToGoP(const bool,
                       const uint8_t)         noexcept;
        void updateNPCount()                  noexcept;
        bool shiftColor(const bool,
                        const uint8_t,
                        const bool)           noexcept;
        bool crossfadeColors(const uint8_t,
                             const uint8_t)   noexcept;

    private:
        Adafruit_NeoPixel pixels;
        const uint8_t NUM_NEOPIXELS;
        uint8_t np_count = 8;

        uint8_t current_rgbw[4] {255, 255, 255, 0};
        uint8_t brightness {255};
        uint8_t step_delay   {1};
        uint8_t step_delta   {2};

        elapsedMillis step_timer;

        bool is_engaged_p {false};
};

