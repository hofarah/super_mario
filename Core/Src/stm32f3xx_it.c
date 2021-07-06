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
#include <time.h>
#include <stdlib.h>
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
extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern UART_HandleTypeDef huart2;
/* USER CODE BEGIN EV */
int welcomePage[4][20];
unsigned char data[1];

int gameMode = -1,x=0;
float gameSpeed = 1.6;//change by volume
int heart = 3;//decrease when Mario loose the game
float marioToDirection = 0;//if left or right key clicked,this variable fill.it will empty when Mario do that.
int windowStart = 0, windowEnd = 20;
int map[4][60];
int lastLcd[4][20];
int score = 0;
int marioX = 0, marioY = 0;//in window
int timer = 0;
int dir = 0, jump = -1, heartMarioShow = 0;
int marioYTmp = 0, marioXTmp = 0;
int marioLeftRight = 0;
int jumpLimit = 3;
int windowDir = 1;
float willChangeWindow = 0, w = 0, willChangeMario = 0;//for changing window position we need this variable
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
  * @brief This function handles ADC1 and ADC2 interrupts.
  */
void ADC1_2_IRQHandler(void)
{
  /* USER CODE BEGIN ADC1_2_IRQn 0 */

	if (timer%4==0){
		int x=HAL_ADC_GetValue(&hadc1);
		  int  fx=(int)((float)x*100/4095);
		gameSpeed=0.5+(fx*3.1/200);
//		unsigned char h[100];
//		           int sq = sprintf(h, "qqq%d qqq", fx*31/200);
//		           HAL_UART_Transmit(&huart2, h, sq, 1000);
	}else{

		           HAL_ADC_Start_IT(&hadc1);

		           return;
	}
  /* USER CODE END ADC1_2_IRQn 0 */
  HAL_ADC_IRQHandler(&hadc1);
  /* USER CODE BEGIN ADC1_2_IRQn 1 */

           HAL_ADC_Start_IT(&hadc1);
  /* USER CODE END ADC1_2_IRQn 1 */
}

/**
  * @brief This function handles TIM2 global interrupt.
  */
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */

  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */

  if (x%4==0){
  		sevenSeg(0);
  		BCDtoSev((int)gameSpeed);
        HAL_GPIO_WritePin(GPIOD,GPIO_PIN_6,0);

  	}else
  	if (x%4==1){
  		sevenSeg(1);
  		BCDtoSev(((int)(gameSpeed*10))%10);
  	}
  	else
  	if (x%4==2){
  		sevenSeg(2);
  		BCDtoSev((score/10)%10);
        HAL_GPIO_WritePin(GPIOD,GPIO_PIN_6,1);

  	}
  	else
  	if (x%4==3){
  		sevenSeg(3);
  		BCDtoSev(score%10);
        HAL_GPIO_WritePin(GPIOD,GPIO_PIN_6,1);

  	}

  	x++;
  /* USER CODE END TIM2_IRQn 1 */
}

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
        case -1:
            for (int c = 0; c < 4; c++) {
                for (int i = 0; i < 20; i++) {
                    if (welcomePage[c][i] != 0) {
                        setCursor(i, c);
                        write(welcomePage[c][i]);
                    }
                }
            }
            setCursor(4, 1);

//        	   print("s");
//            displayLcd(welcomePage, 0);
//            setCursor(6, 2);

            print("SUPER MARIO");
            setCursor(5, 3);
            if (timer % 3 == 0) {
                print("press any key!");
            } else {
                print("              ");
            }


            break;
        case 0:


            marioX = 2;
            marioY = 2;
            setCursor(0, 0);
            createMap();
            showMap();
            gameMode++;

            break;
        case 1:
            updateWindowMarioPosition();//change position of window and mario.mario locate according to window
            if (dir) {
                updateMarioPosition(dir);
                dir = 0;

            }
            updateMap();

            break;
        case 2:
            clear();
            setCursor(2, 1);
            print("press o to resume");
            break;
        case 3:
            gameOverPage();
            break;
        case 4:
            winGamePage();
            break;
        case 5:
            //TODO in show details page
        case 6:

            heartMarioPage();
            gameMode = 0;
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

    // 	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, 1);

  /* USER CODE END USART2_IRQn 0 */
  HAL_UART_IRQHandler(&huart2);
  /* USER CODE BEGIN USART2_IRQn 1 */
    if (gameMode == -1) {
        gameMode = 0;
    }
    if (data[0] == 'r') {
    	windowDir=1;
        dir = 1;
    }

    if (data[0] == 'l') {
    	windowDir=-1;
        dir = -1;
    }
    if (data[0] == 'p') {
        gameMode = 2;
    }

    if (data[0] == 'o') {
        gameMode = 0;
    }

    if (data[0] == 'u') {
        //if under ario!=0

        if (lastLcd[marioY + 1][marioX] != 0) {
        	  HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_12);
            jump = 1;
            jumpLimit = 3;
        }
    }
    HAL_UART_Receive_IT(&huart2, data, sizeof(data));

  /* USER CODE END USART2_IRQn 1 */
}

