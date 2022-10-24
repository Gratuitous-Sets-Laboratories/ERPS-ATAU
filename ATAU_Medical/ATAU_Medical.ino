/*
 * GRATUITOUS SETS LABORATORIES
 * Dallas, TX, USA
 * 
 * ESCAPE ROOM, PALM SPRINGS
 * Palm Springs, CA, USA
 * 
 * 2022
 */

//============== DEFINITIONS & DECLAIRATIONS =================//

//-------------- LIBRARIES -----------------------------------//
/* Call all function libraries required by the sketch. 
 */
  #include <Adafruit_NeoPixel.h>  // WS2812 (NeoPixel) addressable LEDs
  #include <Wire.h>
  #include "Adafruit_MPR121.h"

  #ifndef _BV
  #define _BV(bit) (1 << (bit)) 
  #endif

//-------------- SETTINGS & GLOBAL CONSTANTS -----------------//
/* Define constraits used by various functions.
 * Variables using '#define' are defined by hardware, and should be left alone.
 * Variables using 'const' can be changed to tune the puzzle.
 */
  const String myNameIs = "ATAU_Medical";                // name of sketch
  const String verNum = "1.0";                               // version of sketch
  const String lastUpdate = "2022 Oct 22";                      // last update
  
  const int serialDelay = 500;                                // length of time before sending a blank line via Serial
  const int debounceDelay = 50;                               // delay after a "somethingNew" to avoid bouncing comm to R.Pi



//-------------- PIN DEFINITIONS  ----------------------------//
/* Most of the I/O pins on the Arduino Nano are hard-wired to various components on the ARDNEX2.
 * Pins not used for their standard fuction have header pins for alternate uses.
 */

  const int npxCmdPin[2] = {8,9};
  #define neoPixelPin 5           // data line to WS2812 (NeoPixel) via 470R resistor

//============== HARDWARE PARAMETERS =========================//
/*
 * Control basic paramaters for external devices from here.
 * Pin definitions should be kept above, to insure that there is no overlap.
 * As with settings & global constants: 
 * #define refers to installed hardare
 * const refers to soft settings
 */
//.............. WS2812B NeoPixels ...........................//
  #define numLEDs 24                                          // number of pixels in the daisy chain
  const int npxBright = 255;                                  // relative brighness of NeoPixels (0-255)
  Adafruit_NeoPixel npxLED = Adafruit_NeoPixel(               // neoPixel object name
    numLEDs, neoPixelPin, NEO_GRB + NEO_KHZ800);              // # of pixels, signal pin, type
    
//.............. MPR121 Touch Sensor .........................//

  Adafruit_MPR121 cap = Adafruit_MPR121();

//============== GLOBAL VARIABLES ============================//
/* Decrlare variables used by various functions.
 */
  byte npxCmd;                                                // 0-3 incoming from R.Pi
  byte npxPrev;                                               // previous loop's command from R.Pi

  uint16_t rawData = 0;
  uint16_t rawPrev = 0;
  bool handsOn;
  bool handsPrev;

  bool somethingNew;                                          // flag to indicate that some input has changed since the last loop

//============================================================//
//============== SETUP =======================================//
//============================================================//

void setup() {

//-------------- SERIAL MONITOR ------------------------------//
/*
 * ERPS note:
 * This is my standard initial report,
 * so that future me/us knows what sketch was loaded.
 * This can/will cange for ATAU
 */
  Serial.begin(9600);                                         //

  while(!Serial){
    delay(10);
  }

//-------------- PINMODES ------------------------------------//

//.............. NeoPixel Sign Command .......................//
  for (int cmd = 0; cmd < 2; cmd++){
    pinMode (npxCmdPin, INPUT);
  }

//-------------- HARDWARE SETUP ------------------------------//

//.............. NeoPixels ...................................//
  npxLED.begin();
  npxLED.setBrightness(npxBright);
  npxLED.show();

//............................................................//


//-------------- A/V FEEDBACK --------------------------------//

  if (!cap.begin(0x5A)){
    Serial.println("MPR121 not found");
    while(1);
  }
  Serial.println("Ready.");
  delay(serialDelay);
  Serial.println();
}

//============================================================//
//============== LOOP ========================================//
//============================================================//

void loop() {

  readNeoPixelCommand();
  updateSignColor();

  handPrints();

  if (handsOn){
    Serial.println("Hands On.");
    delay(serialDelay);
//    Serial.println();
  }
  else{
    Serial.println("Hands Off.");
    delay(serialDelay);
//    Serial.println();
  }

//============== ROUTINE MAINTAINENCE ========================//

//  delay(10);
  dbts();
  cycleReset();
}
