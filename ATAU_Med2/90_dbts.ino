//============================================================//
//============== DEBUG & TROUBLESHOOT ========================//
//============================================================//
/*
 * This function's call in the vod loop is commented out.
 */
void dbts(){
/*
  for (int c = 0; c < 2; c++){
    Serial.print(cap.filteredData(c));
    Serial.print(" ");
    Serial.print(cap.baselineData(c));
    Serial.print(" | ");
  }
  Serial.println();
*/
  if (somethingNew){
//    Serial.println(rawData,BIN);
  }
}
