//============================================================//
//============== SHIFT REGISTER I/O ==========================//
//============================================================//

/* These functions will read and write via PISO & SIOP shift registers.
 * They require the global variable byte arrays of:
 * byte PISOdata[numPISOregs];
 * 
 * Devices use 74HC165 PISO registers and 74HC595 SIPO registers.
 * 
 * This section updated  Aug 2022
 */

//-------------- RISING EDGE PUSLE ---------------------------//

/* This function will send a rising edge signal to the designated output pin.
 * Paramaters required are:
 * pinName (loadPin, latchPin, clockPin)
 */

void pulsePin(int pinName){
  int pulseTime = 10;
  digitalWrite(pinName, LOW);
  delayMicroseconds(pulseTime);
  digitalWrite(pinName, HIGH);
  delayMicroseconds(pulseTime);
}
