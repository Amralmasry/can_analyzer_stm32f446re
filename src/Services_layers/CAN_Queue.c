
#include "CAN_QUEUE.h"
#include "string.h"
char CAN_Queue_isEmpty(CAN_Queue_t *me)
{
	return   (me->conut == 0);
}

char CAN_Queue_isFull(CAN_Queue_t *me)
{
	return (me->conut >= BUFFER_SIZE-1);
}

int CAN_Queue_getSize(CAN_Queue_t *me)
{
	return me->conut;
}

void CAN_Queue_Enqueue(CAN_Queue_t *me , CAN_Queue_ELEMENT_t *incomingdata)
{
	if(CAN_Queue_isFull(me) == 0)
	{
		memcpy((uint8_t*)&me->ELEMENT[me->head++],(uint8_t * )incomingdata,sizeof(CAN_Queue_ELEMENT_t));
 		me->conut++;
		me->head %= BUFFER_SIZE;
	}

}

void CAN_Queue_Dequeue(CAN_Queue_t *me , CAN_Queue_ELEMENT_t *Data)
{
	if(CAN_Queue_isEmpty(me) == 0)
	{
		memcpy((uint8_t * )Data,(uint8_t*)&me->ELEMENT[me->tail++],sizeof(CAN_Queue_ELEMENT_t));
		me->conut--;
		me->tail %= BUFFER_SIZE;
	}
}






























