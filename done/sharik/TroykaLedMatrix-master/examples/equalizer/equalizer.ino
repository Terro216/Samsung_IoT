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
  // включаем аналоговый вход
  matrix.enableAudioInput();
  // выставляем нужное усиление
  matrix.setAudioGain(AUDIO_GAIN_0DB);
  // включаем эквалайзер
  matrix.enableEqualizer();
}

void loop()
{

}
