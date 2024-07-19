#ifndef _PWR_ON_OFF_H
#define _PWR_ON_OFF_H
#include "sys.h"
#include "main.h"


#define PWR_KEY        HAL_GPIO_ReadPin(POWER_ON_OFF_GPIO_Port,POWER_ON_OFF_Pin)  //on/off°´¼ü

void PWR_ON_OFF(void);








#endif


