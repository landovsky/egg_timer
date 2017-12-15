void display(void) {
  // nastavení písma, toto písmo umožní vypsat
  // přibližně 15x4 znaků
  mujOled.setFont(u8g_font_fub17);

  // nastavení pozice výpisu v pixelech
  // souřadnice jsou ve tvaru x, y
  // souřadnice 0, 0 je v levém horní rohu
  // OLED displeje, maximum je 128, 64
  mujOled.setPrintPos(0, 20);
  // výpis textu na zadanou souřadnici
  mujOled.print(menuName);
  //mujOled.setPrintPos(0, 25);
  //mujOled.print("arduino-shop.cz");
  mujOled.setPrintPos(0, 50);
  mujOled.print(timer);
  mujOled.setPrintPos(40, 55);
}
