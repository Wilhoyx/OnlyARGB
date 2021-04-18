#include <Wire.h>

#include <FastLED.h>
int argbSwitch = 2;    // This pin is used to feed the argb led strip with 5V
int currpal = 4;        // This is the index of the default palette ( fourthpalette)
int maxPalette = 4;     // This is the number of registrered palette we got

#define LED_PIN     3       // Pin that is used to send the data to command the led
#define NUM_LEDS    60       // This is in fact 9(headset support) + 37(screen top) + 14(pc rgbing)
#define BRIGHTNESS  128      // Value between 0 and 255
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 1 // Didn't see lot of improvements... I used 42 for the secondPalette() 2520/42=60   see line 73 to see the calculation of the speed and fluidity        in order to keep the 60 ratio we can also have like 60*1000=60000 
CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;

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
    fill_solid( currentPalette, 16, CRGB::White);
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */
    FillLEDsFromPaletteColors( startIndex);
    FastLED.show();
	  //digitalWrite(argbSwitch, HIGH);  // By activating this output we feed the Vin of the color ring and so it light up
    FastLED.delay(1000 / UPDATES_PER_SECOND);
    //digitalWrite(argbSwitch, LOW);   // And then we shut it off, init thing ya know
    delay(420);
    j++;
  }
  Serial.println("Hello!");
  digitalWrite(argbSwitch, HIGH);           // This means that once the init done we light the argb on on the default palette
}
void loop () {
  if (currpal == 1){
    FirstPalette();
  }
  if (currpal == 2){
    SecondPalette();
  }
  if (currpal == 3){
    ThirdPalette();
  }
  if (currpal == 4){
    FourthPalette();
  }
  if (currpal > maxPalette){    // This way we cycle throught the palette we got
    currpal = 1;
  }


  static uint8_t startIndex = 0;   // I'll have to search but it is for the moving part, lika snake.
  startIndex = startIndex + 1;

  FillLEDsFromPaletteColors( startIndex);

  FastLED.show();
  FastLED.delay(120 / UPDATES_PER_SECOND);

  if ( Serial.available()) {     // Check if any char available on serial, if there's any instructions
    char c = Serial.read();
    if (c == 's'){
      Serial.println(c);
      Serial.println("Switching.");
      currpal = currpal +1;
    }
    if (c == 'n'){
      digitalWrite(argbSwitch, HIGH);
    }
    if (c == 'f'){
      digitalWrite(argbSwitch, LOW);
    }
  }
}

// FastLED provides several 'preset' palettes: RainbowColors_p, RainbowStripeColors_p,
// OceanColors_p, CloudColors_p, LavaColors_p, ForestColors_p, and PartyColors_p.
// This function sets up a palette of black and white stripes,
// using code.  Since the palette is effectively an array of
// sixteen CRGB colors, the various fill_* functions can be used
// to set them up.

void FirstPalette()
{
  CRGB c1 = CHSV( HUE_RED, 255, 255);
  CRGB c2 = CHSV( HUE_ORANGE, 255, 255);
  CRGB c3 = CHSV( HUE_YELLOW, 255, 255);
  CRGB c4 = CHSV( HUE_GREEN, 255, 255);
  CRGB c5 = CHSV( HUE_AQUA, 255, 255);
  CRGB c6 = CHSV( HUE_BLUE, 255, 255);
  CRGB c7 = CHSV( HUE_PURPLE, 255, 255);
  CRGB c8 = CHSV( HUE_PINK, 255, 255);
  // 'black out' all 16 palette entries...
  fill_solid( currentPalette, 16, CRGB::Black);
  currentPalette[0] = c1;
  currentPalette[2] = c2;
  currentPalette[4] = c3;
  currentPalette[6] = c4;
  currentPalette[8] = c5;
  currentPalette[10] = c6;
  currentPalette[12] = c7;
  currentPalette[14] = c8;

}

void SecondPalette()
{
  CRGB c1 = CHSV( HUE_AQUA, 255, 255);
  CRGB c2 = CHSV( HUE_PINK, 255, 255);
  CRGB c3  = CRGB::Black;

  currentPalette = CRGBPalette16(
                     c1, c1, c2, c2,
                     c1, c1, c2, c2,
                     c1, c1, c2, c2,
                     c1, c1, c2, c2 );
}
void ThirdPalette()
{
  CRGB c1 = CHSV( HUE_RED, 255, 255);
  CRGB c2  = CHSV( HUE_ORANGE, 255, 255);
  CRGB c3 = CHSV( HUE_YELLOW, 255, 255);
  CRGB c4 = CHSV( HUE_PINK, 255, 255);
  CRGB c5  = CRGB::Black;

  currentPalette = CRGBPalette16(
                     c1, c2, c3, c4,
                     c1, c2, c3, c4,
                     c1, c2, c3, c4,
                     c1, c2, c3, c4 );
}

void FourthPalette()
{
  CRGB c1 = CHSV(HUE_YELLOW, 255, 255);
  CRGB c2 = CHSV(HUE_PINK, 255, 255);
  fill_solid( currentPalette, 16, CRGB::Black);
  currentPalette[0] = c1;
  currentPalette[2] = c2;
  currentPalette[5] = c1;
  currentPalette[8] = c2;
  currentPalette[11] = c1;
  currentPalette[14] = c2;
}

// This example shows how to set up a static color palette
// which is stored in PROGMEM (flash), which is almost always more
// plentiful than RAM.  A static PROGMEM palette like this
// takes up 64 bytes of flash.
const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM = {
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
