/*
 * Queue.h
 *
 *  Created on: 1 Feb 2019
 *      Author: root
 */

#ifndef SERVIdCES_LAYERS_QUEUE_H_
#define SERVIdCES_LAYERS_QUEUE_H_

#define BUFFER_SIZE 80

#include <stdint.h>


typedef struct QueueCAN_ELEMETN CAN_Queue_ELEMENT_t;
struct QueueCAN_ELEMETN
{
	unsigned char Buffer[8];
	uint16_t ID ;
	uint8_t DLC ;
};


typedef struct CANQueue CAN_Queue_t;
struct CANQueue
{
	CAN_Queue_ELEMENT_t ELEMENT[BUFFER_SIZE];
	int head;
	int tail;
	int conut;
};

void CAN_Queue_Enqueue(CAN_Queue_t *me , CAN_Queue_ELEMENT_t * incomingdata);
void CAN_Queue_Dequeue(CAN_Queue_t *me , CAN_Queue_ELEMENT_t * Data);
int CAN_Queue_getSize(CAN_Queue_t *me);
char CAN_Queue_isFull(CAN_Queue_t *me);
char CAN_Queue_isEmpty(CAN_Queue_t *me);


#endif /* SERVICES_LAYERS_QUEUE_H_ */
