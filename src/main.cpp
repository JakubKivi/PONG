#include <Arduino.h>
#include <Wire.h>
#include <I2C_RTC.h>
#include <Keypad.h>
#include <fastled.h>

static DS1307 RTC;

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
    {'1', '2', '3','A'},
    {'4', '5', '6','B'},
    {'7', '8', '9','C'},
    {'*', '0', '#','D'}};

byte rowPins[ROWS] = {3, 4, 5, 6};
byte colPins[COLS] = {7, 8, 9, 10};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

#define LED_PIN     2
#define NUM_LEDS    128
#define BRIGHTNESS  255
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100

void setup()
{
    delay(1000); // Power-up safety delay
    Serial.begin(9600);
    Wire.begin();
    
    FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
    FastLED.setBrightness(  255 );

    RTC.begin();
    if (!RTC.isConnected())
    {
        Serial.println("RTC not connected!");
    }
    if (RTC.isConnected() && !RTC.isRunning())
    {
        Serial.println("RTC is NOT running, setting the time!");
        RTC.setDateTime(__DATE__, __TIME__);
        RTC.startClock();
    }
}

void loop()
{
    // char key = keypad.getKey();
    // if (key)
    // {
    //     Serial.print("Key Pressed: ");
    //     Serial.println(key);
    // }

    // tm now = RTC.getDateTime();
    // Serial.print("Current Time: ");
    // Serial.print(now.tm_hour);
    // Serial.print(":");
    // Serial.print(now.tm_min);
    // Serial.print(":");
    // Serial.println(now.tm_sec);

    //Serial.println("BLINK");
  
    // Turn the LED on, then pause

    
    FastLED.setBrightness(  50 );
    for(int i=0; i<NUM_LEDS; i++){
        leds[i] = CRGB::White;
    }
    FastLED.show();
    delay(1000);
    
    FastLED.setBrightness(  100 );
    for(int i=0; i<NUM_LEDS; i++){
        leds[i] = CRGB::White;
    }
    FastLED.show();
    delay(1000);
    
    FastLED.setBrightness(  150 );
    for(int i=0; i<NUM_LEDS; i++){
        leds[i] = CRGB::White;
    }
    FastLED.show();
    delay(1000);
    
    FastLED.setBrightness(  200 );
    for(int i=0; i<NUM_LEDS; i++){
        leds[i] = CRGB::White;
    }
    FastLED.show();
    delay(1000);
    
    FastLED.setBrightness(  255 );
    for(int i=0; i<NUM_LEDS; i++){
        leds[i] = CRGB::White;
    }
    FastLED.show();
    delay(1000);
    
    for(int i=0; i<NUM_LEDS; i++){
        leds[i] = CRGB::Black;
    }
    leds[0] = CRGB::Black;
    FastLED.show();
    delay(3000);

    while (true)
    {
        static uint16_t globalHue = 0;

        // Fill with colors based on globalHue + LED index offset
        for (int i = 0; i < NUM_LEDS; i++) {
            // Each LED gets hue shifted by i to create a full moving rainbow
            leds[i] = CHSV((globalHue + i * 3) & 255, 255, 255);
        }

        FastLED.show();

        globalHue++;  // controls speed of movement
        delay(10);    // lower = faster
    }
    
    
}