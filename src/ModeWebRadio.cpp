
#include <stdint.h>
#include <Arduino.h>

#include "ModeWebRadio.h"



ModeWebRadio::ModeWebRadio(VS1053& _vica, Kerl& _kerl, Sixteen& _sixteen,
                           const WebStation** _web_stations,
                           const uint8_rc _NUM_WEBSTATIONS,
                           AudioController& _jefa)
    : vica                  {_vica},
      kerl                  {_kerl},
      sixteen               {_sixteen},
      web_stations          {_web_stations},
      NUM_WEBSTATIONS       {_NUM_WEBSTATIONS},
      jefa                  {_jefa},
      initialized_p         {0},
      suspended_p           {1},
      volume                {87},
      webstation_select_time{0},
      current_station_index {0},
      is_engaged_p          {false} {
}

const char* ModeWebRadio::getModeName() const {
    return mode_name;
}

const bool ModeWebRadio::isAudioNeeder() const {
    return true;
}

uint8_rc ModeWebRadio::init() {
    deebug("web radio mode", "init-ing web radio");
    SPI.begin();
    // TODO: error checking?!
    vica.begin();
    vica.loadDefaultVs1053Patches(); 
    vica.switchToMp3Mode();
    vica.setVolume(volume);

    return 0;
}

uint8_rc ModeWebRadio::engage() {
    if (is_engaged_p) {
        deebug("web radio mode", "engaged called but already engaged");
        return 0;
    }
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
    is_engaged_p = true;

    // TODO: PLAY SOMETHING!

    return 0;
}

uint8_rc ModeWebRadio::suspend() {
    // TODO: TURN OFF WIFI?!
    kerl.disconnect();
    suspended_p = 1;
    is_engaged_p = false;
    return false;
}

uint8_rc ModeWebRadio::tick() {

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

    if (kerl.client.available()) {
        uint8_t bytesread = kerl.client.read(mp3buff, MP3BUFFERSIZE);
        if (bytesread) {
            vica.playChunk(mp3buff, bytesread);
        }
    }
    return 0;
}

uint8_rc ModeWebRadio::reCw() {
    deebug("web radio mode", "reCw()");
    if (webstation_select_time) {
        deebug("web radio mode", "  (while in webstation select mode)");
        // reset time (for timeout)
        webstation_select_time = millis();
        if (webstation_select_index == (NUM_WEBSTATIONS-1))
            return true;
        ++webstation_select_index;
    }
    return true;
}

uint8_rc ModeWebRadio::reCcw() {
    deebug("web radio mode", "reCcw()");
    if (webstation_select_time) {
        deebug("web radio mode", "  (while in webstation select mode)");
        // reset time (for timeout)
        webstation_select_time = millis();
        if (webstation_select_index == 0)
            return true;
        --webstation_select_index;
    }
    return true;
}

uint8_rc ModeWebRadio::rePress() {
    deebug("web radio mode", "pressed!");
    // if not already in webstation select mode
    if (!webstation_select_time) {
        deebug("web radio mode", "  entering webstation select mode");
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

uint8_rc ModeWebRadio::remOK() {
    deebug("web radio mode", "remOK() is going to masquerade as a rePress");
    return rePress();
}

uint8_rc ModeWebRadio::remCircleLeft() {
    deebug("web radio mode", "remCircleLeft() is going to masquerade as a reCcw");
    return reCcw();
}

uint8_rc ModeWebRadio::remCircleRight() {
    deebug("web radio mode", "remCircleRight() is going to masquerade as a reCw");
    return reCw();
}

uint8_rc ModeWebRadio::remRewind() {
    deebug("web radio mode", "going back a station");
    if (current_station_index == 0)
        return 1;
    kerl.client.stop();
    --current_station_index;
}

uint8_rc ModeWebRadio::remFastForward() {
    deebug("web radio mode", "going forward a station");
    if (current_station_index == (NUM_WEBSTATIONS - 1))
        return 1;
    kerl.client.stop();
    ++current_station_index;
}

uint8_rc ModeWebRadio::remVolumeUp() {
    if (volume == MAX_WEBRADIO_VOLUME)
        return 1;
    deebug("web radio mode", "turning volume up");
    ++volume;
    vica.setVolume(volume);
}

uint8_rc ModeWebRadio::remVolumeDown() {
    deebug("MWR", "volume down");
    if (volume == 0)
        return 1;
    deebug("web radio mode", "turning volume down");
    --volume;
    vica.setVolume(volume);
}

// TODO TODO TODO: have it display error message (if there's an error)
uint8_rc ModeWebRadio::display() {
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

