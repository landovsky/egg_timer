// Global vars: timerCh

void getTime(long val) {
  //int days = elapsedDays(abs(val));
  int hours = numberOfHours(abs(val));
  int minutes = numberOfMinutes(abs(val));
  int seconds = numberOfSeconds(abs(val));
  timerCh = prefix(val) + String(hours) + getDigits(minutes) + getDigits(seconds);
}

String getDigits(byte digits) {
  String output = ":";
  if(digits < 10) {
   output = ":0" + String(digits);
  }
  else {
    output = ":" + String(digits);
  }
  return output;
}

char prefix(int val) {
  char sign;
  if(val < 0) {
    sign = '-';
  }
  else {
    sign = ' ';
  }
  return sign;
}


