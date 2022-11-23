#include "DHT11/Dht11.h"
#include "mbed.h"
#include <Ticker.h>

Dht11 sensor(D3);
DigitalOut myrele(D4);
DigitalOut myled(LED1);
Ticker ticker;
Thread thread;
int ledDelay = 1000;
// bool tooMuch = false;

void ledControl() {
  while (true) {
    myrele = !myrele;
    thread_sleep_for(ledDelay);
  }
}

int main() {
  // ticker.attach(ledControl, 1);
  thread.start(callback(ledControl));

  while (true) {
    sensor.read();
    int tempC = sensor.getCelsius();
    int hum = sensor.getHumidity();
    ledDelay = (10 - (hum / 10 % 10)) * 100;
    if (hum > 75) {
      // ledDelay = 100;
      printf("!WARNING! T: %d, H: %d\n", tempC, hum);
    } else {
      // ledDelay = 1000;
      printf("T: %d, H: %d\n", tempC, hum);
    }
    thread_sleep_for(1000);
  }
}