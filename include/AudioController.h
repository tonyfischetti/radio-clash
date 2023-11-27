
#pragma once

#include "deebug.hpp"
#include "common.h"


class AudioController {
    public:
        AudioController(const uint8_rc, const uint8_rc) noexcept;

        void init()                 noexcept;

        void turnOnMP3Audio()       noexcept;
        void turnOnWebRadioAudio()  noexcept;
        void turnOnFMAudio()        noexcept;

    private:
        const uint8_rc MUX_CONTROL_A;
        const uint8_rc MUX_CONTROL_B;
};

