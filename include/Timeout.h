
#pragma once

#include "common.h"

struct Timeout {

    Timeout(uint64_rc); 
    bool hasExpired();
    void reset();
    void expire();

  private:
    uint64_rc began;
    const uint64_rc expiry;
    bool expired_p {true};
};
