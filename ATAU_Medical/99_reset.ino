//============================================================//
//============== CYCLE RESET =================================//
//============================================================//
void cycleReset(){

  npxPrev = npxCmd;

  rawPrev = rawData;
  handsPrev = handsOn;

  if (somethingNew){
    delay(debounceDelay);
    Serial.println(rawData%4);
  }
  
  somethingNew = false;
}
