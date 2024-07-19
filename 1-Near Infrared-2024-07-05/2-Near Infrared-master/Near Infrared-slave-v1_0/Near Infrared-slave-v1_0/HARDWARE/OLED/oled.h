#ifndef __OLED_H
#define __OLED_H

#include "main.h"
#include "sys.h"
#include "gpio.h"

//#define u8 uint8_t
//#define u32 uint32_t

#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����

#define OLED0561_ADD	0x78  // OLED I2C��ַ
#define COM				0x00  // OLED 
#define DAT 			0x40  // OLED 

#define OLED_MODE 0
#define SIZE 8
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF
#define X_WIDTH 	128
#define Y_WIDTH 	64


//-----------------OLED IIC GPIO����ģ��----------------

#define OLED_SCLK_Clr() HAL_GPIO_WritePin(OLED_SCL_GPIO_Port,OLED_SCL_Pin, GPIO_PIN_RESET) //GPIO_ResetBits(GPIOB,GPIO_Pin_10)//SCL
#define OLED_SCLK_Set() HAL_GPIO_WritePin(OLED_SCL_GPIO_Port, OLED_SCL_Pin, GPIO_PIN_SET) //GPIO_SetBits(GPIOB,GPIO_Pin_10)

#define OLED_SDIN_Clr() HAL_GPIO_WritePin(OLED_SDA_GPIO_Port, OLED_SDA_Pin, GPIO_PIN_RESET) // GPIO_ResetBits(GPIOB,GPIO_Pin_11)//SDA
#define OLED_SDIN_Set() HAL_GPIO_WritePin(OLED_SDA_GPIO_Port, OLED_SDA_Pin, GPIO_PIN_SET) // GPIO_SetBits(GPIOB,GPIO_Pin_11)


//I2C GPIOģ��
void IIC_Start(void);
void IIC_Stop(void);
void IIC_WaitAck(void);
void IIC_WriteByte(unsigned char IIC_Byte);
void IIC_WriteCommand(unsigned char IIC_Command);
void IIC_WriteData(unsigned char IIC_Data);
void OLED_WR_Byte(unsigned dat,unsigned cmd);

//���ܺ���
void OLED_Init(void);
void OLED_WR_Byte(unsigned dat,unsigned cmd);

void OLED_FillPicture(unsigned char fill_Data);
void OLED_SetPos(unsigned char x, unsigned char y);
void OLED_DisplayOn(void);
void OLED_DisplayOff(void);
void OLED_Clear(void);
void OLED_On(void);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size);
u32 oled_pow(u8 m,u8 n);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size2);
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 Char_Size);

void OLED_DrawBMP2(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);

#endif

