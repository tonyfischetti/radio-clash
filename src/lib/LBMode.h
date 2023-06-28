
#pragma once

#include "deebug.hpp"
#include "common.h"


// base class
class LBMode {
    public:

        LBMode() noexcept;

        virtual const char* getModeName()  const noexcept;
        virtual const bool isAudioNeeder() const noexcept;

        virtual uint8_t tick()      noexcept;
        virtual uint8_t engage()    noexcept;
        virtual uint8_t suspend()   noexcept;
        virtual uint8_t reCw()      noexcept;
        virtual uint8_t reCcw()     noexcept;
        virtual uint8_t rePress()   noexcept;

        /* these are reserved
         * virtual uint8_t remTVPower();
         * virtual uint8_t remSource();
         * virtual uint8_t remRedPower(); */

        virtual uint8_t remOK()             noexcept;
        virtual uint8_t remBack()           noexcept;
        virtual uint8_t remHome()           noexcept;
        virtual uint8_t remCircleLeft()     noexcept;
        virtual uint8_t remCircleRight()    noexcept;
        virtual uint8_t remMute()           noexcept;
        virtual uint8_t remCircleUp()       noexcept;
        virtual uint8_t remCircleDown()     noexcept;
        virtual uint8_t remAsterisk()       noexcept;
        virtual uint8_t remRewind()         noexcept;
        virtual uint8_t remPlayPause()      noexcept;
        virtual uint8_t remFastForward()    noexcept;
        virtual uint8_t remVolumeUp()       noexcept;
        virtual uint8_t remVolumeDown()     noexcept;
        virtual uint8_t remChannelUp()      noexcept;
        virtual uint8_t remChannelDown()    noexcept;
        virtual uint8_t remNetflix()        noexcept;
        virtual uint8_t remHulu()           noexcept;
        virtual uint8_t display()           noexcept;

        const bool audio_needer {false};

        const char* mode_name {"Base/Interface for Light-Box Modes"};
};

