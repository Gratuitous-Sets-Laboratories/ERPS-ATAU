//============================================================//
//============== GENERATE PUZZLE ID & ANSWER =================//
//============================================================//

void genPuzzIDAnswer(){

  puzzleID = random(1,10);                                    // pick a number between 1 & 9
  
 
//------------------------------------------------------------//
  byte CargoAnsGrid[36] = {                               // 1 = Grav Lens, 2 = Flux Cap, 3 = Misc Tard, 4 = Anti-Mat
    1,2,3,4,
    1,4,2,3,
    3,1,2,4,
    4,1,3,2,
    3,2,1,4,
    4,3,1,2,
    2,4,3,1,
    4,3,2,1,
    3,2,4,1
  };
  for (int j = 0; j < 4; j++){                            // for each jack in the electrical game...
    cableAns[j] = CargoAnsGrid[(((puzzleID-1)*4)+j)];     // slot in the approriate value from the answerGrid
  }
}

//============================================================//

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
