#include <stdint.h>
#include <stdio.h>
#include "GeneralTimer.h"

volatile uint32_t value ;
GTimer_type DELAY_TIMER  ;
void _delay_ms(int n)
{
    int i, j;
    for(i = 0 ; i < n; i++)
        for(j = 0; j < (1590*24)/8; j++)
        {} /* do nothing for 1 ms */
}


void DELAY_INIT (void)
{

	GeneralTimer_Create(&DELAY_TIMER);
	DELAY_TIMER.Start(&DELAY_TIMER);
}


void DELAY (uint32_t dd )
{
	value=DELAY_TIMER.Get_VALUE(&DELAY_TIMER);
	while (!((DELAY_TIMER.Get_VALUE(&DELAY_TIMER)-value)>=dd));
}
