/*Процедура чтения значений из EEPROM и присвоение к строкам*/
void readEEPROM() {
  char readCode_EEPROM[] = " "; //массив символов для чтения из EEPROM
  for (uint8_t i = 0; i < 6; i++) {
    EEPROM.readBlock<char>(EEPROM_adress[i], readCode_EEPROM, EEPROM_RECORDING_SIZE);
    irCodes[i] = readCode_EEPROM;
  }
  sendProtocol = EEPROM.read(0);
  lcd.clrScr();
  chargeCheck();
}
