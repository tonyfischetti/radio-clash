
#include "Timeout.h"

Timeout::Timeout(uint64_rc _expiry) :
    began  {millis()},
    expiry {_expiry} {
}

bool Timeout::hasExpired() {
    if (expired_p)
        return expired_p;
    const uint64_rc now {millis()};
    if ((now - began) >= expiry)
        expired_p = true;
    return expired_p;
}

void Timeout::reset() {
    began = millis();
    expired_p = false;
}

void Timeout::expire() {
    expired_p = true;
}

