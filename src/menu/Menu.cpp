#include "Menu.h"

Menu::Menu(Keypad* keypad, DS1307* RTC, CRGB (&leds)[128], int fotresistorPin, int errorLedPin)
    : keypad(keypad), RTC(RTC), leds(leds), fotresistorPin(fotresistorPin), errorLedPin(errorLedPin){
    pinMode(fotresistorPin, INPUT);
    pinMode(errorLedPin, OUTPUT);
    digitalWrite(errorLedPin, LOW);
    
}


MenuScreen Menu::getCurrentScreen() const{ 
    return currentScreen;
}

TimeStruct Menu::getCurrentTime() const{
    return currentTime;
}

void Menu::setCurrentTime(TimeStruct input, bool updateRTC){
    if(updateRTC){
        RTC->setTime(input.hour,input.minute,0);
        RTC->startClock();
    }
    currentTime = input;
}

DateStruct Menu::getCurrentDate() const{
    return currentDate;
}

void Menu::setCurrentDate(DateStruct input, bool updateRTC){
    if(updateRTC){
        RTC->setDate(input.day, input.month, input.year);
        RTC->startClock();
    }
    currentDate = input;
}

void Menu::showErrorLed(int number, bool loop){
    do{
        for(int i=0; i<number; i++){
            digitalWrite(errorLedPin, HIGH);
            delay(200);
            digitalWrite(errorLedPin, LOW);
            delay(200);
        }
        if(loop){
            delay(2000);
        }
    }while(loop);
}