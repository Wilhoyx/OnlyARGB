#include <Wire.h>
#include <FastLED.h>

#define currpal = 4    // Numero de la palette de depart
#define maxPalette = 4 // Nombre de palettes disponibles
#define argbSwitch = 5 // Broche d'alimentation des leds

int paletteSwitch = 3; // Pin du button de changement de palette
int buttonState;
int lastButtonState = LOW;
long bouncing = 300;    // Temps d'appui sur le button pour eviter que la sortie ne yoyotte

#define LED_PIN 5       // Pin de signal des leds
#define NUM_LEDS 60     // Nombre de leds sur la bande
#define BRIGHTNESS 188  // \o/
#define LED_TYPE WS2812 // Type des leds
#define COLOR_ORDER GRB // Depends du type des leds
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 1 // I used 42 for the secondPalette() 2520/42=60   see line 73 to see the calculation of the speed and fluidity        in order to keep the 60 ratio we can also have like 60*1000=60000

CRGBPalette16 currentPalette;
TBlendType currentBlending;

void setup()
{
  delay(200); // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  currentPalette = RainbowColors_p;
  currentBlending = LINEARBLEND;
  Serial.begin(115200);
  while (!Serial)
  {
    // will pause Zero, Leonardo, etc until serial console opens
    delay(1);
  }

  uint32_t currentFrequency;
  pinMode(argbSwitch, OUTPUT);
  pinMode(paletteSwitch, INPUT);
  int j = 0;
  while (j < 2)
  { // Just an init as we love'em
    fill_solid(currentPalette, 16, CRGB::Grey);
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */
    FillLEDsFromPaletteColors(startIndex);
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
    delay(420);
    j++;
  }
  Serial.println("Ready to go.");
  digitalWrite(argbSwitch, HIGH);
}

void loop()
{
  static uint8_t startIndex = 0;

  buttonState = digitalRead(paletteSwitch);

  // Si le button est appuye assez longtemps on incremente la selection de palette
  if (buttonState == HIGH && lastButtonState == LOW && millis() - time > debounce)
  {
    if (state == HIGH)
      currpal = currpal + 1;
    else
      state = HIGH;

    time = millis();
  }

  lastButtonState = buttonState;

  if (currpal == 1)
  {
    FirstPalette();
    startIndex = startIndex + 1; /* motion speed */
    FillLEDsFromPaletteColors(startIndex);
  }

  if (currpal == 2)
  {
    SecondPalette();
    startIndex = startIndex + 1; /* motion speed */
    FillLEDsFromPaletteColors(startIndex);
  }

  if (currpal == 3)
  {
    ThirdPalette();
  }

  if (currpal == 4)
  {
    FourthPalette();
    startIndex = startIndex + 1; /* motion speed */
    FillLEDsFromPaletteColors(startIndex);
  }

  if (currpal > maxPalette)
  { // Retour a la premiere palette
    currpal = 1;
  }
  FastLED.show();
  FastLED.delay(120 / UPDATES_PER_SECOND);

  /*                       COMMUNICATION





                           COMMUNICATION
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
  */
}
