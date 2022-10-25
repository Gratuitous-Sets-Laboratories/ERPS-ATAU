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

//-------------- Read Hand Prints ----------------------------//

void handPrints(){

  rawData = cap.touched();
  
  if (rawData % 4 == 3){
    handsOn = true;
  }
  else{
    handsOn = false;
  }

  if (rawData != rawPrev){
    somethingNew = true;
  }
/*  
  currtouched = cap.touched();
  
  for (uint8_t i=0; i<12; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
      Serial.print(i); Serial.println(" touched");
    }
    // if it *was* touched and now *isnt*, alert!
    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
      Serial.print(i); Serial.println(" released");
    }
  }
*/  
}
