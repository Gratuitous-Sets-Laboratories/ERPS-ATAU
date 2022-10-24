void dbts(){
  
  if (somethingNew){
//    analogReport();
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
