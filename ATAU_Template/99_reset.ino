/*
 * Cycle Reset
 */

void cycleReset(){

  npxPrev = npxCmd;
  for (int j = 0; j < 4; j++) cablePrev[j] = cableNum [j];
  commGamePrev = commGameRead;
/*
  for (int reg = 0; reg < numPISOregs; reg++){
    PISOprev[reg] = PISOdata[reg];
  }
*/  
  somethingNew = false;
}
