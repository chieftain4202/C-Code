#include "device_driver.h"
#include <stdio.h>
#define TIM4_TICK	  		(20) 				// usec
#define TIM4_FREQ 	  		(1000000/TIM4_TICK) // Hz
#define TIME4_PLS_OF_1ms  	(1000/TIM4_TICK)

static void Sys_Init(int baud) 
{
	SCB->CPACR |= (0x3 << 10*2)|(0x3 << 11*2); 
	Clock_Init();
	Uart2_Init(baud);
	setvbuf(stdout, NULL, _IONBF, 0);
	LED_Init();
}

int time;

void Main(void)
{
	Sys_Init(115200);
	printf("\nTest 1\n");

	Macro_Write_Block(GPIOA->MODER, 0x3, 0x1, 10);
	Macro_Clear_Bit(GPIOA->OTYPER, 5);
	Macro_Clear_Bit(GPIOA->ODR, 5); 

	int key_cnt = 0;
	char data;
	for(;;)
	{

		Macro_Set_Bit(RCC->APB1ENR, 2);
		TIM4->CR1 = (1<<4)|(0<<3);
		TIM4->PSC = (unsigned int)(TIMXCLK/(double)TIM4_FREQ + 0.5)-1;
		TIM4->ARR = TIME4_PLS_OF_1ms * time;
		Macro_Set_Bit(TIM4->EGR,0);

		if(TIM4->ARR) printf(".");

		if(data == '\n')
  {
    while(!Macro_Check_Bit_Set(USART2->SR, 7));
    USART2->DR = 0x0d;
  }

  	while(!Macro_Check_Bit_Set(USART2->SR, 7));
  	USART2->DR = data;
	}
}
