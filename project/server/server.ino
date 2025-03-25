#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <WiFiMulti.h>

const char *ssid = "Galaxy M12 250A";
const char *password = "oyxe8115";

WiFiMulti wifiMulti;
WebServer server(80);

int counter = 0;

#define LED_BUILTIN 2

void handleRoot() {
    digitalWrite(LED_BUILTIN, HIGH);
    server.send(200, "text/plain", String(counter));
    ++counter;
    digitalWrite(LED_BUILTIN, LOW);
}

void handleNotFound() {
    digitalWrite(LED_BUILTIN, HIGH);
    server.send(200, "text/plain", "Only crickets here.");
    digitalWrite(LED_BUILTIN, LOW);
}

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(115200);
    Serial.println("\n\n:-----: New session :-----:\n");
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    wifiMulti.addAP(ssid, password);
    wifiMulti.addAP("MoE Wi-Fi"); // fallback

    if (MDNS.begin("esp32")) {
        Serial.println("MDNS responder started.");
    }

    server.on("/", handleRoot);

    server.onNotFound(handleNotFound);

    server.begin();
    Serial.println("HTTP server started.");
}

void loop() {
    if (wifiMulti.run() == WL_CONNECTED) {
        Serial.println(String("Connected to ") + WiFi.SSID() + ".");
        Serial.println(String("BSSID: ") + WiFi.BSSIDstr());
        server.handleClient();
    }
    delay(1000);
}
