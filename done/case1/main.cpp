#include "mbed.h"

DigitalIn mybutton1(A4);
DigitalIn mybutton2(A5);
DigitalIn mybutton3(D2);
DigitalIn mybutton4(D7);
DigitalOut myrele(D9);
DigitalOut mydiod(LED1);

int main() {
  int currentButton = 0;
  const int PIN = 4231;
  const int delayTime = 1000; // default = 1000
  DigitalIn *buttons = new DigitalIn[4]{mybutton1, mybutton2, mybutton3, mybutton4};
  for (int i = 0; i < 4; i++) {
    buttons[i].mode(PullUp);
  }
  printf("Enter PIN\n");

  while (1) {
    // printf("CODE -1: %d%d%d%d\n", PIN / 1000 - 1, PIN / 100 % 10 - 1, PIN / 10 % 10 - 1, PIN % 10 - 1);
    bool firstButtonPressed = buttons[PIN / 1000 - 1].read() == 0;
    bool secondButtonPressed = buttons[PIN / 100 % 10 - 1].read() == 0;
    bool thirdButtonPressed = buttons[PIN / 10 % 10 - 1].read() == 0;
    bool fourthButtonPressed = buttons[PIN % 10 - 1].read() == 0;
    bool correctButtonPressed = buttons[currentButton - 1].read() == 0;
    bool someButtonPressed = firstButtonPressed || secondButtonPressed || thirdButtonPressed || fourthButtonPressed;

    if (firstButtonPressed && (currentButton == 0 || currentButton == 1)) {
      printf("button 1 pressed\n");
      currentButton = 1;
    } else if (secondButtonPressed && (currentButton == 1 || currentButton == 2)) {
      printf("button 2 pressed\n");
      currentButton = 2;
    } else if (thirdButtonPressed && (currentButton == 2 || currentButton == 3)) {
      printf("button 3 pressed\n");
      currentButton = 3;
    } else if (fourthButtonPressed && (currentButton == 3 || currentButton == 4)) {
      printf("button 4 pressed\n");
      currentButton = 4;
    } else if (currentButton != 0 && someButtonPressed && !correctButtonPressed) {
      printf("Error. Try again :) \n");
      currentButton = 0;
    }

    if (currentButton == 4) {
      printf("PIN correct\n");
      myrele = 1;
      for (int i = 0; i < 10; i += 1) {
        mydiod = !mydiod;
        thread_sleep_for(delayTime);
      }
      myrele = 0;
      mydiod = 0;
      currentButton = 0;
    }
  }
}