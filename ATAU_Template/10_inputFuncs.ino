//-------------- Read NPX Command ----------------------------//

void readNeoPixelCommand(){
  
  npxCmd = 0;
  
  for (int pos = 0; pos < 2; pos++){
    bool bitVal = digitalRead(npxCmdPin[pos]);
    bitWrite(npxCmd, pos, bitVal);
  }
  
  if (npxCmd != npxPrev){
    somethingNew = true;
  }
}
//-------------- Analog Inputs -------------------------------//

void readAnalogCables(){
  
  int target[5] = {0,237,409,609,838};                        // calculated analog read values for each key's chosen resistor
  int range = 10;                                             // the margin of error (+/-) to allow a key to read

  for (int j = 0; j < 4; j++){
    int rawRead = analogRead(jackPin[j]);
    cableNum = 0;                                             // assume there is no cable
    
    for (int c = 1; c <= 4; c++) {                             // for each of 7 possible keys...
      if (rawRead >= target[c]-range                        // if the read is at or above the low end...
      && rawRead <= target[c]+range) {                      // and it is at or below the high end...
        cableNum[j] = c;                                        // that is the key number
      }
    }
    if (cableNum[j] != cablePrev[j]){
      somethingNew = true;
    }
  }
}
//-------------- Register Inputs -----------------------------//

void readShiftRegisters(){
  
  readPISO(0,numPISOregs);                                    // read all PISO registers
  for (int reg = 0; reg < numPISOregs; reg++){                // for each register...
    if (PISOdata[reg] != PISOprev[reg]){                      // if its data has changed...
      somethingNew = true;                                    // raise the somethingNew flag
    }
  }
}
