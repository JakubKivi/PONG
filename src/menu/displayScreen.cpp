#include "Menu.h"

void Menu::displayScreen(){
    if (isSubmenu)
    {
        if (currentSubScreen == COLOR)
        {
            leds[getLedIndex(0,7)] = currentColor;
            leds[getLedIndex(0,8)] = currentColor;
            leds[getLedIndex(0,9)] = currentColor;
            
            leds[getLedIndex(6,6)] = CRGB(255,0,0);
            leds[getLedIndex(6,8)] = CRGB(0,255,0);
            leds[getLedIndex(6,10)] = CRGB(0,0,255);

            if(inputBuffer==""){
                if (millis() - lastBlinking_Time > 400)
                {
                    lastBlinking_Time = millis();
                    blinkState = !blinkState;
                }         
                if (blinkState){
                    switch (currentInputColorIndex)
                    {
                    case 0:
                        leds[getLedIndex(6,6)] = CRGB::Black;
                        displayLongNumber(0, currentColor.r, CRGB(255,0,0));
                        break;
                    case 1:
                        leds[getLedIndex(6,8)] = CRGB::Black;
                        displayLongNumber(0, currentColor.g, CRGB(0,255,0));
                        break;
                    case 2:
                        leds[getLedIndex(6,10)] = CRGB::Black;
                        displayLongNumber(0, currentColor.b, CRGB(0,0,255));
                        break;
                    default:
                        break;
                    }
                }
            }else{
                switch (currentInputColorIndex)
                {
                case 0:
                    displayLongNumber(0, inputBuffer.toInt(), CRGB(255,0,0));
                    break;
                case 1:
                    displayLongNumber(0, inputBuffer.toInt(), CRGB(0,255,0));
                    break;
                case 2:
                    displayLongNumber(0, inputBuffer.toInt(), CRGB(0,0,255));
                    break;
                default:
                    break;
                }
            }
            
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
                if (millis() - lastBlinking_Time > 1000)
                {
                    lastBlinking_Time = millis();
                    blinkState = !blinkState;
                }
                if(blinkState){
                    leds[64] = CRGB::Black;
                    leds[66] = CRGB::Black;     

                }else{
                    leds[64] = currentColor;
                    leds[66] = currentColor;     
                }    
                displayNumber(0, currentTime.hour, currentColor);
                displayNumber(70, currentTime.minute, currentColor);// Serial.println(String(currenColor.r)+"," + String(currenColor.g) + "," + String(currenColor.b));
                break;
            case SETTINGS:
                leds[getLedIndex(0,7)] = currentColor;
                leds[getLedIndex(0,8)] = currentColor;
                leds[getLedIndex(0,9)] = currentColor;

                leds[getLedIndex(1,6)] = currentColor;
                leds[getLedIndex(1,11)] = currentColor;

                leds[getLedIndex(2,6)] = currentColor;
                leds[getLedIndex(2,12)] = currentColor;
                
                leds[getLedIndex(4,6)] = currentColor;
                leds[getLedIndex(4,12)] = currentColor;

                leds[getLedIndex(5,6)] = currentColor;
                leds[getLedIndex(5,11)] = currentColor;

                leds[getLedIndex(6,7)] = currentColor;
                leds[getLedIndex(6,8)] = currentColor;
                leds[getLedIndex(6,9)] = currentColor;
                break;   
            case ANIMATIONS:
                Serial.print("Showing Animation: ");










                Serial.println(currentAnimationIndex);
            default:
                break;
        }
    }
    
    
}