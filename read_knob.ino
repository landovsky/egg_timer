byte readKnob() {
  byte knob;
  stavCLK = digitalRead(pinCLK);
  if (stavCLK != stavPred) {
    stavDT = digitalRead(pinDT);
    if (stavDT != stavCLK) {
      poziceEnkod ++;
      knob = 1;
      //Serial.print("Po směru ");
    }
    else {
      poziceEnkod--;
      knob = -1;
      //Serial.print("Proti směru ");
    }
    //Serial.print("DT: ");
    //Serial.print(stavDT);
    //Serial.print(" CLK: ");
    //Serial.print(stavCLK);
    //Serial.print(" pozice: ");
    //Serial.println(poziceEnkod);
  }
  else {
    knob = 0;
  }
  stavPred = stavCLK;
  return knob;
}
