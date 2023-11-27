
#include "AudioController.h"


AudioController::AudioController(const uint8_rc _control_a,
                                 const uint8_rc _control_b) noexcept
    : MUX_CONTROL_A {_control_a},
      MUX_CONTROL_B {_control_b} {
}

void AudioController::init() noexcept {
    deebug("audio cntrl", "init-ing");
    pinMode(MUX_CONTROL_A, OUTPUT);
    pinMode(MUX_CONTROL_B, OUTPUT);
    digitalWrite(MUX_CONTROL_A, LOW);
    digitalWrite(MUX_CONTROL_B, LOW);
}

void AudioController::turnOnMP3Audio() noexcept {
    deebug("audio cntrl", "turning on MP3 audio");
    digitalWrite(MUX_CONTROL_A, LOW);
    digitalWrite(MUX_CONTROL_B, LOW);
}

void AudioController::turnOnWebRadioAudio() noexcept {
    deebug("audio cntrl", "turning on web radio audio");
    digitalWrite(MUX_CONTROL_A, HIGH);
    digitalWrite(MUX_CONTROL_B, LOW);
}

void AudioController::turnOnFMAudio() noexcept {
    deebug("audio cntrl", "turning on fm radio audio");
    digitalWrite(MUX_CONTROL_A, LOW);
    digitalWrite(MUX_CONTROL_B, HIGH);
}

