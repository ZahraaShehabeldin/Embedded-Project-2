/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ssd1306.h"
#include "fonts.h"
#include "mylibrary.h"
#include <stdlib.h>
#include "FreeRTOS.h"
#include "queue.h"
#include "cmsis_os.h"
#include "semphr.h"
#include "DC_MOTOR.h"
#include "DC_MOTOR_cfg.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define DC_MOTOR1    0

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart1;

/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for myTask02 */
osThreadId_t myTask02Handle;
const osThreadAttr_t myTask02_attributes = {
  .name = "myTask02",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for myTask03 */
osThreadId_t myTask03Handle;
const osThreadAttr_t myTask03_attributes = {
  .name = "myTask03",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for myTask04 */
osThreadId_t myTask04Handle;
const osThreadAttr_t myTask04_attributes = {
  .name = "myTask04",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for myTask05 */
osThreadId_t myTask05Handle;
const osThreadAttr_t myTask05_attributes = {
  .name = "myTask05",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for myQueue01 */
osMessageQueueId_t myQueue01Handle;
const osMessageQueueAttr_t myQueue01_attributes = {
  .name = "myQueue01"
};
/* Definitions for myQueue02 */
osMessageQueueId_t myQueue02Handle;
const osMessageQueueAttr_t myQueue02_attributes = {
  .name = "myQueue02"
};
/* Definitions for myMutex01 */
osMutexId_t myMutex01Handle;
const osMutexAttr_t myMutex01_attributes = {
  .name = "myMutex01"
};
/* Definitions for myMutex02 */
osMutexId_t myMutex02Handle;
const osMutexAttr_t myMutex02_attributes = {
  .name = "myMutex02"
};
/* Definitions for myBinarySem01 */
osSemaphoreId_t myBinarySem01Handle;
const osSemaphoreAttr_t myBinarySem01_attributes = {
  .name = "myBinarySem01"
};
/* Definitions for myBinarySem02 */
osSemaphoreId_t myBinarySem02Handle;
const osSemaphoreAttr_t myBinarySem02_attributes = {
  .name = "myBinarySem02"
};
/* USER CODE BEGIN PV */
SemaphoreHandle_t xSemaphore;

typedef struct {
	GPIO_TypeDef* port;
	uint16_t pin;
	char status;
	char* name; /* like "slot 1" */
	}slot;
	
	uint8_t nl[2] ="\r\n";

	int slots_num = 4; /*number of slots*/
	
	uint8_t check;
	slot slots[4];
	
	char* BCompare;
	int var=9;
	char* str = "\r\n";
	int flag =0;
	uint8_t MOTOR1_DIR;
  uint8_t DIR_FLAG;
	uint16_t speed;
	uint32_t delay;
	int entry_car;
	int bar_speed = 1000;
	int bar_time=60;


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_TIM2_Init(void);
void StartDefaultTask(void *argument);
void StartTask02(void *argument);
void StartTask03(void *argument);
void StartTask04(void *argument);
void StartTask05(void *argument);

/* USER CODE BEGIN PFP */
void readSensors(slot slots[slots_num]);
void DisplaySlot(int slotNum, int x1, int y1,int x2,int y2, slot slots[slots_num]);
void SendReceive_BT();

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */


void DC_Motor_Cntrl()
{
	int space_available=0;
	for (int i=0;i<slots_num;i++)
	{
		if (slots[i].status=='E')
			space_available =1;
	}
	
	if(entry_car==0)
	{ 
	if(HAL_GPIO_ReadPin(GPIOA , GPIO_PIN_8)== GPIO_PIN_RESET)
	{
		if(space_available==1){
		entry_car=1;
		//DC_MOTOR_Set_Speed(DC_MOTOR1, speed);
		
		if(DIR_FLAG == 0)
		{
			speed = bar_speed;

			MOTOR1_DIR = DIR_CW;
			DIR_FLAG = 1;
			delay = bar_time;
		}
	}

//		else if(DIR_FLAG == 1)
//		{
			//	speed = 0;

//			DIR_FLAG = 2;
//			delay = 5000;
//			////MOTOR1_DIR = DIR_CCW;
//		}
//		else if(DIR_FLAG == 2)
//		{
			//	speed = 1000;

//			
//			MOTOR1_DIR = DIR_CCW;
//			DIR_FLAG = 3;
//			delay = 300;
//		}
//		else 
//		{
		//	speed = 0;
//			
//			DIR_FLAG = 0;
//			delay = 5000;
//		}
		
//		DC_MOTOR_Set_Dir(DC_MOTOR1, MOTOR1_DIR);		
		
////		DC_MOTOR_Set_Speed(DC_MOTOR1, 1000);
////		DC_MOTOR_Set_Dir(DC_MOTOR1, DIR_CW);
////		HAL_Delay(1000);
////		
////		DC_MOTOR_Set_Speed(DC_MOTOR1, 0);
////		HAL_Delay(2000);
////		
////		DC_MOTOR_Set_Speed(DC_MOTOR1, 1000);
////		DC_MOTOR_Set_Dir(DC_MOTOR1, DIR_CCW);
////		HAL_Delay(1000);

////		
////		DC_MOTOR_Set_Speed(DC_MOTOR1, 0);
		
	}
	
}
	else if(entry_car==1)
	{
 if(DIR_FLAG == 1)
		{
			speed = 0;
			DIR_FLAG = 2;
			delay = 5000;
			////MOTOR1_DIR = DIR_CCW;
		}
		else if(DIR_FLAG == 2)
		{
			speed = bar_speed;
			MOTOR1_DIR = DIR_CCW;
			DIR_FLAG = 3;
			delay = bar_time;
		}
		else 
		{
    	speed = 0;
			DIR_FLAG = 0;
			delay = 5000;
			entry_car=0;
		}
	}
		else
	{
		DC_MOTOR_Set_Speed(DC_MOTOR1, 0);
	}
	
	DC_MOTOR_Set_Speed(DC_MOTOR1, speed);
	DC_MOTOR_Set_Dir(DC_MOTOR1, MOTOR1_DIR);		


//		readSensors(slots);

		//HAL_Delay(5000);

}
int i=0;
int count=0;
char BluetoothMsg[50];

void readSensors(slot slots[slots_num])
{
//taskENTER_CRITICAL();
for (int i=0;i<slots_num;i++)
	{
	if(HAL_GPIO_ReadPin(slots[i].port , slots[i].pin)== GPIO_PIN_RESET) /*obstacle is detected*/
		slots[i].status='F';
	else
		if(slots[i].status !='B')
				slots[i].status='E';
//		
//	HAL_UART_Transmit(&huart2,slots[i].name,10,5000);
//	HAL_UART_Transmit(&huart2,&slots[i].status,1,5000);
//	HAL_UART_Transmit(&huart2,nl,2,5000);
	
	}
//taskEXIT_CRITICAL();

}

void DisplaySlot(int slotNum, int x1, int y1,int x2,int y2, slot slots[slots_num])
{

			SSD1306_UpdateScreen();										//print the changes on the display	
			SSD1306_GotoXY (x1,y1); 										//Goto 0,0
			SSD1306_Puts(slots[slotNum].name, &Font_11x18, 1);		//puts WORLD on the display
			SSD1306_GotoXY (x2,y2); 										//Goto 10,10
			SSD1306_Puts(&slots[slotNum].status, &Font_11x18, 1);		//puts WORLD on the display
			SSD1306_UpdateScreen();										//print the changes on the display

}

void DisplayOLED(slot slots[slots_num])
{
	//taskENTER_CRITICAL();

		for(int i=0;i<slots_num;i++)
	{
		DisplaySlot(i, i*30, 0, i*30, 30, slots);
	}
//	taskEXIT_CRITICAL();


}
void Booking_BT()
{
	//buffer_index =0;

	if(HAL_UART_Receive(&huart1, (uint8_t*)&buffer[buffer_index++], 1, 10)==HAL_OK) //entrrupt the handler to recieve char by char 
	{
				flag=0;

	if(buffer[buffer_index-1] == '\n') //revieving eof
	
	{
//		strncpy(BluetoothMsg, buffer, strlen(buffer));
//		HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 500);
//		
//		i = string_compare(buffer,"S1\r\n", strlen(buffer));
//		if ( i == 1)
//		{
//				HAL_UART_Transmit(&huart1, (uint8_t*)"SLOT RESERVED.\n", strlen("SLOT RESERVED.\n"), 500); 
//		} 
//		
//	 else 
//			if(strlen(buffer) != 0)
//					HAL_UART_Transmit(&huart1, (uint8_t*)"Try another Slot.\n", strlen("Try another Slot.\n"), 500);
		
			//taskENTER_CRITICAL();
		for (int j=0; j< slots_num; j++)
		{
			BCompare = (char *) malloc(1 + strlen(slots[j].name)+ strlen(str));
      strcpy(BCompare, slots[j].name); //P1
      strcat(BCompare, str);
			//var = string_compare(buffer,BCompare,strlen(buffer));
			var= strcmp(BCompare, buffer);
			
			free(BCompare);

			if (var == 0)  //P1 == P1
			{
				flag=1;
				if (slots[j].status == 'E')			//Slot can be reservd 
			{
					HAL_UART_Transmit(&huart1, (uint8_t*)"SLOT RESERVED.\n", strlen("SLOT RESERVED.\n"), 500); 
				  slots[j].status = 'B';
					//memset(BCompare, 0, 50* (sizeof BCompare[0]) );	//clear the BCCompare
			}
			else if (slots[j].status == 'F'||slots[j].status == 'B') //Slot cannot be reservd 
			{
				HAL_UART_Transmit(&huart1, (uint8_t*)"Please choose another slot.\n", strlen("Please chose another slot.\n"), 500);
				//memset(BCompare, 0, 50* (sizeof BCompare[0]) );	//clear the BCCompare
			}
		}
			 					
		}
		if(flag==0)   //Invalid input
			{
				HAL_UART_Transmit(&huart1, (uint8_t*)"Invalid Input.\n", strlen("Invalid Input.\n"), 500);
				//memset(BCompare, 0, 50* (sizeof BCompare[0]) );	//clear the BCCompare
				flag =1;
			}
		
		//	taskEXIT_CRITICAL();

			
	 	//memset(BluetoothMsg, 0, sizeof(BluetoothMsg));	//clear the buffer
    //free(BCompare);
		memset(buffer, 0, 50* (sizeof buffer[0]) );	//clear the buffer	
		buffer_index =0;
	}
}
		__HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);

	}
	
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_USART1_UART_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
	
	//BLUETOOTH//
	//HAL_Delay(200);
	//HAL_GPIO_WritePin(BluetoothReset_GPIO_Port, BluetoothReset_Pin, GPIO_PIN_SET);
	//HAL_Delay(1000);
	memset(buffer, 0, sizeof(buffer));	//clear the buffer
	
	memset(BluetoothMsg, 0, sizeof(BluetoothMsg));	//clear the buffer
	HAL_TIM_Base_Start_IT(&htim2);			//launch the timer that launches every 20 msec 
  __HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);  //enable UART interrupt
//	__HAL_UART_ENABLE_IT(&huart2, UART_IT_RXNE);  //enable UART interrupt  


	SSD1306_Init();
	
	SSD1306_Clear ();
	//check = SSD1306_Init ();
	SSD1306_Fill (0); 												//fill color 0 ie black
	SSD1306_UpdateScreen();										//print the changes on the display
	
	SSD1306_GotoXY (0,0); 										//Goto 0,0
	SSD1306_Puts("HELLO", &Font_11x18, 0x01);		//puts HELLO on the display with color ie blue
	SSD1306_UpdateScreen();										//print the changes on the display
	

	DC_MOTOR_Init(DC_MOTOR1);
	DC_MOTOR_Start(DC_MOTOR1, DIR_CW, 0);
	speed = 0;
	delay = 2000;
	MOTOR1_DIR = DIR_CW;
  DIR_FLAG = 0;
	entry_car=0;
//	
//	SSD1306_GotoXY (10,0); 										//Goto 10,10
//	SSD1306_Puts("WORLD", &Font_11x18, 1);		//puts WORLD on the display
//	
//	SSD1306_UpdateScreen();										//print the changes on the display
//	
//	HAL_Delay (1000);
//	//Clear the screen
//	SSD1306_Fill(0); 												//fill color 0 ie black
//	SSD1306_UpdateScreen();										//print the changes on the display
//	SSD1306_DrawCircle (20,10,5,1);						//Draw circle 
//	SSD1306_UpdateScreen();										//print the changes on the display	
//	
//	SSD1306_DrawFilledRectangle(60,40,20,30,1);
//	SSD1306_UpdateScreen();										//print the changes on the display	
	
  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();
  /* Create the mutex(es) */
  /* creation of myMutex01 */
  myMutex01Handle = osMutexNew(&myMutex01_attributes);

  /* creation of myMutex02 */
  myMutex02Handle = osMutexNew(&myMutex02_attributes);

  /* USER CODE BEGIN RTOS_MUTEX */
		xSemaphore = xSemaphoreCreateMutex();


  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* creation of myBinarySem01 */
  myBinarySem01Handle = osSemaphoreNew(1, 1, &myBinarySem01_attributes);

  /* creation of myBinarySem02 */
  myBinarySem02Handle = osSemaphoreNew(1, 1, &myBinarySem02_attributes);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of myQueue01 */
  myQueue01Handle = osMessageQueueNew (16, sizeof(uint16_t), &myQueue01_attributes);

  /* creation of myQueue02 */
  myQueue02Handle = osMessageQueueNew (16, sizeof(uint16_t), &myQueue02_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of myTask02 */
  myTask02Handle = osThreadNew(StartTask02, NULL, &myTask02_attributes);

  /* creation of myTask03 */
  myTask03Handle = osThreadNew(StartTask03, NULL, &myTask03_attributes);

  /* creation of myTask04 */
  myTask04Handle = osThreadNew(StartTask04, NULL, &myTask04_attributes);

  /* creation of myTask05 */
  myTask05Handle = osThreadNew(StartTask05, NULL, &myTask05_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

	
  while (1)
  {
//	   DC_MOTOR_Set_Speed(DC_MOTOR1, 1000);

//		if(DIR_FLAG == 0)
//		{
//			MOTOR1_DIR = DIR_CW;
//			DIR_FLAG = 1;
//		}
//		else
//		{
//			MOTOR1_DIR = DIR_CCW;
//			DIR_FLAG = 0;
//		}
//		DC_MOTOR_Set_Dir(DC_MOTOR1, MOTOR1_DIR);

////		readSensors(slots);

//		HAL_Delay(5000);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE|RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 40;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_I2C1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Enable MSI Auto calibration
  */
  HAL_RCCEx_EnableMSIPLLMode();
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x00702991;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 720;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 1999;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA0 PA1 PA8 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PA6 PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_StartTask02 */
/**
* @brief Function implementing the myTask02 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask02 */
void StartTask02(void *argument)
{
  /* USER CODE BEGIN StartTask02 */
	
	
	slots[0].name = "P1";
	slots[0].port= GPIOA;
	slots[0].pin=GPIO_PIN_0;
	slots[0].status='E';
	
	slots[1].name = "P2";
	slots[1].port= GPIOA;
	slots[1].pin=GPIO_PIN_1;
	slots[1].status='E';	
	
	slots[2].name = "P3";
	slots[2].port= GPIOB;
	slots[2].pin=GPIO_PIN_0;
	slots[2].status='E';	
	
	slots[3].name = "P4";
	slots[3].port= GPIOB;
	slots[3].pin=GPIO_PIN_1;
	slots[3].status='E';	
	
  /* Infinite loop */
  for(;;)
  {
		readSensors(slots);
		osDelay(1);
		 /*read sensors every 1 sec*/ 
   // osDelay(1000);
  }
  /* USER CODE END StartTask02 */
}

/* USER CODE BEGIN Header_StartTask03 */
/**
* @brief Function implementing the myTask03 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask03 */
void StartTask03(void *argument)
{
  /* USER CODE BEGIN StartTask03 */
  /* Infinite loop */
	SSD1306_Clear ();

  for(;;)
  {
		DisplayOLED(slots);
    osDelay(1);
  }
  /* USER CODE END StartTask03 */
}

/* USER CODE BEGIN Header_StartTask04 */
/**
* @brief Function implementing the myTask04 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask04 */
void StartTask04(void *argument)
{
  /* USER CODE BEGIN StartTask04 */
  /* Infinite loop */
  for(;;)
  {
		if(xSemaphoreTake(myBinarySem01Handle, 9999999))
		{
				if(xSemaphoreTake(xSemaphore, 1000))
				{

				Booking_BT();		//Booking Bluetooth
				xSemaphoreGive(xSemaphore);		//UART1 Semaphore/Mutex

				}

		}

    osDelay(1);
  }
  /* USER CODE END StartTask04 */
}

/* USER CODE BEGIN Header_StartTask05 */
/**
* @brief Function implementing the myTask05 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask05 */
void StartTask05(void *argument)
{
  /* USER CODE BEGIN StartTask05 */
  /* Infinite loop */
  for(;;)
  {		
		DC_Motor_Cntrl();
    osDelay(delay);	
		//osDelay(2000);	

  }
  /* USER CODE END StartTask05 */
}

 /**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
