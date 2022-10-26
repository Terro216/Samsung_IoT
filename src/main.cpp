#include "mbed.h"

DigitalOut led(LED1);
int main()
{    
    int i = 0;
    printf("Hello World !\n");
    while(1)     {
        thread_sleep_for(1000); // 1 second 
        led = !led; // Toggle LED
        printf("This program runs since %d seconds.\n", i++);    
    }
} 