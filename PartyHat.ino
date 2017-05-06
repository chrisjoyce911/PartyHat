#include "FastLED.h"

FASTLED_USING_NAMESPACE

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN    6
//#define CLK_PIN   4
#define LED_TYPE    WS2811
#define COLOR_ORDER RGB
#define NUM_LEDS    50
CRGB leds[NUM_LEDS];

#define BRIGHTNESS          20
#define FRAMES_PER_SECOND  120

int layer_1_size = 13; 
int layer_2_size = 10; 
int layer_3_size = 10; 
int layer_4_size = 17;  

int start_layer_1 = 0 ;
int end_layer_1 = layer_1_size ;
int layer_1_colour = 0 ;
        
int start_layer_2 = end_layer_1 ;
int end_layer_2 = end_layer_1 + layer_2_size ;
int layer_2_colour = 1 ;
        
int start_layer_3 = end_layer_2 ;
int end_layer_3 = end_layer_2 +layer_3_size ;
int layer_3_colour = 2 ;
        
int start_layer_4 = end_layer_3 ;
int end_layer_4 = end_layer_3 + layer_4_size ;
int layer_4_colour = 4 ;





int fl_len = 13;
int fl[] = { 3,4,5,6,   16,17,18,  27,28,       40,41,42,43};

int fr_len = 13;
int fr[] = { 7,8,9,     19,20,     29,30,31,       44,45,46,47,48};

int rl_len = 13;
int rl[] = { 0,1,2,     13,14,15,  24,25,26,       36,37,38,39 };

int rr_len = 12;
int rr[] = { 10,11,12,  21,22,23,  32,33,34,       35,49};


int fr_colour = 0 ;
int fl_colour = 1 ;
int rl_colour = 2 ;
int rr_colour = 3 ;

int i;

void setup() {
Serial.begin(57600);

  delay(3000); // 3 second delay for recovery
  
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}


// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
//SimplePatternList gPatterns = { rainbow, rainbowWithGlitter, confetti, sinelon, juggle, bpm };
SimplePatternList gPatterns = {  juggle, layers, roundhat };
// rainbowWithGlitter, juggle, layers, roundhat

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns
  
void loop()
{
  // Call the current pattern function once, updating the 'leds' array
  gPatterns[gCurrentPatternNumber]();

  // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND); 

  // do some periodic updates
  EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow
  EVERY_N_SECONDS( 15 ) { nextPattern(); } // change patterns periodically
}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
}

void rainbow() 
{
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, NUM_LEDS, gHue, 7);
}

void rainbowWithGlitter() 
{
  // built-in FastLED rainbow, plus some random sparkly glitter
  rainbow();
  addGlitter(80);
}

void addGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
}

void confetti() 
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( gHue + random8(64), 200, 255);
}

void sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = beatsin16(13,0,NUM_LEDS);
  leds[pos] += CHSV( gHue, 255, 192);
}


void setcolour (int led, int mycolour)
{
    if (mycolour == 0)
    {leds[led].setRGB( 0, 155, 242);} //Standard Link Blue
    if (mycolour == 1)
    {leds[led].setRGB( 153, 214, 255);} //Light Link Blue
    if (mycolour == 2)
    {leds[led].setRGB( 242, 84, 50);} //C2A Orange
    if (mycolour == 3)
    {leds[led].setRGB( 0, 64, 89);} //Nav
    if (mycolour == 4)
    {leds[led].setRGB( 31, 183, 173);} //Success
    if (mycolour == 5)
    {leds[led].setRGB( 244, 44, 47);} //Error
    if (mycolour == 6)
    {leds[led].setRGB( 255, 175, 10);} //Favourite
    if (mycolour == 7)
    {leds[led].setRGB( 205, 216, 220);} //Grey 5
}

