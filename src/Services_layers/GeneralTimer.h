/*
 * Speical_Timer.h
 *
 *  Created on: 8 Feb 2019
 *      Author: root
 */

#ifndef SERVICESpecialTimerLAYERSpecialTimerSPEICAL_TIMER_H_
#define SERVICESpecialTimerLAYERSpecialTimerSPEICAL_TIMER_H_

#include "stdint.h"


#define TIMER_COUNTER_NUMBER 20
typedef struct timer_g GTimer_type ;
struct timer_g {

	uint8_t Timer_ID ;
 	void    (*Reset)(GTimer_type * me);
	void    (*Start)(GTimer_type * me);
	void    (*Stop)(GTimer_type * me );
	char    (*CheckTimeout)(GTimer_type * me , uint64_t compare);
	unsigned char (*IsActive)(GTimer_type * me);
	uint64_t (*Get_VALUE)( GTimer_type * me );
	void (*Set_VALUE)( GTimer_type * me,uint64_t data );
	int created_flag ;

};
uint8_t GeneralTimer_Create(GTimer_type * me);
void GeneralTimer_Init(void);



#endif /* SERVICESpecialTimerLAYERSpecialTimerSPEICAL_TIMER_H_ */
