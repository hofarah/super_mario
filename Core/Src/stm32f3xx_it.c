/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f3xx_it.c
  * @brief   Interrupt Service Routines.
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
#include "stm32f3xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim3;
extern UART_HandleTypeDef huart2;
extern unsigned char data[1];

/* USER CODE BEGIN EV */
 int gameMode=0;
float gameSpeed = 1.5;//change by volume
int heart = 3;//decrease when Mario loose the game
float marioToDirection = 0;//if left or right key clicked,this variable fill.it will empty when Mario do that.
int windowStart=0, windowEnd=20;
int map[4][60];
int lastLcd[4][20];

int marioX = 0, marioY = 0;//in window
int timer = 0;
int dir = 0,jump=0;

int marioLeftRight=0;
float willChangeWindow = 0,w=0, willChangeMario = 0;//for changing window position we need this variable
//every .5 second decrease this variable
/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
    while (1) {
    }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F3xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f3xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles TIM3 global interrupt.
  */
void TIM3_IRQHandler(void)
{
  /* USER CODE BEGIN TIM3_IRQn 0 */

  /* USER CODE END TIM3_IRQn 0 */
  HAL_TIM_IRQHandler(&htim3);
  /* USER CODE BEGIN TIM3_IRQn 1 */

  timer++;
switch (gameMode) {
      case 0:


	marioX = 2;
	            marioY = 2;
	            setCursor(0, 0);
	            fillTestMap();
	           showMap();
gameMode++;
          //TODO not started game


          break;
      case 1:
          //TODO in game
      	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, 1);
if (timer%2==0){
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, 0);

}
            updateWindowMarioPosition();//change position of window and mario.mario locate according to window
            if (dir) {
                updateMarioPosition(dir);
            	dir=0;

            }
            updateMap();

          break;
      case 2:
          //TODO in pause page
          break;
      case 3:
          //TODO in show details page
          break;
  }
  /* USER CODE END TIM3_IRQn 1 */
}

/**
  * @brief This function handles USART2 global interrupt / USART2 wake-up interrupt through EXTI line 26.
  */
void USART2_IRQHandler(void)
{
  /* USER CODE BEGIN USART2_IRQn 0 */

	if ((data[0]=='r')&&(marioLeftRight==0)){
		dir=1;
		marioLeftRight=1;
	}

	if ((data[0]=='u')){
		jump=1;
//		lockJump=1;
	}
 // 	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, 1);

  /* USER CODE END USART2_IRQn 0 */
  HAL_UART_IRQHandler(&huart2);
  /* USER CODE BEGIN USART2_IRQn 1 */
  HAL_UART_Receive_IT(&huart2, data,sizeof(data));

  /* USER CODE END USART2_IRQn 1 */
}

/* USER CODE BEGIN 1 */
void updateWindowMarioPosition() {
	if (jump!=0){
    float check1 = w + (gameSpeed / 4);
    if ((int) check1 != (int) w) {
 if (jump==1){
	 marioY--;
 }
 if (jump==-1){
	 marioY++;
 }
 if (marioY==0){
	 jump=-1;
 }
 if (marioY==2){
	 jump=0;
 }

    }
	w=check1;}

    float check = willChangeMario + (gameSpeed / 4);
		    if ((int) check != (int) willChangeMario) {
		 windowStart++;
		        windowEnd++;
		        if (windowEnd>60){
		        	windowEnd=60;
		        	windowStart=40;
		        	marioX++;
		        }
		        marioX--;
	}

willChangeMario=check;


}

void updateMarioPosition(int dir) {
    //dir is -1(left) or +1(right)

if (dir>0){
	marioX++;
}else if (dir<0){
	marioX--;
}
}

void updateMap() {
//	unsigned char h[100];
//	int s=sprintf(h,"%d",1);
//		HAL_UART_Transmit(&huart2, h, s, 1000);

    int show[4][20];
    for (int i = windowStart, j = 0; i < windowEnd; i++, j++) {
        show[0][j] = map[0][i];
        show[1][j] = map[1][i];
        show[2][j] = map[2][i];
        show[3][j] = map[3][i];
    }
    show[marioY][marioX] = 2;
    for(int c=0;c<4;c++){
       	for (int i=0;i<20;i++){
       		if (lastLcd[c][i]!=show[c][i]){
           		setCursor(i, c);
       	    	write(show[c][i]);
       	 	}
       	    }
       }
    for(int c=0;c<4;c++){
          	for (int i=0;i<20;i++){
lastLcd[c][i]=show[c][i];
}
    }
    marioLeftRight=0;
}
void showMap() {

    int show[4][20];
    if (windowEnd>=59){
    	return;
    }
    for (int i = windowStart, j = 0; i < windowEnd; i++, j++) {
        show[0][j] = map[0][i];
        show[1][j] = map[1][i];
        show[2][j] = map[2][i];
        show[3][j] = map[3][i];
    }
    show[marioY][marioX] = 2;
    for(int c=0;c<4;c++){
   		setCursor(0, c);
       	for (int i=0;i<20;i++){
       	    	write(show[c][i]);

       	    }
       }
    for(int c=0;c<4;c++){
              	for (int i=0;i<20;i++){
    lastLcd[c][i]=show[c][i];
    }
        }
}
void fillTestMap() {
	for (int i=0;i<4;i++){
		for(int j=0;j<60;j++){
			map[i][j]=0;
		}
	}
//    for (int i = 0; i < 60; i++) {
//        map[0][i] = 4;
//    }
    for (int i = 0; i < 60; i++) {
        map[3][i] = 3;
    }
map[2][17]=6;

}
/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
