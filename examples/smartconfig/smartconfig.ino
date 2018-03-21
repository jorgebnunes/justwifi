/*
 *  This sketch trys to Connect to the best AP based on a given list
 *
 */

#include <JustWifi.h>
#include <ESP8266WiFi.h>

void setup() {

    Serial.begin(115200);
    delay(10);

    // Debug message callback
    jw.subscribe([](justwifi_messages_t code, char * parameter) {

        if (code == MESSAGE_SCANNING) {
            Serial.printf("[WIFI] Scanning\n");
        }

        if (code == MESSAGE_SCAN_FAILED) {
            Serial.printf("[WIFI] Scan failed\n");
        }

        if (code == MESSAGE_NO_NETWORKS) {
            Serial.printf("[WIFI] No networks found\n");
        }

        if (code == MESSAGE_NO_KNOWN_NETWORKS) {
            Serial.printf("[WIFI] No known networks found\n");
        }

        if (code == MESSAGE_FOUND_NETWORK) {
            Serial.printf("[WIFI] %s\n", parameter);
        }

        if (code == MESSAGE_CONNECTING) {
            Serial.printf("[WIFI] Connecting to %s\n", parameter);
        }

        if (code == MESSAGE_CONNECT_WAITING) {
            // too much noise
        }

        if (code == MESSAGE_CONNECT_FAILED) {
            Serial.printf("[WIFI] Could not connect to %s\n", parameter);
        }

        if (code == MESSAGE_CONNECTED) {

            uint8_t * bssid = WiFi.BSSID();

            Serial.printf("[WIFI] MODE STA -------------------------------------\n");
            Serial.printf("[WIFI] SSID  %s\n", WiFi.SSID().c_str());
            Serial.printf("[WIFI] BSSID %02X:%02X:%02X:%02X:%02X:%02X\n",
                bssid[0], bssid[1], bssid[2], bssid[3], bssid[4], bssid[5], bssid[6]
            );
            Serial.printf("[WIFI] CH    %d\n", WiFi.channel());
            Serial.printf("[WIFI] RSSI  %d\n", WiFi.RSSI());
            Serial.printf("[WIFI] IP    %s\n", WiFi.localIP().toString().c_str());
            Serial.printf("[WIFI] MAC   %s\n", WiFi.macAddress().c_str());
            Serial.printf("[WIFI] GW    %s\n", WiFi.gatewayIP().toString().c_str());
            Serial.printf("[WIFI] MASK  %s\n", WiFi.subnetMask().toString().c_str());
            Serial.printf("[WIFI] DNS   %s\n", WiFi.dnsIP().toString().c_str());
            Serial.printf("[WIFI] HOST  %s\n", WiFi.hostname().c_str());
            Serial.printf("[WIFI] ----------------------------------------------\n");

        }

        if (code == MESSAGE_ACCESSPOINT_CREATED) {

            Serial.printf("[WIFI] MODE AP --------------------------------------\n");
            Serial.printf("[WIFI] SSID  %s\n", jw.getAPSSID().c_str());
            Serial.printf("[WIFI] IP    %s\n", WiFi.softAPIP().toString().c_str());
            Serial.printf("[WIFI] MAC   %s\n", WiFi.softAPmacAddress().c_str());
            Serial.printf("[WIFI] ----------------------------------------------\n");

        }

        if (code == MESSAGE_DISCONNECTED) {
            Serial.printf("[WIFI] Disconnected\n");
        }

        if (code == MESSAGE_ACCESSPOINT_CREATING) {
            Serial.printf("[WIFI] Creating access point\n");
        }

        if (code == MESSAGE_ACCESSPOINT_FAILED) {
            Serial.printf("[WIFI] Could not create access point\n");
        }

        if (code == MESSAGE_SMARTCONFIG_START) {
            Serial.printf("[WIFI] Smart config start\n");
        }

        if (code == MESSAGE_SMARTCONFIG_END) {
            Serial.printf("[WIFI] Smart config end\n");
        }

    });

    jw.smartconfig();

}

void loop() {

    // This call takes care of it all
    jw.loop();

    // Small delay to give some breath
    delay(10);

}
