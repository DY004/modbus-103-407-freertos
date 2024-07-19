#include "matrix_key.h"
#include "main.h"

/* 方法一 */

/*******************************************************************************
*函数的原型：void Matrix_ssKey_Pin_Init(void)
*函数的功能：矩阵键盘引脚初始化函数
*函数的参数：None
*函数返回值：None
*函数的说明： 行线：PB8-PB11 列线：PB12-PB15
*函数编写者：庆
*函数编写日期：2022/3/19
*函数的版本号：V1.0
********************************************************************************/
//void Matrix_ssKey_Pin_Init(void)
//{
//	GPIO_InitTypeDef GPIO_InitStructure;

//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOB,&GPIO_InitStructure);
//	
//	
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ; 
//	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
//	GPIO_Init(GPIOB,&GPIO_InitStructure);
//}	

/*******************************************************************************
*函数的原型：int Matrix_Key_Scan(void)
*函数的功能：按键扫描函数
*函数的参数：None
*函数返回值：
	成功，返回按键值；失败，-1
*函数的说明： 行线：PB8-PB11 列线：PB12-PB15
*函数编写者：庆
*函数编写日期：2022/3/19
*函数的版本号：V1.0
********************************************************************************/
//int Matrix_Key_Scan(void)
//{
//	u8 temp = 0;
//	int key_val = -1;
//	
////	GPIO_ResetBits(GPIOB,GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11);			//拉低行线
//	/***将上述代码改成hal库的形式***/
//	HAL_GPIO_WritePin(RR1_GPIO_Port,RR1_Pin|RR2_Pin|RR3_Pin|RR4_Pin,GPIO_PIN_RESET);//拉低行线
//	
//	
//	delay_us(10);
////	temp=(GPIO_ReadInputData(GPIOB) >> 8)&0xff;	
//	/***将上述代码改成hal库的形式***/
//	temp=(HAL_GPIO_ReadPin(RR1_GPIO_Port,GPIO_PIN_All >>8))&0xf0;	
//	
//	//没有按键按下时扫描
//	if (temp == 0xf0) 
//	{
//			delay_ms(50); 
////			GPIO_ResetBits(GPIOB,GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11);			//拉低行线
//		HAL_GPIO_WritePin(RR1_GPIO_Port,RR1_Pin|RR2_Pin|RR3_Pin|RR4_Pin,GPIO_PIN_RESET);//拉低行线
//		
//			delay_us(10);
////			temp=(GPIO_ReadInputData(GPIOB) >> 8)&0xff;	
//		temp=(HAL_GPIO_ReadPin(RR1_GPIO_Port,GPIO_PIN_All >> 8))&0xf0;
//		
//			if (temp != 0xf0) //按键按下时，对键值进行赋值
//			{
//				//第一行
////				GPIO_Write(GPIOB,0);
//				HAL_GPIO_WritePin(CC1_GPIO_Port,GPIO_PIN_All,GPIO_PIN_RESET);
//				delay_ms(5);
////				GPIO_Write(GPIOB,(uint16_t)(0xFE << 8)); 
//				HAL_GPIO_WritePin(CC1_GPIO_Port,GPIO_PIN_All,GPIO_PIN_RESET);
//				
//				if(((GPIO_ReadInputData(GPIOB) >> 8) & 0XF0) != 0XF0)
//				{
//						delay_ms(20);//消抖

//						if(((GPIO_ReadInputData(GPIOB) >> 8) & 0XF0) != 0XF0)
//						{
//								temp=((GPIO_ReadInputData(GPIOB) >> 8) & 0XFE);		//对列进行扫描
//								switch(temp)
//								{
//										case 0xEE:  key_val = 1;   break;

//										case 0xDE:  key_val = 2;   break;

//										case 0xBE:  key_val = 3;   break;

//										case 0x7E:  key_val = 4;   break;

