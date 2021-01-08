/*
 * main.c
 *
 *  Created on: Dec 21, 2020
 *      Author: Osama Elmorady
 */
#include "LIB/BIT_MATH.h"

#include "FreeRTOS.h"
#include "task.h"
#include "avr/io.h"




TaskHandle_t task1_handler ;
TaskHandle_t task2_handler ;
TaskHandle_t task3_handler ;

void vTask1 (void * pvParameters)
{
	for(;;)
	{
		TOGGLE_BIT(PORTC,0) ;
		vTaskDelay(500) ;
	}
	/*  */
	return;
}

void vTask2 (void * pvParameters)
{
	for(;;)
	{
		TOGGLE_BIT(PORTC,1) ;
		vTaskDelay(1000) ;
	}
	/*  */
	return;
}


void vTask3 (void * pvParameters)
{
	for(;;)
	{
		TOGGLE_BIT(PORTC,2) ;
		vTaskDelay(2000) ;
	}
	/*  */
	return;
}







int main(void)
{
	SET_BIT(DDRC,0)   ;
	SET_BIT(DDRC,1)   ;
	SET_BIT(DDRC,2)   ;

	xTaskCreate(vTask1 , "Toggle1" , configMINIMAL_STACK_SIZE , NULL , 3  , &task1_handler  ) ;
	xTaskCreate(vTask2 , "Toggle2" , configMINIMAL_STACK_SIZE , NULL , 2  , &task2_handler  ) ;
	xTaskCreate(vTask3 , "Toggle3" , configMINIMAL_STACK_SIZE , NULL , 1  , &task3_handler  ) ;

	vTaskStartScheduler() ;

while(1)
{





}

return 0;
}

