/*Функция проверки уровня заряда*/
void chargeControl() {
  timerCharge = millis(); //сбросить счётчик
  /*
    Строка prozent равна = конвертировать показания с функции
    chargeCheck (от 3300 (3.3В) до 4214 (4.2В)) до
    показаний от 1 до 99 + символ %
  */
  prozent = String(map(chargeCheck(), 3300, 4214, 1, 99)) + "%";
}
