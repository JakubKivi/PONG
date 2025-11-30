#ifndef MENU_H
#define MENU_H

#include <Arduino.h>
#include <Wire.h>
#include <Keypad.h>
#include <I2C_RTC.h>
#include <fastled.h>
#include "logic/TimeStruct.h"
#include "logic/DateStruct.h"

enum MenuScreen { TIME, SETTINGS, GAME, ANIMATIONS};
enum MenuSubScreen {COLOR, BRIGHTNESS, CURRENT_TIME};

class Menu {
private:
    Keypad* keypad;
    DS1307* RTC;
    CRGB (&leds)[128];

    int fotresistorPin;
    int errorLedPin;

    MenuScreen currentScreen = TIME;
    MenuSubScreen currentSubScreen = COLOR;    
    bool isSubmenu = false;  

    TimeStruct currentTime;
    DateStruct currentDate;

    String inputBuffer = "";

    bool isAutoBrightness = false;  //TODO zmienić na true!!!!!!!!!!
    bool isBacklightOn = false;
    bool isBacklightAnimation = false;

    int currentAnimationIndex = 0;

    CRGB currenColor = CRGB::White;
    int currentInputColorIndex =0;

    unsigned long lastUpdate_Time = 0;
    unsigned long lastUpdate_Fotoresistor = 0; // 1 minute

    int manualBrightness = 15;

    void displayScreen();


public:
    void displayNumber( int place , int number, CRGB c);

    Menu(Keypad* keypad,DS1307* RTC, CRGB (&leds)[128], int fotresistorPin, int errorLedPin);

    void updateTime();
    void update(char key);

    MenuScreen getCurrentScreen() const;

    TimeStruct getCurrentTime() const;
    void setCurrentTime(TimeStruct input, bool updateRTC);

    DateStruct getCurrentDate() const;
    void setCurrentDate(DateStruct input, bool updateRTC);

    void showErrorLed(int number, bool loop);
};

#endif
