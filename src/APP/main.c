
#include "stdio.h"


#include "UART.h"
#include "CAN.h"
#include "../Services_layers/GeneralTimer.h"
#include "../Services_layers/delay.h"
#include "../Services_layers/Queue.h"




GTimer_type uart_timer ;
Queue_t uart_queue ;

void UART_INT_CALLBACK (uint8_t data)
{

	Queue_Enqueue(&uart_queue , data) ;
	uart_timer.Start(&uart_timer);
	uart_timer.Reset(&uart_timer);

}




int main (void)
{
	GeneralTimer_Init();

	DELAY_INIT();


	UART_INIT_2(UART_INT_CALLBACK);


	GeneralTimer_Create(&uart_timer);

	CAN_Queue_ELEMENT_t CAN_DATA ;

	while ( Queue_getSize(&uart_queue) < 4) ;
	uint16_t ID1 = Queue_Dequeue(&uart_queue)<<8 ;
	ID1 |= Queue_Dequeue(&uart_queue);

	uint16_t ID2 = (Queue_Dequeue(&uart_queue)<<8) ;
	ID2 |= Queue_Dequeue(&uart_queue);
	CAN1_Init(ID1 ,ID2 ) ;

	uint16_t TEMP_ID ;
	uint8_t buff[100];
	int counter = 0 ;
	for(;;)
	{

		if (Can_GetSize_Queue())
		{
			Can_Read_Queue(&CAN_DATA);
			if (CAN_DATA.ID == 2) //identifier register number 2 has the id number 1
			{
				UART_Write_Array(USART2,(uint8_t *)&ID1,2 );

			}
			else if (CAN_DATA.ID == 6)  // identifier register number 6 has the id number 2
			{
				UART_Write_Array(USART2,(uint8_t *)&ID2,2 );

			}
			UART_Write_Array(USART2,CAN_DATA.Buffer,CAN_DATA.DLC );

		}




		if (Queue_getSize(&uart_queue) && uart_timer.CheckTimeout(&uart_timer,10))
		{
			TEMP_ID   = ( Queue_Dequeue(&uart_queue)<<8) ;
			TEMP_ID |=  Queue_Dequeue(&uart_queue);
			while(Queue_getSize(&uart_queue))
			{
				buff[counter] =  Queue_Dequeue(&uart_queue);
				counter++;
			}
			CAN_SEND_ARRAY(buff,counter,TEMP_ID);
			counter = 0 ;

			uart_timer.Stop(&uart_timer);
			uart_timer.Reset(&uart_timer);
		}


	}
}
