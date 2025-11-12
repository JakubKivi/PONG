#include <Wire.h>
#include <FastLED.h>
#include <RTClib.h>


const int Digits[10][10] =
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

#define LED_PIN     2
#define NUM_LEDS    128
#define BRIGHTNESS  10
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];
RTC_DS1307 rtc;
#define UPDATES_PER_SECOND 100
DateTime now;
CRGB chosenColor = 0xFFFFFF;

int animacja=1;
bool normal=1;
bool service=0;
bool rainbow=0;
bool example=0;
bool stopwatch=0;
bool dino=0;

unsigned long prevtime=0;
unsigned long tempo=30;
int iter;

bool start=0;
int colorNr=0;

int bright=55;

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;

#include "functions.h"

void setup() {
    delay( 100 ); // power-up safety delay

    Serial.begin(9600);

    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );

     if (! rtc.begin()) {
      error(1,1);
     }
     //rtc.adjust(DateTime(2020, 1, 30, 16, 32, 0));  //fuckcja zmieniajaca czas
     if (! rtc.isrunning()) {
       error(2,1);
     }


}

void loop()
{
    now = rtc.now();
    Serial.println(now.timestamp());
    displaynumber(0,10, chosenColor);
    displaynumber(70,30, chosenColor);
    delay(1000);
}
    /*
      if(digitalRead(1)==LOW){
          if(bright<5)bright+=1;
          else if(bright<50)bright+=3;
          else if(bright<155)bright+=7;
          else if(bright<255)bright+=10;
          else bright=1;
          FastLED.setBrightness(bright);
          delay(50);
      }
      if(digitalRead(A1)==LOW){
          if(normal){
            if(colorNr<9)colorNr++;
            else colorNr=0;
            delay(500);
          }else if(rainbow){
            colorNr==0?colorNr=9:colorNr=0;
            delay(500);
          }else if(example){
            if(animacja<10)animacja++;
            else animacja=1;
            delay(500);
          }
      }
      if(digitalRead(A3)==LOW){
          if(normal){
            normal=0;
            rainbow=1;
            colorNr=0;
            animacja=1;
          }else if(rainbow){
            rainbow=0;
            example=1;
          }else if(example){
            example=0;
            stopwatch=1;
            start=0;
            animacja=8;
            tempo=30;
            iter=0;
          }else if(stopwatch){
            stopwatch=0;
            dino=1;
            kaktusMillis=millis();
            kI=0;
            kIP=0;
            n3=0;
          }else if(dino){
            dino=0;
            normal=1;
          }
          delay(500);
      }

      switch(colorNr){
        case 0: chosenColor=0xFFFFFF; break;
        case 1: chosenColor=0xFF0000; break;
        case 2: chosenColor=0xFF5000; break;
        case 3: chosenColor=0xFFFF00; break;
        case 4: chosenColor=0x00FF00; break;
        case 5: chosenColor=0x00FFFF; break;
        case 6: chosenColor=0x0000FF; break;
        case 7: chosenColor=0xFF00FF; break;
        case 8: chosenColor=0x5000ff; break;
        case 9: chosenColor=0x000000; break;

      }
      if(normal){
        displaynumber(0,now.hour(), chosenColor);
        displaynumber(70,now.minute(), chosenColor);

        if ( now.second()%2 == 0 ){
          leds[64] = chosenColor;
          leds[66] = chosenColor;
        }

        FastLED.show();
        FastLED.clear();
      }
      else if(rainbow){
        ChangePalettePeriodically();

        static uint8_t startIndex = 0;
        startIndex = startIndex + 1; 

        FillLEDsFromPaletteColors( startIndex);
        displaynumber(0,now.hour(), chosenColor);
        displaynumber(70,now.minute(), chosenColor);

        if ( now.second()%2 == 0 ){

          leds[64] = chosenColor;
          leds[66] = chosenColor;
        }

        FastLED.show();
        FastLED.delay(1000 / UPDATES_PER_SECOND);
      }

      else if(example){
          ChangePalettePeriodically();

          static uint8_t startIndex = 0;
          startIndex = startIndex + 1;

          FillLEDsFromPaletteColors( startIndex);

          FastLED.show();
          FastLED.delay(1000 / UPDATES_PER_SECOND);
      }

      else if(stopwatch){
        fStopwatch();
      }
      else if(dino){

        fDino();

      }*/


void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
    uint8_t brightness = 255;

    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}

void ChangePalettePeriodically()
{
        if( animacja==1)  { currentPalette = RainbowColors_p;         currentBlending = LINEARBLEND; }
        if( animacja==2)  { currentPalette = RainbowStripeColors_p;   currentBlending = NOBLEND;  }
        if( animacja==3)  { currentPalette = RainbowStripeColors_p;   currentBlending = LINEARBLEND; }
        if( animacja==4)  { SetupPurpleAndGreenPalette();             currentBlending = LINEARBLEND; }
        if( animacja==5)  { SetupBlackAndWhiteStripedPalette();       currentBlending = NOBLEND; }
        if( animacja==6)  { SetupBlackAndWhiteStripedPalette();       currentBlending = LINEARBLEND; }
        if( animacja==7)  { currentPalette = CloudColors_p;           currentBlending = LINEARBLEND; }
        if( animacja==8)  { currentPalette = PartyColors_p;           currentBlending = LINEARBLEND; }
        if( animacja==9)  { currentPalette = myRedWhiteBluePalette_p; currentBlending = NOBLEND;  }
        if( animacja==10)  { currentPalette = myRedWhiteBluePalette_p; currentBlending = LINEARBLEND; }
}

void SetupTotallyRandomPalette()
{
    for( int i = 0; i < 16; i++) {
        currentPalette[i] = CHSV( random8(), 255, random8());
    }
}

// This function sets up a palette of black and white stripes,
// using code.  Since the palette is effectively an array of
// sixteen CRGB colors, the various fill_* functions can be used
// to set them up.
void SetupBlackAndWhiteStripedPalette()
{
    // 'black out' all 16 palette entries...
    fill_solid( currentPalette, 16, CRGB::Black);
    // and set every fourth one to white.
    currentPalette[0] = CRGB::White;
    currentPalette[4] = CRGB::White;
    currentPalette[8] = CRGB::White;
    currentPalette[12] = CRGB::White;

}

// This function sets up a palette of purple and green stripes.
void SetupPurpleAndGreenPalette()
{
    CRGB purple = CHSV( HUE_PURPLE, 255, 255);
    CRGB green  = CHSV( HUE_GREEN, 255, 255);
    CRGB black  = CRGB::Black;

    currentPalette = CRGBPalette16(
                                   green,  green,  black,  black,
                                   purple, purple, black,  black,
                                   green,  green,  black,  black,
                                   purple, purple, black,  black );
}


// This example shows how to set up a static color palette
// which is stored in PROGMEM (flash), which is almost always more
// plentiful than RAM.  A static PROGMEM palette like this
// takes up 64 bytes of flash.
const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM =
{
    CRGB::Red,
    CRGB::Gray, // 'white' is too bright compared to red and blue
    CRGB::Blue,
    CRGB::Black,

    CRGB::Red,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Black,

    CRGB::Red,
    CRGB::Red,
    CRGB::Gray,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Blue,
    CRGB::Black,
    CRGB::Black
};
