
#include "Kerl.h"


Kerl::Kerl(const uint8_rc _numwebcredentials,
           const WifiCredential* _wificredentials) noexcept
    : num_wifi_credentials {_numwebcredentials},
      WIFI_CREDENTIALS     {_wificredentials},
      connected_p          {0} {
    WiFiClient client;
}

void Kerl::init() noexcept {
    deebug("kerl", "initing...");
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    connected_p = 0;
}

void Kerl::disconnect() noexcept {
    deebug("kerl", "disconnecting");
    connected_p = 0;
    WiFi.disconnect();
}

// TODO: BLOCKING!!! BAD!!!! SPINNING!!!
uint8_rc Kerl::connectWebKeepAlive() noexcept {
    // deebug("kerl", "calling connectWebKeepAlive()");
    if (const uint8_rc wstatus = WiFi.status(); wstatus != WL_CONNECTED) {
        deebug("kerl", "  it's not connected!!");
        deebug("kerl", "  status code: +%d", wstatus);
        connected_p = 0;
        const uint64_rc began = millis();
        WiFi.begin(WIFI_CREDENTIALS[using_index].ssid,
                   WIFI_CREDENTIALS[using_index].pw);
        while (WiFi.status() != WL_CONNECTED) {
            if ((millis() - began) > KERL_CONNECTION_TIMEOUT) {
                deebug("kerl", "  timeout reached... returning error code");
                return 1;
            }
            // Serial.print(".");
            delay(100);
        }
        connected_p = 1;
        return 0;
    }
    return 0;
}

uint8_rc Kerl::connectToAnyNetwork() noexcept {
    deebug("kerl", "connectToAnyNetwork() called");
    const uint16_rc found = WiFi.scanNetworks();
    if (!found) {
        deebug("kerl", "  no networks found... returning error code");
        return 1;
    }
    deebug("kerl", "  found %d networks!", found);
    for (auto i = 0; i < found; i++) {
        std::string this_ssid = WiFi.SSID(i).c_str();
        deebug("kerl", "    checking -> %s", &this_ssid[0]);
        for (auto j = 0; j < num_wifi_credentials; j++) {
            if (!strcmp(&this_ssid[0], WIFI_CREDENTIALS[j].ssid)) {
                deebug("kerl", "    ! using %s", &this_ssid[0]);
                deebug("kerl", "    ! rssi: %4d", WiFi.RSSI(i));
                using_index = j;
                if (connectWebKeepAlive() > 0)
                    return 1;
                return 0;
            }
        }
    }
    deebug("kerl", "  fell through... returning error code");
    return 1;
}

uint8_rc Kerl::connectClientKeepAlive(const WebStation* astation) noexcept {
    if (!client.connected()) {
        deebug("kerl", "connectClientKeep... says 'not connected'");
        char* request;
        deebug("kerl", "  host: %s", astation->host);
        deebug("kerl", "  port: %d", astation->port);
        if (!client.connect(astation->host, astation->port)) {
            deebug("kerl", "could not connect... returning error code");
            return 1;
        }
        // dynamic memory allocation (without error checking) as a treat
        asprintf(&request, "GET %s HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n",
                 astation->path, astation->host);
        client.print(request);
        free(request);
    }
    return 0;
}

