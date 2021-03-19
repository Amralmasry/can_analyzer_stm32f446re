
#include <stm32f4xx.h>
#include "CAN.h"
#include "../Services_layers/CAN_QUEUE.h"
#include "string.h"

CAN_Queue_t  can_queue;

void CAN1_Init(uint16_t ID_1 , uint16_t ID_2)
{
	/* Configure GPIO with AF9, CAN1 connected to APB1 with 45MHz clock
	 * CAN1_RX  -> PA11 (IN)
	 * CAN1_TX  -> PA12 (OUT)
	 * ***********************/
	/* Enable port A clock */
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	/* Select alternate function mode */
	GPIOA->MODER &= ~(GPIO_MODER_MODER11 | GPIO_MODER_MODER12);
	GPIOA->MODER |= (GPIO_MODER_MODER11_1 | GPIO_MODER_MODER12_1);
	/* Select output type push-pull */
	GPIOA->OTYPER &= ~(GPIO_OTYPER_OT_12);
	/* Select output speed medium */
	GPIOA->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR12);
	GPIOA->OSPEEDR |= (GPIO_OSPEEDER_OSPEEDR12_0);
	/* Select pull up */
	GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPDR11 | GPIO_PUPDR_PUPDR12);
	GPIOA->PUPDR |= (GPIO_PUPDR_PUPDR11_0 | GPIO_PUPDR_PUPDR12_0);
	/* Select AF9 */
	GPIOA->AFR[1] &= ~(GPIO_AFRH_AFRH11 | GPIO_AFRH_AFRH12);
	GPIOA->AFR[1] |= (GPIO_AFRH_AFRH11_AF9 | GPIO_AFRH_AFRH12_AF9);
	RCC->APB1ENR |= RCC_APB1ENR_CAN1EN;
	/* Set automatic bus-off management */
	CAN1->MCR |= CAN_MCR_ABOM;
	/* Set transmit FIFO priority driven by the request order */
	CAN1->MCR |= CAN_MCR_TXFP;
	/* Initialization request */
	CAN1->MCR |= CAN_MCR_INRQ;
	/* Request to exit Sleep mode */
	CAN1->MCR &= ~CAN_MCR_SLEEP;
	/* Wait for initialization mode */
	CAN1->IER |= CAN_IER_FMPIE0 ;
	while((CAN_MSR_SLAK == (CAN_MSR_SLAK & CAN1->MSR))
			|| (CAN_MSR_INAK != (CAN_MSR_INAK & CAN1->MSR)))
	{
		/* Do nothing until initialization mode is entered */
	}
	CAN1->BTR = 0x00060004;
	/* Reset identifier register, no extension, no remote */
	CAN1->sTxMailBox[0].TIR = 0;
	/* Set CAN frame length to 8 */
	/* Reset transmit data registers  */
	CAN1->sTxMailBox[0].TDLR = 0;
	CAN1->sTxMailBox[0].TDHR = 0;
	/* Set Filter init mode */
	CAN1->FMR |= CAN_FMR_FINIT;

	/* Set filer mode, 1   list  */
	CAN1->FM1R |= (CAN_FM1R_FBM1 | CAN_FM1R_FBM2  );

	/* Set FIFO 0 for all filters */
	CAN1->FFA1R &= ~(CAN_FFA1R_FFA1  | CAN_FFA1R_FFA2);



	/* Set filter 1, list mode with ID = 0x25 */
	CAN1->sFilterRegister[1].FR1 =(ID_1 << 21)|(ID_1 << 5); /* No. 2, 3 */
	CAN1->sFilterRegister[1].FR2 =(ID_1 << 21)|(ID_1 << 5); /* No. 4, 5 */

	CAN1->sFilterRegister[2].FR1 =(ID_2 << 21)|(ID_2 << 5);
	CAN1->sFilterRegister[2].FR2 =(ID_2 << 21)|(ID_2 << 5);

	/* Activate filters */
	CAN1->FA1R |= (CAN_FA1R_FACT1 | CAN_FA1R_FACT2  );

	/* Active filters mode */
	CAN1->FMR &= ~CAN_FMR_FINIT;

	/* Request normal mode */
	CAN1->MCR &= ~(CAN_MCR_INRQ | CAN_MCR_SLEEP);

	NVIC_EnableIRQ(CAN1_RX0_IRQn);

}


