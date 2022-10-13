void dbts(){
  
  if (somethingNew){
//    analogReport();
//    gridReport();
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

void gridReport(){
  Serial.println("GRD\tA\tB\tC\tD\tE");
  for (int j = 24; j > 19; j--){
    Serial.print("\t");
    bool bitVal = bitRead(PISOregRead,j);
    Serial.print(bitVal);
  }
  Serial.println();
  for (int j = 19; j > 14; j--){
    Serial.print("\t");
    bool bitVal = bitRead(PISOregRead,j);
    Serial.print(bitVal);
  }
  Serial.println();
  for (int j = 14; j > 9; j--){
    Serial.print("\t");
    bool bitVal = bitRead(PISOregRead,j);
    Serial.print(bitVal);
  }
  Serial.println();
  for (int j = 9; j > 4; j--){
    Serial.print("\t");
    bool bitVal = bitRead(PISOregRead,j);
    Serial.print(bitVal);
  }
  Serial.println();
  for (int j = 4; j >= 0; j--){
    Serial.print("\t");
    bool bitVal = bitRead(PISOregRead,j);
    Serial.print(bitVal);
  }
  Serial.println();
}
void regCheck(){
      for (int r = 0; r < 4; r++){
      Serial.print("Reg# ");
      Serial.print(r);
      Serial.print(" ");
      Serial.println(PISOdata[r],BIN);
    }
    Serial.println();
}
