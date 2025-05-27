#include "Weather.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "Redmi Note 8 Pro";
const char* password = "t1a2r3a4s55";
const char* apiKey = "18c45cb3fe1d3899035662b82198cdf6";

float temperature = 0.0;
int humidity = 0;
String description = ""; 

void initWiFi() {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }
}

void fetchWeather() {
    if (WiFi.status() == WL_CONNECTED) {
        WiFiClient client;
        HTTPClient http;
        String url = "http://api.openweathermap.org/data/2.5/weather?lat=49.842957&lon=24.031111&appid=" + String(apiKey) + "&units=metric";
        http.begin(client, url);

        int httpCode = http.GET();
        if (httpCode > 0) {
            String payload = http.getString();
            StaticJsonDocument<1024> doc;
            deserializeJson(doc, payload);
            temperature = doc["main"]["temp"];
            humidity = doc["main"]["humidity"];
            description = doc["weather"][0]["description"].as<String>();
        }

        http.end();
    }
}

