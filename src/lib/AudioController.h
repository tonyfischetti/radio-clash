
#ifndef audiocontroller_h
#define audiocontroller_h

#include "deebug.hpp"
#include "common.h"


class AudioController {
    public:
        AudioController(const uint8_t, const uint8_t) noexcept;

        void init()                 noexcept;

        void turnOnMP3Audio()       noexcept;
        void turnOnWebRadioAudio()  noexcept;
        void turnOnFMAudio()        noexcept;

    private:
        const uint8_t MUX_CONTROL_A;
        const uint8_t MUX_CONTROL_B;
};

#endif

