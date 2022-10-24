//============================================================//
//============== CYCLE RESET =================================//
//============================================================//
void cycleReset(){

  npxPrev = npxCmd;

  PISOregPrev = PISOregRead;

  if (somethingNew){
    delay(debounceDelay);
  }

  somethingNew = false;
}
