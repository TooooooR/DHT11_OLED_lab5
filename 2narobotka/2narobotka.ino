#include <Arduino.h>
#include "Display.h"
#include "Weather.h"

unsigned long lastWeatherUpdate = 0;
unsigned long weatherUpdateInterval = 60000;  // 1 хв

void setup() {
  Serial.begin(115200);
  initWiFi();
  initDisplay();
  fetchWeather();
  showWeather();
}

void loop() {
  handleButton();

  if (millis() - lastWeatherUpdate >= weatherUpdateInterval) {
    fetchWeather();
    lastWeatherUpdate = millis();
    Serial.println("Weather updated in background");
    showWeather();
  }

  static unsigned long lastUpdate = 0;
  if (currentScreen && millis() - lastUpdate > 2000) {
    drawAlternateScreen();
    lastUpdate = millis();
  }

  delay(10);
}
