#include "Menu.h"

#define THREE_DIGIT_INDEX 27

#define RED_DOT_POSITION 1
#define GREEN_DOT_POSITION 0
#define BLUE_DOT_POSITION 5

#define CURRENT_COLOR_POSITION 125
#define CURRENT_COLOR_POSITION_2 126    
#define CURRENT_COLOR_POSITION_3 127

void Menu::displayScreen(){
    if (isSubmenu)
    {
        if (currentSubScreen == COLOR)
        {
            leds[CURRENT_COLOR_POSITION] = currentInputColor;
            leds[CURRENT_COLOR_POSITION_2] = currentInputColor;       \
            leds[CURRENT_COLOR_POSITION_3] = currentInputColor;
            
            leds[RED_DOT_POSITION] = CRGB::Red;
            leds[GREEN_DOT_POSITION] = CRGB::Green;         
            leds[BLUE_DOT_POSITION] = CRGB::Blue;

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
                        leds[RED_DOT_POSITION] = CRGB::Black;
                        displayLongNumber(THREE_DIGIT_INDEX, currentInputColor.r, CRGB(255,0,0));
                        break;
                    case 1:
                        leds[GREEN_DOT_POSITION] = CRGB::Black;
                        displayLongNumber(THREE_DIGIT_INDEX, currentInputColor.g, CRGB(0,255,0));
                        break;
                    case 2:
                        leds[BLUE_DOT_POSITION] = CRGB::Black;
                        displayLongNumber(THREE_DIGIT_INDEX, currentInputColor.b, CRGB(0,0,255));
                        break;
                    default:
                        break;
                    }
                }
            }else{
                switch (currentInputColorIndex)
                {
                case 0:
                    displayLongNumber(THREE_DIGIT_INDEX, inputBuffer.toInt(), CRGB(255,0,0));
                    break;
                case 1:
                    displayLongNumber(THREE_DIGIT_INDEX, inputBuffer.toInt(), CRGB(0,255,0));
                    break;
                case 2:
                    displayLongNumber(THREE_DIGIT_INDEX, inputBuffer.toInt(), CRGB(0,0,255));
                    break;
                default:
                    break;
                }
            }
            
        }else if(currentSubScreen == BRIGHTNESS){
            displayLongNumber(THREE_DIGIT_INDEX, inputBuffer.toInt(), currentColor);
            
        }else if (currentSubScreen == CURRENT_TIME)
        {
            if (millis() - lastBlinking_Time > 250)
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
            displayNumber(0, (inputBuffer.toInt()-inputBuffer.toInt() % 100)/100, currentColor);
            displayNumber(70, inputBuffer.toInt() % 100, currentColor);
        }
        
    }else{
        switch (currentScreen)
        {
            case TIME:
                if(isBacklightAnimation){
                    (this->*animationList[currentAnimationIndex])();
                }else if(isBacklightOn){
                    for(int i=0; i<128; i++){
                        leds[i] = currentBacklightColor;
                    }
                }

                if (millis() - lastBlinking_Time > 1000)
                {
                    lastBlinking_Time = millis();
                    blinkState = !blinkState;
                }
                if(blinkState){
                    if(!isBacklightOn and !isBacklightAnimation){
                        leds[64] = CRGB::Black;
                        leds[66] = CRGB::Black; 
                    }    

                }else{
                    leds[64] = currentColor;
                    leds[66] = currentColor;     
                }    
                displayNumber(0, currentTime.hour, currentColor);
                displayNumber(70, currentTime.minute, currentColor);
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
                (this->*animationList[currentAnimationIndex])();
            default:
                break;
        }
    }
    
    
}