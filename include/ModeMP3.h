
#pragma once

#include "deebug.hpp"
#include "common.h"

#include "Defe.h"
#include "AudioController.h"
#include <Sixteen.h>
#include "LBMode.h"



class ModeMP3 final : public LBMode {
    public:
        ModeMP3(Defe&, Sixteen&, AudioController&) noexcept;

        const char* getModeName()  const noexcept override;
        bool isAudioNeeder() const noexcept override;

        void resume()             noexcept;
        uint8_rc engage()         noexcept override;
        uint8_rc suspend()        noexcept override;
        uint8_rc tick()           noexcept override;
        uint8_rc reCw()           noexcept override;
        uint8_rc reCcw()          noexcept override;
        uint8_rc rePress()        noexcept override;
        uint8_rc remOK()          noexcept override;
        uint8_rc remCircleLeft()  noexcept override;
        uint8_rc remCircleRight() noexcept override;
        uint8_rc remAsterisk()    noexcept override;
        uint8_rc remRewind()      noexcept override;
        uint8_rc remPlayPause()   noexcept override;
        uint8_rc remFastForward() noexcept override;
        uint8_rc remVolumeUp()    noexcept override;
        uint8_rc remVolumeDown()  noexcept override;
        uint8_rc remNetflix()     noexcept override;
        uint8_rc remHulu()        noexcept override;
        uint8_rc display()        noexcept override;

        const char* mode_name {"MP3 Mode"};

    private:
        Defe& defe;
        Sixteen& sixteen;
        AudioController& jefa;

        bool is_engaged_p;
        Timeout playlist_select_TMO;

        const uint16_rc PLAYLIST_SELECT_TIMEOUT {5000};

        uint8_rc playlist_select_index;

};

