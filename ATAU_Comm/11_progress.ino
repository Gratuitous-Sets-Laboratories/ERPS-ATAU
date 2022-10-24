//============================================================//
//============== MAIN GAME FUNCTIONS =========================//
//============================================================//

void checkProgress(){

  solved = true;                                              // assume the the player is correct
  if (!firstLoop){
    if (PISOregRead < PISOregPrev){                         // if the new long is less than the old (active LOWs)... 
      Serial.println("Connect.");                             // inform R.Pi of a disconnect
      delay(serialDelay);
      Serial.println();
    }
    else if (PISOregRead > PISOregPrev){                    // otherwise, if it's higher...
      Serial.println("Disconnect.");                          // inform R.Pi of a disconnect
      delay(serialDelay);
      Serial.println();
    }
  }
  if (PISOregRead != PISOregAns){
    solved = false;
  }
}
