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

void Menu::displayNumber(int place, int number, CRGB c) {
    // Diagnostyka: Co my tu właściwie wyświetlamy?
    Serial.print("DEBUG: Number=");
    Serial.print(number);
    Serial.print(" Digit1_Idx=");
    Serial.print(number / 10);
    Serial.print(" Digit2_Idx=");
    Serial.println(number % 10);

    Serial.print("READING: "); // Zobaczymy jakie LEDy chce zapalić

    for (int i = 0; i < 10; i++) {
        // Pobieramy bajt z PROGMEM
        uint8_t pos1 = pgm_read_byte(&Digits[number / 10][i]);
        uint8_t pos2 = pgm_read_byte(&Digits[number % 10][i]);
        
        // WYPISZ WARTOŚCI NA SERIAL - to nam powie prawdę
        Serial.print("["); Serial.print(pos1); Serial.print("|"); Serial.print(pos2); Serial.print("] ");

        if (pos1 != 0) {
            leds[(pos1 + place)] = c;
        }
        if (pos2 != 0) {
            leds[(pos2 + 28 + place)] = c; // Sprawdź czy offset 28 jest na pewno dobry dla Twojego paska!
        }
    }
    Serial.println(); // Nowa linia po pętli
}