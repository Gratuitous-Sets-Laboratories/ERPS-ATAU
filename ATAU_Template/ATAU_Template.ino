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
  const String myNameIs = "ATAU_Template";                   // name of sketch
  const String verNum = "Alpha";                              // version of sketch
  const String lastUpdate = "2022 Sept";                   // last update

  const int stationNum = 1;                                   
  
  const int serialDelay = 500;
  
//  #define numPISOregs 4                                       // total number of PISO shift registers (data in)

//-------------- PIN DEFINITIONS  ----------------------------//
/* Most of the I/O pins on the Arduino Nano are hard-wired to various components on the ARDNEX2.
 * Pins not used for their standard fuction have header pins for alternate uses.
 */

  const int npxCmdPin[2] = {8,9};
  #define neoPixelPin 5           // data line to WS2812 (NeoPixel) via 470R resistor

  const int jackPin[4] = {A0,A1,A2,A3};
  
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
  #define numLEDs 32                                          // number of pixels in the daisy chain
  const int npxBright = 255;                                  // relative brighness of NeoPixels (0-255)
  Adafruit_NeoPixel npxLED = Adafruit_NeoPixel(               // neoPixel object name
    numLEDs, neoPixelPin, NEO_GRB + NEO_KHZ800);              // # of pixels, signal pin, type

//============== GLOBAL VARIABLES ============================//
/* Decrlare variables used by various functions.
 */
  byte npxCmd;                                                // 0-3 incoming from R.Pi
  byte npxPrev;                                               // previous loop's command from R.Pi

  int puzzleID;                                               // the ID number of the selected puzzle
  
//  byte PISOdata[numPISOregs];                                 // raw data from PISO shift registers
//  byte PISOprev[numPISOregs];                                 // previous loop's raw data

  long commGameRead;
  long commGamePrev;
  long commGameAns;

  byte cableNum[4];                                           // the cable/hose hooked up via analaog read
  byte cablePrev[4];                                          // previous loop's cable numbers
  byte cableAns[4];                                           //
  
  bool somethingNew;                                          // flag to indicate that some input has changed since the last loop
  bool solved;

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
  Serial.begin(19200);                                        // !! Serial monitor must be set to 19200 baud to read feedback !!
  Serial.println();
  Serial.println("Setup initialized.");
  Serial.print(myNameIs);                                     // report the sketch name and last update
  Serial.print(" ver ");
  Serial.println(verNum);
  Serial.print("Last updated on ");
  Serial.println(lastUpdate);

//-------------- PINMODES ------------------------------------//

//.............. NeoPixel Sign Command .......................//
  for (int cmd = 0; cmd < 2; cmd++){
    pinMode (npxCmdPin, INPUT);
  }
//.............. Analog Cables ...............................//
  for (int cab = 0; cab < 4; cab++){
    pinMode (jackPin[cab], INPUT);
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

//.............. (Pseudo)Random Seed .........................//
  randomSeed(analogRead(A7));
  genPuzzIDAnswer(stationNum);                    // 2 = Life Sup', 3 = Electrical, 4 = Comm

//-------------- A/V FEEDBACK --------------------------------//

  Serial.println("READY");
  Serial.println();
}

//============================================================//
//============== LOOP ========================================//
//============================================================//

void loop() {

  readNeoPixelCommand();
  readAnalogCables();
  readShiftRegisters();

  updateSignColor();

  if  (somethingNew){
    checkProgress(stationNum);
  }

  if (solved){
    Serial.print("Win!");
    delay(serialDelay);
    Serial.println();

    genPuzzIDAnswer(stationNum);
  }

//============== ROUTINE MAINTAINENCE ========================//

  dbts();
  cycleReset();
}