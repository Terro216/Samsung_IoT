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
  // Инициализируем I2C
  Wire.begin();
  // начало работы с матрицей
  matrix.begin();
  // для нестандартного Wire
  // matrix.begin(Wire1);

  // очищаем матрицу
  matrix.clear();
  // отображаем на матрице сердце
  matrix.drawBitmap(heart);
}

void loop()
{
  // считываем значение с потенциометра
  int sensorValue = analogRead(A3);
  // в зависимоти от занчения регулятора
  // устанавливаем яркость светодиодной матрицы
  if (sensorValue < 100) {
    matrix.setCurrentLimit(ROW_CURRENT_05MA);
  } else if (sensorValue >= 100 && sensorValue < 200) {
    matrix.setCurrentLimit(ROW_CURRENT_10MA);
  } else if (sensorValue >= 200 && sensorValue < 300) {
    matrix.setCurrentLimit(ROW_CURRENT_15MA);
  } else if (sensorValue >= 300 && sensorValue < 400) {
    matrix.setCurrentLimit(ROW_CURRENT_20MA);
  } else if (sensorValue >= 400 && sensorValue < 500) {
    matrix.setCurrentLimit(ROW_CURRENT_25MA);
  } else if (sensorValue >= 500 && sensorValue < 600) {
    matrix.setCurrentLimit(ROW_CURRENT_30MA);
  } else if (sensorValue >= 600 && sensorValue < 700) {
    matrix.setCurrentLimit(ROW_CURRENT_35MA);
  } else if (sensorValue >= 700 && sensorValue < 800) {
    matrix.setCurrentLimit(ROW_CURRENT_40MA);
  } else if (sensorValue >= 800 && sensorValue < 900) {
    matrix.setCurrentLimit(ROW_CURRENT_45MA);
  } else if (sensorValue >= 900 && sensorValue < 1000) {
    matrix.setCurrentLimit(ROW_CURRENT_45MA);
  } else {
    matrix.setCurrentLimit(ROW_CURRENT_50MA);
  }
}
