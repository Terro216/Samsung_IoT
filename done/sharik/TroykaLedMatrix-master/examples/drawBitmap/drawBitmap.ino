// библиотека для работы I²C
#include "Wire.h"
// библиотека для работы со светодиодной матрицей
#include "TroykaLedMatrix.h"

// создаём объект matrix для работы с матрицей
TroykaLedMatrix matrix;

// массив картнки сердца
const uint8_t heart[] {
  0b00000000,
  0b01100110,
  0b11111111,
  0b11111111,
  0b11111111,
  0b01111110,
  0b00111100,
  0b00011000,
};

void setup()
{
  Wire.begin();
  // начало работы с матрицей
  matrix.begin();
  // очищаем матрицу
  matrix.clear();
  // отображаем на матрице сердце и вращаем по часовой стрелке
  matrix.drawBitmap(heart);
}

void loop()
{
}
