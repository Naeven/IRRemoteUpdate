/*Работа кнопки отправить/ОК*/
void buttUseVoid() {
  switch (choosePosition) {
    case 0:
      send(&irCodes[choosePosition], 3);
      break;
    case 1:
    case 2:
      send(&irCodes[choosePosition], 2);
      break;
    case 3:
    case 4:
    case 5:
      send(&irCodes[choosePosition], 1);
      break;
    case 6:
      if (!receiverPowerFlag) {
        lcd.clrScr();
        choosePosition = 7;
        arrowPosition = 2;
      } else {
        receiverPowerFlag = false;
        digitalWrite(RECEIVER_POWER, receiverPowerFlag); //вкл/выкл (0/1)
        irrecv.blink13(false);
        digitalWrite(BLINK_PIN, LOW);
      }
      break;
    case 7:
      switch (arrowPosition) {
        case 2:
          saveEEPROM();
          break;
        case 3:
          clearEEPROM();
          break;
        case 4:
        case 5:
          lcd.clrScr();
          choosePosition = (arrowPosition + 4);
          arrowPosition = 2;
          break;
      }
      break;
    case 8:
      switch (arrowPosition) {
        case 2:
          uploadCode(myCode);
          break;
        case 3:
          uploadCode(myCode1);
          break;
        case 4:
          uploadCode(myCode2);
          break;
        case 5:
          uploadCode(myCode3);
          break;
      }
      lcd.clrScr();
      choosePosition = 0;
      break;
    case 9:
      switch (arrowPosition) {
        case 2:
        case 3:
        case 4:
        case 5:
          sendProtocol = (arrowPosition - 2);
          break;
      }
      lcd.clrScr();
      choosePosition = 0;
      break;
  }
  chargeControl(); //вывести уровень заряда
  show(); //главное меню
}

void uploadCode(const char * *code) {
  for (uint8_t i = 0; i < 6; i++) irCodes[i] = code[i];
  sendProtocol = atoi(code[6]);
}
