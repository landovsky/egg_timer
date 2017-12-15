  // macros from DateTime.h 
/* Useful Constants */
#define SECS_PER_MIN  (60UL)
#define SECS_PER_HOUR (3600UL)
#define SECS_PER_DAY  (SECS_PER_HOUR * 24L)

/* Useful Macros for getting elapsed time */
#define numberOfSeconds(_time_) (_time_ % SECS_PER_MIN)  
#define numberOfMinutes(_time_) ((_time_ / SECS_PER_MIN) % SECS_PER_MIN) 
#define numberOfHours(_time_) (( _time_% SECS_PER_DAY) / SECS_PER_HOUR)
#define elapsedDays(_time_) ( _time_ / SECS_PER_DAY)  

void printTime(long val) {
  //int days = elapsedDays(abs(val));
  int hours = numberOfHours(abs(val));
  int minutes = numberOfMinutes(abs(val));
  int seconds = numberOfSeconds(abs(val));
  // digital clock display of current time
  Serial.print(prefix1(val));
  Serial.print(hours);
  printDigits1(minutes);
  printDigits1(seconds);
  Serial.print(" mode: ");
  Serial.print(mode);
  Serial.print(" full sec: ");
  Serial.println(fullSec);
}

char prefix1(int val) {
  char sign;
  if(val < 1) {
    sign = '-';
  }
  else {
    sign = ' ';
  }
  return sign;
}

void printDigits1(byte digits){
 // utility function for digital clock display: prints colon and leading 0
 Serial.print(":");
 if(digits < 10)
   Serial.print('0');
 Serial.print(digits,DEC);  
}
