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
