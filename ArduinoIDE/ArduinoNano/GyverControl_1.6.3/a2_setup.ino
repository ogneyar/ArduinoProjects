void setup() {
#if (DEBUG_ENABLE == 1)
  uart.begin(9600);
#endif

#if (DEBUG_PID > 0)
#if (PID_AUTOTUNE == 1)
  uart.println("input , min , max");
#else
#if (SHOW_INTEGRAL == 1)
  uart.println("set , input , integral/3 , out");
#else
  uart.println("set , input , out");
#endif
#endif

#endif

  boolean startupPress = false;
  initHardware();

  // просто сброс настроек
#if (START_MENU == 0)
  // сброс настроек
  if (!digitalRead(SW)) {
    startupPress = true;
    lcd.setCursor(0, 0);
    lcd.print(F("Reset settings OK"));
  }
  while (!digitalRead(SW));
#else
  // стартовое меню
  EEPROM.get(EEPR_SETTINGS, settings);    
  // settings.backlight = eeprom_read_byte(EEPR_SETTINGS);
  // settings.backlTime = eeprom_read_byte(EEPR_SETTINGS + 1);
  // settings.drvSpeed = eeprom_read_byte(EEPR_SETTINGS + 2);
  // settings.srv1_Speed = eeprom_read_byte(EEPR_SETTINGS + 3);
  // settings.srv2_Speed = eeprom_read_byte(EEPR_SETTINGS + 4);
  // settings.srv1_Acc = eeprom_read_float(EEPR_SETTINGS + 5);
  // settings.srv2_Acc = eeprom_read_float(EEPR_SETTINGS + 9);
  // settings.comSensPeriod = eeprom_read_word(EEPR_SETTINGS + 13);
  // settings.plotMode = eeprom_read_byte(EEPR_SETTINGS + 15);
  // settings.minAngle[0] = eeprom_read_byte(EEPR_SETTINGS + 16);
  // settings.minAngle[1] = eeprom_read_byte(EEPR_SETTINGS + 17);
  // settings.maxAngle[0] = eeprom_read_byte(EEPR_SETTINGS + 18);
  // settings.maxAngle[1] = eeprom_read_byte(EEPR_SETTINGS + 19);
  // settings.driveTimeout = eeprom_read_word(EEPR_SETTINGS + 20);
  if (!digitalRead(SW)) {
    drawStartMenu(0);
    while (!digitalRead(SW));
    startMenu();
  }

#endif

  // ----- первый запуск или сброс -----
  if (EEPROM.read(EEPR_KEY_ADDR) != EEPR_KEY || startupPress) {
    clearEEPROM();  // сброс настроек
  }
  EEPROM.get(EEPR_SETTINGS, settings);     // чтение настроек
  // settings.backlight = eeprom_read_byte(EEPR_SETTINGS);
  // settings.backlTime = eeprom_read_byte(EEPR_SETTINGS + 1);
  // settings.drvSpeed = eeprom_read_byte(EEPR_SETTINGS + 2);
  // settings.srv1_Speed = eeprom_read_byte(EEPR_SETTINGS + 3);
  // settings.srv2_Speed = eeprom_read_byte(EEPR_SETTINGS + 4);
  // settings.srv1_Acc = eeprom_read_float(EEPR_SETTINGS + 5);
  // settings.srv2_Acc = eeprom_read_float(EEPR_SETTINGS + 9);
  // settings.comSensPeriod = eeprom_read_word(EEPR_SETTINGS + 13);
  // settings.plotMode = eeprom_read_byte(EEPR_SETTINGS + 15);
  // settings.minAngle[0] = eeprom_read_byte(EEPR_SETTINGS + 16);
  // settings.minAngle[1] = eeprom_read_byte(EEPR_SETTINGS + 17);
  // settings.maxAngle[0] = eeprom_read_byte(EEPR_SETTINGS + 18);
  // settings.maxAngle[1] = eeprom_read_byte(EEPR_SETTINGS + 19);
  // settings.driveTimeout = eeprom_read_word(EEPR_SETTINGS + 20);
  applySettings();  // применение настроек

  // ----- понеслась -----
  currentChannel = -1;  // окно дебаг
  currentLine = 4;
  drawArrow();
  redrawScreen();
  disableABC();
  customSetup();        // вызов кастомного блока инициализации (вкладка custom)
}

ISR(INT0_vect) {        // External interrupt vectors
  enc.tick(controlState);
}

ISR(INT1_vect) {
  enc.tick(controlState);
}
