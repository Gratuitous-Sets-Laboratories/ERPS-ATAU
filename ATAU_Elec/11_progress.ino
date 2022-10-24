//============================================================//

void checkProgress(){

  solved = true;                                              // assume the the player is correct

  if (!firstLoop){
    for (int j = 0; j < 4; j++){                              // for each of the 4 jacks...
      if (cableNum[j] > cablePrev[j]){                        // if it's got a higher value than it used to...
        Serial.print("Wire Connect.");                        // inform R.Pi of a connect
        delay(serialDelay);                                   // this delay is set in the global constants
        Serial.println();                                     // print a blank line to clear the Serial
      }
      else if (cableNum[j] < cablePrev[j]){                   // otherwise, if the jack has a lower value...
        Serial.print("Wire Disconnect.");                     // inform R.Pi of a disconnect
        delay(serialDelay);
        Serial.println();
      }
    }
  }
  for (int j = 0; j < 4; j++){                                // for each of the 4 jacks...
    if (cableNum[j] != cableAns[j]){                          // if it's cable doesn't match the answer...
      solved = false;                                         // you're WRONG!
    }
  }
}
