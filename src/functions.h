void showStart(){
  for(int i=0; i<5; i++){
    digitalWrite(0, 1);
    delay(100);
    digitalWrite(0, 0);
    delay(100);
  }
}

void error(int a, bool b){
  for(int i=0; i<a; i++){
    digitalWrite(13, 1);
    delay(500);
    digitalWrite(13, 0);
    delay(500);
  }
  while(b){
    for(int i=0; i<a; i++){
    digitalWrite(13, 1);
    delay(500);
    digitalWrite(13, 0);
    delay(500);
  }
  delay(3000);
  }
}

void displaynumber( int place , int number, CRGB c){
  for (int i = 0 ; i < 10 ; i++) {
    if (Digits[number/10][i] != 0) {
      leds[(Digits[number/10][i]+place)] = c;
    }
    if (Digits[number%10][i] != 0) {
      leds[(Digits[number%10][i]+28+place)] = c;
    }
  }
}

void fNormal(){
      displaynumber(0,now.hour(), chosenColor);
      displaynumber(70,now.minute(), chosenColor);

      if ( now.second()%2 == 0 ){
        leds[64] = chosenColor;
        leds[66] = chosenColor;
      }

      FastLED.show();
      FastLED.clear();
}

void fStopwatch(){
  int hue=0;
  int counter=0;
  CHSV colourOfNumbers( 160, 255, 255);
  while(!digitalRead(A3)==LOW){
    if(digitalRead(A1)==LOW){
      if(start){
        start=0;
        //wypisz czas do edenu
        delay(500);
      }else{
        while(digitalRead(A1)==LOW){
          start=1;
          hue=0;
          counter=0;
        }
      }
    }

    if(digitalRead(1)==LOW && !start){
        if(bright<5)bright+=1;
        else if(bright<50)bright+=3;
        else if(bright<155)bright+=7;
        else if(bright<255)bright+=10;
        else bright=1;
        FastLED.setBrightness(bright);
        delay(50);
    }
    if(start){
        counter=(counter+1)%10000;
        hue=(hue+1)%2550;
        colourOfNumbers.hue = hue/10;
    }
    displaynumber(0,counter/100,colourOfNumbers);
    displaynumber(70,counter%100,colourOfNumbers);
    FastLED.show();
    FastLED.clear ();
  }
}


CRGB dinosourColor = 0xFF0000;
CRGB kaktusColor = 0x00FF00;
bool loose=0;
bool jump=0;
bool jump1=0;
bool jump2=0;
bool jump3=0;
bool jump4=0;
unsigned long currentMillis, previousMillis, kaktusMillis;

int dHigh=1;
int kI=0;
bool kIP=0;
bool n3=0;

void fDino(){

      currentMillis = millis();
      if(!loose){
          if(!jump){
            leds[19] = dinosourColor;
            leds[18] = dinosourColor;
            leds[7] = dinosourColor;
            leds[17] = dinosourColor;
            if(digitalRead(A1)==LOW){
              previousMillis=millis();
              jump=1;
            }
          }else{
            if(jump1){
              if(currentMillis - previousMillis >= 300){
                jump1=0;
                jump2=1;
                previousMillis=millis();
              }
              leds[17] = dinosourColor;
              leds[16] = dinosourColor;
              leds[9] = dinosourColor;
              leds[15] = dinosourColor;
            }
            else if(jump2){
              if(currentMillis - previousMillis >= 600){
                jump2=0;
                jump3=1;
                previousMillis=millis();
              }
              leds[15] = dinosourColor;
              leds[14] = dinosourColor;
              leds[11] = dinosourColor;
              leds[13] = dinosourColor;
            }
            else if(jump3){
              if(currentMillis - previousMillis >= 300){
                jump3=0;
                jump4=1;
                previousMillis=millis();
              }
              leds[17] = dinosourColor;
              leds[16] = dinosourColor;
              leds[9] = dinosourColor;
              leds[15] = dinosourColor;
            }
            else if(jump4){
              if(currentMillis - previousMillis >= 200){
                jump4=0;
                jump=0;
                previousMillis=millis();
              }
              leds[19] = dinosourColor;
              leds[18] = dinosourColor;
              leds[7] = dinosourColor;
              leds[17] = dinosourColor;
            }
            else{
              if(currentMillis - previousMillis >= 100){
                jump1=1;
                previousMillis=millis();
              }
              leds[19] = dinosourColor;
              leds[18] = dinosourColor;
              leds[7] = dinosourColor;
              leds[17] = dinosourColor;
            }
          }
          if(currentMillis - kaktusMillis >= 200){
            kaktusMillis=millis();
            if(kI<108){
              if(kIP==0){
                kI+=3;
                kIP=1;
              }else{
                kI+=11;
                kIP=0;
              }
            }else if(kI<115){
              kI+=3;
              n3=1;
            }else{
              n3=0;
              kI=0;
              kIP=0;
            }
          }
          if(
            leds[118-kI]==dinosourColor||
            leds[119-kI]==dinosourColor||
            leds[120-kI]==dinosourColor
          ){
            loose=1;
            delay(200);
            kI=0;
            kIP=0;
            n3=0;
            bool jump=0;
            bool jump1=0;
            bool jump2=0;
            bool jump3=0;
            bool jump4=0;
          }
          if(!n3)leds[118-kI] = kaktusColor;
          leds[119-kI] = kaktusColor;
          leds[120-kI] = kaktusColor;

      }else{
        displaynumber(0, 88, 0xFF0000);
        displaynumber(70, 88, 0xFF0000);
        if(digitalRead(A1)==LOW){
          loose=0;
          delay(500);
        }
      }

      FastLED.show();
      FastLED.clear();
}
