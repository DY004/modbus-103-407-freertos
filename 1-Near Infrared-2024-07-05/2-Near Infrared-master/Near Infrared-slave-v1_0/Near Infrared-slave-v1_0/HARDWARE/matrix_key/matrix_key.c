#include "matrix_key.h"
#include "main.h"

/* ����һ */

/*******************************************************************************
*������ԭ�ͣ�void Matrix_ssKey_Pin_Init(void)
*�����Ĺ��ܣ�����������ų�ʼ������
*�����Ĳ�����None
*��������ֵ��None
*������˵���� ���ߣ�PB8-PB11 ���ߣ�PB12-PB15
*������д�ߣ���
*������д���ڣ�2022/3/19
*�����İ汾�ţ�V1.0
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
*������ԭ�ͣ�int Matrix_Key_Scan(void)
*�����Ĺ��ܣ�����ɨ�躯��
*�����Ĳ�����None
*��������ֵ��
	�ɹ������ذ���ֵ��ʧ�ܣ�-1
*������˵���� ���ߣ�PB8-PB11 ���ߣ�PB12-PB15
*������д�ߣ���
*������д���ڣ�2022/3/19
*�����İ汾�ţ�V1.0
********************************************************************************/
//int Matrix_Key_Scan(void)
//{
//	u8 temp = 0;
//	int key_val = -1;
//	
////	GPIO_ResetBits(GPIOB,GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11);			//��������
//	/***����������ĳ�hal�����ʽ***/
//	HAL_GPIO_WritePin(RR1_GPIO_Port,RR1_Pin|RR2_Pin|RR3_Pin|RR4_Pin,GPIO_PIN_RESET);//��������
//	
//	
//	delay_us(10);
////	temp=(GPIO_ReadInputData(GPIOB) >> 8)&0xff;	
//	/***����������ĳ�hal�����ʽ***/
//	temp=(HAL_GPIO_ReadPin(RR1_GPIO_Port,GPIO_PIN_All >>8))&0xf0;	
//	
//	//û�а�������ʱɨ��
//	if (temp == 0xf0) 
//	{
//			delay_ms(50); 
////			GPIO_ResetBits(GPIOB,GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11);			//��������
//		HAL_GPIO_WritePin(RR1_GPIO_Port,RR1_Pin|RR2_Pin|RR3_Pin|RR4_Pin,GPIO_PIN_RESET);//��������
//		
//			delay_us(10);
////			temp=(GPIO_ReadInputData(GPIOB) >> 8)&0xff;	
//		temp=(HAL_GPIO_ReadPin(RR1_GPIO_Port,GPIO_PIN_All >> 8))&0xf0;
//		
//			if (temp != 0xf0) //��������ʱ���Լ�ֵ���и�ֵ
//			{
//				//��һ��
////				GPIO_Write(GPIOB,0);
//				HAL_GPIO_WritePin(CC1_GPIO_Port,GPIO_PIN_All,GPIO_PIN_RESET);
//				delay_ms(5);
////				GPIO_Write(GPIOB,(uint16_t)(0xFE << 8)); 
//				HAL_GPIO_WritePin(CC1_GPIO_Port,GPIO_PIN_All,GPIO_PIN_RESET);
//				
//				if(((GPIO_ReadInputData(GPIOB) >> 8) & 0XF0) != 0XF0)
//				{
//						delay_ms(20);//����

//						if(((GPIO_ReadInputData(GPIOB) >> 8) & 0XF0) != 0XF0)
//						{
//								temp=((GPIO_ReadInputData(GPIOB) >> 8) & 0XFE);		//���н���ɨ��
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
//				//�ڶ���
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
//				//������
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
//				//������
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



///* ������ */

///*******************************************************************************
//*������ԭ�ͣ�void KEY_Init(void)
//*�����Ĺ��ܣ��������ų�ʼ������
//*�����Ĳ�����None
//*��������ֵ��None
//*������˵���� ���ߣ�PA0-PB3 ���ߣ�PA4-PA5
//*������д�ߣ���
//*������д���ڣ�2021/3/2
//*�����İ汾�ţ�V1.0
//********************************************************************************/
//void KEY_Init(void)
//{
//	
////	GPIO_InitTypeDef GPIO_InitStructure;

//// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//ʹ��PORTAʱ��
////	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;//PA 0 1 2 3
////	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //���ó��������
//// 	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA
////	
////	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;//PA 4 5 6 7
////	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
//// 	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA
//	
//} 

///*******************************************************************************
//*������ԭ�ͣ�int key_scan(void)
//*�����Ĺ��ܣ�����ɨ�躯��
//*�����Ĳ�����None
//*��������ֵ��
//	�ɹ������ذ���ֵ��ʧ�ܣ�0
//*������˵���� ���ߣ�PA0-PB3 ���ߣ�PA4-PA5
//*������д�ߣ���
//*������д���ڣ�2021/3/2
//*�����İ汾�ţ�V1.0
//********************************************************************************/
//int key_scan(void)
//{
//	static u8 key_up=1;
//	int key_num=0;
//	u8 temp=0;								//�ж��е����ݻ�����
//	u8 temp1=0;								//�ж��е����ݻ�����
//	GPIO_ResetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);			//��������
//	delay_us(10);
//	temp=GPIO_ReadInputData(GPIOA)&0xff;				//����A�����ݼĴ�����ֵ
//	delay_us(1);
//	if (key_up&&(temp != 0xf0))							//�жϼ��Ƿ������Ƿ�����
//	{
//		delay_ms(10);						//����
//		key_up=0;							//���м�����ʱ����������־λ����
//		temp = GPIO_ReadInputData(GPIOA)&0xff;			//���������µõ�A��ֵ
//		if(temp != 0xf0)
//		{			
//			switch(temp)								//������̰��µ���Ӧ����
//			{
//				case 0xe0:
//				{
//					
//					GPIO_SetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_0);		//���δӵ�һ�����͵������У�����A�����ݣ��Ӷ��ж�
//					GPIO_ResetBits(GPIOA,GPIO_Pin_0);										//����һ�еļ��̰��£��Ӷ�������Ӧ�ļ�ֵ
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
//	{												//��û�м����º󣬽�������־��λ
//		key_up=1;
//	}
//	return key_num;	
//}


/***�����з�ʽ���Ĵ����ķ���***/

uint16_t keyboard_scan(void)
{
    uint16_t key_val=0;
    uint16_t temp=0;
	
	
	/*************Scan  1st Line************************/

    GPIOB->ODR=0X0000;

    GPIOB->ODR=0XFE00;//�Լ����к��еĽӷ���CSDN�еĽӷ���Щ��һ��������������Ҫ�Ķ���

    if((GPIOB->IDR&0XF000)!=0XF000)//�а������¡���ΪĬ��״̬�£��е��������ͣ��е��������ߡ�Ϊ0XF000������Ϊ���ֵ��ʱ�򣬿϶��а��������ˡ�
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

 




