void settings() {
  if (millis() - timer >= 4000) { //защита от приёма "мусорных" значений
    switch (choosePosition) {
      case 0:
      case 1:
      case 2:
      case 3:
      case 4:
      case 5:
        settingsMethode(&irCodes[choosePosition]);
        break;
    }
  }
}

void settingsMethode(String *code) { //принимаем строку с кодом для обработки и записи
  if (irrecv.decode(&results)) { //если пришёл сигнал
    *code = String(results.value, HEX); //записать результаты в кодировке HEX в строку
    code->toUpperCase(); //перевести строку в вверхний регистр (аа -> AA)
    *code = String("0x") + *code; //добавить 0x в начале ir кода
    irrecv.resume(); //готов принять следующий сигнал
    show(); //главное меню
  }
}
