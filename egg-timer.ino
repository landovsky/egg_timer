#include <LowPower.h>
//#include <U8glib.h>

///Encoder
const byte pinCLK = 3;
const byte pinDT  = 4;
const byte pinSW  = 2;

int poziceEnkod = 0;
byte stavPred;
byte stavCLK;
byte stavSW;
byte stavDT;
byte btnState = 0; // vypnuto
int btnTimeSt;
int btnTime; // elapsed time in button pressed state
byte timerType = 1;
int timer;
byte buttonMode;
boolean btnRd = 1; // allow reading of button state
byte mode = 1;
byte menuId = 1;
char menuName[10];
int previousMillis = 0;

///Oled

void setup() {
  attachInterrupt(digitalPinToInterrupt(pinSW), wake, FALLING);
  Serial.begin(9600);
  pinMode(pinCLK, INPUT);
  pinMode(pinDT, INPUT);
  pinMode(pinSW, INPUT_PULLUP);
  stavPred = digitalRead(pinCLK);
}

void loop() {
  btnMode();

  //readEncoder();
  // read encoder data
  // output: +1, -1 (nebo raději abs. číslo?)
  //display();
  // inputs: name, time, blinking 0/1

  switch (mode) {
    // Switched off
    case 0:
      // act: sleep
      LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
      break;

    // Listing menu
    case 1:
      setMenu(readKnob());
      // output: display default/selected item & time
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

  if ((millis() - previousMillis) > 1000) {
    // Serial.print("known state: ");
    // Serial.println(btnState);
    //    Serial.print(" allow reading: ");
    //    Serial.print(btnRd);
//      Serial.print("Menu: ");
//      Serial.println(menuName);
    previousMillis = millis();
  }
  //end
}

void wake() {
}





