/*Работа кнопки настройки/назад*/
void buttSettingsVoid() {
  /*
     Функция включения ИК приёмника доступна
     только пока мы не находимся на 6,7,8 или 9 позиции
  */
  if (choosePosition != 6
      && choosePosition != 7
      && choosePosition != 8
      && choosePosition != 9) {
    /*Вкл/Выкл (0/1), с каждым нажатием
      значение меняется с 0 на 1 и
      наоборот, и это значение подставляется
      ниже по коду..
    */
    receiverPowerFlag = !receiverPowerFlag;
    digitalWrite(RECEIVER_POWER, receiverPowerFlag); //вкл/выкл (0/1)
    if (digitalRead(RECEIVER_POWER) == HIGH) { //если питание ИК-приёмника есть
      irrecv.enableIRIn(); //включение ИК-приёмника
      irrecv.blink13(true); //включить мигалку
    } else {
      irrecv.blink13(false); //выключить мигалку
      digitalWrite(BLINK_PIN, LOW); //подать на мигалку низкий сигнал
    }
  } else if (choosePosition == 8 || choosePosition == 9) {
    /*
       Если мы на 8 или 9 позиции, при нажатиии
       кнопки очистить экран, сбросить стрелочку
       и вернутся в меню настроек
    */
    lcd.clrScr();
    chargeCheck();
    arrowPosition = 2;
    choosePosition = 7;
  } else if (choosePosition == 7) {
    /*
       Если мы в меню настроек, при нажатии кнопки
       возвращаемся на первую позицию
    */
    lcd.clrScr();
    chargeCheck();
    choosePosition = 0;
  }
  show(); //главное меню
}
