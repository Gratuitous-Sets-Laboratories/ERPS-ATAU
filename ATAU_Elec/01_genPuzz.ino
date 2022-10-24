
//============================================================//

void genPuzzIDAnswer(){

  puzzleID = random(1,10);                                    // pick a number between 1 & 9
  
//------------------------------------------------------------//

  byte ElecAnsGrid[36] = {                                // 1 = Main, 2 = Aux, 3 = Reactor, 4 = Cooling
    1,3,2,4,
    1,4,3,2,
    4,2,1,3,
    3,4,1,2,
    2,1,3,4,
    3,1,4,2,
    4,3,2,1,
    4,2,3,1,
    2,3,4,1
  };
  for (int j = 0; j < 4; j++){                            // for each jack in the electrical game...
    cableAns[j] = ElecAnsGrid[(((puzzleID-1)*4)+j)];      // slot in the approriate value from the answerGrid
  }
}

//------------------------------------------------------------//

void analogAnsReport(){
  Serial.println("Correct Answer as follows:");
  for (int c = 0; c < 4; c++){
    Serial.print(cableAns[c]);
    if (c < 3){
      Serial.print(" - ");
    }
  }
  Serial.println();
}
