//============================================================//
//============== CYCLE RESET =================================//
//============================================================//
void cycleReset(){

  npxPrev = npxCmd;

  rawPrev = rawData;
  handsPrev = handsOn;

  if (somethingNew){
    delay(debounceDelay);
  }
  
  somethingNew = false;
}
