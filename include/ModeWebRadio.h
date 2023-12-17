
#pragma once

#include "deebug.hpp"
#include "common.h"

#include <VS1053.h>
#include <Sixteen.h>
#include "AudioController.h"
#include "Kerl.h"
#include "LBMode.h"
#include "WebStation.h"


#define CURRENT_STATION web_stations[current_station_index]

// TODO: try 32 and 128!
static constexpr uint8_rc MP3BUFFERSIZE        {64};
static constexpr uint8_rc MAX_WEBRADIO_VOLUME {100};


class ModeWebRadio final : public LBMode {
    public:
        ModeWebRadio(VS1053&, Kerl&, Sixteen&, const WebStation**,
                     const uint8_rc, AudioController&) noexcept;

        const char* getModeName()  const noexcept override;
        bool isAudioNeeder() const noexcept override;

        uint8_rc init()           noexcept;
        uint8_rc engage()         noexcept override;
        uint8_rc suspend()        noexcept override;
        uint8_rc tick()           noexcept override;
        uint8_rc reCw()           noexcept override;
        uint8_rc reCcw()          noexcept override;
        uint8_rc rePress()        noexcept override;
        uint8_rc remOK()          noexcept override;
        uint8_rc remCircleLeft()  noexcept override;
        uint8_rc remCircleRight() noexcept override;
        uint8_rc remRewind()      noexcept override;
        uint8_rc remFastForward() noexcept override;
        uint8_rc remVolumeUp()    noexcept override;
        uint8_rc remVolumeDown()  noexcept override;
        uint8_rc display()        noexcept override;

        const char* mode_name {"Web Radio Mode"};


    private:
        VS1053& vica;
        Kerl& kerl;
        Sixteen& sixteen;
        const WebStation** web_stations;
        const uint8_rc NUM_WEBSTATIONS;
        AudioController& jefa;

        uint8_rc initialized_p;
        uint8_rc suspended_p;
        uint8_rc volume;
        uint8_rc current_station_index;
        bool is_engaged_p;
        Timeout webstation_select_TMO;

        const uint16_rc WEBSTATION_SELECT_TIMEOUT {5000};
        uint8_rc webstation_select_index {};
        uint8_t mp3buff[MP3BUFFERSIZE]{};
};

