/**
  ******************************************************************************
  * @file    Templates/Src/stm32f1xx.c
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    29-April-2016
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx.h"
#include "stm32f1xx_it.h"
#include "lcd.h"

extern TIM_HandleTypeDef htim1;
extern ADC_HandleTypeDef hadc1;
extern UART_HandleTypeDef huart1;
/** @addtogroup STM32F1xx_HAL_Examples
  * @{
  */

/** @addtogroup Templates
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
  HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

/******************************************************************************/
/*                 STM32F1xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f1xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */

void LCD_Car2(unsigned x)											//顯示圖形之方程式
{  
	LCD_Car(0,0,4*x);
	LCD_Car(2,0,4*x+1);
	LCD_Car(4,0,4*x+2);
	LCD_Car(6,0,4*x+3);
}


extern int R,Y,G,flag,i,j,button,mode,a;
extern unsigned char set[][16];
extern unsigned char num[2];
void TIM1_UP_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_UP_IRQn 0 */
  button=HAL_GPIO_ReadPin(WAKEUP_BUTTON_GPIO_PORT, WAKEUP_BUTTON_PIN);
	if(button==1&&mode>0)												//在普通模式時按鈕按下
	{
	
		HAL_Delay(200);
		while(HAL_GPIO_ReadPin(WAKEUP_BUTTON_GPIO_PORT, WAKEUP_BUTTON_PIN)){}
		HAL_Delay(200);
		flag=0;																		//顯示全關
		i=j=0;
		LCD_Clear();
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_6,0);
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_7,0);
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_8,0);			
		set[0][14]=G/10;													//設定設定初值
		set[0][15]=G%10;
		set[1][14]=Y/10;
		set[1][15]=Y%10;
		set[2][14]=R/10;
		set[2][15]=R%10;
		mode=0;
	}
	if(button==1&&mode==0)											//在設定模式時按鈕按下
	{
		HAL_Delay(200);
		while(HAL_GPIO_ReadPin(WAKEUP_BUTTON_GPIO_PORT, WAKEUP_BUTTON_PIN)){}
		HAL_Delay(200);
		flag++;
		i=j=0;
		LCD_DrawString(0, 0, set[0], 16);					//顯示秒數設定字型
		LCD_DrawString(2, 0, set[1], 16);
		LCD_DrawString(4, 0, set[2], 16);
		if(flag>3)																//判斷是否設定完了
		{
			flag=0;
			mode=1;
			LCD_Clear();
		}
	}
	
	if(mode>0)
	{
  	j++;
		i=j/2;
	}
	else
	{
		j++;
		i=j;
	}

	if(mode==1)																	//顯示綠燈時的圖形
	{
		if(j<2)
		{
			LCD_Car2(0);
		}
		else if(j%3==2)
		{
			LCD_Car2(1);
		}
		else if(j%3==0)
		{
			LCD_Car2(2);
		}
		else if(j%3==1)
		{
			LCD_Car2(3);
		}
		LCD_DrawString(0, 112, num, 2);						//顯示綠燈秒數
	}
	if(mode==2)																	//顯示黃燈時的圖形
	{
		if(j%6==0)
		{
			LCD_Car2(5);
		}
		else if(j%6==1)
		{
			LCD_Car2(6);
		}
		else if(j%6==2)
		{
			LCD_Car2(7);
		}
		else if(j%6==3)
		{
			LCD_Car2(8);
		}
		else if(j%6==4)
		{
			LCD_Car2(9);
		}
		else if(j%6==5)
		{
			LCD_Car2(4);
		}
		LCD_DrawString(0, 112, num, 2);						//顯示黃燈秒數
	}
	if(mode==3)																	//顯示紅燈時的圖形
	{
		LCD_Car2(10);
		LCD_DrawString(0, 112, num, 2);						//顯示紅燈秒數
	}
	
	
	

  /* USER CODE END TIM1_UP_IRQn 0 */
  HAL_TIM_IRQHandler(&htim1);

}

/**
  * @}
  */ 

/**
  * @}
  */

