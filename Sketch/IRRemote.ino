/*IRRemote дублирующий пульт
   от swiezdo v2.0
   http://swiezdo.com/
*/

#define I2C_ADRESS 0x78 //адрес I2C/TWI дисплея
#define RECEIVER_PIN 2 //пин ИК приёмника (DATA/OUT)
#define RECEIVER_POWER 8 //пин питания ИК приёмника (VCC)
#define BLINK_PIN 4 //пин анода светодиода, для моргания при получении ИК сигналов
#define SETTINGS_BUTTON_PIN 5 //пин кнопки (Настройки/Назад)
#define USE_BUTTON_PIN 6 //пин кнопки (ОК/Отправить)
#define CHOOSE_BUTTON_PIN 7 //пин кнопки скроллинга
/*
   Начальный адрес для записи в EEPROM,
   начинаем с 1 потому, что на 0 адрес мы записываем
   1 байт, хранящий в себе информацию о том, какой протокол
   для отправки ИК сигнала мы сохранили. По умолчанию 0 - NEC.
*/
#define EEPROM_START_ADRESS 1
#define EEPROM_NUMBER_OF_RECORDS 6 //кол-во записей/кнопок в EEPROM
/*
   32-битный код содержит 10 символов (1x23456789).
   В виде строки типа String содержится 10 символов +
   терминирующий символ `\0`. При записи и чтении в/из EEPROM мы
   записываем/читаем 11 символов с терминатором, а перед записью -
   проверяем только 10 символов, т.к. ноль нас не интересует.
*/
#define EEPROM_RECORDING_SIZE (EEPROM_BUFFER_SIZE + 1) //размер для записи/чтения EEPROM
#define EEPROM_BUFFER_SIZE 10 //размер буфера для проверки перед записью в EEPROM

/*Библиотека для работы с памятью EEPROM*/
#include <EEPROMex.h>
/*Библиотека для дисплея*/
#include <iarduino_OLED_txt.h>
/*Библиотеки для ИК передатчика и приёмника*/
#include <IRremote.h>

iarduino_OLED_txt lcd(I2C_ADRESS); //инициализация дисплея
extern uint8_t SmallFontRus[]; //подключение шрифта
IRrecv irrecv(RECEIVER_PIN, BLINK_PIN); //инициализация ИК приёмника и мерцающего светодиода
IRsend irsend; //объявление обьекта ИК передатчика
decode_results results; //объявления обьекта для приходящих ИК сигналов

bool flagChoose, flagUse, flagSettings, buttChoose, buttUse, buttSettings, receiverPowerFlag;
uint8_t sendProtocol, choosePosition, arrowPosition, EEPROM_adress[EEPROM_NUMBER_OF_RECORDS];
const uint8_t buttonsArray[] = {SETTINGS_BUTTON_PIN, USE_BUTTON_PIN, CHOOSE_BUTTON_PIN}; //массив с пинами кнопок
uint32_t timer; //для таймера на millis
String irCodes[EEPROM_NUMBER_OF_RECORDS]; //хранение ir кодов в виде строки
/*Для проверки уровня заряда*/
String prozent;
unsigned long timerCharge;
int16_t vcc;

/*LG*/
const char *myCode[] = {
  "0x20DF10EF",
  "0x20DF40BF",
  "0x20DFC03F",
  "0x20DF906F",
  "0x20DF00FF",
  "0x20DF807F",
  /*
     Номер протокола
     0 - NEC
     1 - SAMSUNG
     2 - SONY
     3 - LG
  */
  "3",
};
/*SAMSUNG*/
const char *myCode1[] = {
  "0xE0E040BF",
  "0xE0E0E01F",
  "0xE0E0D02F",
  "0xE0E0F00F",
  "0xE0E048B7",
  "0xE0E008F7",
  "1",
};
/*SONY*/
const char *myCode2[] = {
  "0xA90",
  "0x490",
  "0xC90",
  "0x290",
  "0x090",
  "0x890",
  "2",
};
/*Свои коды 3*/
const char *myCode3[] = {
  "",
  "",
  "",
  "",
  "",
  "",
  "0",
};

/*Функция определения напряжения питания устройства*/
static int chargeCheck() {
  ADMUX = 1 << REFS0; //опорное напряжение - vcc
  ADMUX |= 0x0E;    //объект измерения - внутренний источник стабилизированного напряжения 1.1В
  delayMicroseconds(250);
  ADCSRA |= 1 << ADSC; //запуск АЦ-преобразования
  while (ADCSRA & (1 << ADSC)); //и ожидание его завершения
  return ADC ? (1100L * 1023) / ADC : -1;
}

void setup() {
  /*Включение дисплея*/
  lcd.begin(); // инициируем работу с дисплеем.
  lcd.setFont(SmallFontRus); //включаем шрифт

  /*Настроить пин для ИК приёмника как выход и подать низкий сигнал*/
  pinMode(RECEIVER_POWER, OUTPUT);
  digitalWrite(RECEIVER_POWER, LOW);

  /*Настроить пины кнопок с подтягивающим резистором*/
  for (uint8_t i = 0; i < (sizeof(buttonsArray)) / sizeof(buttonsArray[0]); i++) pinMode(buttonsArray[i], INPUT_PULLUP);

  /*Создание массива с адресами для записи/чтения в/из EEPROM*/
  for (uint8_t i = 0, j = EEPROM_START_ADRESS; i < EEPROM_NUMBER_OF_RECORDS; i++, j += EEPROM_RECORDING_SIZE) EEPROM_adress[i] = j;

  readEEPROM(); //запустить чтение из EEPROM
  show(); //главное меню
  chargeControl(); //вывести уровень заряда
}
void loop() {
  buttRequest(); //опрос кнопок
  /*Если ИК приёмник включен, заходим в настройку*/
  if (digitalRead(RECEIVER_POWER) == HIGH) settings();
  /*Если прошло 10 секунд, проверить уровень заряда*/
  if (millis() - timerCharge >= 10000) chargeControl();
}
