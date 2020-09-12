/*Процедура сохранения значений и их запись в EEPROM*/
void saveEEPROM () {
  /*Отправляем в метод записи/обновления параметры (строку, адрес для записи/обновления)*/
  for (uint8_t i = 0; i < 6; i++) saveMethode(&irCodes[i], EEPROM_adress[i]);
  EEPROM.write(0, sendProtocol); //записать выбор протокола по адресу 0

  lcd.clrScr();
  choosePosition = 0;
}

bool saveMethode(String *code, uint8_t adress) { //принимаем код и адрес для записи в EEPROM
  bool check = false; //флаг
  char buff[EEPROM_RECORDING_SIZE]; //создаем буфер типа char размером 11 ячеек
  code->toCharArray(buff, EEPROM_RECORDING_SIZE); //преобразуем переданную в метод строку в наш массив

  for (uint8_t i = adress; i < (adress + EEPROM_BUFFER_SIZE); i++) { //цикл, проверяющий, пустые ли адреса
    if (EEPROM.read(i) == 0) { //если да, то..
      check = !check; //поднять флаг
    }
  }
  if (check) { //если адреса пустые, то..
    return EEPROM.writeBlock<char>(adress, buff, EEPROM_RECORDING_SIZE); //запись в EEPROM (по адресу, из массива, кол-во байт)
  } else { //если нет..
    return EEPROM.updateBlock<char>(adress, buff, EEPROM_RECORDING_SIZE); //обновление
  }
}
