//============================================================//

void checkProgress(int game){

  switch(game){

    solved = true;                                            // assume the cable positions are correct
//------------------------------------------------------------//
    case 2:                                                   // Life Support or
    case 3:                                                   // Electrical
      for (int j = 0; j < 4; j++){                            // for each of the 4 jacks...
        if (cableNum[j] > cablePrev[j]){                      // if it's got a higher value than it used to...
          Serial.print("Connect.");                           // inform R.Pi of a connect
          delay(serialDelay);                                 // this delay is set in the global constants
          Serial.println();                                   // print a blank line to clear the Serial
        }
        else if (cableNum[j] < cablePrev[j]){                 // otherwise, if the jack has a lower value...
          Serial.print("Disconnect.");                         // inform R.Pi of a disconnect
          delay(serialDelay);
          Serial.println();
        }
      }
      for (int j = 0; j < 4; j++){                            // for each of the 4 jacks...
        if (cableNum[j] != cableAns[j]){                      // if it's cable doesn't match the answer...
          solved = false;                                     // you're WRONG!
        }
      }
      break;                                                  // EXIT SWITCH CASE
//------------------------------------------------------------//
    case 4:                                                   // Communications
      if (PISOregRead < PISOregPrev){                       // if the new long is less than the old (active LOWs)... 
        Serial.print("Connect.");                              // inform R.Pi of a disconnect
        delay(serialDelay);
        Serial.println();
      }
      else if (PISOregRead > PISOregPrev){                  // otherwise, if it's higher...
        Serial.print("Disconnect.");                           // inform R.Pi of a disconnect
        delay(serialDelay);
        Serial.println();
      }
      if (PISOregRead != PISOregAns){
        solved = false;
      }
      break;
//------------------------------------------------------------//
    case 8:                                                   // Cargo
      int cargoStream = PISOregRead % 32768;
      byte magsInBay[4];
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
      
      break;
  }
  if (solved){
    Serial.print("Win!");
    delay(serialDelay);
    Serial.println();
    
  }
}
