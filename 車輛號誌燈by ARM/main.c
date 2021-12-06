/**
  ******************************************************************************
  * @file    Templates/Src/main.c 
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    29-April-2016
  * @brief   Main program body
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
#include "lcd.h"
/** @addtogroup STM32F1xx_HAL_Examples
  * @{
  */
#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
/** @addtogroup Templates
  * @{
  */


ADC_HandleTypeDef hadc1;
UART_HandleTypeDef huart1;
TIM_HandleTypeDef htim1;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_TIM1_Init(void);
void Error_Handler(void);
//static void MX_FSMC_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

int G=10,Y=5,R=11,flag=0,i,j,button,mode=1,a;					//mode->1:Green,2:Yellow,3:Red,4:set ；flag->1:設定綠燈,2:設定黃燈,3:設定紅燈
unsigned char num[2]={1,0};														//顯示秒數
unsigned char set[][16]={															//設定模式時顯示的字型
	{DG,Dr,De,De,Dn,82,82,DT,Di,Dm,De,82,DColon,82,3,0},
	{DY,De,Dl,Dl,Do,Dw,82,DT,Di,Dm,De,82,DColon,82,1,0},
	{DR,De,Dd,82,82,82,82,DT,Di,Dm,De,82,DColon,82,3,0},
	{82,82,82,82,82,82,82,82,82,82,82,82,82,82,82,82},
};

int main(void)
{
  HAL_Init();
  /* Configure the system clock */
  SystemClock_Config();
  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_USART1_UART_Init();
  MX_TIM1_Init();
	LCD_Init();
	LCD_Clear();

  HAL_TIM_Base_Start_IT(&htim1);
	
  while (1)
  {		
		if(mode==1)																		//Green
		{
			if(i<G)																			//判斷數字是否超過
			{
				HAL_GPIO_WritePin(GPIOF, GPIO_PIN_6,1);		//亮綠燈
				HAL_GPIO_WritePin(GPIOF, GPIO_PIN_7,0);
				HAL_GPIO_WritePin(GPIOF, GPIO_PIN_8,0);
				num[0]=(G-i)/10;													//設定數字
				num[1]=(G-i)%10;
			}
			else
			{
				mode=2;																		//跳黃燈模式
				i=j=0;
			}
		}
		if(mode==2)																		//Yellow	
		{
			if(i<Y)																			//判斷數字是否超過
			{
				HAL_GPIO_WritePin(GPIOF, GPIO_PIN_6,0);		
				HAL_GPIO_WritePin(GPIOF, GPIO_PIN_7,1);		//亮黃燈
				HAL_GPIO_WritePin(GPIOF, GPIO_PIN_8,0);
				num[0]=(Y-i)/10;													//設定數字
				num[1]=(Y-i)%10;
			}
			else
			{
				mode=3;																		//跳紅燈模式
				i=j=0;
			}
		}
		if(mode==3)																		//Red
		{
			if(i<R)																			//判斷數字是否超過
			{
				HAL_GPIO_WritePin(GPIOF, GPIO_PIN_6,0);
				HAL_GPIO_WritePin(GPIOF, GPIO_PIN_7,0);
				HAL_GPIO_WritePin(GPIOF, GPIO_PIN_8,1);		//亮紅燈
				num[0]=(R-i)/10;													//設定數字
				num[1]=(R-i)%10;
			}
			else
			{
				mode=1;																		//跳綠燈模式
				i=j=0;
			}
		}
		if(mode==0)																		//set
		{

			
			set[0][14]=G/10;														//設定目前數字
			set[0][15]=G%10;
			set[1][14]=Y/10;
			set[1][15]=Y%10;
			set[2][14]=R/10;
			set[2][15]=R%10;
			HAL_Delay(250);
			HAL_ADC_Start(&hadc1);											//讀取ADC
			a = HAL_ADC_GetValue(&hadc1);
			HAL_ADC_Stop(&hadc1);
			
			if(flag==1)																	//設定綠燈秒數
			{
				G=a/41+1;
				if(i%2==0)																//綠燈那行字型閃爍
				{
					LCD_DrawString(0, 0, set[0], 16);				//顯示綠燈設定之秒數
				}
				else if(i%2==1)
				{
					LCD_DrawString(0, 0, set[3], 16);				//綠燈那行字型不顯示
				}
			}
			if(flag==2)																	//設定黃燈秒數
			{
				Y=a/82+1;
				if(i%2==0)																//黃燈那行字型閃爍
				{
					LCD_DrawString(2, 0, set[1], 16);				//顯示黃燈設定之秒數
				}
				else if(i%2==1)
				{
					LCD_DrawString(2, 0, set[3], 16);				//黃燈那行字型不顯示
				}
			}
			if(flag==3)																	//設定紅燈秒數
			{
				R=a/41+1;
				if(i%2==0)																//紅燈那行字型閃爍
				{
					LCD_DrawString(4, 0, set[2], 16);				//顯示紅燈設定之秒數
				}
				else if(i%2==1)
				{
					LCD_DrawString(4, 0, set[3], 16);				//紅燈那行字型不顯示
				}
			}
			
		}	
	}
  /* USER CODE END 3 */
}


/** System Clock Configuration
*/
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART1 and Loop until the end of transmission */
	
  HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xffff);

  return ch;
}
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* ADC1 init function */
static void MX_ADC1_Init(void)
{

  ADC_ChannelConfTypeDef sConfig;

    /**Common config 
    */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

    /**Configure Regular Channel 
    */
  sConfig.Channel = ADC_CHANNEL_14;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

}

/* USART1 init function */
void MX_USART1_UART_Init(void)
{

  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_9B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  HAL_UART_Init(&huart1);

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_TIM1_Init(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_SlaveConfigTypeDef sSlaveConfig;
  TIM_MasterConfigTypeDef sMasterConfig;

  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 7200;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 500;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  HAL_TIM_Base_Init(&htim1);

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig);

  sSlaveConfig.SlaveMode = TIM_SLAVEMODE_TRIGGER;
  sSlaveConfig.InputTrigger = TIM_TS_ITR0;
  HAL_TIM_SlaveConfigSynchronization(&htim1, &sSlaveConfig);

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig);

}

static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  
	__GPIOA_CLK_ENABLE();
  __GPIOE_CLK_ENABLE();
  __GPIOD_CLK_ENABLE();
  __GPIOG_CLK_ENABLE();
  __GPIOF_CLK_ENABLE();
	WAKEUP_BUTTON_GPIO_CLK_ENABLE();
  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pins : PF6 PF7 PF8 PF9 */
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
	
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Pin = WAKEUP_BUTTON_PIN;
	HAL_GPIO_Init(WAKEUP_BUTTON_GPIO_PORT,&GPIO_InitStruct);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */


void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler */ 
}





#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */


