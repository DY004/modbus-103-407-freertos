#ifndef __MENU_H
#define __MENU_H

#include "main.h"
#define  u8 unsigned char

//按键定义
#define KEY0 HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_3)		//向下一个,低电平有效  	KEY0
#define KEY_UP HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0)		//向下一个,高电平有效  	KEY——
#define KEY1 HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_2)		//确定,低电平有效
#define KEY2 HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13)		//退出,高电平有效


typedef struct
{
    u8 current;	//当前状态索引号
    u8 next; 		//向下一个
	u8 up; 		//向上一个
    u8 enter; 	//确定
    u8 back; 		//退出
    void (*current_operation)(void); //当前状态应该执行的操作
} Menu_table;

//界面UI
void home(void);
void Temperature(void);
void Palygame(void);
void Setting(void);
void Info(void);
void home1(void);


void  Menu_key_set(void);
u8 KEY_Scan(u8 mode);

void TestTemperature(void);
void ConrtolGame(void);
void Set(void);
void Information(void);
void Information1(void);

void LED(void);
void RTC_display(void);

#endif
