
#pragma once

#include <cstdint>
#include <Arduino.h>
#include <Esp.h>

using uint8_rc  = uint_fast8_t;
using uint16_rc = uint_fast16_t;
using uint32_rc = uint_fast32_t;
using uint64_rc = uint_fast64_t;

// Eighties - Killing Joke
static constexpr uint8_rc ALARM_FOLDER  {76};
static constexpr uint8_rc ALARM_TRACK  {172};

static constexpr uint8_rc CLIMATEWAVE_PLAYLIST     {17};
static constexpr uint8_rc THE_ALTERNATIVE_PLAYLIST {76};

