
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



// TODO: try 32 and 128!
#define MP3BUFFERSIZE 64

#define MAX_WEBRADIO_VOLUME 100

#define CURRENT_STATION web_stations[current_station_index]


class ModeWebRadio final : public LBMode {
    public:
        ModeWebRadio(VS1053&, Kerl&, Sixteen&, const WebStation**,
                     const uint8_t, AudioController&);

        const char* getModeName();
        const bool isAudioNeeder() override;

        uint8_t init();

        uint8_t engage();
        uint8_t suspend();

        uint8_t tick();

        uint8_t reCw();
        uint8_t reCcw();
        uint8_t rePress();

        uint8_t remRewind();
        uint8_t remFastForward();
        uint8_t remVolumeUp();
        uint8_t remVolumeDown();

        uint8_t display();

        const char* mode_name {"Web Radio Mode"};


    private:
        VS1053& vica;
        Kerl& kerl;
        Sixteen& sixteen;
        const WebStation** web_stations;
        const uint8_t NUM_WEBSTATIONS;
        AudioController& jefa;

        uint64_t webstation_select_time;
        const uint16_t WEBSTATION_SELECT_TIMEOUT = 5000;

        uint8_t webstation_select_index;

        uint8_t mp3buff[MP3BUFFERSIZE];
        uint8_t volume;
        uint8_t initialized_p;

        uint8_t suspended_p;

        uint8_t current_station_index;
};

#endif
