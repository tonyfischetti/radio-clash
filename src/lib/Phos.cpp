
#include "Phos.h"


Phos::Phos(const uint8_t  _neopixel_pin,
           const uint8_t _num_neopixels)
    : pixels        {_num_neopixels, _neopixel_pin, NEO_GRBW + NEO_KHZ800},
      NUM_NEOPIXELS {_num_neopixels},
      is_engaged_p  {false},
      brightness    {255} {
}

void Phos::init() {
    deebug("phas", "calling init()");
    pixels.begin();
}

void Phos::displayUpdate() {
    while (!IrReceiver.isIdle()) { }
    pixels.show();
}

