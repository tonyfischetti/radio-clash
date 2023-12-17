
#pragma once

#include "deebug.hpp"
#include "common.h"

#include <SPI.h>
#include <WiFi.h>
#include <WiFiClient.h>

#include "WifiCredential.h"
#include "WebStation.h"


static constexpr uint16_rc KERL_CONNECTION_TIMEOUT {60000};


class Kerl {
    public:
        Kerl(const uint8_rc, const WifiCredential*)             noexcept;
        void init()                                             noexcept;
        uint8_rc connectWebKeepAlive()                          noexcept;
        uint8_rc connectToAnyNetwork()                          noexcept;
        void disconnect()                                       noexcept;
        uint8_rc connectClientKeepAlive(const WebStation*)      noexcept;

        WiFiClient client;

    private:
        const uint8_rc num_wifi_credentials;
        const WifiCredential* WIFI_CREDENTIALS;
        uint8_rc connected_p;
        uint8_rc using_index;
};