/* USER CODE BEGIN 1 */
void updateWindowMarioPosition() {
    if (jump != 0) {
        float check1 = w + (gameSpeed);
        if ((int) check1 != (int) w) {
            if (marioY <= 0) {
                jump = -1;
            }
            if (jump == 1) {
                marioYTmp--;
            }
            if (jump == -1) {
                marioYTmp++;
            }

//            if (marioY == 2) {
//                jump = 0;
//            }

        }
        w = check1;
    }

    float check = willChangeMario + (gameSpeed / 4);
    if ((int) check != (int) willChangeMario) {
        if (windowDir == 1) {
            windowStart++;
            windowEnd++;
            if (windowEnd > 60) {
                windowEnd = 60;
                windowStart = 40;
                marioX++;
            }
            marioX--;
        } else if (windowDir == -1) {
            windowStart--;
            windowEnd--;
            if (windowStart < 0) {
                windowEnd = 20;
                windowStart = 0;
                marioX--;
            }
            marioX++;
        }


    }

    willChangeMario = check;


}

void updateMarioPosition(int dir) {
    //dir is -1(left) or +1(right)

    if (dir > 0) {
        if (lastLcd[marioY][marioX + 1] == 0) {
            if (!jump) {
                marioX++;
            } else if (jumpLimit > 0) {
                marioX++;
                jumpLimit--;
            }

        } else if (lastLcd[marioY][marioX + 1] == 6) {
            gameMode = 4;
        }
    } else if (dir < 0) {
        if (lastLcd[marioY][marioX - 1] == 0) {

            marioX--;
        } else if (lastLcd[marioY][marioX - 1] == 6) {
            gameMode = 4;
        }
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
    if (show[marioY + marioYTmp][marioX] == 0) {
        if (marioY + marioYTmp >= 0) {
            marioY += marioYTmp;

        }
    } else {
        if (jump == 1) {
            jump = -1;
        }
        if (show[marioY - 1][marioX] == 5) {
            score++;
            HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, 1);
            unsigned char h[100];
            int sq = sprintf(h, "%d", score);
            HAL_UART_Transmit(&huart2, h, sq, 1000);

        }
        if (show[marioY + 1][marioX] == 6) {
            gameMode = 4;
        }
    }
    marioYTmp = 0;
    show[marioY][marioX] = 2;
    show[0][0] = 9;
    show[1][0] = 9;
    show[2][0] = 9;
    show[3][0] = 9;

    for (int c = 0; c < 4; c++) {
        for (int i = 0; i < 20; i++) {
            if (lastLcd[c][i] != show[c][i]) {
                setCursor(i, c);
                write(show[c][i]);
            }
        }
    }
    for (int c = 0; c < 4; c++) {
        for (int i = 0; i < 20; i++) {
            lastLcd[c][i] = show[c][i];
        }
    }
    marioLeftRight = 0;
    if (marioY >= 3 || marioX <= 0) {
        heart--;
        decLed();
        marioY = 2;
        marioX = 2;
        clear();
        if (heart == 0) {
            gameMode = 3;
        } else {
            gameMode = 6;
        }
        if (windowStart > 2) {
            windowStart -= 2;
            windowEnd -= 2;

        }
    }
}

void showMap() {

    int show[4][20];
    if (windowEnd >= 59) {
        return;
    }
    for (int i = windowStart, j = 0; i < windowEnd; i++, j++) {
        show[0][j] = map[0][i];
        show[1][j] = map[1][i];
        show[2][j] = map[2][i];
        show[3][j] = map[3][i];
    }
    show[marioY][marioX] = 2;
    show[0][0] = 9;
    show[1][0] = 9;
    show[2][0] = 9;
    show[3][0] = 9;

    for (int c = 0; c < 4; c++) {
        setCursor(0, c);
        for (int i = 0; i < 20; i++) {
            write(show[c][i]);

        }
    }
    for (int c = 0; c < 4; c++) {
        for (int i = 0; i < 20; i++) {
            lastLcd[c][i] = show[c][i];
        }
    }
}

