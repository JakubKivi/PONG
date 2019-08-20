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
    digitalWrite(0, 1);
    delay(500);
    digitalWrite(0, 0);
    delay(500);
  }
  while(b){
    for(int i=0; i<a; i++){
    digitalWrite(0, 1);
    delay(500);
    digitalWrite(0, 0);
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

struct dwa {
  int a;
  int b;
};
dwa pD;

CRGB dinosourColor = 0x00FF00;
bool jump=0;
bool jump1=0;
bool jump2=0;
bool jump3=0;
bool jump4=0;
unsigned long currentMillis, previousMillis;

void fStopwatch(){

      currentMillis = millis();

      if(!jump){
        leds[19] = dinosourColor;
        leds[18] = dinosourColor;
        leds[7] = dinosourColor;
        leds[17] = dinosourColor;
        pD.a=19;
        pD.b=20;
        if(digitalRead(A1)==LOW){
          previousMillis=millis();
          jump=1;
        }
      }else{
        if(jump1){
          if(currentMillis - previousMillis >= 200){
            jump1=0;
            jump2=1;
            previousMillis=millis();
          }
          leds[17] = dinosourColor;
          leds[16] = dinosourColor;
          leds[9] = dinosourColor;
          leds[15] = dinosourColor;
          pD.a=17;
          pD.b=18;
        }
        else if(jump2){
          if(currentMillis - previousMillis >= 200){
            jump2=0;
            jump3=1;
            previousMillis=millis();
          }
          leds[15] = dinosourColor;
          leds[14] = dinosourColor;
          leds[11] = dinosourColor;
          leds[13] = dinosourColor;
          pD.a=16;
          pD.b=17;
        }
        else if(jump3){
          if(currentMillis - previousMillis >= 200){
            jump3=0;
            jump4=1;
            previousMillis=millis();
          }
          leds[17] = dinosourColor;
          leds[16] = dinosourColor;
          leds[9] = dinosourColor;
          leds[15] = dinosourColor;
          pD.a=15;
          pD.b=14;
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
          pD.a=14;
          pD.b=13;
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
          pD.a=18;
          pD.b=19;
        }
      }
      FastLED.show();
      FastLED.clear();
}
