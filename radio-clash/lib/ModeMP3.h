
#ifndef modemp3_h
#define modemp3_h

#include "deebug.hpp"
#include "common.h"

#include "Defe.h"
#include "AudioController.h"
#include <Sixteen.h>
#include "LBMode.h"



class ModeMP3 final : public LBMode {
    public:
        ModeMP3(Defe&, Sixteen&, AudioController&);

        const char* getModeName()  override;
        const bool isAudioNeeder() override;

        void resume();

        uint8_t engage()         override;
        uint8_t suspend()        override;

        uint8_t tick()           override;

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

        uint8_t display() override;

        const char* mode_name {"MP3 Mode"};

    private:
        Defe& defe;
        Sixteen& sixteen;
        AudioController& jefa;

        uint64_t playlist_select_time;
        const uint16_t PLAYLIST_SELECT_TIMEOUT {5000};

        uint8_t playlist_select_index;
};

#endif
