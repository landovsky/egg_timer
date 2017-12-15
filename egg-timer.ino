#include <LowPower.h>
#include <U8glib.h>

///Encoder
const byte pinCLK = 3;
const byte pinDT  = 4;
const byte pinSW  = 2;

//Oled
long int prepis = 0;

int poziceEnkod = 0;
byte stavPred;
byte stavCLK;
byte stavSW;
byte stavDT;
byte btnState = 0; // vypnuto
int btnTimeSt;
int btnTime; // elapsed time in button pressed state
byte timerType;
int timer = 90;
byte buttonMode;
boolean btnRd = 1; // allow reading of button state
byte mode = 1;
byte menuId = 0;
char menuName[10];
byte knob;
String timerCh;
long int previousMillis = 0;
boolean fullSec;

///Oled
U8GLIB_SSD1306_128X64 mujOled(U8G_I2C_OPT_NONE);

void wake() {
}



void setTimer(byte direction) {
  switch(direction) {
    case 1:
      timer++;
      break;
    case 255:
      timer--;
      break;
  }
}

void setup() {
  setMenu(1);
  getTime(timer);
  showDisplay(false);
  attachInterrupt(digitalPinToInterrupt(pinSW), wake, FALLING);
  Serial.begin(9600);
  pinMode(pinCLK, INPUT);
  pinMode(pinDT, INPUT);
  pinMode(pinSW, INPUT_PULLUP);
  stavPred = digitalRead(pinCLK);
}

void loop() {
  btnMode();
  knob = readKnob();
  getFullSec();
  
  switch (mode) {
    // Sleep
    case 0:
      clearDisplay();
      delay(1);
      LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
      break;

    // Listing menu
    case 1:
      setMenu(knob);
      refreshDisplay(false);
      break;

    // Timer running
    case 2:
      if (fullSec == true) {
        timer--;
      }
      autoMode();
      setTimer(knob);
      refreshDisplay(false);
      break;

    // Timer timed out
    case 3:
      setTimer(knob);
      if (fullSec == true) {
        //Serial.print("beep beep");
        timer--;
      }
      refreshDisplay(blinkText());
      autoMode();
      break;

    // Timer paused / Set custom timer
    case 4:
      setTimer(knob);
      refreshDisplay(blinkText());
      break;

    // Set new default time for item (for selected items)
    case 5:
      // act: blink name var as sign of special mode
      // act: change timer by knob
      // act: save new values
      break;

  };

 

} //end loop

boolean blinkText() {
  if((millis() - previousMillis) > 200) {
    return true;
  }
  else {
    return false;
  }
}

void getFullSec() {
  if ((millis() - previousMillis) > 1000) {
    previousMillis = millis();
    getTime(timer);
    fullSec = true;
    }
   else {
    fullSec = false;
   }
}

