#pragma once
#include <Adafruit_SSD1306.h>
#include <DHT.h>

extern Adafruit_SSD1306 display;
extern DHT dht;
extern bool currentScreen;

void initDisplay();
void showWeather();
void drawAlternateScreen();
void handleButton();