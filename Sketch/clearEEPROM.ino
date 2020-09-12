/*Процедура очистки памяти EEPROM и значений String*/
void clearEEPROM() {
  /*
     Ниже мы получаем значение (то есть последний адрес),
     который используется для записи, добавляем к нему
     размер буфера для записи и с начального адреса до
     получившегося стираем значения EEPROM
  */
  const uint8_t bytesToClear = EEPROM_adress[(sizeof(EEPROM_adress) / sizeof(EEPROM_adress[0])) - 1] + EEPROM_BUFFER_SIZE;

  /*Удаление записей из EEPROM*/
  for (uint8_t i = 0 ; i <= bytesToClear ; i++) EEPROM.write(i, 0);

  /*Удаление записей из String*/
  for (uint8_t i = 0; i < 6; i++) irCodes[i].remove(0);

  sendProtocol = 0;
  lcd.clrScr();
  choosePosition = 0;
}
