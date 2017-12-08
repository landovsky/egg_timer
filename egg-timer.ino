#include <LowPower.h>
//#include <U8glib.h>


///Encoder
const byte pinCLK = 3;
const byte pinDT  = 4;
const byte pinSW  = 2;
const byte interruptPin = 2;

int poziceEnkod = 0;
byte stavPred;
byte stavCLK;
byte stavSW;
byte stavDT;
byte btnState = 1; // vypnuto
int btnTime;
byte buttonMode;
byte mode;

///Oled

void setup() {
  attachInterrupt(digitalPinToInterrupt(interruptPin), wake, FALLING);
  Serial.begin(9600);
  pinMode(pinCLK, INPUT);
  pinMode(pinDT, INPUT);
  pinMode(pinSW, INPUT_PULLUP);
  stavPred = digitalRead(pinCLK);   
} 

void loop() {
  mode = btnMode();
  //setMode();
    // act: set mode based on current mode and btn pressed
    // act: start stand-by timeup
    // inputs: btn pressed, time up (standby)
  //readEncoder();
    // read encoder data
    // output: +1, -1 (nebo raději abs. číslo?)
  //display();
    // inputs: name, time, blinking 0/1

  switch(mode) {
    // Switched off
    case 0:
      // act: sleep
      break;

    // Listing menu
    case 1:
      // act: loop through items (forward / backward)
      // inputs: knob (relative)
      // output: display default/selected item & time
      LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
      break;

    // Timer running
    case 2:
      // act: decrease timer by seconds
      // act: change timer by knob
      // inputs: knob (abs.), current timer
      break;

    // Timer timed out
    case 3:
      // act: beep
      // act: blink display
      break;

    // Timer paused / Set custom timer
    case 4:
      // act: change timer by knob
      // act: blink timer var
      break;

    // Set new default time for item (for selected items)
    case 5:
      // act: blink name var as sign of special mode
      // act: change timer by knob
      // act: save new values
      break;
   
    };
  
  stavCLK = digitalRead(pinCLK);
  if (stavCLK != stavPred) {
    stavDT = digitalRead(pinDT);
    if (stavDT != stavCLK) {
      poziceEnkod ++;
    }
    else {
      poziceEnkod--;
    }
  }
  stavPred = stavCLK;
}

void wake() {
    mode = 0;
    Serial.println("Zív");
}

byte btnMode() {
  // 0 zapnuto, 1 vypnuto
  if(digitalRead(pinSW) == 0 && btnState == 1) {
    // Button pressed > counter started 
    btnTime = millis();
    btnState = 0;
  } else if (digitalRead(pinSW) == 1 && btnState == 0) {
    // Button released > calculate btnMode
    btnState = 1;
    btnTime = (millis() - btnTime);
    if(btnTime < 700) {
        Serial.println("Short click");
        buttonMode = 0;
        return buttonMode;
      } else {
        Serial.println("Long click");
        buttonMode = 1;
        return buttonMode;
      }
      return buttonMode;
  }
  return buttonMode;
}


