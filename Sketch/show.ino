/*Отображение элементов на экране в зависимости от позиции*/
void show() {
  frame(); //отрисовка "скелета"/рамы
  switch (choosePosition) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
      lcd.print(button[choosePosition], OLED_C, 0); //Пред. канал
      lcd.print(F("\212\256\244 \252\255\256\257\252\250:"), OLED_C, 2);
      lcd.print(irCodes[choosePosition], OLED_C, 3);
      break;
    case 6:
      lcd.print(F("\214\245\255\356"), OLED_C, 2); //Меню
      lcd.print(F("\215\240\341\342\340\256\245\252"), OLED_C, 3); //Настроек
      break;
    case 7:
      lcd.print(F(">"), 4, arrowPosition); //отрисовать стрелку
      lcd.print(F("\215\240\341\342\340\256\251\252\250"), OLED_C, 0); //Настройки

      lcd.print(F("\221\256\345\340\240\255\250\342\354"), 11, 2); //Сохранить
      lcd.print(F("\216\347\250\341\342\250\342\354"), 11, 3); //Очистить
      lcd.print(F("\221\242\256\250 \252\256\244\353"), 11, 4); //Свои коды
      lcd.print(F("\217\340\256\342\256\252\256\253"), 11, 5); //Протокол
      break;
    case 8:
      lcd.print(F(">"), 4, arrowPosition); //отрисовать стрелку
      lcd.print(F("\221\242\256\250 \252\256\244\353"), OLED_C, 0); //Свои коды

      lcd.print(F("LG"), 11, 2);
      lcd.print(F("SAMSUNG"), 11, 3);
      lcd.print(F("SONY"), 11, 4);
      lcd.print(F("\221\242\256\250 \252\256\244\353"), 11, 5); //Свои коды
      break;
    case 9:
      lcd.print(F(">"), 4, arrowPosition); //отрисовать стрелку
      lcd.print(F("<"), 118, (sendProtocol + 2)); //отрисовать стрелку на уже выбранном протоколе
      lcd.print(F("\217\340\256\342\256\252\256\253"), OLED_C, 0); //Протокол

      lcd.print(F("NEC"), 11, 2);
      lcd.print(F("SAMSUNG"), 11, 3);
      lcd.print(F("SONY"), 11, 4);
      lcd.print(F("LG"), 11, 5);
      break;
  }
  /*Если ИК приёмник включен - отобразить "иконку" в углу дисплея*/
  (receiverPowerFlag == 1) ? lcd.print(F("[S]"), 0 , 0) : lcd.print(F("   "), 0 , 0);
}
