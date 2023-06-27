
#ifndef webstation_h
#define webstation_h


typedef struct WebStation {
    const char* name;
    const char* host;
    const char* path;
    const uint16_t port;
} WebStation;

#endif
