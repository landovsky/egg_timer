// act: set mode based on current mode and btn pressed
// act: start stand-by timeup
// inputs: btn pressed, time up (standby)
void setMode() {
  switch (mode) {
    case 0: // power down
      mode = 1;
      Serial.println("Menu");
      break;

    // in menu
    case 1:
      if (buttonMode == 0) {
        if (timerType == 99) {
          mode = 4; // user chose custom timer
          Serial.println("Timer is paused");
        }
        else {
          mode = 2; // user chose named timer
          Serial.println("Timer is running");
        }
      }
      else {
        // sleep
        Serial.println("Powering down");
        mode = 0;
      }
      break;

    // timer running
    case 2:
      mode = 4;
      Serial.println("Timer is paused");
      break;

    // case 3 only happens by time-out

    // timer paused
    case 4:
      if (buttonMode == 0) {
        mode = 2;
        Serial.println("Timer is running");
      }
      else {
        mode = 1;
        Serial.println("Menu");
      }
      break;
  }
}

