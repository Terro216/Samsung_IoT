// библиотека для работы I²C
#include "Wire.h"
// библиотека для работы со светодиодной матрицей
#include "TroykaLedMatrix-master/TroykaLedMatrix.h"

#include "Troyka-IMU/src/TroykaIMU.h"

// создаём объект matrix для работы с матрицей
TroykaLedMatrix matrix;
// Создаём объект для фильтра Madgwick
Madgwick filter;
// Создаём объект для работы с гироскопом
Gyroscope gyroscope;
// Создаём объект для работы с акселерометром
Accelerometer accelerometer;

struct BallPosition
{
  int x = 0;
  int y = 0;
  double aX = 0;
  double v0X = 0;
  double t = 0;
  double aY = 0;
  double v0Y = 0;
  const double g = 9.8;
  double distanceX = 0;
  double lastDistanceX = 0;
  double distanceY = 0;

  BallPosition(int x, int y)
  {
    this->x = x;
    this->y = y;
  }
};
BallPosition ball(3, 3);

// Переменные для данных с гироскопа и акселерометра
float gx, gy, gz, ax, ay, az;

// Переменные для хранения самолётных углов ориентации
float yaw, pitch, roll;

// Переменная для хранения частоты выборок фильтра
float sampleRate = 100;

uint8_t bitmap[]{
    0b00000000,
    0b00000000,
    0b00100000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
};

void setup()
{
  Serial.begin(9600);
  // начало работы с матрицей
  matrix.begin();
  // очищаем матрицу
  matrix.clear();
  // Инициализируем гироскоп
  gyroscope.begin();
  // Инициализируем акселерометр
  accelerometer.begin();
  // Инициализируем фильтр
  filter.begin();
  // Выводим сообщение об удачной инициализации
  Serial.println("Initialization completed");
}

void changeBitmap()
{
  // clear
  for (int i = 0; i < 8; i++)
    bitmap[i] = 0b00000000;

  // set
  bitmap[ball.y] = 0b00000001 << ball.x;
}

void changeball(double deltaMillis)
{
  ball.t = deltaMillis / 1000;
  ball.aX = ball.g * sin(roll * PI / 180);
  ball.aY = ball.g * sin(pitch * PI / 180);
  ball.v0X += ball.aX * ball.t;
  ball.v0Y = ball.aY * ball.t;
  if (abs(roll) > 3)
  {
    double dX = ball.v0X * ball.t + (ball.aX * ball.t * ball.t / 2);
    ball.distanceX = ball.distanceX + (dX);
    Serial.print("dX: ");
    Serial.print(dX);
    Serial.print("\t\t");
    Serial.print("ball.distanceX: ");
    Serial.print(ball.distanceX);
    Serial.print("\t\t");
    Serial.print("ball.aX: ");
    Serial.print(ball.aX);
    Serial.print("\t\t");

    if (ball.distanceX > 0.07)
    {
      ball.distanceX = 0.07;
      ball.v0X = 0;
    }
    else if (ball.distanceX < 0)
    {
      ball.distanceX = 0;
      ball.v0X = 0;
    }
    ball.x = (int)(ball.distanceX / 0.01);
  }
  else
  {
    ball.aX = 0;
    ball.v0X = 0;
  }
}

void getData()
{
  // Запоминаем текущее время
  unsigned long startMillis = millis();
  // Считываем данные с акселерометра в единицах G
  accelerometer.readAccelerationGXYZ(ax, ay, az);
  // Считываем данные с гироскопа в радианах в секунду
  gyroscope.readRotationRadXYZ(gx, gy, gz);
  // Устанавливаем частоту фильтра
  filter.setFrequency(sampleRate);
  // Обновляем входные данные в фильтр
  filter.update(gx, gy, gz, ax, ay, az);

  // Получаем из фильтра углы: yaw, pitch и roll
  yaw = filter.getYawDeg();
  pitch = filter.getPitchDeg();
  roll = filter.getRollDeg();
  Serial.print("pitch: ");
  Serial.print(pitch);
  Serial.print("\t\t");
  Serial.print("roll: ");
  Serial.println(roll);
  Serial.print("\t\t");

  // Вычисляем затраченное время на обработку данных
  unsigned long deltaMillis = millis() - startMillis;
  // Вычисляем частоту обработки фильтра
  sampleRate = 1000 / deltaMillis;

  changeball(deltaMillis);
  changeBitmap();
}

void loop()
{
  getData();
  matrix.drawBitmap(bitmap);
}