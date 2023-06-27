
#ifndef lbmode_h
#define lbmode_h

#include "deebug.hpp"
#include "common.h"

#define MODE_STANDBY  0
#define MODE_LIGHT    1
#define MODE_TIME     2
#define MODE_MP3      3
#define MODE_RADIO    4
#define MODE_WEBRADIO 5
#define MODE_CHOOSE   6


// base class
class LBMode {
    public:

        LBMode();

        virtual const char* getModeName();
        virtual const bool isAudioNeeder();

        virtual uint8_t tick();

        virtual uint8_t engage();
        virtual uint8_t suspend();

        virtual uint8_t reCw();
        virtual uint8_t reCcw();
        virtual uint8_t rePress();

        /* these are reserved
         * virtual uint8_t remTVPower();
         * virtual uint8_t remSource();
         * virtual uint8_t remRedPower(); */

        virtual uint8_t remOK();
        virtual uint8_t remBack();
        virtual uint8_t remHome();
        virtual uint8_t remCircleLeft();
        virtual uint8_t remCircleRight();
        virtual uint8_t remMute();
        virtual uint8_t remCircleUp();
        virtual uint8_t remCircleDown();
        virtual uint8_t remAsterisk();
        virtual uint8_t remRewind();
        virtual uint8_t remPlayPause();
        virtual uint8_t remFastForward();
        virtual uint8_t remVolumeUp();
        virtual uint8_t remVolumeDown();
        virtual uint8_t remChannelUp();
        virtual uint8_t remChannelDown();
        virtual uint8_t remNetflix();
        virtual uint8_t remHulu();

        virtual uint8_t display();

        const bool audio_needer {false};

        const char* mode_name = "Base/Interface for Light-Box Modes";
};

#endif
