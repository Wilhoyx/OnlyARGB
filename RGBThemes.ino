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

void SecondPalette()                 // What I got in This Function is a half and half circle cyan and pink, way too much aestethicc and the speed is calculated and smooth enought.
{
  CRGB c1 = CHSV( HUE_AQUA, 255, 255);
  CRGB c2 = CHSV( HUE_PINK, 255, 255);
  //fill_solid( currentPalette, 16, c2);

  currentPalette = CRGBPalette16(
                     c1, c1, c2, c2,
                     c1, c1, c2, c2,
                     c1, c1, c2, c2,
                     c1, c1, c2, c2 );
}
void ThirdPalette()
{
  fill_solid(leds, 60, CRGB( 200, 0, 200));
  FastLED.show();
}

void FourthPalette()
{
  CRGB c1 = CHSV(HUE_YELLOW, 255, 255);
  CRGB c2 = CHSV(HUE_PINK, 200, 255);
  fill_solid( currentPalette, 16, CRGB::Black);
  currentPalette[0] = c1;
  currentPalette[2] = c2;
  currentPalette[5] = c1;
  currentPalette[8] = c2;
  currentPalette[11] = c1;
  currentPalette[14] = c2;
}

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
  uint8_t brightness = 255;

  for ( int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
    colorIndex += 3;
  }
}
