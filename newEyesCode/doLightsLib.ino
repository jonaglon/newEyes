  

void SetRgbwWheelVars(uint8_t WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    wheelR = 255 - WheelPos * 3;
    wheelG = 0;
    wheelB = WheelPos * 3;
    return;
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    wheelR = 0;
    wheelG = WheelPos * 3;
    wheelB = 255 - WheelPos * 3;
    return;
  }
  WheelPos -= 170;
  wheelR = WheelPos * 3;
  wheelG = 255 - WheelPos * 3;
  wheelB = 0;
  return;
}

void setGoodRandomColorVars() {
  uint16_t randomNum = random(20);
  switch (randomNum) {
    case 0: 
      goodColR = 255;
      goodColG = 0;
      goodColB = 0;
      goodColW = 0;
      break;
    case 1: 
      goodColR = 0;
      goodColG = 255;
      goodColB = 0;
      goodColW = 0;
      break;
    case 2: 
      goodColR = 0;
      goodColG = 0;
      goodColB = 255;
      goodColW = 0;
      break;
    case 3: 
      goodColR = 0;
      goodColG = 0;
      goodColB = 0;
      goodColW = 100;
      break;
    case 4: 
      goodColR = 245;
      goodColG = 7;
      goodColB = 225;
      goodColW = 0;
      break;
    case 5: 
      goodColR = 245;
      goodColG = 140;
      goodColB = 7;
      goodColW = 0;
      break;
    case 6: 
      goodColR = 2;
      goodColG = 133;
      goodColB = 142;
      goodColW = 0;
      break;
    case 7: 
      goodColR = 0;
      goodColG = 40;
      goodColB = 160;
      goodColW = 80;
      break;
    case 8: 
      goodColR = 82;
      goodColG = 104;
      goodColB = 4;
      goodColW = 0;
      break;
    case 9: 
      goodColR = 120;
      goodColG = 50;
      goodColB = 130;
      goodColW = 0;
      break;
    default: 
      SetRgbwWheelVars(random(255));
      goodColR = wheelR;
      goodColG = wheelG;
      goodColB = wheelB;
      goodColW = 0;
      break;
  }
}

void setGoodRGBRandomColorVars() {
  uint16_t randomNum = random(16);
  switch (randomNum) {
    case 0: 
      goodColR = 255;
      goodColG = 0;
      goodColB = 0;
      break;
    case 1: 
      goodColR = 0;
      goodColG = 255;
      goodColB = 0;
      break;
    case 2: 
      goodColR = 0;
      goodColG = 0;
      goodColB = 255;
      break;
    case 3: 
      goodColR = 245;
      goodColG = 7;
      goodColB = 225;
      break;
    case 4: 
      goodColR = 245;
      goodColG = 140;
      goodColB = 7;
      break;
    case 5: 
      goodColR = 2;
      goodColG = 133;
      goodColB = 142;
      break;
    case 6: 
      goodColR = 0;
      goodColG = 40;
      goodColB = 160;
      break;
    case 7: 
      goodColR = 82;
      goodColG = 104;
      goodColB = 4;
      break;
    case 8: 
      goodColR = 120;
      goodColG = 50;
      goodColB = 130;
      break;
    default: 
      SetRgbwWheelVars(random(255));
      goodColR = wheelR;
      goodColG = wheelG;
      goodColB = wheelB;
      goodColW = 0;
      break;
  }
}

uint16_t getCoord(uint16_t ledNum, uint16_t xOrY) {
  if (ledNum < 109)
    return eyeCoords[ledNum][xOrY];
  else
    return eyeCoords[ledNum+109][xOrY];
}

uint16_t quickAbsolute(int32_t number) {
  if (number < 0)
    return number * (-1);
  else
    return number;
}

//const int pupilRadius=26;
//const int maxRadius=42;
void drawEyeHexagon(int8_t ledNum, int32_t xCoord, int32_t  yCoord, int32_t pupilRadius, int32_t maxRadius, uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
  for (uint16_t j = 0; j < 109; j++) { 
    if ((eyeCoords[j][0] < (xCoord+pupilRadius)) && (eyeCoords[j][1] < (yCoord+pupilRadius))) {
      if ((eyeCoords[j][0] > (xCoord-pupilRadius)) && (eyeCoords[j][1] > (yCoord-pupilRadius))) {
        uint32_t x = quickAbsolute(xCoord-eyeCoords[j][0]);
        uint32_t y = quickAbsolute(yCoord-eyeCoords[j][1]);
        if (x + y < maxRadius) {
          setLedDirect(ledNum+j, r, g, b, w);
        }
      }
    }
  }
}

void drawEyeSquare(int32_t offSet, int32_t xCoord, int32_t  yCoord, int32_t radius, uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
  for(uint16_t j = 0; j < 109; j++) { 
    if ((eyeCoords[j][0] < (xCoord+radius)) && (eyeCoords[j][1] < (yCoord+radius))) {
      if ((eyeCoords[j][0] > (xCoord-radius)) && (eyeCoords[j][1] > (yCoord-radius))) {
        setLedDirect(offSet+j, r, g, b, w);
      }
    }
  }
}

void drawEyeIrisNoPupil(int8_t ledNum, int32_t xCoord, int32_t  yCoord, uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
  for (uint16_t j = 0; j < 109; j++) { 
    uint16_t eyeX = eyeCoords[j][0];
    uint16_t eyeY = eyeCoords[j][1];
    if ((eyeX < (xCoord+7)) && (eyeY < (yCoord+7))) {
      if ((eyeX > (xCoord-7)) && (eyeY > (yCoord-7))) {
        continue;
      }
    }    
    if ((eyeX < (xCoord+26)) && (eyeY < (yCoord+26))) {
      if ((eyeX > (xCoord-26)) && (eyeY > (yCoord-26))) {
        uint16_t x = quickAbsolute(xCoord-eyeX);
        uint16_t y = quickAbsolute(yCoord-eyeY);
        if (x + y < 42) {
          setLedDirect(ledNum+j, r, g, b, w);
        }
      }
    }
  }
}

// ledSections[17] needs 1 adding to it
void setSection(uint16_t section, uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
  for(int16_t j = ledSections[section]; j < ledSections[section+1]; j++) { 
    setLedDirect(j, r, g, b, w);
  }
}

void setSectionLed(uint16_t section, uint16_t ledNum, uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
  if (ledNum < 0)
    return;
    
    if (section == 0)
    {
      setLedDirect(ledNum, r, g, b, w);
    }
    else 
    {
      setLedDirect(ledNum+109, r, g, b, w);
    }
}

void everySingleLight(uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
  for(uint16_t j = 0; j < numLeds; j++) { 
    setLedDirect(j, r, g, b, w);
  }
}

void lightEyes(uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
  for(uint16_t j = 0; j < 218; j++) { 
    setLedDirect(j, r, g, b, w);
  }
}

void allOff() {
  for(uint16_t j = 0; j < numLeds; j++) {
    setLedDirect(j, 0, 0, 0, 0);
  }
}
void eyeBackground() {
  setSection(0, 20, 20, 20, 0);
  setSection(1, 20, 20, 20, 0);
}

void allOffBySection() {
    setSection(0, 0, 0, 0, 0);
    setSection(1, 0, 0, 0, 0);
}

void setLedDirect(uint16_t ledNum, uint8_t rVal, uint8_t gVal, uint8_t bVal, uint8_t wVal) {
if (ledNum < 0)
  return;

  strip.setPixelColor(ledNum, (strip.Color(rVal, gVal, bVal)));
}

