#include "Wire.h"                      // библиотека для протокола I2C
#include "LiquidCrystal_I2C.h"        // библиотека для LCD 16x02 
LiquidCrystal_I2C LCD(0x27, 20, 2);  // присвоение  имени дисплею

// переменные для отсчета времени и будильника
byte SEC = 0;
byte MIN = 34;
byte HOUR = 12;
byte MIN_A = 35;
byte HOUR_A = 12;
unsigned long timer;

// переменные для считывания нажатия на кнопки
boolean button1WasUp = true;
boolean button2WasUp = true;
boolean button1IsUp;
boolean button2IsUp;

boolean alarm = true;
byte c1, c2, c3, w, i;

// значок будильника
byte bell [8] = {
  0b11000,
  0b11110,
  0b01100,
  0b01000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
};

void setup() {
  pinMode(9, INPUT_PULLUP);   // подключение тактовых кнопок
  pinMode(8, INPUT_PULLUP);
  pinMode(5, OUTPUT);        // подключение баззера
  LCD.init();               // инициализация дисплея
  LCD.backlight();         // включение подсветки
  LCD.createChar(1, bell);
  timer = millis();
}

void loop() {
  // детект текущего состояние кнопки
  button1IsUp = digitalRead(9);
  button2IsUp = digitalRead(8);

  // если кнопка 1 нажата, зайти в настройки (цикл while)
  if (button1WasUp && !button1IsUp) {
    delay(10);
    button1IsUp = digitalRead(9);
    if (!button1IsUp) {
      SEC = 0; w = 1;
    }
  }
  button1WasUp = button1IsUp;

  // если кнопка 2 была нажата выключить будильник
  if (button2WasUp && !button2IsUp) {
    delay(10);
    button2IsUp = digitalRead(8);
    if (!button2IsUp) {
      alarm = false;
    }
  }
  button2WasUp = button2IsUp;

  // если прошло 1000 мс - прибавить одну секунду
  if (millis() - timer > 1000) {
    timer = millis();
    SEC++;
    // если прошло 59 секунд, прибавить 1 минуту
    if (SEC > 59) { SEC = 0; MIN++; }
    // если прошло 59 минут, прибавить 1 час
    if (MIN > 59) { MIN = 0; HOUR++; }
    if (HOUR > 23) { HOUR = 0; }
    // включение будильника в течении 1 минуты
    if (alarm == true && HOUR == HOUR_A && MIN == MIN_A && i < 60) { tone(5, 50); i++; }
    if (i >= 60) { noTone(5); alarm == false; i = 0; }

    if (HOUR < 10) { c1 = 5; }
    if (HOUR >= 10) { c1 = 4; }
    if (MIN < 10) { c2 = 8; }
    if (MIN >= 10) { c2 = 7; }
    if (SEC < 10) { c3 = 11; }
    if (SEC >= 10) { c3 = 10; }

    // вывод времени на дисплей
    LCD.setCursor(4, 0);
    LCD.print("0");
    LCD.setCursor(c1, 0);
    LCD.print(HOUR);
    LCD.print(":");
    LCD.setCursor(7, 0);
    LCD.print("0");
    LCD.setCursor(c2, 0);
    LCD.print(MIN);
    LCD.print(":");
    LCD.setCursor(10, 0);
    LCD.print("0");
    LCD.setCursor(c3, 0);
    LCD.print(SEC);
    if (alarm == true) { LCD.print(char(1)); }
    if (alarm == false) { LCD.print(" "); }
    noTone(5);
  }

  while (w == 1) {

    if (HOUR > 23) { HOUR = 0; }
    if (HOUR < 10) { c1 = 5; }
    if (HOUR >= 10) { c1 = 4; }
    if (MIN < 10) { c2 = 8; }
    if (MIN >= 10) { c2 = 7; }

    LCD.setCursor(4, 0);
    LCD.print("0");
    LCD.setCursor(c1, 0);
    LCD.print(HOUR);
    LCD.print(":");
    LCD.setCursor(7, 0);
    LCD.print("0");
    LCD.setCursor(c2, 0);
    LCD.print(MIN);
    LCD.print(":");
    LCD.setCursor(10, 0);
    LCD.print("00");
    if (alarm == true) { LCD.print(char(1)); }
    if (alarm == false) { LCD.print(" "); }

    LCD.setCursor(2, 1);
    LCD.print("HOUR SETTING");

    button1IsUp = digitalRead(9);
    button2IsUp = digitalRead(8);

    // если кнопка 1 была нажата  2 цикл while
    if (button1WasUp && !button1IsUp) {
      delay(10);
      button1IsUp = digitalRead(9);
      if (!button1IsUp) {
        LCD.clear(); w = 2;
      }
    }
    button1WasUp = button1IsUp;

    // если кнопка 2 была нажата, прибавить 1 час
    if (button2WasUp && !button2IsUp) {
      delay(10);
      button2IsUp = digitalRead(8);
      if (!button2IsUp) {
        HOUR++;
      }
    }
    button2WasUp = button2IsUp;

  }

  while (w == 2) {

    if (MIN > 59) { MIN = 0;}
    if (HOUR < 10) { c1 = 5; }
    if (HOUR >= 10) { c1 = 4; }
    if (MIN < 10) { c2 = 8; }
    if (MIN >= 10) { c2 = 7; }

    LCD.setCursor(4, 0);
    LCD.print("0");
    LCD.setCursor(c1, 0);
    LCD.print(HOUR);
    LCD.print(":");
    LCD.setCursor(7, 0);
    LCD.print("0");
    LCD.setCursor(c2, 0);
    LCD.print(MIN);
    LCD.print(":");
    LCD.setCursor(10, 0);
    LCD.print("00");
    if (alarm == true) { LCD.print(char(1)); }
    if (alarm == false) { LCD.print(" "); }

    LCD.setCursor(1, 1);
    LCD.print("MINUTE SETTING");

    button1IsUp = digitalRead(9);
    button2IsUp = digitalRead(8);

    // если кнопка 1 была нажата 3 цикл while
    if (button1WasUp && !button1IsUp) {
      delay(10);
      button1IsUp = digitalRead(9);
      if (!button1IsUp) {
        LCD.clear(); w = 3;
      }
    }
    button1WasUp = button1IsUp;

    // если кнопка 2 была нажата  прибавить 1 минуту
    if (button2WasUp && !button2IsUp) {
      delay(10);
      button2IsUp = digitalRead(8);
      if (!button2IsUp) {
        MIN++;
      }
    }
    button2WasUp = button2IsUp;

  }

  while (w == 3) {

    if (MIN_A > 59) { MIN_A = 0; HOUR_A++; }
    if (HOUR_A > 23) { HOUR_A = 0; }
    if (HOUR_A < 10) { c1 = 5; }
    if (HOUR_A >= 10) { c1 = 4; }
    if (MIN_A < 10) { c2 = 8; }
    if (MIN_A >= 10) { c2 = 7; }

    LCD.setCursor(4, 0);
    LCD.print("0");
    LCD.setCursor(c1, 0);
    LCD.print(HOUR_A);
    LCD.print(":");
    LCD.setCursor(7, 0);
    LCD.print("0");
    LCD.setCursor(c2, 0);
    LCD.print(MIN_A);
    LCD.print(":");
    LCD.setCursor(10, 0);
    LCD.print("00");
    if (alarm == true) { LCD.print(char(1)); LCD.setCursor(4, 1); LCD.print("ALARM ON "); }
    if (alarm == false) { LCD.print(" "); LCD.setCursor(4, 1); LCD.print("ALARM OFF"); }
 
    button1IsUp = digitalRead(9);
    button2IsUp = digitalRead(8);

    // если кнопка 1 была нажата  4 цикл while
    if (button1WasUp && !button1IsUp) {
      delay(10);
      button1IsUp = digitalRead(9);
      if (!button1IsUp) {
        LCD.clear(); w = 4;
      }
    }
    button1WasUp = button1IsUp;

    // если кнопка 2 была нажата прибавить 1 минуту
    if (button2WasUp && !button2IsUp) {
      delay(10);
      button2IsUp = digitalRead(8);
      if (!button2IsUp) {
        alarm = !alarm;
      }
    }
    button2WasUp = button2IsUp;

  }

  while (w == 4) {

    if (MIN_A > 59) { MIN_A = 0; HOUR_A++; }
    if (HOUR_A > 23) { HOUR_A = 0; }
    if (HOUR_A < 10) { c1 = 5; }
    if (HOUR_A >= 10) { c1 = 4; }
    if (MIN_A < 10) { c2 = 8; }
    if (MIN_A >= 10) { c2 = 7; }

    LCD.setCursor(4, 0);
    LCD.print("0");
    LCD.setCursor(c1, 0);
    LCD.print(HOUR_A);
    LCD.print(":");
    LCD.setCursor(7, 0);
    LCD.print("0");
    LCD.setCursor(c2, 0);
    LCD.print(MIN_A);
    LCD.print(":");
    LCD.setCursor(10, 0);
    LCD.print("00");
    if (alarm == true) { LCD.print(char(1)); }
    if (alarm == false) { LCD.print(" "); }

    LCD.setCursor(1, 1);
    LCD.print("ALARM SET HOUR");

    button1IsUp = digitalRead(9);
    button2IsUp = digitalRead(8);

    // если кнопка 1 была нажата 5 цикл while
    if (button1WasUp && !button1IsUp) {
      delay(10);
      button1IsUp = digitalRead(9);
      if (!button1IsUp) {
        LCD.clear(); w = 5;
      }
    }
    button1WasUp = button1IsUp;

    // если кнопка 2 была нажата прибавить 1 час
    if (button2WasUp && !button2IsUp) {
      delay(10);
      button2IsUp = digitalRead(8);
      if (!button2IsUp) {
        HOUR_A++;
      }
    }
    button2WasUp = button2IsUp;
  }

  while (w == 5) {

    if (MIN_A > 59) { MIN_A = 0; HOUR_A++; }
    if (HOUR_A > 23) { HOUR_A = 0; }
    if (HOUR_A < 10) { c1 = 5; }
    if (HOUR_A >= 10) { c1 = 4; }
    if (MIN_A < 10) { c2 = 8; }
    if (MIN_A >= 10) { c2 = 7; }

    LCD.setCursor(4, 0);
    LCD.print("0");
    LCD.setCursor(c1, 0);
    LCD.print(HOUR_A);
    LCD.print(":");
    LCD.setCursor(7, 0);
    LCD.print("0");
    LCD.setCursor(c2, 0);
    LCD.print(MIN_A);
    LCD.print(":");
    LCD.setCursor(10, 0);
    LCD.print("00");
    if (alarm == true) { LCD.print(char(1)); }
    if (alarm == false) { LCD.print(" "); }

    LCD.setCursor(0, 1);
    LCD.print("ALARM SET MINUTE");

    button1IsUp = digitalRead(9);
    button2IsUp = digitalRead(8);

    // если кнопка 1 была нажата  выйти из цикла
    if (button1WasUp && !button1IsUp) {
      delay(10);
      button1IsUp = digitalRead(9);
      if (!button1IsUp) {
        LCD.clear(); w = 0;
      }
    }
    button1WasUp = button1IsUp;

    // если кнопка 2 была нажата прибавить 1 минуту
    if (button2WasUp && !button2IsUp) {
      delay(10);
      button2IsUp = digitalRead(8);
      if (!button2IsUp) {
        MIN_A++;
      }
    }
    button2WasUp = button2IsUp;

  }
}