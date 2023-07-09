/* ******************************* EYES & MOUTH ********************************** */

void eyeController() {
  // heartEyes();
  doNormalEyes();
  // doAutomaticEyesWithPatterns();
  // if (lastEyeMoveTime+10000 > timey) {
  //   if (eyesAutomatic) {
  //     resetEyes();
  //     eyesAutomatic = false;
  //   }
  //   
  // } else {
  //   if (!eyesAutomatic) {
  //     resetEyes();
  //     eyesAutomatic = true;
  //   }
  //   doAutomaticEyesWithPatterns();
  // }
}

uint8_t selectedAnim = 0;
unsigned long eyeAnimStart=5000;
uint32_t eyePatternLength=1000;
void doAutomaticEyesWithPatterns() {
  // if (timey > (eyeAnimStart + eyePatternLength)) {
  //   // animation over, reset
  //   selectedAnim = random(8);
  //   if ((selectedAnim == 4) || (selectedAnim == 5)) {
  //     eyePatternLength = random(1000,3000);     
  //   } else {
  //     eyePatternLength = random(4000,10000);
  //   }
  //   eyeAnimStart = timey + random(10000,30000);
  //   resetEyes();
  //   doNormalEyes();
  // } else if (timey > eyeAnimStart) {
    uint32_t percIntoAnim = ((timey - eyeAnimStart)*100)/(eyePatternLength/2);
    switch (selectedAnim) {
      case 0:
        heartEyes();
        break;
      case 1:
        pacManEyes();
        break;
      case 2:
        smileyEyes();
        break;
      case 3:
        doStonerEyes();
        break;
      case 4:
        hypnotEyes();
        break;
      case 5:
        flashingEyes();
        break;
      case 6:
        rollEyes(percIntoAnim);
        break;
      case 7:
        lookLeftAndRight(percIntoAnim);
        break;
      default:
        doAutomaticEyes();
        break;
  // } else {
  //   doAutomaticEyes();
  }
}