void CAN1_Transmit(uint64_t  data,uint8_t DLC,uint16_t ID)
{


	/* Check if transmission mailbox empty */
	while(CAN_TSR_TME0 != (CAN_TSR_TME0 & (CAN1->TSR)))
	{

	}

	uint32_t data_32[2] = {0,0} ;
	memcpy((uint8_t*)data_32,(uint8_t*)&data,DLC);


	CAN1->sTxMailBox[0].TIR = 0;
	/* Set CAN standard identifier = 0x100 */
	CAN1->sTxMailBox[0].TIR &=~ (0xB<<21);
	CAN1->sTxMailBox[0].TIR |= (ID<<21);

	/* Set CAN frame length to 8 */
	CAN1->sTxMailBox[0].TDTR &= ~CAN_TDT0R_DLC;
	CAN1->sTxMailBox[0].TDTR |= DLC;

	//		UART_Write_Array(USART1,(uint8_t *)&data_32,DLC);
	//		UART_Write_Array(USART1,(uint8_t *)"\n",1);



	CAN1->sTxMailBox[0].TDLR = data_32[0];
	if (DLC > 4)
		CAN1->sTxMailBox[0].TDHR = data_32[1];
	else
		CAN1->sTxMailBox[0].TDHR = 0;



	/* Transmission request */
	CAN1->sTxMailBox[0].TIR |= CAN_TI0R_TXRQ;


}


void CAN_SEND_ARRAY(uint8_t *array , int size, int ID)
{
	int size_64 = size/8 ;
	int size_remain = size%8;

	for (int i = 0 ; i < size_64 ; i++)
	{
		CAN1_Transmit(*((uint64_t *)(&array[i*8])),8,ID);
	}
	if (size_remain)
	{
		CAN1_Transmit(*((uint64_t *)(&array[size_64*8])),size_remain,ID);
	}

}


//uint32_t CAN1_Receive(void)
//{
//	uint32_t rxData = 0;
//	uint8_t dlc;
//	uint8_t filterIndex;
//
//	/* Check FIFO message pending */
//	if(0 != (CAN_RF0R_FMP0 & CAN1->RF0R))
//	{
//		//UART_Write_Array(USART2,"RX",3);
//
//		/* FIFO not empty, read data */
//		rxData = (uint32_t)(CAN1->sFIFOMailBox[0].RDLR);
//
//		/* Get filter match index */
//		filterIndex = (uint8_t)(CAN1->sFIFOMailBox[0].RDTR >> 8);
//
//		/* Get data length code */
//		dlc = (uint8_t)(CAN1->sFIFOMailBox[0].RDTR);
//
//		CAN1->RF0R |= CAN_RF0R_RFOM0;
//
//	}
//	return rxData;
//}
//



uint8_t Can_GetSize_Queue(void)
{
	return CAN_Queue_getSize(&can_queue );
}


void Can_Read_Queue(CAN_Queue_ELEMENT_t * data)
{
	if (!CAN_Queue_isEmpty(&can_queue))
	{
		CAN_Queue_Dequeue(&can_queue ,data);
	}
}

void CAN1_RX0_IRQHandler(void)
{
	CAN_Queue_ELEMENT_t can_elemt  = {0};
	uint32_t __rxData_1 = 0;
	uint32_t __rxData_2 = 0;

	uint8_t dlc;
	uint8_t filterIndex;

	/* Check FIFO message pending */
	if(0 != (CAN_RF0R_FMP0 & CAN1->RF0R))
	{

		__rxData_1 = (uint32_t)(CAN1->sFIFOMailBox[0].RDLR);
		__rxData_2 = (uint32_t)(CAN1->sFIFOMailBox[0].RDHR);
		filterIndex = (uint8_t)(CAN1->sFIFOMailBox[0].RDTR >> 8);
		dlc = (uint8_t)(CAN1->sFIFOMailBox[0].RDTR);


		*((uint32_t *)can_elemt.Buffer) = __rxData_1 ;
		if (dlc > 4)
			*(((uint32_t *)can_elemt.Buffer)+1) = __rxData_2 ;
		can_elemt.DLC = dlc ;
		can_elemt.ID = filterIndex  ;
 		CAN_Queue_Enqueue(&can_queue, &can_elemt );

		CAN1->RF0R |= CAN_RF0R_RFOM0;
	}

}


