
#include "Phos.h"


Phos::Phos(const uint8_rc  _neopixel_pin,
           const uint8_rc _num_neopixels)
    : pixels        {static_cast<uint16_t>(_num_neopixels),
                     static_cast<int16_t>(_neopixel_pin),
                     NEO_GRBW + NEO_KHZ800},
      NUM_NEOPIXELS {_num_neopixels} {
}

void Phos::init() {
    deebug("phas", "calling init()");
    pixels.begin();
}

void Phos::displayUpdate() {
    while (!IrReceiver.isIdle()) { }
    pixels.show();
}

void Phos::setPixelColor(const uint8_rc i) {
    // TODO: gamma?
    pixels.setPixelColor(i, current_rgbw[RED_INDEX],
                            current_rgbw[GREEN_INDEX],
                            current_rgbw[BLUE_INDEX],
                            current_rgbw[WHITE_INDEX]);
}

void Phos::displayRGBwColors() {
    for (uint8_rc i {0}; i < np_count; i++) {
        setPixelColor(i);
    }
    displayUpdate();
}

void Phos::turnOffPixels() {
    for (uint8_rc i {0}; i < np_count; i++) {
        pixels.setPixelColor(i, 0, 0, 0, 0);
    }
    displayUpdate();
}

void Phos::displayExactColor(const uint8_rc R, const uint8_rc G,
                             const uint8_rc B, const uint8_rc W) {
    current_rgbw[RED_INDEX]   = R;
    current_rgbw[GREEN_INDEX] = G;
    current_rgbw[BLUE_INDEX]  = B;
    current_rgbw[WHITE_INDEX] = W;
    displayRGBwColors();
}

void Phos::displayDot(const uint8_rc index, const bool mirror_p=true,
                      const bool project_p=true) {
    for (uint8_rc i {0}; i < np_count; i++) {
        if ((index == i) ||
            (project_p && ((i % 8) == index)) ||
            (mirror_p  && ((7 - i)  == index)) ||
            ((project_p && mirror_p) &&
             ((7 - index) == (i % 8)))) {
            setPixelColor(i);
        }
    }
    displayUpdate();
}

bool Phos::roomToGoP(const bool direction, const uint8_rc color_index) {
    if (direction)
        return (current_rgbw[color_index] <=
                  (max_brightnesses[color_index] - step_delta));
    else
        return (current_rgbw[color_index] >= step_delta);
}

void Phos::updateNPCount() {
    if (np_count == 8) {
        np_count = 16;
    }
    else if (np_count == 16) {
        np_count = 24;
    }
    else if (np_count == 24) {
        np_count = 32;
    }
    else {
        np_count = 8;
        for (byte i = np_count; i < NUM_NEOPIXELS; i++) {
            pixels.setPixelColor(i, 0, 0, 0, 0);
        }
        while (!IrReceiver.isIdle()) { }
        pixels.show();
    }
}

bool Phos::shiftColor(const bool direction, const uint8_rc color_index,
                      const bool reset_timer_p=true) {
    if (step_timer > step_delay) {
        if (roomToGoP(direction, color_index)) {
            if (direction)
                current_rgbw[color_index] = current_rgbw[color_index] +
                                              step_delta;
            else
                current_rgbw[color_index] = current_rgbw[color_index] -
                                              step_delta;
            displayRGBwColors();
            if (reset_timer_p)
                step_timer = 0;
            return true;
        }
        else
            return false;
    }
    // we have to assume there's more to go
    return true;
}

// first color goes up, second goes down
bool Phos::crossfadeColors(const uint8_rc color_goes_up,
                           const uint8_rc color_goes_down) {
    const bool more_up_p    {roomToGoP(UP, color_goes_up)};
    const bool more_down_p  {roomToGoP(DOWN, color_goes_down)};
    if (more_up_p || more_down_p) {
        if (step_timer > step_delay) {
            if (more_up_p)
                current_rgbw[color_goes_up] = current_rgbw[color_goes_up] +
                                                step_delta;
            if (more_down_p)
                current_rgbw[color_goes_down] = current_rgbw[color_goes_down] -
                                                  step_delta;
            displayRGBwColors();

            step_timer = 0;
        }
        return true;
    }
    return false;
}


