/*
 * Cycle Reset
 */

void cycleReset(){

  npxPrev = npxCmd;
  
  for (int j = 0; j < 4; j++) cablePrev[j] = cableNum [j];

  if (somethingNew){
    delay(debounceDelay);
  }
  
  somethingNew = false;
}
