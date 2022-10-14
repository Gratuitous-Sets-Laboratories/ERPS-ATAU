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
  const String myNameIs = "Electrical";                      // name of sketch
  const String verNum = "1.0";                                // version of sketch
  const String lastUpdate = "2022 Oct";                       // last update

  const int stationNum = 3;                                   // 2 = Life Sup', 3 = Electrical, 4 = Comm, 8 = Cargo    
  
  const int serialDelay = 500;                                // length of time before sending a blank line via Serial
  const int debounceDelay = 50;                               // delay after a "somethingNew" to avoid bouncing comm to R.Pi

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
  long PISOregAns;

  byte cableNum[4];                                           // the cable/hose hooked up via analaog read
  byte cablePrev[4];                                          // previous loop's cable numbers
  byte cableAns[4];                                           //
  
  bool somethingNew;                                          // flag to indicate that some input has changed since the last loop
  bool solved;

  //
  byte PISOdata[3];
  byte PISOprev[3];

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
/*
  Serial.println();
  Serial.println("Setup initialized.");
  Serial.print(myNameIs);                                     // report the sketch name and last update
  Serial.print(" ver ");
  Serial.println(verNum);
  Serial.print("Last updated on ");
  Serial.println(lastUpdate);
*/
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

//............................................................//
  randomSeed(analogRead(A7));
  readNeoPixelCommand();
  readAnalogCables();
  readShiftRegisters(25);
  cycleReset();
  genPuzzIDAnswer(stationNum);

//-------------- A/V FEEDBACK --------------------------------//

  while(!Serial){}
  Serial.println("Ready.");
  delay(serialDelay);
  Serial.println(puzzleID);
  delay(serialDelay);
  Serial.println();
}

//============================================================//
//============== LOOP ========================================//
//============================================================//

void loop() {

  readNeoPixelCommand();
/* Comment out one or both of the below functions as needed by each station. */
  readAnalogCables();                                         // used for Life Support & Electrical
//  readShiftRegisters(25);                                     // 25 for Comm, 16 for Cargo

  updateSignColor();

  if  (somethingNew){
    checkProgress(stationNum);
  
    if (solved){
      Serial.println("Win.");
      while(solved){
                                                              // infinite loop
      }
    }
  }

//============== ROUTINE MAINTAINENCE ========================//

//  dbts();
  cycleReset();
}
