#include "Menu.h"
#include "Arduino.h"



Menu::Menu(Keypad* keypad, DS1307* RTC, CRGB (&leds)[128], int fotresistorPin, int errorLedPin)
    : keypad(keypad), RTC(RTC), leds(leds), fotresistorPin(fotresistorPin), errorLedPin(errorLedPin){
    pinMode(fotresistorPin, INPUT);
    pinMode(errorLedPin, OUTPUT);
    digitalWrite(errorLedPin, LOW);
}


void Menu::updateTime(){
    // Update current time and date from RTC
    tm now = RTC->getDateTime();
    currentTime.hour = now.tm_hour;
    currentTime.minute = now.tm_min;
    currentDate.day = now.tm_mday;
    currentDate.month = now.tm_mon;
    currentDate.year = now.tm_year + 1900;

    displayScreen();
}

void Menu::update(char key){  
    Serial.print("Key pressed: ");
    Serial.println(key);       
    if (isSubmenu)
    {
        /* code */
    }else if(isEditing){

    }else{
        if(key=='D'){
            currentScreen = static_cast<MenuScreen>((currentScreen + 1) % 4);
            return;
        }
        if (currentScreen==TIME)
        {
            switch (key)
            {
                case 'A':
                    isAutoBrightness= !isAutoBrightness;
                    break;
                case 'B':
                    isBacklightOn = !isBacklightOn;
                    break;
                case 'C':
                    isBacklightrainbow = !isBacklightrainbow;
                    break;  
                default:
                    break;
            }
        }else if (currentScreen==SETTINGS){
            switch (key)
            {
                case 'A':
                    isSubmenu = true;
                    currentSubScreen = CURRENT_TIME;
                break;   
                default:
                    break;
            }  
        }else if (currentScreen==GAME){
            switch (key)
            {        
                default:
                    break;
            }   
        }else if (currentScreen==ANIMATIONS){
            switch (key)
            {
                case 'A':
                    currentAnimationIndex += 1;
                    break;   
                case 'B':
                    currentAnimationIndex>0 ? currentAnimationIndex -= 1 : currentAnimationIndex = 0;                    
                    break;
                case 'C':
                    break;
                case '*':
                    currentAnimationIndex = inputBuffer.toInt();
                    inputBuffer = "";
                    break;
                case '#':
                    inputBuffer = "";
                    break;
                default:
                    inputBuffer += key;
                    break;
            }   
        }           
    }    
}


void Menu::displayScreen(){
    if (isSubmenu)
    {
        /* code */
    }
    
    switch (currentScreen)
    {
        case TIME:
            Serial.print("Time:");
            Serial.print(currentTime.hour);
            Serial.print(":");  
            Serial.print(currentTime.minute);
            Serial.print("       ");
            Serial.print("autoBrightness:");
            Serial.print(isAutoBrightness ? "ON":"OFF");
            Serial.print("  backlight:");
            Serial.print(isBacklightOn ? "ON":"OFF");
            Serial.print("  rainbow:");
            Serial.println(isBacklightrainbow ? "ON":"OFF");
            break;
        case SETTINGS:
            Serial.println("Settings Menu");
            break;
        case GAME:
            Serial.println("Game Menu");
            break;     
        case ANIMATIONS:
            Serial.print("Showing Animation: ");
            Serial.print(currentAnimationIndex);
            Serial.print("  InputBuffer: ");
            Serial.println(inputBuffer);
        default:
            break;
    }
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