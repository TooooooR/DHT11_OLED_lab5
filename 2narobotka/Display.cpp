#include "Display.h"
#include "Weather.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define DHTPIN D5
#define DHTTYPE DHT11
const int8_t button = D7;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
DHT dht(DHTPIN, DHTTYPE);
bool currentScreen = false;

bool lastButtonState = LOW;
unsigned long debounceDelay = 200;

void initDisplay() {
    pinMode(button, INPUT_PULLUP);
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("Init OLED OK");
    display.display();
    delay(1000);
    dht.begin();
}

void showWeather() {
    extern float temperature;
    extern int humidity;
    extern String description;

    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("Weather in Lviv:");
    display.printf("Temp: %.1f C\n", temperature);
    display.printf("Humidity: %d%%\n", humidity);
    display.println(description);
    display.display();
    Serial.println("Displayed weather");
}

void drawAlternateScreen() {
    float temp = dht.readTemperature();
    float hum = dht.readHumidity();

    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(1);

    if (isnan(temp) || isnan(hum)) {
        display.println("Error reading DHT11");
    } else {
        display.println("Sensor:");
        display.printf("Temp: %.1f C\n", temp);
        display.printf("Humidity: %.1f%%", hum);
    }

    display.display();
}

void handleButton() {
    bool reading = digitalRead(button);

    if (reading == HIGH && lastButtonState == LOW) {
        currentScreen = !currentScreen;
        if (currentScreen)
            drawAlternateScreen();
        else
            showWeather();
        delay(debounceDelay);
    }

    lastButtonState = reading;
}
