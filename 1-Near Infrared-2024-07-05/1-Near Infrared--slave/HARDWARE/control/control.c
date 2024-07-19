#include "control.h"
#include "oled.h"
#include "dinogame.h"
#include "stdlib.h"
//#include "tim.h"

unsigned char key_num = 0;
unsigned char cactus_category = 0;
unsigned char cactus_length = 8;
unsigned int score = 0;
unsigned int highest_score = 0;
int height = 0;
int cactus_pos = 128;
unsigned char cur_speed = 30;
char failed = 0;
char reset = 0;


int get_key()
{
	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2)==0)
	{
		HAL_Delay(10);            //延迟
		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2)==0)
		{
		return 2;
		}
	}
	
	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3)==0)
	{
		HAL_Delay(10);            //延迟
		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3)==0)
		{
		return 1;
		}
	}

	if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13)==0)
	{
		HAL_Delay(10);            //延迟
		if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13)==0)
		{
		return 3;
		}
	}
	
	return 0;
}

void Game_control()
{
	
	while(1)
	{
	
		if(get_key() == 3)		//wk_up按键按下强制退出一次循环
		{
			break;
		}
		
			if (failed == 1)
		{
			OLED_DrawRestart();

			key_num = get_key();
			if (key_num == 2)
			{
				if(score > highest_score) highest_score = score;
				score = 0;
				failed = 0;
				height = 0;
				reset = 1;
				OLED_DrawDinoJump(reset);
				OLED_DrawCactusRandom(cactus_category, reset);
				OLED_Clear();
			}
			continue;
		}


		score ++;
		if (height <= 0) key_num = get_key();

		OLED_DrawGround();
		OLED_DrawCloud();

		if (height>0 || key_num == 1) height = OLED_DrawDinoJump(reset);
		else OLED_DrawDino();

		cactus_pos = OLED_DrawCactusRandom(cactus_category, reset);
		if(cactus_category == 0) cactus_length = 8;
		else if(cactus_category == 1) cactus_length = 16;
		else cactus_length = 24;

		if (cactus_pos + cactus_length < 0)
		{
		  cactus_category = rand()%4;
			OLED_DrawCactusRandom(cactus_category, 1);
		}

		if ((height < 16) && ( (cactus_pos>=16 && cactus_pos <=32) || (cactus_pos + cactus_length>=16 && cactus_pos + cactus_length <=32)))
		{
			failed = 1;
		}

		
		OLED_ShowString(35, 0, "HI:", 12);
		OLED_ShowNum(58, 0, highest_score, 5, 12);
		OLED_ShowNum(98, 0, score, 5, 12);


		reset = 0;

		cur_speed = score/20;
		if (cur_speed > 29) cur_speed = 29;
		HAL_Delay(30 - cur_speed);
//		HAL_Delay(500);
		key_num = 0;
	
	}
	
}

