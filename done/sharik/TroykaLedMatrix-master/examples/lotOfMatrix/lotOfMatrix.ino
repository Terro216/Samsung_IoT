// библиотека для работы I²C
#include "Wire.h"
// библиотека для работы со светодиодной матрицей
#include "TroykaLedMatrix.h"

// создаём объекты matrix для работы с матрицами
// для каждой матрицы передаём свой адрес
// подробнее читайте на:
// http://wiki.amperka.ru/продукты:troyka-led-matrix
TroykaLedMatrix matrix1(0b01100000);
TroykaLedMatrix matrix2(0b01100001);
TroykaLedMatrix matrix3(0b01100010);

void setup()
{
  // Инициализируем I2C
  Wire.begin();
  
  // начало работы с матрицами
  matrix1.begin();
  matrix2.begin();
  matrix3.begin();
  // очищаем матрицы
  matrix1.clear();
  matrix2.clear();
  matrix3.clear();
  // устанавливаем шрифт
  matrix1.selectFont(FONT_8X8_BASIC);
  matrix2.selectFont(FONT_8X8_BASIC);
  matrix3.selectFont(FONT_8X8_BASIC);
  // выводим на каждую матрицу по символу из строки «C++»
  matrix1.drawSymbol('C');
  matrix2.drawSymbol('+');
  matrix3.drawSymbol('+');
}

void loop()
{

}
