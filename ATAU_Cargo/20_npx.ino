//============================================================//
//============== STATION SIGN UPDATE =========================//
//============================================================//

//-------------- Update Station Sign -------------------------//

void updateSignColor(){
  
  uint32_t signColor [4] = {0,0xFF0000,0x00FF00,0x8888BB};    // hexidecimal sign color for each npxCmd ?0xGGRRBB?

  for ( int pxl = 0; pxl < numLEDs; pxl++){                   // for each pixel in the sign...
    npxLED.setPixelColor(pxl,signColor[npxCmd]);              // set it to the npxCmd color
  }
  npxLED.show();                                              // illuminate the sign
}
  
