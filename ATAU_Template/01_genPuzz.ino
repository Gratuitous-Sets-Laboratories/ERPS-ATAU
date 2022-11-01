//============================================================//

void genPuzzIDAnswer(int game){

  puzzleID = random(1,10);                                    // pick a number between 1 & 9
  
  switch (game){
//------------------------------------------------------------//
    case 2:                                                   // Life Support
      int LifeAnsGrid[36] = {                                 // 1 = CO2, 2 = Air, 3 = Tank, 4 = Regulator
        /*1*/ 1,2,3,4,
        /*2*/ 2,1,3,4,
        /*3*/ 3,1,4,2,
        /*4*/ 3,2,4,1,
        /*5*/ 3,4,2,1,
        /*6*/ 4,1,2,3,
        /*7*/ 4,2,1,3,
        /*8*/ 1,4,2,3,
        /*9*/ 2,3,1,4
      };
      for (int j = 0; j < 4; j++){                            // for each jack in the life support game...
        cableAns[j] = LifeAnsGrid[(((puzzleID-1)*4)+j)];      // slot in the approriate value from the answerGrid
      }
      break;
//------------------------------------------------------------//
    case 3:                                                   // Electrical
      byte ElecAnsGrid[36] = {                                // 1 = Main, 2 = Aux, 3 = Reactor, 4 = Cooling
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
        cableAns[j] = ElecAnsGrid[(((puzzleID-1)*4)+j)];      // slot in the approriate value from the answerGrid
      }
      break;
//------------------------------------------------------------//
    case 4:                                                   // Communiucations
/*
 * Wiring Hookup to the shift registers...
 * For the Columns:
 * Column A is on the red marked ribbon cable, brown-green.
 * Column B is on the red marked ribbon cable, black-blue.
 * Column C is on the black marked ribbon cable, brown-green.
 * Column D is on the black marked ribbon cable, black-blue.
 * Column E is on the yellow marked half-ribbon cable, brown-green.
 * For the number rows:
 * 1 is brown or black
 * 2 is red or white
 * 3 is orange or gray
 * 4 is yellow or purple
 * 5 is green or blue
 */
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
      PISOregAns = answerList[puzzleID-1];
      break;
//------------------------------------------------------------//
    case 8:                                                   // Cargo
      byte CargoAnsGrid[36] = {                               // 1 = Grav Lens, 2 = Flux Cap, 3 = Misc Tard, 4 = Anti-Mat
           //H I R B                                             Heat, Inert, Refrig, Bulk
        /*1*/1,2,3,4,
        /*2*/1,4,2,3,
        /*3*/3,1,2,4,
        /*4*/4,1,3,2,
        /*5*/4,2,1,3,
        /*6*/4,3,1,2,
        /*7*/2,4,3,1,
        /*8*/4,3,2,1,
        /*9*/3,2,4,1
      };
      for (int j = 0; j < 4; j++){                            // for each jack in the electrical game...
        cableAns[j] = CargoAnsGrid[((puzzleID-1*4)+j)];       // slot in the approriate value from the answerGrid
      }
      break;
  }
//------------------------------------------------------------//
//  Serial.print("PuzzleID #");
//  Serial.print(puzzleID);
//  delay(serialDelay);
//  Serial.println();
//  analogAnsReport();                                          // !! for DBTS only !! comment out of final
}

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
