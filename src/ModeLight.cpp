
#include "ModeLight.h"


ModeLight::ModeLight(Phos& _phos, Sixteen& _sixteen)
    : phos                  {_phos},
      sixteen               {_sixteen} {
}

const char* ModeLight::getModeName() const {
    return mode_name;
}

bool ModeLight::isAudioNeeder() const {
    return false;
}


uint8_rc ModeLight::engage() {
    deebug("light mode", "engaging");
    return true;
}

uint8_rc ModeLight::suspend() {
    deebug("light mode", "suspending");
    return true;
}

uint8_rc ModeLight::tick() {

    return 0;
}


uint8_rc ModeLight::display() {
    snprintf(sixteen.line0, 17, "Light Mode");
    sixteen.update();
    return true;
}

