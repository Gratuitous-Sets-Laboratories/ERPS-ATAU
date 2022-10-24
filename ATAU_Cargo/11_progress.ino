//============================================================//
//============== MAIN GAME FUNCTIONS =========================//
//============================================================//

void checkProgress(){

  solved = true;                                              // assume the the player is correct

  uint16_t cargoStream = PISOregRead % 32768;             // make a 16bit copy of the PISOregRead
  byte magsInBay[4];                                      // the magnetic reads from each bay
  for (int b = 0; b < 4; b++){
    magsInBay[b] = cargoStream % 16;
    cargoStream = cargoStream >> 4;
  }
  for (int b = 0; b < 4; b++){
    cableNum[b] = 0;
    if      (magsInBay[b] == 0b1010) cableNum[b] = 1;
    else if (magsInBay[b] == 0b1001) cableNum[b] = 2;
    else if (magsInBay[b] == 0b0110) cableNum[b] = 3;
    else if (magsInBay[b] == 0b0101) cableNum[b] = 4;
  }

  if (!firstLoop){
    String bayName[4] = {"Heat","Inert","Refrig","Bulk"};
    for (int b = 0; b < 4; b++){
      if (cableNum[b] > cablePrev[b]){
        Serial.print(bayName[b]);
        Serial.print(" On.");
        delay (serialDelay);
        Serial.println();
      }
      else if (cableNum[b] < cablePrev[b]){
        Serial.print(bayName[b]);
        Serial.print(" Off.");
        delay (serialDelay);
        Serial.println();
      }
      if (cableNum[b] != cableAns[b]){
        solved = false;
      }
    }
  }
}
