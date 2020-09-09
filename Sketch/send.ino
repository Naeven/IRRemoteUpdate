/* Процедура подготовки к отправке ИК сигналов с устройства
 * Первый метод отправляет сигнал один раз
 * Второй метод отправляет сигнал пока нажата кнопка
 * Третий метод отправляет 3 сигнала с интервалом 40 миллисекунд
 */
void send(String *code, uint8_t methode) { //принимаем ссылку на строку кода сигнала и метод для отправки
  if (receiverPowerFlag == false) { //если ИК приёмник выключен
    char* stringToChar = code->c_str(); //разбиваем ir код на биты
    unsigned long int sendIRCode = strtoul(stringToChar, NULL, 16); //конвертируем в unsigned long int
    if (methode == 1) sendProtocolCheck(sendIRCode); //если первый метод
    else if (methode == 2) { //если второй метод
      do {
        sendProtocolCheck(sendIRCode);
        delay(40);
      }
      while (digitalRead(buttonsArray[1]) == 0);
    } else if (methode == 3) { //если третий метод
      for (uint8_t i = 0; i < 3; i++) {
        sendProtocolCheck(sendIRCode);
        delay(40);
      }
    }
  } else { //если ИК приёмник включен - выключить
    receiverPowerFlag = !receiverPowerFlag;
    digitalWrite(RECEIVER_POWER, receiverPowerFlag); //вкл/выкл (0/1)
    irrecv.blink13(false);
    digitalWrite(BLINK_PIN, LOW);
  }
}

/*Процедура отправки ИК сигнала в зависимости от выбранного протокола*/
void sendProtocolCheck(unsigned long int code) {
  switch (sendProtocol) {
    case 0:
      irsend.sendLG(code, 32);
      break;
    case 1:
      irsend.sendSAMSUNG(code, 32);
      break;
    case 2:
      irsend.sendSony(code, 20);
      break;
    case 3:
      irsend.sendNEC(code, 32);
      break;
  }
}
