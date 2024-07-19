#ifndef _MATRIX_KEY_H_
#define _MATRIX_KEY_H_

//#include "stm32f10x.h"
#include "delay.h"
#include "stdio.h"

void Matrix_ssKey_Pin_Init(void);
int Matrix_Key_Scan(void);
uint16_t keyboard_scan(void);

void KEY_Init(void);
int key_scan(void);
#endif

