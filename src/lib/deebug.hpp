
#pragma once

#include <cstdarg>
#include <cstdio>
#include <Arduino.h>

#ifdef DEBUG
    #define deebug(...) secret_debug_helper(__VA_ARGS__)
#else
    #define deebug(...) (void)0
#endif

static void secret_debug_helper(const char* mod_name, const char* fmt, ...) {
    va_list vargs;
    va_start(vargs, fmt);
    printf("%-9ld%-17s", millis(), mod_name);
    vprintf(fmt, vargs);
    printf("\n");
}

