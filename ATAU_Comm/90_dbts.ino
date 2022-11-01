//============================================================//
//============== DEBUG & TROUBLESHOOT ========================//
//============================================================//
/*
 * This function's call in the vod loop is commented out.
 */
void dbts(){
  
  if (somethingNew){
//    portList();
  }
}

void portList(){
  Serial.println("A-A-AB-B-BC-C-CD-D-DE-E-E");
  Serial.println("1234512345123451234512345");
  for (int b = 24; b >= 0; b--){
    bool bitVal = bitRead(PISOregAns,b);
    Serial.print(bitVal);
  }
  Serial.println();
  
  for (int b = 24; b >= 0; b--){
    bool bitVal = bitRead(PISOregRead,b);
    Serial.print(bitVal);
  }
  Serial.println();
  Serial.println();
}
