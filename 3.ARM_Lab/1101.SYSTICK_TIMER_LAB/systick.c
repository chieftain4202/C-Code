#include "device_driver.h"

void SysTick_Run(unsigned int msec)
{
	// Timer 설정 : 인터럽트 발생 안함, clock source는 HCLK/8, Timer 정지
	SysTick->CTRL = 0;
	// 주어진 msec 값 만큼의 msec를 count하는 초기값 설정 (LOAD)
	SysTick->LOAD = (HCLK / 8 / 1000) * msec - 1;
	// VAL 레지스터 값 초기화(0) 및 COUNTFLAG Clear
	SysTick->VAL = 0;
	// Timer Start (시작이 되면 자동으로 LOAD의 값을 VAL로 가져간다)
	SysTick->CTRL = (0 << 2) | (0 << 1) | (1 << 0);
}

int SysTick_Check_Timeout(void)
{
	// Timer의 Timeout이 발생하면 참(1)리턴, 아니면 거짓(0) 리턴
	return (SysTick->CTRL & (1<<16)) ? 1 : 0;
}

unsigned int SysTick_Get_Time(void)
{
	// Timer의 현재 count 값 리턴
	return SysTick->VAL;
}

unsigned int SysTick_Get_Load_Time(void)
{
	// Timer에 설정된 초기값을 리턴
	return SysTick->LOAD;
}

void SysTick_Stop(void)
{
	// Timer Stop
	SysTick->CTRL = 0;
}
