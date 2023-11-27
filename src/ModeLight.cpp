
#include "ModeLight.h"


ModeLight::ModeLight(Phos& _phos, Sixteen& _sixteen)
    : phos                  {_phos},
      sixteen               {_sixteen} {
      // playlist_select_time  {0} {
}

const char* ModeLight::getModeName() const {
    return mode_name;
}

const bool ModeLight::isAudioNeeder() const {
    return false;
}


uint8_t ModeLight::engage() {
    deebug("light mode", "engaging");
    return true;
}

uint8_t ModeLight::suspend() {
    deebug("light mode", "suspending");
    return true;
}

uint8_t ModeLight::tick() {

    return 0;
}


uint8_t ModeLight::display() {
    snprintf(sixteen.line0, 17, "Light Mode");
    sixteen.update();
    return true;
}

