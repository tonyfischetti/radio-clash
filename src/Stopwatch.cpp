
#include "Stopwatch.h"

Stopwatch::Stopwatch(uint64_rc _expiry) :
    began  {millis()},
    expiry {_expiry} {
}

bool Stopwatch::hasExpired() {
    if (expired_p)
        return expired_p;
    const uint64_rc now {millis()};
    if ((now - began) >= expiry)
        expired_p = true;
    return expired_p;
}

void Stopwatch::reset() {
    began = millis();
    expired_p = false;
}


