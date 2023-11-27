
#pragma once

#include "deebug.hpp"
#include "common.h"


// base class
class LBMode {
    public:

        LBMode() noexcept;

        virtual const char* getModeName()  const noexcept;
        virtual const bool isAudioNeeder() const noexcept;

        virtual uint8_rc tick()      noexcept;
        virtual uint8_rc engage()    noexcept;
        virtual uint8_rc suspend()   noexcept;
        virtual uint8_rc reCw()      noexcept;
        virtual uint8_rc reCcw()     noexcept;
        virtual uint8_rc rePress()   noexcept;

        /* these are reserved
         * virtual uint8_rc remTVPower();
         * virtual uint8_rc remSource();
         * virtual uint8_rc remRedPower(); */

        virtual uint8_rc remOK()             noexcept;
        virtual uint8_rc remBack()           noexcept;
        virtual uint8_rc remHome()           noexcept;
        virtual uint8_rc remCircleLeft()     noexcept;
        virtual uint8_rc remCircleRight()    noexcept;
        virtual uint8_rc remMute()           noexcept;
        virtual uint8_rc remCircleUp()       noexcept;
        virtual uint8_rc remCircleDown()     noexcept;
        virtual uint8_rc remAsterisk()       noexcept;
        virtual uint8_rc remRewind()         noexcept;
        virtual uint8_rc remPlayPause()      noexcept;
        virtual uint8_rc remFastForward()    noexcept;
        virtual uint8_rc remVolumeUp()       noexcept;
        virtual uint8_rc remVolumeDown()     noexcept;
        virtual uint8_rc remChannelUp()      noexcept;
        virtual uint8_rc remChannelDown()    noexcept;
        virtual uint8_rc remNetflix()        noexcept;
        virtual uint8_rc remHulu()           noexcept;
        virtual uint8_rc display()           noexcept;

        const bool audio_needer {false};

        const char* mode_name {"Base/Interface for Light-Box Modes"};
};