void heartEyes() {
  changeEyeCol(1);

  for(uint8_t j = 0; j < 93; j++) {
    setSectionLed(0, j, 0, 0, 0, 0);
    setSectionLed(1, j, 0, 0, 0, 0);
  }

  for(uint8_t j = 0; j < 56; j++) {
    setSectionLed(0, eyeHeartLeds[j], eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(1, eyeHeartLeds[j], eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
  }
}


void doAutomaticEyes() {
  
  if (whiteEyeBackground) {
    for(uint8_t j = 0; j < 110; j++) {
      setSectionLed(0, j, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
      setSectionLed(1, j, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    }
  }
  drawEyeIrisNoPupil(ledSections[0], 64+leftEyeX, 64-leftEyeY, 0, 0, 0, 0);
  drawEyeIrisNoPupil(ledSections[1], 64+rightEyeX, 64-rightEyeY, 0, 0, 0, 0);
  doBlinking();
  doLeftWink();
  doRightWink();
}

void doNormalEyes() {
  if (whiteEyeBackground) {
    for(uint8_t j = 0; j < 109; j++) {
      setSectionLed(0, j, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
      setSectionLed(1, j, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    }
  }
  drawIrisAndPupil();
  doBlinking();
  doLeftWink();
  doRightWink();
}

void drawIrisAndPupil() {
  // iris
  drawEyeHexagon(ledSections[0], leftEyeX, leftEyeY, 26, 42, 0, 0, 0, 0);
  drawEyeHexagon(ledSections[1], rightEyeX, rightEyeY, 26, 42, 0, 0, 0, 0);

  // pupil
  // drawEyeSquare(ledSections[0], 90+leftEyeX, 90-leftEyeY, 7, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
  // drawEyeSquare(ledSections[1], 30+rightEyeX, 30-rightEyeY, 7, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
  drawEyeSquare(ledSections[0], leftEyeX, leftEyeY, 7, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
  drawEyeSquare(ledSections[1], rightEyeX, rightEyeY, 7, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
}

void changeEyeBackground(bool eyeBackgroundToWhite) {
  whiteEyeBackground = eyeBackgroundToWhite;
}


// // Eye patterns
void doStonerEyes() {
  changeEyeCol(0);

  for(uint8_t j = 0; j < 93; j++) {
    if (eyeCoords[j][1] < 56) {
      setSectionLed(0, j, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
      setSectionLed(1, j, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    } else {
      setSectionLed(0, j, 0, 0, 0, 0);
      setSectionLed(1, j, 0, 0, 0, 0);
    }
  }

  // dark eye squares
  drawEyeHexagon(ledSections[0], 55+leftEyeX, 29-leftEyeY, 20, 35, 0, 0, 0, 0);
  drawEyeHexagon(ledSections[1], 55+rightEyeX, 29-rightEyeY, 20, 35, 0, 0, 0, 0);

  // pupil
  drawEyeSquare(ledSections[0], 55+leftEyeX, 29-leftEyeY, 8, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
  drawEyeSquare(ledSections[1], 55+rightEyeX, 29-rightEyeY, 8, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);

  doLeftWink();
  doRightWink();
}

void pacManEyes() {
  // 16384 is a beat length  1365 is an 12th-ish
  //int animationStep = percentThroughBeat / 1365;
  
  uint32_t animationStep1 = (timey / 2048)%8;
  uint32_t animationStep2 = (timey / 1024)%16;   // todo you might need to change these vars to get pac man in time
  
  for(uint8_t j = 0; j < 93; j++) {
    if (pacManAnimationMask[(animationStep2)%16][j]) {
      setSectionLed(1, j, 120, 120, 0, 0);
    } else if (pacManAnimationMask2[(animationStep1+4)%8][j]) {
      setSectionLed(1, j, 0, 0, 0, 0);
    } else {
      setSectionLed(1, j, 255, 255, 255, 0);
    }
  }
  for(uint8_t j = 0; j < 93; j++) {
    if (pacManAnimationMask2[animationStep1][j]) {
      setSectionLed(0, j, 0, 0, 0, 0);
    } else {
      setSectionLed(0, j, 255, 255, 255, 0);
    }
  }
}

void smileyEyes() {
  changeEyeCol(2);
  for(uint8_t j = 0; j < 93; j++) {
    setSectionLed(0, j, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(1, j, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
  }
  for(uint8_t j = 0; j < 24; j++) {
    setSectionLed(0, eyeSmileyLeds[j], 0, 0, 0, 0);
    setSectionLed(1, eyeSmileyLeds[j], 0, 0, 0, 0);
  }
}

const byte circleFirstLeds[9] = {0,32,56,72,84,92,93};
const byte circleFirstR[24] = {245, 0, 0,  10, 0, 0, 255, 0, 0,   0, 0, 0, 100, 0, 0,   0, 0, 0, 200, 0, 0,   0, 0, 0};
const byte circleFirstG[24] = {140, 0, 0, 140, 0, 0,   0, 0, 0,  60, 0, 0, 100, 0, 0,   0, 0, 0,  80, 0, 0, 255, 0, 0};
const byte circleFirstB[24] = { 10, 0, 0, 160, 0, 0,   0, 0, 0, 200, 0, 0,  40, 0, 0, 255, 0, 0,  50, 0, 0,   0, 0, 0};

void hypnotEyes() {
  uint16_t myCycle = timey/16384;

  for (int j = 1; j < 8; j++) {
    int ledToLightFrom = circleFirstLeds[j-1];
    int ledToLightTo = circleFirstLeds[j];
    uint8_t lightyModMod = (myCycle-j)%24;
    for (int led = ledToLightFrom; led < ledToLightTo; led++) {
      setSectionLed(0, led, circleFirstR[lightyModMod], circleFirstG[lightyModMod], circleFirstB[lightyModMod], 0);
      setSectionLed(1, led, circleFirstR[lightyModMod], circleFirstG[lightyModMod], circleFirstB[lightyModMod], 0);
    }
  }
}

void flashingEyes() {
  uint32_t myCycle = (timey / 2048)%16;
  for (int led = 0; led < 93; led++) {
    setSectionLed(0, led, circleFirstR[myCycle], circleFirstG[myCycle], circleFirstB[myCycle], 0);
    setSectionLed(1, led, circleFirstR[myCycle], circleFirstG[myCycle], circleFirstB[myCycle], 0);
  }
  drawIrisAndPupil();
}

void rollEyes(uint8_t percentIntoAnim) {
  
  if (percentIntoAnim > 93)
    percentIntoAnim = 92;
  leftEyeX = eyeCoords[percentIntoAnim][1]-55;
  leftEyeY = eyeCoords[percentIntoAnim][0]-55;
  rightEyeX = eyeCoords[percentIntoAnim][1]-55;
  rightEyeY = eyeCoords[percentIntoAnim][0]-55;
  drawIrisAndPupil();
}

uint8_t sineLUT[128] = { 
  92,92,92,86,86,86,86,75,75,75,75,60,60,60,60,60,
  38,38,38,38,38,38,38,8,8,8,8,8,8,8,8,8,
  8,8,8,8,8,8,8,8,8,8,38,38,38,38,38,38,
  38,60,60,60,60,60,75,75,75,75,86,86,86,86,92,92,
  92,92,92,90,90,90,90,81,81,81,81,68,68,68,68,68,
  50,50,50,50,50,50,50,24,24,24,24,24,24,24,24,24,
  24,24,24,24,24,24,24,24,24,24,50,50,50,50,50,50,
  50,68,68,68,68,68,81,81,81,81,90,90,90,90,92,92 };

void lookLeftAndRight(uint8_t percentIntoAnim) {
  if (percentIntoAnim > 127)
    percentIntoAnim = 127;

  leftEyeX = eyeCoords[sineLUT[percentIntoAnim]][1]-55;
  leftEyeY = eyeCoords[sineLUT[percentIntoAnim]][0]-55;
  rightEyeX = eyeCoords[sineLUT[percentIntoAnim]][1]-55;
  rightEyeY = eyeCoords[sineLUT[percentIntoAnim]][0]-55;
  drawIrisAndPupil();
}

unsigned long blinkStart=4000;
const uint32_t blinkLength=240;
void doBlinking() {
  uint32_t drawTo = 0;
  //uint32_t drawTo2 = 0;
  uint32_t blinkHeight = 60;
  
  if (timey > (blinkStart + blinkLength)) {
    // blink over, reset
    if (random(9) == 0) {
      blinkStart = timey + random(400);
    } else {
      blinkStart = timey + random(4000,9000);
    }
  } else if (timey > blinkStart) {
    uint32_t percIntoBlink = ((timey - blinkStart)*100)/(blinkLength/2);
    if (timey > (blinkStart + (blinkLength/2))) {
      // on way up
      drawTo = ((blinkHeight * percIntoBlink)/100)-blinkHeight+50;
    } else {
      // on way down
      drawTo = blinkHeight+50-((blinkHeight * percIntoBlink)/100);
    }
    for(uint8_t j = 0; j < 93; j++) {
      if (eyeCoords[j][1] < 110 - drawTo) {
        setSectionLed(0, j, 0, 0, 0, 0);
      }
      if (eyeCoords[j][1] > drawTo) {
        setSectionLed(0, j, 0, 0, 0, 0);
      }
      if (eyeCoords[j][1] < 110 - drawTo) {
        setSectionLed(1, j, 0, 0, 0, 0);
      }
      if (eyeCoords[j][1] > drawTo) {
        setSectionLed(1, j, 0, 0, 0, 0);
      }
    }
  }
}

uint16_t lWinkStart=0;
uint16_t rWinkStart=0;
uint16_t lWinkEnd=0;
uint16_t rWinkEnd=0;
bool lWinking = false;
bool rWinking = false;
const uint16_t winkLength=350;

// Note, left and right winks are copied and pasted, change both the same.
void doLeftWink() {
  if (!lWinking)
    return;

  uint16_t drawTo = 0;  
  if (lWinkEnd!=0 && (timey > (lWinkEnd + (winkLength/2)))) {
    // blink over, reset
    lWinking = false;
    lWinkEnd=0;
    drawTo = 110;
  } else if (lWinkEnd==0 && timey < (lWinkStart + (winkLength/2))) {
    // on way down
    uint32_t percIntoBlink = ((timey - lWinkStart)*100)/(winkLength/2);
    drawTo = 110-((60 * percIntoBlink)/100);
  } else if (lWinkEnd!=0) {
    // on way up
    uint32_t percIntoBlink = ((timey - lWinkEnd)*100)/(winkLength/2);
    drawTo = 50+((60 * percIntoBlink)/100);
  } else {
    // in the middle
    for(uint16_t j = 0; j < 109; j++) {
      setSectionLed(1, j, 0, 0, 0, 0);
    }
    setSectionLed(1, 24, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(1, 50, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(1, 68, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(1, 81, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(1, 90, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(1, 92, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(1, 86, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(1, 75, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(1, 60, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(1, 38, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(1,  8, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    return;
  }
  for(uint16_t j = 0; j < 109; j++) {
    if (eyeCoords[j][1] < 110 - drawTo) {
        setSectionLed(1, j, 0, 0, 0, 0);
    }
    if (eyeCoords[j][1] > drawTo) {
        setSectionLed(1, j, 0, 0, 0, 0);
    }
  }
}

void doRightWink() {
  if (!rWinking)
    return;

  uint16_t drawTo = 0;  
  if (rWinkEnd!=0 && (timey > (rWinkEnd + (winkLength/2)))) {
    // blink over, reset
    rWinking = false;
    rWinkEnd=0;
    drawTo = 110;
  } else if (rWinkEnd==0 && timey < (rWinkStart + (winkLength/2))) {
    // on way down
    uint32_t percIntoBlink = ((timey - rWinkStart)*100)/(winkLength/2);
    drawTo = 110-((60 * percIntoBlink)/100);
  } else if (rWinkEnd!=0) {
    // on way up
    uint32_t percIntoBlink = ((timey - rWinkEnd)*100)/(winkLength/2);
    drawTo = 50+((60 * percIntoBlink)/100);
  } else {
    // in the middle
    for(uint16_t j = 0; j < 93; j++) {
      setSectionLed(0, j, 0, 0, 0, 0);
    }
    setSectionLed(0, 24, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(0, 50, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(0, 68, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(0, 81, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(0, 90, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(0, 92, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(0, 86, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(0, 75, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(0, 60, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(0, 38, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(0,  8, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    return;
  }
  for(uint16_t j = 0; j < 93; j++) {
    if (eyeCoords[j][1] < 110 - drawTo) {
        setSectionLed(5, j, 0, 0, 0, 0);
    }
    if (eyeCoords[j][1] > drawTo) {
        setSectionLed(5, j, 0, 0, 0, 0);
    }
  }
}

void winkLeftMessage(uint16_t blinkOnOffMessage) {
  if (blinkOnOffMessage == 0) {
    // start new wink
    lWinkStart=timey;
    lWinking = true;
    lWinkEnd=0;
    // push forward the next blink
    blinkStart = timey + random(3000,8000);
  } else if (blinkOnOffMessage == 1) {
    // end wink
    lWinkEnd=timey;
  }
}

void winkRightMessage(uint16_t blinkOnOffMessage) {
  if (blinkOnOffMessage == 0) {
    // start new wink
    rWinkStart=timey;
    rWinking = true;
    rWinkEnd=0;
    // push forward the next blink
    blinkStart = timey + random(3000,8000);
  } else if (blinkOnOffMessage == 1) {
    // end wink
    rWinkEnd=timey;
  }
}

void resetEyes() {
  eyePrimaryR = 110;
  eyePrimaryG = 150;
  eyePrimaryB = 150;
  leftEyeX = 0;
  leftEyeY = 0;
  rightEyeX = 0;
  rightEyeY = 0;
  uint8_t oneInThree= random(3);
  if (oneInThree == 0) {
    changeEyeBackground(true);
  } else {
    changeEyeBackground(false);
  }  
}

// 0=random, 1=red, 2=yellow
uint8_t currentColourSet = 0;
void changeEyeCol(uint8_t colourSet) {
  if (colourSet == currentColourSet) {
    return;
  }
  uint8_t oneInThree= random(3);

  switch (colourSet) {
    case 0:
      setGoodRGBRandomColorVars();
      eyePrimaryR = goodColR; eyePrimaryG = goodColG; eyePrimaryB = goodColB;
      break;
    case 1:
      if (oneInThree == 0) {
        setGoodRGBRandomColorVars();
        eyePrimaryR = goodColR; eyePrimaryG = goodColG; eyePrimaryB = goodColB;
      } else {
        eyePrimaryR = 250; eyePrimaryG = 0; eyePrimaryB = 0;
      }
      break;
    case 2:
      if (oneInThree == 0) {
        setGoodRGBRandomColorVars();
        eyePrimaryR = goodColR; eyePrimaryG = goodColG; eyePrimaryB = goodColB;
      } else {
        eyePrimaryR = 140; eyePrimaryG = 160; eyePrimaryB = 0;
      }
      break;
  }
  currentColourSet = colourSet;
}

