/*
 * Cycle Reset
 */

void cycleReset(){

  npxPrev = npxCmd;
  for (int j = 0; j < 4; j++) cablePrev[j] = cableNum [j];
  PISOregPrev = PISOregRead;

  for (int reg = 0; reg < 3; reg++){
    PISOprev[reg] = PISOdata[reg];
  }

  if (somethingNew){
    delay(debounceDelay);
  }
/*
  for (int reg = 0; reg < numPISOregs; reg++){
    PISOprev[reg] = PISOdata[reg];
  }
*/  
  somethingNew = false;
}
