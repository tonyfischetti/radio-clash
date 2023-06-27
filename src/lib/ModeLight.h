
#ifndef modelight_h
#define modelight_h

#include "deebug.hpp"
#include "common.h"

#include "Phos.h"
#include <Sixteen.h>
#include "LBMode.h"



class ModeLight final : public LBMode {
    public:
        ModeLight(Phos&, Sixteen&);

        const char* getModeName()  override;
        const bool isAudioNeeder() override;

        uint8_t engage()         override;
        uint8_t suspend()        override;

        uint8_t tick()           override;

        /*
        uint8_t reCw()           override;
        uint8_t reCcw()          override;
        uint8_t rePress()        override;

        uint8_t remCircleLeft()  override;
        uint8_t remCircleRight() override;
        uint8_t remAsterisk()    override;
        uint8_t remRewind()      override;
        uint8_t remPlayPause()   override;
        uint8_t remFastForward() override;
        uint8_t remVolumeUp()    override;
        uint8_t remVolumeDown()  override;
        uint8_t remNetflix()     override;
        uint8_t remHulu()        override;
        */

        uint8_t display() override;

        const char* mode_name {"Light Mode"};

    private:
        Phos& phos;
        Sixteen& sixteen;

        // uint64_t playlist_select_time;
        // const uint16_t PLAYLIST_SELECT_TIMEOUT {5000};
        //
        // uint8_t playlist_select_index;
};

#endif
