
#pragma once

#include <common.h>

struct Stopwatch {

    Stopwatch(uint64_rc); 
    bool hasExpired();
    void reset();

  private:
    uint64_rc began;
    const uint64_rc expiry;
    bool expired_p {false};
};
