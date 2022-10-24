//============================================================//
//============== GENERATE PUZZLE ID & ANSWER =================//
//============================================================//

void genPuzzIDAnswer(){

  puzzleID = random(1,10);                                    // pick a number between 1 & 9
  

//------------------------------------------------------------//
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
    /*5*/0b1101110111101011110001101,
    /*6*/0b1011001011011111111010011,
    /*7*/0b1101111011010010001111111,
    /*8*/0b0111101011101001101110111,
    /*9*/0b1111001110110010111010111
         //1234512345123451234512345
         //AAAAABBBBBCCCCCDDDDDEEEEE
    };
  PISOregAns = answerList[puzzleID];

}
