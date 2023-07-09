void ps2ToLights() {
  

  doWinking();

  //if ((ps2.readButton(PS2_LEFT_1) == 1) && (ps2.readButton(PS2_LEFT_2) == 1) && (ps2.readButton(PS2_RIGHT_1) == 1))
    checkAnalogsForEyeMovements();

  if (ps2.readButton(PS2_RIGHT_1) == 0)
    checkButtonsForEyeAndPatternChange();

  checkButtonsSendInfoToLights();
}

void doLightsByMessage(int16_t function, int16_t message) {  
  if (function == 1) {
    if (message < 2) {
      return;
    } else if (message < 4) {
      winkLeftMessage(message % 2);
    } else if (message < 6) {
      winkRightMessage(message % 2);
    } else if (message < 7) {
      lastEyeMoveTime = timey;
      changeEyeBackground(!whiteEyeBackground);
    } else if (message < 8) {
      return;
    } else if (message < 9) {
      return;
    } else if (message < 11) {
      // TODO changeOnOff(message % 2);
      return;
    } else if (message < 13) {
      changeManualAutomatic(message % 2);
    } else if (message < 40) {
      return;
    }
  } else if (function == 2) {
    return;
  } else if (function == 3) {
    return;
  } else if (function == 4) {
    return;
  } else if (function == 5 || function == 6 || function == 7 || function == 8) {
    lastEyeMoveTime = timey;
    setEyeCoords(function, message);
  }
}

void changeManualAutomatic(int16_t message) {
  allOffBySection();
  if (message == 0) {
    eyesAutomatic = false;
    setSectionLed(0, 0, 0, 0, 255, 0);
    setSectionLed(1, 1, 0, 0, 255, 0);
  } else {
    eyesAutomatic = true;
    setSectionLed(0, 0, 0, 0, 0, 255);
    setSectionLed(1, 1, 0, 0, 0, 255);
  }
  strip.show();
  delay(100);
}

int leftEyeXIn = 0;
int leftEyeYIn = 0;
void setEyeCoords(int16_t function, int16_t message) {
  if (function == 5) {
    leftEyeX = message;
  } else if (function == 6) {
    leftEyeY = -(message - 130);
  } else if (function == 7) {
    rightEyeX = message;
  } else if (function == 8) {
    rightEyeY = -(message - 130);
  }
}

void checkAnalogsForEyeMovements() {

  // EYE MOVEMENT
  int newLeftX=ps2.readButton(PS2_JOYSTICK_LEFT_X_AXIS)/2;
  if (newLeftX > leftEyeX || newLeftX < leftEyeX) {
    leftEyeX = newLeftX;
    doLightsByMessage(7, leftEyeX);
  }
  
  int newLeftY=ps2.readButton(PS2_JOYSTICK_LEFT_Y_AXIS)/2;
  if (newLeftY > leftEyeY || newLeftY < leftEyeY) {
    leftEyeY = newLeftY;
    doLightsByMessage(8, leftEyeY);
  }    

  int newRightX=ps2.readButton(PS2_JOYSTICK_RIGHT_X_AXIS)/2;
  if (newRightX > rightEyeX || newRightX < rightEyeX) {
    rightEyeX = newRightX;
    doLightsByMessage(5, rightEyeX);
  }
  
  int newRightY=ps2.readButton(PS2_JOYSTICK_RIGHT_Y_AXIS)/2;
  if (newRightY > rightEyeY || newRightY < rightEyeY) {
    rightEyeY = newRightY;
    doLightsByMessage(6, rightEyeY);
  }    

}

bool ps2LeftStickClickOn=false;
bool ps2RightStickClickOn=false;
void doWinking() {
      // WINKING
    if (!ps2LeftStickClickOn && ps2.readButton(PS2_JOYSTICK_LEFT)==0)
    {
      ps2LeftStickClickOn = true;
      doLightsByMessage(1, 2);
    }
    if (ps2LeftStickClickOn && ps2.readButton(PS2_JOYSTICK_LEFT)==1)
    {
      ps2LeftStickClickOn = false;
      doLightsByMessage(1, 3);
    }
  
    if (!ps2RightStickClickOn && ps2.readButton(PS2_JOYSTICK_RIGHT)==0)
    {
      ps2RightStickClickOn = true;
      doLightsByMessage(1, 4);
    }
    if (ps2RightStickClickOn && ps2.readButton(PS2_JOYSTICK_RIGHT)==1)
    {
      ps2RightStickClickOn = false;
      doLightsByMessage(1, 5);
    }
}

bool ps2TriangleOn=false;
bool ps2SquareOn=false;
bool ps2CircleOn=false;
bool ps2CrossOn=false;
void checkButtonsForEyeAndPatternChange() {
      // BUTTONS FOR EYE ANIMAITON AND COLOUR CHANGE
    if (!ps2TriangleOn && ps2.readButton(PS2_TRIANGLE)==0) {
      ps2TriangleOn = true;
      doLightsByMessage(1, 6);
    }
    if (ps2TriangleOn && ps2.readButton(PS2_TRIANGLE)==1)
      ps2TriangleOn = false;
    
    if (!ps2CircleOn && ps2.readButton(PS2_CIRCLE)==0) {
      ps2CircleOn = true;
      doLightsByMessage(1, 7);
    }
    if (ps2CircleOn && ps2.readButton(PS2_CIRCLE)==1) {
      ps2CircleOn = false;
    }
    
    if (!ps2CrossOn && ps2.readButton(PS2_CROSS)==0) {
      ps2CrossOn = true;
      doLightsByMessage(1, 8);
    }
    if (ps2CrossOn && ps2.readButton(PS2_CROSS)==1) {
      ps2CrossOn = false;
    }
}

bool ps2Right2On = false;
void checkButtonsSendInfoToLights() {
  // send talking signal
  if (!ps2Right2On && ps2.readButton(PS2_RIGHT_2)==0)
  {
    ps2Right2On = true;
    doLightsByMessage(1, 0);
  }
  if (ps2Right2On && ps2.readButton(PS2_RIGHT_2)==1)
  {
    ps2Right2On = false;
    doLightsByMessage(1, 1);
  }
}
