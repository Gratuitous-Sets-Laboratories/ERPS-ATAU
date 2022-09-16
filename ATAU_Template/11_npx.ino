//-------------- Update Station Sign -------------------------//

void updateSignColor(){
  
  uint32_t signColor [4] = {0,0xFF0000,0x00FF00,0x999999};

  for ( int pxl = 0; pxl < numLEDs; pxl++){
    npxLED.setPixelColor(pxl,signColor[npxCmd]);
  }
  npxLED.show();
}
  