void setcolourA (int led, int mycolour)
{
        if (mycolour == 0)
        {leds[led] = CRGB::Purple;} //Purple
        
        if (mycolour == 1)
        {leds[led] = CRGB::Red;} //Red
        
        if (mycolour == 2)
        {leds[led] = CRGB::Orange;} //Orange
        
        if (mycolour == 3)
        {leds[led] = CRGB::Green;} // Green

        if (mycolour == 4)
        {leds[led] = CRGB::Blue;} //Blue
        
        if (mycolour == 5)
        {leds[led] = CRGB::Yellow; } //Yellow

        if (mycolour == 6)
        {leds[led] = CRGB::HotPink; }
        
        if (mycolour == 7)
        {leds[led] = CRGB::Aqua; }
        
        if (mycolour == 8)
        {leds[led] = CRGB::Chartreuse; }
        
        if (mycolour == 9)
        {leds[led] = CRGB::LawnGreen; }
        
        if (mycolour == 10)
        {leds[led] = CRGB::Black; } //Black



        
}


int nextcolour (int currentcolour)
{
        int maxcolour = 7 ;
        currentcolour ++ ;
        if (currentcolour > maxcolour)
        {currentcolour = 0 ; } 
        return  currentcolour ;
}


void layers()
{

        layer_1_colour = nextcolour (layer_1_colour) ;
        for(int led = start_layer_1; led < end_layer_1; led++) { 
          setcolour ( led ,layer_1_colour ) ;
        }
        
        layer_2_colour = nextcolour (layer_2_colour) ;
        for(int led = start_layer_2; led < end_layer_2 ; led++) { 
         setcolour ( led ,layer_2_colour) ; 
        }
        
        layer_3_colour = nextcolour (layer_3_colour) ;
        for(int led = start_layer_3 ; led < end_layer_3 ; led++) { 
          setcolour ( led ,layer_3_colour ) ;
        }

        layer_4_colour = nextcolour (layer_4_colour) ;
        for(int led = start_layer_4 ; led < end_layer_4 ; led++) { 
          setcolour ( led,layer_4_colour  ) ; 
        }
      delay(250);
}

void roundhat()
{


        fl_colour = nextcolour (fl_colour) ;
        for ( i = 0; i < fl_len; i++) {
            setcolour ( fl[i],fl_colour ) ;
        }

      fr_colour = nextcolour (fr_colour) ;
        for ( i = 0; i < fr_len; i++) {
          setcolour ( fr[i],fr_colour ) ;
        }

       rl_colour = nextcolour (rl_colour) ;
        for ( i = 0; i < rl_len; i++) {
           setcolour ( rl[i],rl_colour ) ;
        }

       rr_colour = nextcolour (rr_colour) ; 
        for ( i = 0; i < rr_len; i++) {
            setcolour ( rr[i] ,rr_colour ) ;
        }
          
        delay(250);
}

void locate()
{

        for ( i = 0; i < fl_len ; i++) {
            leds[fl[i]] = CRGB::Red;
            FastLED.show();
            delay(200);
        }

        for ( i = 0; i < fr_len; i++) {
            leds[fr[i]] = CRGB::Green;
            FastLED.show();
            delay(200);
        }

        for ( i = 0; i < rl_len; i++) {
            leds[rl[i]] = CRGB::Blue;
            FastLED.show();
            delay(200);
        }

        for ( i = 0; i < rr_len; i++) {
            leds[rr[i]] = CRGB::Yellow;
            FastLED.show();
            delay(200);
        }

        delay(2000);
        for ( i = 0; i < rr_len; i++) {
            leds[rr[i]] = CRGB::Black;
        }
        for ( i = 0; i < rl_len; i++) {
            leds[rl[i]] = CRGB::Black;
        }
          
        for ( i = 0; i < fr_len ; i++) {
            leds[fr[i]] = CRGB::Black;
        }
        
        for ( i = 0; i < fl_len ; i++) {
            leds[fl[i]] = CRGB::Black;
        }
}

void bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_LEDS; i++) { //9948
    leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
  }
}

void juggle() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds, NUM_LEDS, 20);
  byte dothue = 0;
  for( int i = 0; i < 8; i++) {
    leds[beatsin16(i+7,0,NUM_LEDS)] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
  addGlitter(80);
}

