//============================================================//
//============== DEBUG & TROUBLESHOOT ========================//
//============================================================//
/*
 * This function's call in the vod loop is commented out.
 */
void dbts(){
  
  if (somethingNew){
    analogReport();
    Serial.println(PISOregRead,BIN);
  }
}

void analogReport(){
  for (int j = 0; j < 4; j++){
    Serial.print(cableNum[j]);
    if (j < 3){
      Serial.print(" - ");  
    }
  }
  Serial.println();
}
