//#include <U8glib.h>

///Stavy
// 0. Vypnuto
// 1. Menu
// 2. Counter running
// 3. Counter stopped
// 4. Counter finished 

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
byte btnMode;
byte mode = 0;

///Oled

void setup() {
  //attachInterrupt(digitalPinToInterrupt(interruptPin), wake, RISING);
  Serial.begin(9600);
  pinMode(pinCLK, INPUT);
  pinMode(pinDT, INPUT);
  pinMode(pinSW, INPUT_PULLUP);
  stavPred = digitalRead(pinCLK);   
} 

void loop() {
  btnMode();
  setMode();
    // set mode based on current mode and btn pressed

  switch(mode) {
    case 1:
      // display default item
      // read knob position
      // on change loop through items (forward / backward)
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
    mode = 1;
}

byte btnMode() {
  // 0 zapnuto, 1 vypnuto
  if(digitalRead(pinSW) == 0 && btnState == 1) {
    // eventOn > counter started 
    btnTime = millis();
    btnState = 0;
  } else if (digitalRead(pinSW) == 1 && btnState == 0) {
    // eventOff > calculate btnMode
    btnState = 1;
    btnTime = (millis() - btnTime);
    if(btnTime < 700) {
        Serial.println("Short click");
        btnMode = 0;
      } else {
        Serial.println("Long click");
        btnMode = 1;
      }
    }
    
  }

