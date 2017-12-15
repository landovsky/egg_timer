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
        delay(1);
        mode = 0;
      }
      break;

    // timer running
    case 2:
      mode = 4;
      Serial.println("Timer is paused");
      break;

    // time-out
    case 3:
      mode = 1; // go to menu if timeout acknowledged
      break;
    
    // timer paused
    case 4:
      if (buttonMode == 0) {
        mode = 2;
        Serial.println("Timer is running");
      }
      else {
        mode = 1;
        menuId = 0;
        setMenu(1);
        Serial.println("Menu");
      }
      break;
  }
}

