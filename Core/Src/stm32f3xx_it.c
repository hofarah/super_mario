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
extern TIM_HandleTypeDef htim2;
/* USER CODE BEGIN EV */
extern int gameMode;
float gameSpeed = 1;//change by volume
int heart = 3;//decrease when Mario loose the game
float marioToDirection = 0;//if left or right key clicked,this variable fill.it will empty when Mario do that.
int windowStart, windowEnd;
char map[4][60];
int marioX = 0, marioY = 0;//in window
int timer = 0;
extern int dir = 0;
float willChangeWindow = 0, willChangeMario = 0;//for changing window position we need this variable
//every .5 second decrease this variable
/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void) {
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
void HardFault_Handler(void) {
    /* USER CODE BEGIN HardFault_IRQn 0 */

    /* USER CODE END HardFault_IRQn 0 */
    while (1) {
        /* USER CODE BEGIN W1_HardFault_IRQn 0 */
        /* USER CODE END W1_HardFault_IRQn 0 */
    }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void) {
    /* USER CODE BEGIN MemoryManagement_IRQn 0 */

    /* USER CODE END MemoryManagement_IRQn 0 */
    while (1) {
        /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
        /* USER CODE END W1_MemoryManagement_IRQn 0 */
    }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void) {
    /* USER CODE BEGIN BusFault_IRQn 0 */

    /* USER CODE END BusFault_IRQn 0 */
    while (1) {
        /* USER CODE BEGIN W1_BusFault_IRQn 0 */
        /* USER CODE END W1_BusFault_IRQn 0 */
    }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void) {
    /* USER CODE BEGIN UsageFault_IRQn 0 */

    /* USER CODE END UsageFault_IRQn 0 */
    while (1) {
        /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
        /* USER CODE END W1_UsageFault_IRQn 0 */
    }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void) {
    /* USER CODE BEGIN SVCall_IRQn 0 */

    /* USER CODE END SVCall_IRQn 0 */
    /* USER CODE BEGIN SVCall_IRQn 1 */

    /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void) {
    /* USER CODE BEGIN DebugMonitor_IRQn 0 */

    /* USER CODE END DebugMonitor_IRQn 0 */
    /* USER CODE BEGIN DebugMonitor_IRQn 1 */

    /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void) {
    /* USER CODE BEGIN PendSV_IRQn 0 */

    /* USER CODE END PendSV_IRQn 0 */
    /* USER CODE BEGIN PendSV_IRQn 1 */

    /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void) {
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
  * @brief This function handles TIM2 global interrupt.
  */
void TIM2_IRQHandler(void) {
    /* USER CODE BEGIN TIM2_IRQn 0 */
    //every 5/10 second this method call
    timer++;;
    switch (gameMode) {
        case 0:
            //TODO not started game
            marioX = 2;
            marioY = 2;
            fillTestMap()
            break;
        case 1:
            //TODO in game
            updateWindowMarioPosition();//change position of window and mario.mario locate according to window
            if (dir) {
                updateMarioPosition(dir);
            }
            showMap();

            break;
        case 2:
            //TODO in pause page
            break;
        case 3:
            //TODO in show details page
            break;
    }
    /* USER CODE END TIM2_IRQn 0 */
    HAL_TIM_IRQHandler(&htim2);
    /* USER CODE BEGIN TIM2_IRQn 1 */

    /* USER CODE END TIM2_IRQn 1 */
}

/* USER CODE BEGIN 1 */
void updateWindowMarioPosition() {
    if (willChangeWindow == 0) {
        willChangeWindow = gameSpeed;
    }

    int check;
    check = willChangeWindow - gameSpeed / 2;//gameSpeed/2 because every .5 second call this method
    if (check <= 0) {
        willChangeWindow = 0;
        //change 1 position window to right and mario to left
        windowStart++;
        windowEnd++;
        marioX--;
        return;
    }
    if ((int) check != (int) willChangeWindow) {
        //change 1 position window to right and mario to left
        windowStart++;
        windowEnd++;
        marioX--;
    }
    willChangeWindow = check;

}

void updateMarioPosition(int dir) {
    //dir is -1(left) or +1(right)
    if (willChangeMario == 0) {
        willChangeMario = dir * gameSpeed;
    }
    int check = willChangeMario - (dir * gameSpeed / 2);
    if (dir * check <= 0) {
        willChangeMario = 0;
        marioX--;
        return;
    }
    if ((int) check != (int) willChangeMario) {
        marioX--;
    }
    willChangeMario = check;
}

void showMap() {
    char show[4][20];
    for (int i = windowStart, j = 0; i < windowEnd; i++, j++) {
        show[0][j] = map[0][i];
        show[1][j] = map[1][i];
        show[2][j] = map[2][i];
        show[3][j] = map[3][i];
    }
    show[marioY][marioX] = 'm';
}

void fillTestMap() {
    for (int i = 0; i < 60; i++) {
        map[0][i] = '-'
    }
    for (int i = 0; i < 60; i++) {
        map[3][i] = '-'
    }
    map[0][0] = '|'
    map[1][0] = '|'
    map[2][0] = '|'
    map[3][0] = '|'
    map[0][59] = '|'
    map[1][59] = '|'
    map[2][59] = '|'
    map[3][59] = '|'

}
/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
