/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "menu.h"
#include "delay.h"
#include "matrix_key.h"
#include "modbus.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId LED_TaskHandle;
osThreadId menu_TaskHandle;
osThreadId modbus_TaskHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void Start_LED_Task(void const * argument);
void Start_menu_Task(void const * argument);
void Start_modbus_Task(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of LED_Task */
  osThreadDef(LED_Task, Start_LED_Task, osPriorityBelowNormal, 0, 128);
  LED_TaskHandle = osThreadCreate(osThread(LED_Task), NULL);

  /* definition and creation of menu_Task */
  osThreadDef(menu_Task, Start_menu_Task, osPriorityBelowNormal, 0, 128);
  menu_TaskHandle = osThreadCreate(osThread(menu_Task), NULL);

  /* definition and creation of modbus_Task */
  osThreadDef(modbus_Task, Start_modbus_Task, osPriorityBelowNormal, 0, 128);
  modbus_TaskHandle = osThreadCreate(osThread(modbus_Task), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_Start_LED_Task */
/**
  * @brief  Function implementing the LED_Task thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_Start_LED_Task */
void Start_LED_Task(void const * argument)
{
  /* USER CODE BEGIN Start_LED_Task */
  /* Infinite loop */
  for(;;)
  {
	  HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port,LED_GREEN_Pin);
//	  printf("modbus.timrun��ֵ�ǣ�%d",modbus.timrun);
//	  printf("�˿�modbus.Host_Sendtime��ֵ�ǣ�%d\r\n",modbus.Host_Sendtime);
//	  printf("modbus.recount��ֵ��%d",modbus.recount);
//	  printf("����һ��������ʵ��\r\n");
	  osDelay(500);
  }
  /* USER CODE END Start_LED_Task */
}

/* USER CODE BEGIN Header_Start_menu_Task */
/**
* @brief Function implementing the menu_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Start_menu_Task */
void Start_menu_Task(void const * argument)
{
  /* USER CODE BEGIN Start_menu_Task */
  /* Infinite loop */
  uint16_t key_value;
  for(;;)
  {
//	  key_value = keyboard_scan();
//	  printf("�㰴�µİ����ǣ�%d\r\n",key_value);
//	  if(key_value == 1)
//	  {
//		  HAL_GPIO_WritePin(LED_GREEN_GPIO_Port,LED_GREEN_Pin,GPIO_PIN_RESET);
////		  osDelay(500);
//	  
//	  }
//	  else if(key_value == 2)
//	  {
//		  HAL_GPIO_WritePin(LED_GREEN_GPIO_Port,LED_GREEN_Pin,GPIO_PIN_SET);
//	  
//	  }
	  Menu_key_set();
  }
  /* USER CODE END Start_menu_Task */
}

/* USER CODE BEGIN Header_Start_modbus_Task */
/**
* @brief Function implementing the modbus_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Start_modbus_Task */
void Start_modbus_Task(void const * argument)
{
  /* USER CODE BEGIN Start_modbus_Task */
  /* Infinite loop */
  for(;;)
  {
	  if(modbus.Host_time_flag)//ÿ1s����һ������
        {
//			printf("Host_time_flag����ֵ��: %d\r\n",modbus.Host_time_flag);
//            //01-��ȡ�ӻ����ݲ���
//            //����1���鿴��i���ӻ�����
            Host_Read03_slave(0x01,0x0000,0x0003);//����1�ӻ���ַ������2��ʼ��ַ������3�Ĵ�������
            if(modbus.Host_send_flag)
            {
                modbus.Host_Sendtime=0;//������Ϻ�������㣨�����ϴε�ʱ�䣩
                modbus.Host_time_flag=0;//�������ݱ�־λ����
                modbus.Host_send_flag=0;//��շ��ͽ������ݱ�־λ
                HOST_ModbusRX();//�������ݽ��д���
            }
					//02-д�����ݲ���
//					Host_write06_slave(0x01,0x06,0x0002,0x0045);
//					if(modbus.Host_send_flag)
//					{
//						modbus.Host_Sendtime=0;//������Ϻ�������㣨�����ϴε�ʱ�䣩
//						modbus.Host_time_flag=0;//�������ݱ�־λ����
//						modbus.Host_send_flag=0;//��շ��ͽ������ݱ�־λ
//						Host_Func6();//�ӻ��������ݴ���
//					}
			//03-д�������ݲ���-��Ϊ����ʹ��
//			Host_write10_slave(0x01,0x10,0x0001,0x0002,0x04,0x0102,0x0305);
////			Host_write06_slave(0x01,0x06,0x0001,0x0045);
//			if(modbus.Host_send_flag)
//			{
//				modbus.Host_Sendtime=0;//������Ϻ�������㣨�����ϴε�ʱ�䣩
//				modbus.Host_time_flag=0;//�������ݱ�־λ����
//				modbus.Host_send_flag=0;//��շ��ͽ������ݱ�־λ
//				Host_Func10();//�ӻ��������ݴ���
//			}
			//4-��Ϊ�ӻ�ʹ��
//			Modbus_Event();//������Ϊ�ӻ�ʹ��ʱ
		

			
        }
//		osDelay(1000);
    
  }
  /* USER CODE END Start_modbus_Task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

