#include "Menu.h"

void Menu::displayScreen(){
    if (isSubmenu)
    {
        if (currentSubScreen == COLOR)
        {
            Serial.print("Color Submenu        ");
            Serial.println(String(currenColor.r)+"," + String(currenColor.g) + "," + String(currenColor.b));

        }else if(currentSubScreen == BRIGHTNESS){
            Serial.print("Brightness Submenu");
            Serial.print("       Manual Brightness:");
            Serial.println(manualBrightness);
            
        }else if (currentSubScreen == CURRENT_TIME)
        {
            Serial.print("Current Time Submenu");
            Serial.print("       Buffer:");
            Serial.println(inputBuffer);
        }
        
    }else{
        switch (currentScreen)
        {
            case TIME:
                displayNumber(0, currentTime.hour, currenColor);
                displayNumber(70, currentTime.minute, currenColor);// Serial.println(String(currenColor.r)+"," + String(currenColor.g) + "," + String(currenColor.b));
                break;
            case SETTINGS:
                leds[getLedIndex(0,8)] = currenColor;
                leds[getLedIndex(0,9)] = currenColor;
                leds[getLedIndex(0,10)] = currenColor;

                leds[getLedIndex(1,7)] = currenColor;
                leds[getLedIndex(1,12)] = currenColor;

                leds[getLedIndex(2,7)] = currenColor;
                leds[getLedIndex(2,13)] = currenColor;
                
                leds[getLedIndex(4,7)] = currenColor;
                leds[getLedIndex(4,13)] = currenColor;

                leds[getLedIndex(5,7)] = currenColor;
                leds[getLedIndex(5,12)] = currenColor;

                leds[getLedIndex(6,8)] = currenColor;
                leds[getLedIndex(6,9)] = currenColor;
                leds[getLedIndex(6,10)] = currenColor;
                break;   
            case ANIMATIONS:
                Serial.print("Showing Animation: ");
                Serial.println(currentAnimationIndex);
            default:
                break;
        }
    }
    
    
}