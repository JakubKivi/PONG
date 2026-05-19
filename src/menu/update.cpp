#include "Menu.h"
#include "logic/TimeStruct.h"

void Menu::update(char key){  
    if (isSubmenu)
    {
        if(key>='0' && key<='9'){
            if (inputBufferLen < (int)sizeof(inputBuffer)-1) {
                inputBuffer[inputBufferLen++] = key;
                inputBuffer[inputBufferLen] = '\0';
            }
            if((inputBufferLen>3 && currentSubScreen!=CURRENT_TIME) || inputBufferLen>4){
                inputBufferLen = 0;
                inputBuffer[0] = '\0';
            }
        }else if(key=='#'){
            inputBufferLen = 0;
            inputBuffer[0] = '\0';

        }else if(key=='*'){
            int value = atoi(inputBuffer);
            if ( value <3 )
                value = 3;
            if ( value >255 )
                value = 255;
            if (currentSubScreen==COLOR)
            {
                if(inputBufferLen==0){
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
                inputBufferLen = 0;
                inputBuffer[0] = '\0';
                currentInputColorIndex = (currentInputColorIndex + 1) % 3;
            }else if(currentSubScreen==BRIGHTNESS)
            {
                manualBrightness = value;
                inputBufferLen = 0;
                inputBuffer[0] = '\0';
                isSubmenu = false;
                updateBrightness();
            }else if (currentSubScreen==CURRENT_TIME)
            {
                TimeStruct value(
                    (atoi(inputBuffer)-atoi(inputBuffer) % 100)/100, 
                    atoi(inputBuffer) % 100);
                RTC->setTime(value.hour, value.minute, 0);
                inputBufferLen = 0;
                inputBuffer[0] = '\0';
                isSubmenu = false;
            }

        }else if(key=='A'){
                currentColor = currentInputColor;
                isSubmenu = false;
                inputBufferLen = 0;
                inputBuffer[0] = '\0';
                saveColorSettings(currentColor, currentBacklightColor);
        }else if(key=='B'){
                currentBacklightColor = currentInputColor;
                isSubmenu = false;
                inputBufferLen = 0;
                inputBuffer[0] = '\0';
                saveColorSettings(currentColor, currentBacklightColor);
        } else if(key=='D'){
                isSubmenu = false;
                inputBufferLen = 0;
                inputBuffer[0] = '\0';
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
                    updateBrightness();
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
                        currentAnimationIndex = constrain(atoi(inputBuffer), 0, Menu::animationListCount - 1);
                        inputBufferLen = 0;
                        inputBuffer[0] = '\0';
                    break;
                case '#':
                        inputBufferLen = 0;
                        inputBuffer[0] = '\0';
                    break;
                default:
                        if (inputBufferLen < (int)sizeof(inputBuffer)-1) {
                            inputBuffer[inputBufferLen++] = key;
                            inputBuffer[inputBufferLen] = '\0';
                        }
                    break;
            }   
        }           
    }    
}

void Menu::updateTime(){
    unsigned long mils = millis();

    if (mils - lastUpdate_Time >= 10000) { 
        lastUpdate_Time = mils;
        
        tm now = RTC->getDateTime();
        currentTime.hour = now.tm_hour;
        currentTime.minute = now.tm_min;
        currentDate.day = now.tm_mday;
        currentDate.month = now.tm_mon;
        currentDate.year = now.tm_year + 1900;
        
        updateBrightness();
    }  

    displayScreen();
}