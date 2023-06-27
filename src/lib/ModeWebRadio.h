
#ifndef modewebradio_h
#define modewebradio_h

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
static const uint8_t MP3BUFFERSIZE        {64};
static const uint8_t MAX_WEBRADIO_VOLUME {100};


class ModeWebRadio final : public LBMode {
    public:
        ModeWebRadio(VS1053&, Kerl&, Sixteen&, const WebStation**,
                     const uint8_t, AudioController&) noexcept;

        const char* getModeName()  const noexcept override;
        const bool isAudioNeeder() const noexcept override;

        uint8_t init()           noexcept;
        uint8_t engage()         noexcept override;
        uint8_t suspend()        noexcept override;
        uint8_t tick()           noexcept override;
        uint8_t reCw()           noexcept override;
        uint8_t reCcw()          noexcept override;
        uint8_t rePress()        noexcept override;
        uint8_t remRewind()      noexcept override;
        uint8_t remFastForward() noexcept override;
        uint8_t remVolumeUp()    noexcept override;
        uint8_t remVolumeDown()  noexcept override;
        uint8_t display()        noexcept override;

        const char* mode_name {"Web Radio Mode"};


    private:
        VS1053& vica;
        Kerl& kerl;
        Sixteen& sixteen;
        const WebStation** web_stations;
        const uint8_t NUM_WEBSTATIONS;
        AudioController& jefa;

        uint64_t webstation_select_time;
        const uint16_t WEBSTATION_SELECT_TIMEOUT {5000};

        uint8_t webstation_select_index;

        uint8_t mp3buff[MP3BUFFERSIZE];
        uint8_t volume;
        uint8_t initialized_p;

        uint8_t suspended_p;
        bool is_engaged_p;

        uint8_t current_station_index;
};

#endif
