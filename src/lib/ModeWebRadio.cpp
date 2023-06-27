
#include <stdint.h>
#include <Arduino.h>

#include "ModeWebRadio.h"



ModeWebRadio::ModeWebRadio(VS1053& _vica, Kerl& _kerl, Sixteen& _sixteen,
                           const WebStation** _web_stations,
                           const uint8_t _NUM_WEBSTATIONS,
                           AudioController& _jefa)
    : vica                  {_vica},
      kerl                  {_kerl},
      sixteen               {_sixteen},
      web_stations          {_web_stations},
      NUM_WEBSTATIONS       {_NUM_WEBSTATIONS},
      jefa                  {_jefa},
      initialized_p         {0},
      suspended_p           {1},
      volume                {100},
      webstation_select_time{0},
      current_station_index {0} {
}

const char* ModeWebRadio::getModeName() {
    return mode_name;
}

const bool ModeWebRadio::isAudioNeeder() {
    return true;
}

uint8_t ModeWebRadio::init() {
    deebug("web radio mode", "init-ing web radio");
    SPI.begin();
    // TODO: error checking?!
    vica.begin();
    vica.loadDefaultVs1053Patches(); 
    vica.switchToMp3Mode();
    vica.setVolume(volume);

    return 0;
}

uint8_t ModeWebRadio::engage() {
    deebug("web radio mode", "engaging web radio");
    jefa.turnOnWebRadioAudio();
    if (!initialized_p)
        init();
    if (kerl.connectToAnyNetwork() > 0) {
        deebug("web radio mode", "failed to connect to any network :(");
        return 1;
    }
    deebug("web radio mode", "WiFi connected!");

    suspended_p = 0;

    // TODO: PLAY SOMETHING!

    return 0;
}

uint8_t ModeWebRadio::suspend() {
    // TODO: TURN OFF WIFI?!
    kerl.disconnect();
    suspended_p = 1;
    return false;
}

uint8_t ModeWebRadio::tick() {

    if (suspended_p)
        return 1;

    // reset from webstation select mode if it times out
    if (webstation_select_time &&
        (millis() - webstation_select_time) > WEBSTATION_SELECT_TIMEOUT)
        webstation_select_time = 0;

    if (kerl.connectWebKeepAlive() > 0) {
        deebug("web radio mode", "SOMETHING'S WRONG WITH WEB CONNECTION!");
        if (kerl.connectToAnyNetwork() > 0) {
            deebug("web radio mode", "failed to connect to any network :(");
            return 1;
        }
    }

    if (kerl.connectClientKeepAlive(CURRENT_STATION) > 0) {
        deebug("web radio mode", "SOMETHING'S WRONG WITH CONNECTION TO STATION!");
        return 2;
    }

    uint8_t bytesread = kerl.fillMP3Buffer(mp3buff, MP3BUFFERSIZE);
    if (bytesread) {
        vica.playChunk(mp3buff, bytesread);
    }
    return 0;
}

uint8_t ModeWebRadio::reCw() {
    if (webstation_select_time) {
        deebug("web radio mode", "(while in webstation select mode)");
        // reset time (for timeout)
        webstation_select_time = millis();
        if (webstation_select_index == (NUM_WEBSTATIONS-1))
            return true;
        ++webstation_select_index;
    }
    return true;
}

uint8_t ModeWebRadio::reCcw() {
    if (webstation_select_time) {
        deebug("web radio mode", "(while in webstation select mode)");
        // reset time (for timeout)
        webstation_select_time = millis();
        if (webstation_select_index == 0)
            return true;
        --webstation_select_index;
    }
    return true;
}

uint8_t ModeWebRadio::rePress() {
    deebug("web radio mode", "pressed!");
    // if not already in webstation select mode
    if (!webstation_select_time) {
        deebug("web radio mode", "entering webstation select mode");
        webstation_select_time = millis();
        webstation_select_index = current_station_index;
    }
    else {
        // choose the current webstation selection index
        deebug("web radio mode", "about to leave webstation select mode");
        webstation_select_time = 0;
        kerl.client.stop();
        current_station_index = webstation_select_index;
    }
    return true;
}

uint8_t ModeWebRadio::remRewind() {
    if (current_station_index == 0)
        return 1;
    kerl.client.stop();
    --current_station_index;
}

uint8_t ModeWebRadio::remFastForward() {
    if (current_station_index == (NUM_WEBSTATIONS - 1))
        return 1;
    kerl.client.stop();
    ++current_station_index;
}

uint8_t ModeWebRadio::remVolumeUp() {
    if (volume == MAX_WEBRADIO_VOLUME)
        return 1;
    ++volume;
    vica.setVolume(volume);
}

uint8_t ModeWebRadio::remVolumeDown() {
    deebug("MWR", "volume down");
    if (volume == 0)
        return 1;
    --volume;
    deebug("MWR", "calling");
    vica.setVolume(volume);
    deebug("MWR", "done");
}

// TODO TODO TODO: have it display error message (if there's an error)
uint8_t ModeWebRadio::display() {
    // if it's not in webstation select mode
    if (!webstation_select_time) {
        snprintf(sixteen.line0, 17, "%s                 ",
                 CURRENT_STATION->name);
        snprintf(sixteen.line1, 17, "  volume: +%d          ", volume);
    }
    else {
        snprintf(sixteen.line0, 17, "Station select:        ");
        snprintf(sixteen.line1, 17, "%s                     ",
                 web_stations[webstation_select_index]->name);
    }
    sixteen.update();
    return true;
}

