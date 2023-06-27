
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
        ModeMP3(Defe&, Sixteen&, AudioController&) noexcept;

        const char* getModeName()  const noexcept override;
        const bool isAudioNeeder() const noexcept override;

        void resume()            noexcept;
        uint8_t engage()         noexcept override;
        uint8_t suspend()        noexcept override;
        uint8_t tick()           noexcept override;
        uint8_t reCw()           noexcept override;
        uint8_t reCcw()          noexcept override;
        uint8_t rePress()        noexcept override;
        uint8_t remCircleLeft()  noexcept override;
        uint8_t remCircleRight() noexcept override;
        uint8_t remAsterisk()    noexcept override;
        uint8_t remRewind()      noexcept override;
        uint8_t remPlayPause()   noexcept override;
        uint8_t remFastForward() noexcept override;
        uint8_t remVolumeUp()    noexcept override;
        uint8_t remVolumeDown()  noexcept override;
        uint8_t remNetflix()     noexcept override;
        uint8_t remHulu()        noexcept override;
        uint8_t display()        noexcept override;

        const char* mode_name {"MP3 Mode"};

    private:
        Defe& defe;
        Sixteen& sixteen;
        AudioController& jefa;

        uint64_t playlist_select_time;
        const uint16_t PLAYLIST_SELECT_TIMEOUT {5000};

        uint8_t playlist_select_index;

        bool is_engaged_p;
};

#endif
