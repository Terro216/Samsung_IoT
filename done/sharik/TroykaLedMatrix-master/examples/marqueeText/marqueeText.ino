#include "TroykaLedMatrix.h"
 
TroykaLedMatrix matrix;
// Массив с текстом для бегущей строки
char Str[] = " Arduino";
// Нам понадобится длина масива
byte  len = sizeof(Str);
uint16_t shift = 0;

 
void setup() {
  // Инициализируем I2C
  Wire.begin();
  // начало работы с матрицей
  matrix.begin();
  // для нестандартного Wire
  // matrix.begin(Wire1);
  // выбираем шрифт
  matrix.selectFont(FONT_8X8_BASIC);
}
 
void loop() {
// Печатаем текст бегущей строкой
  delay(70);
  matrix.marqueeText(Str, len, shift++);
  if (shift == len * 8) {
    shift = 0;
  }
}

