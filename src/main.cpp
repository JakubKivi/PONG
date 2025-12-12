#include <Arduino.h>
#include <Wire.h>
#include <Keypad.h>
#include <fastled.h>
#include "logic/getLedIndex.h"

#include "menu/Menu.h"

#define LED_PIN     2
#define NUM_LEDS    128
#define BRIGHTNESS  255
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define UPDATES_PER_SECOND 100

#define FOTORESISTOR_PIN A1
#define ERROR_LED_PIN 13

static DS1307 RTC;

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns

char keys[ROWS][COLS] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'*','0','#', 'D'}
};
byte rowPins[ROWS] = {10, 9, 8, 7}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6, 5, 4, 3}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

CRGB leds[NUM_LEDS];

Menu menu(&keypad, &RTC, leds, FOTORESISTOR_PIN, ERROR_LED_PIN);

void setup()
{
    delay(1000); // Power-up safety delay
    Serial.begin(9600);
    Wire.begin();
    pinMode(ERROR_LED_PIN, OUTPUT);
    
    FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
    FastLED.setBrightness(BRIGHTNESS);

    RTC.begin();
    if (!RTC.isConnected())
    {
        Serial.println("RTC not connected!");
        menu.showErrorLed(1, true);
    }
    if (RTC.isConnected() && !RTC.isRunning())
    {
        Serial.println("RTC is NOT running. Starting now...");
        RTC.startClock();
        menu.showErrorLed(2, false);
    }
    tm now = RTC.getDateTime();
    menu.setCurrentTime(TimeStruct(now.tm_hour, now.tm_min), false);
    menu.updateBrightness();
    FastLED.setMaxRefreshRate(60); // Limit to 60 FPS
}

void loop()
{

    char key = keypad.getKey();

    if (key)
    {   
        digitalWrite(ERROR_LED_PIN, HIGH);
        delay(50);
        digitalWrite(ERROR_LED_PIN, LOW);
        menu.update(key);
    }

    menu.updateTime();

    
    FastLED.show();
    FastLED.clear();
}