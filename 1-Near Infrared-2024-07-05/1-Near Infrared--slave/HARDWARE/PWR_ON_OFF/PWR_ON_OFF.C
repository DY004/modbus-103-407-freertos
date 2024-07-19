#include "PWR_ON_OFF.h"
#include "gpio.h"
#include "key.h"
#include "delay.h"

void PWR_ON_OFF(void)
{
	if(PWR_KEY == GPIO_PIN_RESET)//检测关机按键的按下
	{
		HAL_Delay(50);
		while(!PWR_KEY);//等待按键松开
		HAL_GPIO_WritePin(POWER_CTR_GPIO_Port,POWER_CTR_Pin, GPIO_PIN_RESET);//把开机的IO
	
	}


}


