#include "delay.h"

void delay( int iteration)
{
int volatile counter;
counter = 0;
while(counter < iteration)
{
++counter;
}
}
