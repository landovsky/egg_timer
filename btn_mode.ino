boolean buttonPressed () {
  return digitalRead(pinSW) == 0;
}

boolean buttonOn () {
  return btnState == 1;
}

boolean btnRead () {
  return btnRd == 1;
}

void btnMode() {
  if ( buttonPressed() && !buttonOn() ) {
    // Button pressed > counter started
    btnTimeSt = millis();
    btnState = 1;
  }
  else if (buttonPressed() && buttonOn() && btnRead() ) {
    // Button state down
    btnTime = millis() - btnTimeSt;

    // Detect long-click and stop
    if (btnTime > 700) {
      // Serial.println("Long click");
      //btnState = 0;
      btnRd = 0;
      buttonMode = 1;
      setMode();
      // return buttonMode;
    }
    // return buttonMode;
  }
  else if ( !buttonPressed() && buttonOn() ) {
    // Button released > calculate short-click
    btnState = 0;
    btnRd = 1;
    btnTime = millis() - btnTimeSt;
    if (btnTime < 700) {
      // Serial.println("Short click");
      buttonMode = 0;
      setMode();
      // return buttonMode;
    }
  }
  // return buttonMode;
}
