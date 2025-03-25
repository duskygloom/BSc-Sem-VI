#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>

WiFiMulti wifiMulti;

void setup() {
    Serial.begin(115200);
    Serial.println("\n\n:-----: New session :-----:\n");

    wifiMulti.addAP("Galaxy M12 250A", "oyxe8115");
    wifiMulti.addAP("MoE Wi-Fi"); // fallback
}

void loop() {
    if((wifiMulti.run() == WL_CONNECTED)) {
        Serial.println(String("Connected to ") + WiFi.SSID());
        Serial.println(String("BSSID: ") + WiFi.BSSIDstr());
        HTTPClient http;
        http.begin("http://esp32.local");
        int httpCode = http.GET();
        if(httpCode > 0) {
            if(httpCode == HTTP_CODE_OK) {
                Serial.println(String("Payload: ") + http.getString());
            }
        } else {
            Serial.println(http.errorToString(httpCode));
        }
        http.end();
    }
    delay(2000);
}
