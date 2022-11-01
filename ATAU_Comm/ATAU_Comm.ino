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
  
//-------------- SETTINGS & GLOBAL CONSTANTS -----------------//
/* Define constraits used by various functions.
 * Variables using '#define' are defined by hardware, and should be left alone.
 * Variables using 'const' can be changed to tune the puzzle.
 */
  const String myNameIs = "ATAU_Comm";                    // name of sketch
  const String verNum = "1.1";                               // version of sketch
  const String lastUpdate = "2022 Oct 24";                      // last update

  const int stationNum = 4;                                   // 2 = Life Sup', 3 = Electrical, 4 = Comm, 8 = Cargo    
  
  const int serialDelay = 500;                                // length of time before sending a blank line via Serial
  const int debounceDelay = 50;                               // delay after a "somethingNew" to avoid bouncing comm to R.Pi

//-------------- PIN DEFINITIONS  ----------------------------//
/* Most of the I/O pins on the Arduino Nano are hard-wired to various components on the ARDNEX2.
 * Pins not used for their standard fuction have header pins for alternate uses.
 */

  const int npxCmdPin[2] = {8,9};
  #define neoPixelPin 5           // data line to WS2812 (NeoPixel) via 470R resistor
  
  #define loadPin     2           // parallel connection to all 74HC165 PISO shift registers, pin 1
  #define dataInPin   3           // serial connection to nearest 74HC165 PISO shift register, pin 9
  #define clockPin    7           // parallel connection to all shift registers (74HC165 pin 2 / 74HC595 pin 11)

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

//============== GLOBAL VARIABLES ============================//
/* Decrlare variables used by various functions.
 */
  byte npxCmd;                                                // 0-3 incoming from R.Pi
  byte npxPrev;                                               // previous loop's command from R.Pi

  int puzzleID;                                               // the ID number of the selected puzzle

  long PISOregRead;
  long PISOregPrev;
  long PISOregAns;                                            //
  
  bool somethingNew;                                          // flag to indicate that some input has changed since the last loop
  bool solved;
  bool firstLoop = true;

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

  Serial.begin(9600);                                        //

//-------------- PINMODES ------------------------------------//

//.............. NeoPixel Sign Command .......................//
  for (int cmd = 0; cmd < 2; cmd++){
    pinMode (npxCmdPin, INPUT);
  }
//.............. Shift Registers .............................//
  pinMode (clockPin, OUTPUT);
  pinMode (loadPin, OUTPUT);
  pinMode (dataInPin, INPUT);

//-------------- HARDWARE SETUP ------------------------------//

//.............. NeoPixels ...................................//
  npxLED.begin();
  npxLED.setBrightness(npxBright);
  npxLED.show();

//............................................................//
  randomSeed(analogRead(A7));
  
  solved = true;
  while(solved){
    genPuzzIDAnswer();
    readShiftRegisters(25);
    checkProgress();
  }
//-------------- A/V FEEDBACK --------------------------------//

  Serial.println("Ready.");
  delay(serialDelay);
  Serial.print(puzzleID);
  Serial.println(".");
  delay(serialDelay);
  Serial.println();
}

//============================================================//
//============== LOOP ========================================//
//============================================================//

void loop() {

  readNeoPixelCommand();
  updateSignColor();
  
  readShiftRegisters(25);                                     // 25 for Comm, 16 for Cargo

  if  (somethingNew){
    checkProgress();
  
    if (solved){
      Serial.println("Win.");
      
      while(1){
        readNeoPixelCommand();
        updateSignColor();
      }
    }
  }

//============== ROUTINE MAINTAINENCE ========================//

  firstLoop = false;
  dbts();
  cycleReset();
}