void fillTestMap() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 60; j++) {
            map[i][j] = 0;
        }
    }
    for (int i = 0; i < 60; i++) {
        if (i % 11 == 1) {
            map[0][i] = 4;
            map[0][i + 1] = 5;
            map[0][i + 2] = 4;


        }
    }
    for (int i = 0; i < 60; i++) {
        if (i % 9 == 1) {
            map[3][i] = 0;

        } else {
            map[3][i] = 3;

        }

    }
    map[2][17] = 6;
    map[2][26] = 7;

}

void createMap() {
    srand(time(NULL));
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 60; j++) {
            map[i][j] = 0;
        }
    }
    int r = 0;
    for (int i = 4; i < 60; i++) {
        r = rand();
        if (r % 7 == 0) {
            map[0][i] = 4;//brick
        }
        if (r % 8 == 0) {
            map[0][i] = 5;//?
        }

    }

    for (int i = 0; i < 60; i++) {
        r = rand();
        if (r % 12 == 0 && i > 4) {
            map[3][i] = 0;//hole

        } else {
            map[3][i] = 3;//ground

        }

    }
    for (int i = 4; i < 60; i++) {
        r = rand();
        if (r % 5 == 0 && map[3][i] == 3) {
            map[2][i] = 7;//mane
        }
    }
    map[2][57] = 6;//flag
    map[2][58] = 0;//empty
    map[2][59] = 0;//empty
    map[3][58] = 3;
    map[3][59] = 3;
}

void heartMarioPage() {
    clear();
    setCursor(3, 1);
    print("OPS! YOU LOST!");

}

void gameOverPage() {
    int s[4][20];
    for (int c = 0; c < 4; c++) {
        for (int i = 0; i < 20; i++) {
            s[c][i] = 0;
        }
    }
    s[1][5] = 71;
    s[1][6] = 65;
    s[1][7] = 77;
    s[1][8] = 69;
    s[1][9] = 32;
    s[1][10] = 79;
    s[1][11] = 86;
    s[1][12] = 69;
    s[1][13] = 82;
//    s[3][0]=97;

    displayLcd(s, 1);
}

void displayLcd(int arr[4][20], int type) {
    for (int c = 0; c < 4; c++) {
        for (int i = 0; i < 20; i++) {
            if (lastLcd[c][i] != arr[c][i]) {
                setCursor(i, c);
                if (type == 0) {
                    write(arr[c][i]);
                } else {
                    char q[1];
                    q[0] = (char) arr[c][i];
                    print(q);
                }
            }
        }
    }
    for (int c = 0; c < 4; c++) {
        for (int i = 0; i < 20; i++) {
            lastLcd[c][i] = arr[c][i];
        }
    }
}

void winGamePage() {
    clear();
    setCursor(5, 1);
    print("YOU WON!!!");
    setCursor(4, 2);
    unsigned char h[100];
    sprintf(h, "YOUR SCORE:%d", score);
    print(h);
    setCursor(4, 3);
    int t = timer / 4;
    sprintf(h, "YOUR TIME:%d:%d", (t / 60), (t % 60));
    print(h);
    gameMode = -2;
}
void BCDtoSev(int i){
       int x1=i&1;
       int x2=i&2;
       int x3=i&4;
       int x4=i&8;
       if(x1>0) x1=1;
       if(x2>0) x2=1;
       if(x3>0) x3=1;
       if(x4>0) x4=1;
       HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, x1);
       HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, x2);
       HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, x3);
       HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, x4);
}
void sevenSeg(int n){
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4, 0);
          switch(n) {
          case 0:
            HAL_GPIO_WritePin(GPIOD,GPIO_PIN_1,1);
            break;
          case 1:
                 HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2,1);
              break;
          case 2:
            HAL_GPIO_WritePin(GPIOD,GPIO_PIN_3,1);
              break;
          case 3:
            HAL_GPIO_WritePin(GPIOD,GPIO_PIN_4,1);
              break;
          }
}
void decLed(){
	switch (heart){
	case 2:
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, 0);
		break;
	case 1:
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, 0);
break;
	case 0:
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, 0);
break;
	}
}
/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
