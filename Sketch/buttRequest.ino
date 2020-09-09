/*Процедура опроса кнопок*/
void buttRequest() {
  /*Присваиваем булевой переменнной инвертированное значение с пина*/
  buttSettings = !digitalRead(buttonsArray[0]);
  buttUse = !digitalRead(buttonsArray[1]);
  buttChoose = !digitalRead(buttonsArray[2]);

  /*Если кнопка нажата И флаг опущен
     И с момента последнего нажатия прошло
     больше 200 миллисекунд, то..
  */
  if (buttChoose && !flagChoose && (millis() - timer > 200)) {
    timer = millis(); //"обнулить счётчик"
    flagChoose = true; //поднять флаг
    buttChooseVoid(); //вызвать метод
  }
  /*Если кнопка не нажата (была отпущена)
     И флаг ещё поднят, то опустить флаг
  */
  if (!buttChoose && flagChoose) flagChoose = false;

  if (buttUse && !flagUse && (millis() - timer > 200)) {
    timer = millis();
    flagUse = true;
    buttUseVoid();
  }
  if (!buttUse && flagUse) flagUse = false;

  if (buttSettings && !flagSettings && (millis() - timer > 200)) {
    timer = millis();
    flagSettings = true;
    buttSettingsVoid();
  }
  if (!buttSettings && flagSettings) flagSettings = false;
}