//										default:    key_val = -1;   break;
//								}
//						}
//				}
//				
//				//第二行
//				GPIO_Write(GPIOB,0);
//				delay_ms(5);
//				GPIO_Write(GPIOB,(uint16_t)(0xFD << 8));
//				
//				if(((GPIO_ReadInputData(GPIOB) >> 8) & 0XF0)!= 0XF0)
//				{
//						delay_ms(20);

//						if(((GPIO_ReadInputData(GPIOB) >> 8) & 0XF0) != 0XF0)
//						{
//								temp=((GPIO_ReadInputData(GPIOB) >> 8) & 0XFD);
//								switch(temp)
//								{
//										case 0xED:  key_val = 5;   break;

//										case 0xDD:  key_val = 6;   break;

//										case 0xBD:  key_val = 7;   break;

//										case 0x7D:  key_val = 8;   break;

//										default:    key_val = -1;   break;
//								}
//						}
//				}
//				
//				//第三行
//				GPIO_Write(GPIOB,0);
//				delay_ms(5);
//				GPIO_Write(GPIOB,(uint16_t)(0xFB << 8));
//				
//				if(((GPIO_ReadInputData(GPIOB) >> 8) & 0XF0) != 0XF0)
//				{
//						delay_ms(20);

//						if(((GPIO_ReadInputData(GPIOB) >> 8) & 0XF0) != 0XF0)
//						{
//								temp=((GPIO_ReadInputData(GPIOB) >> 8) & 0XFB);
//								switch(temp)
//								{
//										case 0xEB:  key_val = 9;   break;

//										case 0xDB:  key_val = 10;   break;

//										case 0xBB:  key_val = 11;   break;

//										case 0x7B:  key_val = 12;   break;

//										default:    key_val = -1;   break;
//								}
//						}
//				}
//				
//				//第四行
//				GPIO_Write(GPIOB,0);
//				delay_ms(5);
//				GPIO_Write(GPIOB,(uint16_t)(0xF7 << 8));
//				
//				if(((GPIO_ReadInputData(GPIOB) >> 8) & 0XF0) !=0XF0)
//				{
//						delay_ms(20);

//						if(((GPIO_ReadInputData(GPIOB) >> 8) & 0XF0) != 0XF0)
//						{
//								temp=((GPIO_ReadInputData(GPIOB) >> 8) & 0XF7);
//								switch(temp)
//								{
//										case 0xE7:  key_val = 13;   break;

//										case 0xD7:  key_val = 14;   break;

//										case 0xB7:  key_val = 15;   break;

//										case 0x77:  key_val = 16;   break;

//										default:    key_val = -1;   break;
//								}
//						}
//					}
//				}
//			}
//	
//	return key_val;

//}



///* 方法二 */

///*******************************************************************************
//*函数的原型：void KEY_Init(void)
//*函数的功能：按键引脚初始化函数
//*函数的参数：None
//*函数返回值：None
//*函数的说明： 行线：PA0-PB3 列线：PA4-PA5
//*函数编写者：庆
//*函数编写日期：2021/3/2
//*函数的版本号：V1.0
//********************************************************************************/
//void KEY_Init(void)
//{
//	
////	GPIO_InitTypeDef GPIO_InitStructure;

//// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能PORTA时钟
////	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;//PA 0 1 2 3
////	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //设置成推挽输出
//// 	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA
////	
////	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;//PA 4 5 6 7
////	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
//// 	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA
//	
//} 

