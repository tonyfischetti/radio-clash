
#include "LBMode.h"


LBMode::LBMode() { }

const char* LBMode::getModeName() const {
    deebug("lbmode", "getModeName()");
    return mode_name;
}

bool LBMode::isAudioNeeder() const {
    return false;
}

uint8_rc LBMode::engage() {
    deebug("lbmode", "engage()");
    return false;
}

uint8_rc LBMode::suspend() {
    deebug("lbmode", "suspend()");
    return false;
}

uint8_rc LBMode::tick() {
    deebug("lbmode", "tick()");
    return false;
}

uint8_rc LBMode::reCw() {
    deebug("lbmode", "reCw()");
    return false;
}

uint8_rc LBMode::reCcw() {
    deebug("lbmode", "reCcw()");
    return false;
}

uint8_rc LBMode::rePress() {
    deebug("lbmode", "rePress()");
    return false;
}

uint8_rc LBMode::remOK() {
    deebug("lbmode", "remOK()");
    return false;
}

uint8_rc LBMode::remBack() {
    deebug("lbmode", "remBack()");
    return false;
}

uint8_rc LBMode::remHome() {
    deebug("lbmode", "remHome()");
    return false;
}

uint8_rc LBMode::remCircleLeft() {
    deebug("lbmode", "remCircleLeft()");
    return false;
}

uint8_rc LBMode::remCircleRight() {
    deebug("lbmode", "remCircleRight()");
    return false;
}

uint8_rc LBMode::remMute() {
    deebug("lbmode", "remMute()");
    return false;
}

uint8_rc LBMode::remCircleUp() {
    deebug("lbmode", "remCircleUp()");
    return false;
}

uint8_rc LBMode::remCircleDown() {
    deebug("lbmode", "remCircleDown()");
    return false;
}

uint8_rc LBMode::remAsterisk() {
    deebug("lbmode", "remAsterisk()");
    return false;
}

uint8_rc LBMode::remRewind() {
    deebug("lbmode", "remRewind()");
    return false;
}

uint8_rc LBMode::remPlayPause() {
    deebug("lbmode", "remPlayPause()");
    return false;
}

uint8_rc LBMode::remFastForward() {
    deebug("lbmode", "remFastForward()");
    return false;
}

uint8_rc LBMode::remVolumeUp() {
    deebug("lbmode", "remVolumeUp()");
    return false;
}

uint8_rc LBMode::remVolumeDown() {
    deebug("lbmode", "remVolumeDown()");
    return false;
}

uint8_rc LBMode::remChannelUp() {
    deebug("lbmode", "remChannelUp()");
    return false;
}

uint8_rc LBMode::remChannelDown() {
    deebug("lbmode", "remChannelDown()");
    return false;
}

uint8_rc LBMode::remNetflix() {
    deebug("lbmode", "remNetflix()");
    return false;
}

uint8_rc LBMode::remHulu() {
    deebug("lbmode", "remHulu()");
    return false;
}

uint8_rc LBMode::display() {
    deebug("lbmode", "display()");
    return false;
}

