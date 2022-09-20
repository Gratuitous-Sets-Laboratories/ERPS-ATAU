//============================================================//

void genPuzzIDAnswer(int game){

  puzzleID = random(1,10);                                    // pick a number between 1 & 9
  
  switch (game){
    case 2:                                                   // Life Support
      byte LifeAnsGrid[36] = {                                 // 1 = CO2, 2 = Air, 3 = Tank, 4 = Regulator
        /*1*/1,2,3,4,
        /*2*/2,1,3,4,
        /*3*/3,1,4,2,
        /*4*/3,2,4,1,
        /*5*/3,4,2,1,
        /*6*/4,1,2,3,
        /*7*/4,2,1,3,
        /*8*/1,4,2,3,
        /*9*/2,3,1,4
      };
      for (int j = 0; j < 4; j++){                            // for each jack in the life support game...
        cableAns[j] = LifeAnsGrid[((puzzleID-1*4)+j)];        // slot in the approriate value from the answerGrid
      }
      break;
//------------------------------------------------------------//
    case 3:                                                   // Electrical
      byte ElecAnsGrid[36] = {                                 // 1 = Main, 2 = Aux, 3 = Reactor, 4 = Cooling
        /*1*/1,2,3,4,
        /*2*/1,4,2,3,
        /*3*/2,3,4,1,
        /*4*/2,4,1,3,
        /*5*/3,1,2,4,
        /*6*/3,4,1,2,
        /*7*/4,2,3,1,
        /*8*/4,3,2,1,
        /*9*/4,1,2,3
      };
      for (int j = 0; j < 4; j++){                            // for each jack in the electrical game...
        cableAns[j] = ElecAnsGrid[((puzzleID-1*4)+j)];        // slot in the approriate value from the answerGrid
      }
      break;
//------------------------------------------------------------//
    case 4:                                                   // Communiucations
      long answerList[9] = {
             //AAAAABBBBBCCCCCDDDDDEEEEE
             //1234512345123451234512345
        /*1*/0b1111110100111010100011111,
        /*2*/0b1110110110111111010101100,
        /*3*/0b1110101111110100101011011,
        /*4*/0b1101110011111010011011101,
        /*5*/0b1101110111101011110001111,
        /*6*/0b1011001011011111111010011,
        /*7*/0b1101111011010010001111111,
        /*8*/0b0111101011101001101110111,
        /*9*/0b1111001110110010111010111
             //1234512345123451234512345
             //AAAAABBBBBCCCCCDDDDDEEEEE
        };
      commGameAns = answerList[puzzleID];
      break;
  }
  Serial.print("PuzzleID #");
  Serial.print(puzzleID);
  delay(serialDelay);
  Serial.println();

}
