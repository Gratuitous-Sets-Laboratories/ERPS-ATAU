//-------------- Read NPX Command ----------------------------//

void readNeoPixelCommand(){
  
  npxCmd = 0;                                                 // assume no command
  
  for (int pos = 0; pos < 2; pos++){                          // for each bit in the command data...
    bool bitVal = digitalRead(npxCmdPin[pos]);                // read the approriate pin
    bitWrite(npxCmd, pos, bitVal);                            // and write that bitVal to the position
  }
  
  if (npxCmd != npxPrev){                                     // if this is different from the last loop
    somethingNew = true;                                      // raise the somethingNew flag
  }
}
//-------------- Analog Inputs -------------------------------//

void readAnalogCables(){
/*
 * RESISTOR VALUES
 * 1  3K3
 * 2  1K5
 * 3  680R
 * 4  220R
 */
  int target[5] = {0,237,409,609,838};                        // calculated analog read values for each key's chosen resistor
  int range = 10;                                             // the margin of error (+/-) to allow a key to read

  for (int j = 0; j < 4; j++){                                // for each of the 4 jacks/ports...
    int rawRead = analogRead(jackPin[j]);                     // get an analog read
    
    cableNum[j] = 0;                                          // assume there is no cable
    for (int c = 1; c <= 4; c++) {                            // for each of 4 possible cables...
      if (rawRead >= target[c]-range                          // if the read is at or above the low end...
      && rawRead <= target[c]+range) {                        // and it is at or below the high end...
        cableNum[j] = c;                                      // that is the jack's cable number
      }
    }
    if (cableNum[j] != cablePrev[j]){                         // if that jack's cable has changed...
      somethingNew = true;                                    // raise the somethingNew flag
    }
  }
}
//-------------- Register Inputs -----------------------------//

void readShiftRegisters(int bitNum){

  pulsePin(loadPin);
  for (int bitPos = 0; bitPos < bitNum; bitPos++){
    bool bitVal = digitalRead(dataInPin);
    if(stationNum == 4 && bitPos == 15){
      pulsePin(clockPin);
    }
    bitWrite(PISOregRead,bitPos,bitVal);
    pulsePin(clockPin);
  }
  if (PISOregRead != PISOregPrev){
    somethingNew = true;
  }
/*  
  readPISO(0,numPISOregs);                                    // read all PISO registers
  for (int reg = 0; reg < numPISOregs; reg++){                // for each register...
    if (PISOdata[reg] != PISOprev[reg]){                      // if its data has changed...
      somethingNew = true;                                    // raise the somethingNew flag
    }
  }
*/
}

//

void readPISO(int fReg, int lReg){

  pulsePin(loadPin);                                       // rend a rising edge signal to load the current data into the registers
  
  for (int dumpReg = 0; dumpReg < fReg; dumpReg++){           // for each register before the first one called for...
    for (int dumpBit = 0; dumpBit < 8; dumpBit++){            // for each bit in that register's byte...
      pulsePin(clockPin);                                  // pulse the clock pin to skip that bit
    }
  }
  for (int readReg = fReg; readReg < lReg+1; readReg++){      // for each requested register...
    for (int pos = 0; pos < 8; pos++){                        // for each bit in that register's byte...
      bool val = digitalRead(dataInPin);                      // read the bit's value from the input pin
      bitWrite(PISOdata[readReg], pos, val);                  // write it to the approriate position in the appropriate byte
      pulsePin(clockPin);                                  // pulse the clock pin to advance the next bit
    }
  }
}
