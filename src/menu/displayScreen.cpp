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
                // Serial.print("Time:");
                // Serial.print(currentTime.hour);
                // Serial.print(":");  
                // Serial.print(currentTime.minute);
                // Serial.print("       ");
                // Serial.print("autoBrightness:");
                // Serial.print(isAutoBrightness ? "ON":"OFF");
                // Serial.print("  backlight:");
                // Serial.print(isBacklightOn ? "ON":"OFF");
                // Serial.print("  rainbow:");
                // Serial.print(isBacklightAnimation ? "ON":"OFF");
                // Serial.print("Color: ");
                // Serial.println(String(currenColor.r)+"," + String(currenColor.g) + "," + String(currenColor.b));
                break;
            case SETTINGS:
                Serial.println("Settings Menu");
                break;
            case GAME:
                Serial.println("Game Menu");
                break;     
            case ANIMATIONS:
                Serial.print("Showing Animation: ");
                Serial.println(currentAnimationIndex);
            default:
                break;
        }
    }
    
    
}