char prefix(int val) {
  char sign;
  if(val < 1) {
    sign = '-';
  }
  else {
    sign = ' ';
  }
  return sign;
}

