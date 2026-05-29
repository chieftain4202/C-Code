#include "device_driver.h"

int d = 0;
int d_cnt = 0;
int oe = 0;
int oe_cnt = 4;

void LED_Init(void)
{
	/* 아래 코드 수정 금지 : Port-A Clock Enable */
	Macro_Set_Bit(RCC->AHB1ENR, 0); 

	// LED를 출력으로 설정하고 초기 OFF
	Macro_Write_Block(GPIOA->MODER, 0x3, 0x1, 10);
	Macro_Write_Block(GPIOA->MODER, 0x3, 0x1, 14);
	Macro_Clear_Bit(GPIOA->OTYPER, 5);
	Macro_Clear_Bit(GPIOA->OTYPER, 7);
	Macro_Clear_Bit(GPIOA->ODR, 5); 
	Macro_Clear_Bit(GPIOA->ODR, 7); 
}

void LED_On(void)
{
	// LED On
	Macro_Set_Bit(GPIOA->ODR, 5); 
}

void LED_Off(void)
{
	// LED Off
	Macro_Clear_Bit(GPIOA->ODR, 5); 
}

extern volatile int TIM4_Expired;

void LED_Blink(void)
{
	d_cnt++;
	if(d_cnt == 10) {
		d ^= 1;
		d_cnt = 0; 
	}
		if (d) {
			Macro_Set_Bit(GPIOA->ODR, 5); 
		}
		else {
			Macro_Clear_Bit(GPIOA->ODR, 5);
		}
}

void OLED_Blink(void)
{
	oe_cnt++;
	if(oe_cnt == 5){
		oe ^= 1; 
		oe_cnt = 0;
	
		if (oe) {
			Macro_Set_Bit(GPIOA->ODR, 7);
		}
		else {
			Macro_Clear_Bit(GPIOA->ODR, 7);
		}
	}
	
	
}
