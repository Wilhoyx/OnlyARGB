#include <Wire.h>

#include <FastLED.h>
int currpal = 3;        // This one is the palette by default (the aestethicc one)
int maxPalette = 4;     // This is the number of registrered palette we got
int argbSwitch = 5;     // This is the command of the relay

#define LED_PIN     3       // This is the signal pin for the leds
#define NUM_LEDS    60       // This is in fact 9(Headset support) + 37(Behind the screen) + 14(Inside the PC case)
#define BRIGHTNESS  188        // Was first at 64 then 16
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 1 // I used 42 for the secondPalette() 2520/42=60   see line 73 to see the calculation of the speed and fluidity        in order to keep the 60 ratio we can also have like 60*1000=60000

CRGBPalette16 currentPalette;
TBlendType    currentBlending;


void setup() {
  delay( 200 ); // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );
  currentPalette = RainbowColors_p;
  currentBlending = LINEARBLEND;
  Serial.begin(115200);
  while (!Serial) {
    // will pause Zero, Leonardo, etc until serial console opens
    delay(1);
  }

  uint32_t currentFrequency;
  pinMode(argbSwitch, OUTPUT);
  int j = 0;
  while (j < 2) {               // Just an init as we love'em
    fill_solid( currentPalette, 16, CRGB::Grey);
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */
    FillLEDsFromPaletteColors( startIndex);
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
    delay(420);
    j++;
  }
  Serial.println("Hello!");
}



void loop () {

  while (!Serial) {
    digitalWrite(argbSwitch, HIGH);
  }

  static uint8_t startIndex = 0;
  if (currpal == 1) {
    FirstPalette();
    startIndex = startIndex + 1; /* motion speed */
    FillLEDsFromPaletteColors( startIndex);
  }

  if (currpal == 2) {
    SecondPalette();
    startIndex = startIndex + 1; /* motion speed */
    FillLEDsFromPaletteColors( startIndex);
  }

  if (currpal == 3) {
    ThirdPalette();
  }

  if (currpal == 4) {
    FourthPalette();
    startIndex = startIndex + 1; /* motion speed */
    FillLEDsFromPaletteColors( startIndex);
  }

  if (currpal > maxPalette) {   // This way we cycle throught the palette we got
    currpal = 1;
  }
  FastLED.show();
  FastLED.delay(120 / UPDATES_PER_SECOND);


  /*                       COMMUNICATION





                           COMMUNICATION
  */
  if ( Serial.available()) {     // Check if any char available on serial, if there's any instructions
    char c = Serial.read();
    if (c == 's') {
      Serial.println(c);
      Serial.println("Switching.");
      currpal = currpal + 1;
    }
    if (c == 'n') {
      Serial.println("Switching on");
    }
    if (c == 'f') {
      Serial.println("Switching off");
    }
  }
}
