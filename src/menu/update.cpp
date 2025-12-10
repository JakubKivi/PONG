#include "Menu.h"
#include "logic/TimeStruct.h"

void Menu::update(char key){  
    if (isSubmenu)
    {
        if(key>='0' && key<='9'){
            inputBuffer += key;
            if((inputBuffer.length()>3 and currentSubScreen!=CURRENT_TIME )or
               inputBuffer.length()>4){
                inputBuffer="";
            }
            
        }else if(key=='#'){
            inputBuffer = "";

        }else if(key=='*'){
            int value = inputBuffer.toInt();
            if ( value <3 )
                value = 3;
            if ( value >255 )
                value = 255;
            if (currentSubScreen==COLOR)
            {
                if(inputBuffer.length()==0){
                    //do nothing
                }else{
                    switch (currentInputColorIndex)
                    {
                    case 0:
                        currentInputColor.r = value;
                        break;
                    case 1:
                        currentInputColor.g = value;
                        break;
                    case 2:
                        currentInputColor.b = value;
                        break;
                    default:
                        break;
                    }
                }
                inputBuffer = "";
                currentInputColorIndex = (currentInputColorIndex + 1) % 3;
            }else if(currentSubScreen==BRIGHTNESS)
            {
                manualBrightness = value;
                inputBuffer = "";
                isSubmenu = false;
            }else if (currentSubScreen==CURRENT_TIME)
            {
                TimeStruct value(
                    (inputBuffer.toInt()-inputBuffer.toInt() % 100)/100, 
                    inputBuffer.toInt() % 100);

                RTC->setTime(value.hour, value.minute, 0);
                inputBuffer = "";
                isSubmenu = false;
            }

        }else if(key=='A'){
                currentColor = currentInputColor;
                isSubmenu = false;
                inputBuffer = "";
        }else if(key=='B'){
                currentBacklightColor = currentInputColor;
                isSubmenu = false;
                inputBuffer = "";
        } else if(key=='D'){
                isSubmenu = false;
                inputBuffer = "";
        }     
    }else{
        if(key=='D'){
            currentScreen = static_cast<MenuScreen>((currentScreen + 1) % 3);
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
                    isBacklightAnimation = !isBacklightAnimation;
                    break;  
                default:
                    break;
            }
        }else if (currentScreen==SETTINGS){
            switch (key)
            {
                case 'A':
                    isSubmenu = true;
                    currentSubScreen = COLOR;
                break; 
                case 'B':
                    isSubmenu = true;
                    currentSubScreen = BRIGHTNESS;
                break;   
                case 'C':
                    isSubmenu = true;
                    currentSubScreen = CURRENT_TIME;
                break;     
                default:
                    break;
            }  
        }else if (currentScreen==ANIMATIONS){
            switch (key)
            {
                case 'A':
                    if(currentAnimationIndex < (Menu::animationListCount - 1))
                        currentAnimationIndex += 1;
                    break;   
                case 'B':
                    currentAnimationIndex>0 ? currentAnimationIndex -= 1 : currentAnimationIndex = 0;                    
                    break;
                case 'C':
                    break;
                case '*':
                    currentAnimationIndex = constrain(inputBuffer.toInt(), 0, Menu::animationListCount - 1);
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

void Menu::updateTime(){
    unsigned long mils = millis();

    if (mils - lastUpdate_Time >= 1000) { 
        lastUpdate_Time = mils;
        
        tm now = RTC->getDateTime();
        currentTime.hour = now.tm_hour;
        currentTime.minute = now.tm_min;
        currentDate.day = now.tm_mday;
        currentDate.month = now.tm_mon;
        currentDate.year = now.tm_year + 1900;
        
        if (isAutoBrightness)
        {
            FastLED.setBrightness(constrain(map(analogRead(fotresistorPin), 30, 1000, 50, 255) , 50, 255));
        }else{
            FastLED.setBrightness(manualBrightness);
        }
    }  

    displayScreen();
}