///*******************************************************************************
//*函数的原型：int key_scan(void)
//*函数的功能：按键扫描函数
//*函数的参数：None
//*函数返回值：
//	成功，返回按键值；失败，0
//*函数的说明： 行线：PA0-PB3 列线：PA4-PA5
//*函数编写者：庆
//*函数编写日期：2021/3/2
//*函数的版本号：V1.0
//********************************************************************************/
//int key_scan(void)
//{
//	static u8 key_up=1;
//	int key_num=0;
//	u8 temp=0;								//判断列的数据缓存区
//	u8 temp1=0;								//判断行的数据缓存区
//	GPIO_ResetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);			//拉低行线
//	delay_us(10);
//	temp=GPIO_ReadInputData(GPIOA)&0xff;				//读出A的数据寄存器的值
//	delay_us(1);
//	if (key_up&&(temp != 0xf0))							//判断键是否按下与是否连按
//	{
//		delay_ms(10);						//消抖
//		key_up=0;							//当有键按下时，将连按标志位挂起
//		temp = GPIO_ReadInputData(GPIOA)&0xff;			//消抖后重新得到A的值
//		if(temp != 0xf0)
//		{			
//			switch(temp)								//进入键盘按下的相应行线
//			{
//				case 0xe0:
//				{
//					
//					GPIO_SetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_0);		//依次从第一行拉低到第四行，读出A的数据，从而判断
//					GPIO_ResetBits(GPIOA,GPIO_Pin_0);										//是哪一行的键盘按下，从而给出相应的键值
//					delay_us(10);
//					temp1=GPIO_ReadInputData(GPIOA)&0xff;
//					if (temp1==0xee)
//						key_num=1;
//					else
//					{
//						GPIO_SetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_0);
//						GPIO_ResetBits(GPIOA,GPIO_Pin_1);
//						delay_us(1);
//						temp1=GPIO_ReadInputData(GPIOA)&0xff;
//					
//						if (temp1==0xed)
//							key_num=5;
//						else
//						{
//							GPIO_SetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_0);
//							GPIO_ResetBits(GPIOA,GPIO_Pin_2);
//							delay_us(1);
//							temp1=GPIO_ReadInputData(GPIOA)&0xff;
//						
//							if (temp1==0xeb)
//								key_num=9;
//							else
//								key_num=13;
//						}
//					}
//				}
//				break;
//				case 0xd0:
//				{
//					GPIO_SetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_0);
//					GPIO_ResetBits(GPIOA,GPIO_Pin_0);
//					delay_us(1);
//					temp1=GPIO_ReadInputData(GPIOA)&0xff;
//					if (temp1==0xde)
//						key_num=2;
//					else
//					{
//							GPIO_SetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_0);
//							GPIO_ResetBits(GPIOA,GPIO_Pin_1);
//							delay_us(1);
//							temp1=GPIO_ReadInputData(GPIOA)&0xff;
//						
//							if (temp1==0xdd)
//								key_num=6;
//							else
//							{
//								GPIO_SetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_0);
//								GPIO_ResetBits(GPIOA,GPIO_Pin_2);
//								delay_us(1);
//								temp1=GPIO_ReadInputData(GPIOA)&0xff;
//							
//								if (temp1==0xdb)
//									key_num=10;
//								else
//									key_num=14;
//							}
//					}
//				}
//				break;
//				case 0xb0:
//				{
//					GPIO_SetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_0);
//					GPIO_ResetBits(GPIOA,GPIO_Pin_0);
//					delay_us(1);
//					temp1=GPIO_ReadInputData(GPIOA)&0xff;
//					if (temp1==0xbe)
//						key_num=3;
//					else
//					{
//							GPIO_SetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_0);
//							GPIO_ResetBits(GPIOA,GPIO_Pin_1);
//							delay_us(1);
//							temp1=GPIO_ReadInputData(GPIOA)&0xff;
//						
//							if (temp1==0xbd)
//								key_num=7;
//							else
//							{
//								GPIO_SetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_0);
//								GPIO_ResetBits(GPIOA,GPIO_Pin_2);
//								delay_us(1);
//								temp1=GPIO_ReadInputData(GPIOA)&0xff;
//							
//								if (temp1==0xbb)
//									key_num=11;
//								else
//									key_num=15;
//							}
//					}
//				}
//				break;
//				case 0x70:
//				{
//					GPIO_SetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_0);
//					GPIO_ResetBits(GPIOA,GPIO_Pin_0);
//					delay_us(1);
//					temp1=(GPIO_ReadInputData(GPIOA)&0xff);
//					if (temp1==0x7e)
//						key_num=4;
//					else
//					{
//						GPIO_SetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_0);
//						GPIO_ResetBits(GPIOA,GPIO_Pin_1);
//						delay_us(1);
//						temp1=GPIO_ReadInputData(GPIOA)&0xff;
//					
//						if (temp1==0x7d)
//							key_num=8;
//						else
//						{
//							GPIO_SetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_0);
//							GPIO_ResetBits(GPIOA,GPIO_Pin_2);
//							delay_us(1);
//							temp1=GPIO_ReadInputData(GPIOA)&0xff;
//						
//							if (temp1==0x7b)
//								key_num=12;
//							else
//								key_num=16;
//						}
//					}
//				}
//				break;
//				default :return 0;
//			}		
//		}
//	}
//	else if(temp == 0xf0)
//	{												//当没有键按下后，将连按标志复位
//		key_up=1;
//	}
//	return key_num;	
//}


