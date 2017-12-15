// Global vars: menuName, timerCh

void display(boolean hide) {
  // nastavení písma, toto písmo umožní vypsat
  // přibližně 15x4 znaků
  mujOled.setFont(u8g_font_fub17);

  // nastavení pozice výpisu v pixelech
  // souřadnice jsou ve tvaru x, y
  // souřadnice 0, 0 je v levém horní rohu
  // OLED displeje, maximum je 128, 64
  mujOled.setPrintPos(0, 20);
  //mujOled.setFontPosCenter();
  // výpis textu na zadanou souřadnici
  mujOled.print(menuName);
  //mujOled.setPrintPos(0, 25);
  //mujOled.print("arduino-shop.cz");
  mujOled.setPrintPos(20, 56);
  if(hide == true) {
    mujOled.print("");
  }
  else {
    mujOled.print(timerCh);
  }
  //mujOled.setPrintPos(40, 55);
}

void clearDisplay(){
    mujOled.firstPage();  
    do {
    } while( mujOled.nextPage() );
}

void refreshDisplay(boolean hide) {
  if (fullSec == true) {
    printTime(timer);
    showDisplay(hide);
  }
}

void showDisplay(boolean hide) {
  getTime(timer);
  mujOled.firstPage();
  do {
    display(hide);
    } while( mujOled.nextPage() );
}
