
#include "LBMode.h"


LBMode::LBMode() { }

const char* LBMode::getModeName() {
    deebug("lbmode", "getModeName()");
    return mode_name;
}

const bool LBMode::isAudioNeeder() {
    return false;
}

uint8_t LBMode::engage() {
    deebug("lbmode", "engage()");
    return false;
}

uint8_t LBMode::suspend() {
    deebug("lbmode", "suspend()");
    return false;
}

uint8_t LBMode::tick() {
    deebug("lbmode", "tick()");
    return false;
}

uint8_t LBMode::reCw() {
    deebug("lbmode", "reCw()");
    return false;
}

uint8_t LBMode::reCcw() {
    deebug("lbmode", "reCcw()");
    return false;
}

uint8_t LBMode::rePress() {
    deebug("lbmode", "rePress()");
    return false;
}

uint8_t LBMode::remOK() {
    deebug("lbmode", "remOK()");
    return false;
}

uint8_t LBMode::remBack() {
    deebug("lbmode", "remBack()");
    return false;
}

uint8_t LBMode::remHome() {
    deebug("lbmode", "remHome()");
    return false;
}

uint8_t LBMode::remCircleLeft() {
    deebug("lbmode", "remCircleLeft()");
    return false;
}

uint8_t LBMode::remCircleRight() {
    deebug("lbmode", "remCircleRight()");
    return false;
}

uint8_t LBMode::remMute() {
    deebug("lbmode", "remMute()");
    return false;
}

uint8_t LBMode::remCircleUp() {
    deebug("lbmode", "remCircleUp()");
    return false;
}

uint8_t LBMode::remCircleDown() {
    deebug("lbmode", "remCircleDown()");
    return false;
}

uint8_t LBMode::remAsterisk() {
    deebug("lbmode", "remAsterisk()");
    return false;
}

uint8_t LBMode::remRewind() {
    deebug("lbmode", "remRewind()");
    return false;
}

uint8_t LBMode::remPlayPause() {
    deebug("lbmode", "remPlayPause()");
    return false;
}

uint8_t LBMode::remFastForward() {
    deebug("lbmode", "remFastForward()");
    return false;
}

uint8_t LBMode::remVolumeUp() {
    deebug("lbmode", "remVolumeUp()");
    return false;
}

uint8_t LBMode::remVolumeDown() {
    deebug("lbmode", "remVolumeDown()");
    return false;
}

uint8_t LBMode::remChannelUp() {
    deebug("lbmode", "remChannelUp()");
    return false;
}

uint8_t LBMode::remChannelDown() {
    deebug("lbmode", "remChannelDown()");
    return false;
}

uint8_t LBMode::remNetflix() {
    deebug("lbmode", "remNetflix()");
    return false;
}

uint8_t LBMode::remHulu() {
    deebug("lbmode", "remHulu()");
    return false;
}

uint8_t LBMode::display() {
    deebug("lbmode", "display()");
    return false;
}

