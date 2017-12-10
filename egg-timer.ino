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
byte buttonMode;
boolean btnRd = 1; // allow reading of button state
byte mode = 1;
char modeName = 'menu';
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

  switch(mode) {
    // Switched off
    case 0:
      // act: sleep
      LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
      break;

    // Listing menu
    case 1:
      // act: loop through items (forward / backward)
      // inputs: knob (relative)
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
  
  stavCLK = digitalRead(pinCLK);
  if (stavCLK != stavPred) {
    stavDT = digitalRead(pinDT);
    if (stavDT != stavCLK) {
      poziceEnkod ++;
      Serial.print("Po směru ");
    }
    else {
      poziceEnkod--;
      Serial.print("Proti směru ");
    }
    Serial.print("DT: ");
    Serial.print(stavDT);
    Serial.print(" CLK: ");
    Serial.print(stavCLK);
    Serial.print(" pozice: ");
    Serial.println(poziceEnkod);
  }
  stavPred = stavCLK;
  
  if((millis() - previousMillis) > 1000) {
    // Serial.print("known state: ");
    // Serial.println(btnState);
//    Serial.print(" allow reading: ");
//    Serial.print(btnRd);
//    Serial.print(" button mode: ");
//    Serial.println("Ping");
    previousMillis = millis();
  }
  //end
}

boolean buttonPressed () {
  return digitalRead(pinSW) == 0;
}

boolean buttonOn () {
  return btnState == 1;
}

boolean btnRead () {
  return btnRd == 1;
}

void wake() {
}

void btnMode() {
  if( buttonPressed() && !buttonOn() ) {
    // Button pressed > counter started 
    btnTimeSt = millis();
    btnState = 1;
  }
  else if (buttonPressed() && buttonOn() && btnRead() ) {
    // Button state down
    btnTime = millis() - btnTimeSt;
    
    // Detect long-click and stop
    if(btnTime > 700) {
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

// act: set mode based on current mode and btn pressed
// act: start stand-by timeup
// inputs: btn pressed, time up (standby)
void setMode() {
  switch(mode) {
    case 0: // power down
      mode = 1;
      Serial.println("Menu");
      break;

    // in menu
    case 1:
      if(buttonMode == 0) {
        if(timerType == 99) {
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
      if(buttonMode == 0) {
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

















