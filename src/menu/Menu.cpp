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

const uint8_t Digits[10][10] PROGMEM =
{
  {7,8,10,11,14,18,22,24},
  {14,16,18,22,24},
  {7,8,9,11,14,16,18,24},
  {7,9,11,14,16,18,22,24},
  {9,10,11,16,18,22,24},
  {7,9,10,11,14,16,18,22},
  {7,8,9,14,15,16,18,22},
  {7,11,14,16,17,24},
  {7,8,9,10,11,14,16,18,22,24},
  {7,9,10,11,14,16,17,24},
};

const uint8_t DigitsShifted[10][10] PROGMEM =
{
  {1,2,4,5,8,18,16,12},
  {8,18,10,8,12},
  {1,12,16,10,3,4,5,8},
  {1,12,16,10,3,18,8,5},
  {1,2,3,10,16,18,8},
  {12,1,2,3,10,18,8,5},
  {1,2,3,4,5,8,18,10,12},
  {1,12,16,10,9,5},
  {1,2,3,4,5,8,18,10,16,12},
  {1,2,3,5,8,18,10,16,12},
};

void Menu::displayNumber(int place, int number, CRGB c) {

    for (int i = 0; i < 10; i++) {
        uint8_t pos1 = pgm_read_byte(&Digits[number / 10][i]);
        uint8_t pos2 = pgm_read_byte(&Digits[number % 10][i]);

        if (pos1 != 0) {
            leds[(pos1 + place)] = c;
        }
        if (pos2 != 0) {
            leds[(pos2 + 28 + place)] = c; 
        }
    }
}

void Menu::displayLongNumber(int place, int number, CRGB c) {

    int hundreds = (number / 100) % 10;
    int tens = (number / 10) % 10;
    int units = number % 10;

    for (int i = 0; i < 10; i++) {
        uint8_t posH = pgm_read_byte(&DigitsShifted[hundreds][i]);
        uint8_t posT = pgm_read_byte(&DigitsShifted[tens][i]);
        uint8_t posU = pgm_read_byte(&DigitsShifted[units][i]);

        if ((number >= 100 ) && posH != 0) {
            leds[(posH + place)] = c;
        }

        if ((number >= 10 ) && posT != 0) {
            leds[(posT + 28 + place)] = c; 
        }

        if (posU != 0) {
            leds[(posU + 56 + place)] = c; 
        }
    }
}

void (Menu::*Menu::animationList[])() = {
    &Menu::rainbow,
    &Menu::police
};

const int Menu::animationListCount = sizeof(Menu::animationList)/sizeof(Menu::animationList[0]);

#define NUM_LEDS 128

void Menu::rainbow(){
    static uint8_t hue = 0;

    // Built-in FastLED function to fill strip with changing colors
    fill_rainbow(leds, NUM_LEDS, hue++, 7);
}
void Menu::police(){
    static uint8_t step = 0;
  
  // Clear strip
  fill_solid(leds, NUM_LEDS, CRGB::Black);

  // Blink logic based on frame count
  if ((step / 5) % 2 == 0) {
    // Left side Red
    fill_solid(leds, NUM_LEDS / 2, CRGB::Red);
  } else {
    // Right side Blue
    fill_solid(leds + (NUM_LEDS / 2), NUM_LEDS / 2, CRGB::Blue);
  }
  
  step++;
}