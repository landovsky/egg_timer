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
int timer;
byte buttonMode;
boolean btnRd = 1; // allow reading of button state
byte mode = 1;
byte menuId = 0;
char menuName[10];
char timerCh[9];
int previousMillis = 0;

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

void autoMode() {
  if(timer < 0) {
    mode = 3;
  }
  else {
    mode = 2;
  }
}

void setup() {
  setMenu(1);
  attachInterrupt(digitalPinToInterrupt(pinSW), wake, FALLING);
  Serial.begin(9600);
  pinMode(pinCLK, INPUT);
  pinMode(pinDT, INPUT);
  pinMode(pinSW, INPUT_PULLUP);
  stavPred = digitalRead(pinCLK);
}

void loop() {
  btnMode();

  if (millis()-prepis > 100) {
    // následující skupina příkazů
    // obnoví obsah OLED displeje
    mujOled.firstPage();
    do {
      // funkce vykresli vykreslí žádaný obsah
      display();
    } while( mujOled.nextPage() );
    // uložení posledního času obnovení
    prepis = millis();
  }

  //display();
  // inputs: name, time, blinking 0/1

  switch (mode) {
    // Sleep
    case 0:
      LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
      break;

    // Listing menu
    case 1:
      setMenu(readKnob());
      // output: display default/selected item & time
      break;

    // Timer running
    case 2:
      autoMode();
      setTimer(readKnob());
      if ((millis() - previousMillis) > 1000) {
        printTime(timer);
        timer--;
        previousMillis = millis();
      }
      
      //decreaseTimer();
      // act: decrease timer by seconds
      // act: change timer by knob
      // inputs: knob (abs.), current timer
      break;

    // Timer timed out
    case 3:
      // act: beep
      // act: blink display
      autoMode();
      setTimer(readKnob());
      if ((millis() - previousMillis) > 1000) {
        printTime(timer);
        Serial.print("beep beep");
        timer--;
        previousMillis = millis();
      }
      break;

    // Timer paused / Set custom timer
    case 4:
      setTimer(readKnob());
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


  //end
}
