//============================================================//
//============== INPUT FUNCTIONS =============================//
//============================================================//

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

//-------------- Register Inputs -----------------------------//

void readShiftRegisters(int bitNum){

  pulsePin(loadPin);
  for (int bitPos = 0; bitPos < bitNum; bitPos++){
    bool bitVal = digitalRead(dataInPin);
    if(stationNum == 4 && bitPos == 14){
      pulsePin(clockPin);
    }
    bitWrite(PISOregRead,bitPos,bitVal);
    pulsePin(clockPin);
  }
  if (PISOregRead != PISOregPrev){
    somethingNew = true;
  }
}
