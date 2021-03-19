/*
 * CAN.h
 *
 *  Created on: Mar 9, 2020
 *      Author: amd
 */

#ifndef CAN_H_
#define CAN_H_
#define GPIO_AFRH_AFRH11                     ((uint32_t) 0x0000F000)
#define GPIO_AFRH_AFRH11_AF9                ((uint32_t) 0x00009000)
#define GPIO_AFRH_AFRH12                     ((uint32_t) 0x000F0000)
#define GPIO_AFRH_AFRH12_AF9                 ((uint32_t) 0x00090000)



#include <stm32f4xx.h>
#include "CAN.h"
#include "../Services_layers/CAN_QUEUE.h"
void CAN1_Init(uint16_t ID_1 , uint16_t ID_2);

void CAN1_Transmit(uint64_t  data,uint8_t DLC,uint16_t ID);
uint8_t Can_GetSize_Queue(void);
void Can_Read_Queue(CAN_Queue_ELEMENT_t * data);
void CAN_SEND_ARRAY(uint8_t *array , int size, int ID);
#endif /* CAN_H_ */
