/*Работа кнопки скроллинга*/
void buttChooseVoid() {
  /*
     Если мы не на 7,8, или 9 позиции, то
     выполняем скроллинг по пунктам главного меню,
     иначе управляем стрелочкой
  */
  if (choosePosition != 7
      && choosePosition != 8
      && choosePosition != 9) {
    choosePosition++; //перелистывание позиций меню
    if (choosePosition > 6) choosePosition = 0; //если больше 6, то всё сначала
    for (uint8_t i = 0; i < 5; i++) if (i != 1) lcd.print(F("           "), OLED_C, i);
  } else {
    arrowPosition_Methode();
  }
  show(); //главное меню
}
