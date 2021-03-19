/*
 * delay.h
 *
 *  Created on: Jun 25, 2019
 *      Author: amd
 */

#ifndef DELAY_H_
#define DELAY_H_
#include <stdint.h>
void _delay_ms(int n);
//void  _delay_ms(uint32_t time);



void DELAY_INIT (void);
void DELAY (uint32_t dd );


#endif /* DELAY_H_ */
