#include "mbed.h"

DigitalIn mybutton1(A4);
DigitalIn mybutton2(A5);
DigitalIn mybutton3(D2);
DigitalIn mybutton4(D7);
DigitalOut myrele(D9);
DigitalOut mydiod(LED1);

int main()
{
    mybutton1.mode(PullUp);
    mybutton2.mode(PullUp);
    mybutton3.mode(PullUp);
    mybutton4.mode(PullUp);

    int pinCounter = 0;
    const int PIN = 1324;
    printf("Enter PIN\n");

    while (1)
    {
        if (mybutton1 == 0)
        {
            printf("Button 1 pressed\n");
            if (pinCounter == 0 || pinCounter == 1)
                pinCounter = 1;
            else
                pinCounter = 0;
        }
        else if (mybutton2 == 0)
        {
            printf("Button 2 pressed\n");
            if (pinCounter == 2 || pinCounter == 3)
                pinCounter = 3;
            else
                pinCounter = 0;
        }
        else if (mybutton3 == 0)
        {
            printf("Button 3 pressed\n");
            if (pinCounter == 1 || pinCounter == 2)
                pinCounter = 2;
            else
                pinCounter = 0;
        }
        else if (mybutton4 == 0)
        {
            printf("Button 4 pressed\n");
            if (pinCounter == 3 || pinCounter == 4)
                pinCounter = 4;
            else
                pinCounter = 0;
        }
        if (pinCounter == 4)
        {
            printf("PIN correct\n");
            myrele = 1;
            mydiod = 1;
            for (int i = 0; i < 10; i += 1)
            {
                mydiod = !mydiod;
                thread_sleep_for(1000);
            }
            myrele = 0;
            mydiod = 0;
            pinCounter = 0;
        }
    }
}