/***第三中方式，寄存器的方法***/

uint16_t keyboard_scan(void)
{
    uint16_t key_val=0;
    uint16_t temp=0;
	
	
	/*************Scan  1st Line************************/

    GPIOB->ODR=0X0000;

    GPIOB->ODR=0XFE00;//自己的行和列的接法和CSDN中的接法有些不一样，所以这里需要改动。

    if((GPIOB->IDR&0XF000)!=0XF000)//有按键按下。因为默认状态下，行的引脚拉低，列的引脚拉高。为0XF000，当不为这个值的时候，肯定有按键按下了。
    {
        delay_ms(50);

        if((GPIOB->IDR & 0XF000)!=0XF000)
        {
            temp=(GPIOB->IDR&0XFE00);
            switch(temp)
            {
                case 0xEE00:  key_val=1;   break;

                case 0xDE00:  key_val=2;   break;

                case 0xBE00:  key_val=3;   break;

                case 0x7E00:  key_val=4;   break;

                default:    key_val=0;   break;
            }
        }
    }
    
		/*************Scan  2st Line************************/
    GPIOB->ODR=0X0000;

    GPIOB->ODR=0XFD00;

    if((GPIOB->IDR&0XF000)!=0XF000)
    {
        delay_ms(50);
        if((GPIOB->IDR & 0XF000)!=0XF000)
        {
            temp=(GPIOB->IDR&0XFD00);
            switch(temp)
            {
                case 0XED00:  key_val=5;  break;

                case 0XDD00:  key_val=6;  break;

                case 0XBD00:  key_val=7;  break;

                case 0X7D00:  key_val=8;  break;

                default:    key_val=0;  break;
            }
        }
    }

		/*************Scan  3st Line************************/
    GPIOB->ODR=0X0000;

    GPIOB->ODR=0XFB00;

    if((GPIOB->IDR&0XF000)!=0XF000)
    {
        delay_ms(50);

        if((GPIOB->IDR & 0XF000)!=0XF000)
        {
            temp=(GPIOB->IDR&0XFB00);
            switch(temp)
            {
                case 0XEB00:  key_val=9;   break;

                case 0XDB00:  key_val=10;  break;

                case 0XBB00:  key_val=11;  break;

                case 0X7B00:  key_val=12;  break;

                default:    key_val=0;   break;
            }
        }
    }

		/*************Scan  4st Line************************/
    GPIOB->ODR=0X0000;

    GPIOB->ODR=0XF700;

    if((GPIOB->IDR&0XF000)!=0XF000)
    {
        delay_ms(50);

        if((GPIOB->IDR & 0XF000)!=0XF000)
        {
            temp=(GPIOB->IDR&0XF700);
            switch(temp)
            {
                case 0XE700:  key_val=13;  break;

                case 0XD700:  key_val=14;  break;

                case 0XB700:  key_val=15;  break;

                case 0X7700:  key_val=16;  break;

                default:    key_val=0;   break;
            }
        }
    }

    return key_val;

}

 




