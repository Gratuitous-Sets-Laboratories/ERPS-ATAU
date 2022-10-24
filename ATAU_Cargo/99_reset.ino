//============================================================//
//============== CYCLE RESET =================================//
//============================================================//
void cycleReset(){

  npxPrev = npxCmd;
  for (int j = 0; j < 4; j++) cablePrev[j] = cableNum [j];

  PISOregPrev = PISOregRead;

  if (somethingNew){
    delay(debounceDelay);
  }
  
  somethingNew = false;
}
