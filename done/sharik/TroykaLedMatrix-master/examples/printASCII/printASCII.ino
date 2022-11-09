// библиотека для работы I²C
#include "Wire.h"
// библиотека для работы со светодиодной матрицей
#include "TroykaLedMatrix.h"

// создаём объект matrix для работы с матрицей
TroykaLedMatrix matrix;

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
  // устанавливаем шрифт
  matrix.selectFont(FONT_8X8_BASIC);
}

void loop()
{
  // с помощью цикла по очереди выводим символы из таблицы ASCII
  for (int i = 32; i < 128; i++) {
    matrix.drawSymbol(i); 
    delay(500);
  }
}
