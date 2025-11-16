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
enum MenuSubScreen {COLOR, CURRENT_TIME};

class Menu {
private:
    Keypad* keypad;
    DS1307* RTC;
    CRGB (&leds)[128];

    int fotresistorPin;
    int errorLedPin;

    MenuScreen currentScreen = TIME;
    MenuSubScreen currentSubScreen = CURRENT_TIME;      

    TimeStruct currentTime;
    DateStruct currentDate;

    String inputBuffer = "";

    bool isAutoBrightness = true;
    bool isBacklightOn = false;
    bool isBacklightrainbow = false;

    int currentAnimationIndex = 0;

    bool isSubmenu = false;
    bool isEditing = false;

    void displayScreen();

public:

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
