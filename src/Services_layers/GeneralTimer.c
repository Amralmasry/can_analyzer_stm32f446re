
#include "Services_layers.h"
#include "GeneralTimer.h"

#include "../MCAL/TIMER_6.h"


static volatile unsigned long Counter_S_Timer[TIMER_COUNTER_NUMBER];
static unsigned char Counter_S_Timer_flag[TIMER_COUNTER_NUMBER];
static uint8_t TIMER_LOOP_COUNTER = 0 ;


static void GeneralTimer_Reset(GTimer_type * me)
{
	if(me->Timer_ID < TIMER_LOOP_COUNTER)
		Counter_S_Timer[me->Timer_ID] = 0;
}

static void GeneralTimer_Start(GTimer_type * me)
{
	if(me->Timer_ID < TIMER_LOOP_COUNTER)
		Counter_S_Timer_flag[me->Timer_ID] = true;
}
static void GeneralTimer_Stop(GTimer_type * me)
{
	if(me->Timer_ID < TIMER_LOOP_COUNTER)
		Counter_S_Timer_flag[me->Timer_ID] = false;
}
static char GeneralTimer_CheckTimeout(GTimer_type * me , uint64_t compare)
{
	if(me->Timer_ID < TIMER_LOOP_COUNTER)
		return !(compare > Counter_S_Timer[me->Timer_ID]);
	else
		return error;
}
static unsigned char GeneralTimer_IsActive(GTimer_type * me)
{
	return Counter_S_Timer_flag[me->Timer_ID];

}
static uint64_t GeneralTimer_VALUE(GTimer_type * me )
{
	return ( Counter_S_Timer[me->Timer_ID]);

}
static void GeneralTimer_update(void)
{
	int __index = 0 ;
	for( __index = 0 ; __index < TIMER_LOOP_COUNTER ; __index ++)
	{
		if(Counter_S_Timer_flag [__index] )
			Counter_S_Timer[__index]++;
	}
}

static void GeneralTimer_Set_VALUE(GTimer_type * me, uint64_t data )
{
	Counter_S_Timer[me->Timer_ID] = data ;

}

void GeneralTimer_Init(void)
{
	timer_6_init();
	timer_6_setcallback(GeneralTimer_update);
}



uint8_t GeneralTimer_Create(GTimer_type * me)
{



	uint8_t RC = false ;
	if (TIMER_LOOP_COUNTER < TIMER_COUNTER_NUMBER && (me->created_flag  != true))
	{
		me->CheckTimeout =  GeneralTimer_CheckTimeout ;
		me->Get_VALUE    =  GeneralTimer_VALUE ;
		me->IsActive     =  GeneralTimer_IsActive ;
		me->Reset        =  GeneralTimer_Reset ;
		me->Start        =  GeneralTimer_Start ;
		me->Stop         =  GeneralTimer_Stop ;
	    me-> Set_VALUE   =  GeneralTimer_Set_VALUE ;

		me->Timer_ID = TIMER_LOOP_COUNTER ;
		me->created_flag = true ;
		RC = true ;
		TIMER_LOOP_COUNTER ++;

	}
	else
	{
		RC = false ;
	}


	return RC ;
}




