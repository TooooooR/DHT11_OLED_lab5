#ifndef WEATHER_H
#define WEATHER_H

#include <Arduino.h>

void initWiFi();
void fetchWeather();

extern float temperature;
extern int humidity;
extern String description;

#endif
