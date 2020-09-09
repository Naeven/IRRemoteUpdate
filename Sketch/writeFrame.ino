/*Процедура отрисовки границ и иконок для кнопок на дисплее*/
void frame() {
  lcd.print(F("~~~~~~~~~~~~~~~~~~~~~"), OLED_C, 1);
  for (uint8_t i = 2; i <= 7; i++) {
    lcd.print(F("|"), OLED_L, i);
    lcd.print(F("|"), OLED_R, i);
  }
  if (choosePosition != 7
      && choosePosition != 8
      && choosePosition != 9)
  {
    lcd.print(F("[S]"), 6, 7);
    lcd.print(F("[OK]"), OLED_C, 7);
    lcd.print(F("[>>]"), 98, 7);
  }
  else
  {
    lcd.print(F("[<]"), 6, 7);
    lcd.print(F("[OK]"), OLED_C, 7);
    lcd.print(F("[>>]"), 98, 7);
  }
}
