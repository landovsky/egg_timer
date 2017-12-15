void setMenu(byte direction) {
  menuId = menuId + direction;
  if(direction != 0) {
    // keep menuId within existing menu values
    switch (menuId) {
      case 4:
        menuId = 1;
        break;
      case 0:
        menuId = 3;
        break;
    }
  
    switch (menuId) {
      case 1:
        strcpy(menuName, "EGGS");
        timer = 5 * 60;
        break;
      case 2:
        strcpy(menuName, "COFFEE");
        timer = 4 * 60;
        break;
      case 3:
        strcpy(menuName, "TIMER");
        timer = 0;
        break;
    }
    Serial.println(menuName);
  }
}
