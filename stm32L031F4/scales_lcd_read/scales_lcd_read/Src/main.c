/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
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
#include "stm32l0xx_hal.h"
#include "adc.h"
#include "usart.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
#include "string.h"
#include "stdlib.h"

#include "lcd.h"
#include "tx.h"
#include "scales.h"

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
void standby();

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */


TXState_TypeDef tx_state = TXSTATE_OFF;

LCD_TypeDef lcd;

uint16_t value = 0;

/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

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
  MX_ADC_Init();
  MX_USART2_UART_Init();

  /* USER CODE BEGIN 2 */

  /* Disable the uart for now */
  //HAL_UART_MspDeInit(&huart2);

  /* Check if the system was resumed from Standby mode */
  if (__HAL_PWR_GET_FLAG(PWR_FLAG_SB) != RESET) {
    /* Clear Standby flag */
    __HAL_PWR_CLEAR_FLAG(PWR_FLAG_SB);
  }

  /* Enable Ultra low power mode */
  HAL_PWREx_EnableUltraLowPower();
  //HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN1);

  /* Ensure the transmitter is off */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_RESET);

  HAL_ADCEx_Calibration_Start(&hadc, ADC_SINGLE_ENDED);
  HAL_ADC_Start(&hadc);

  LCD_int(&lcd);

  /* Buffer used for transmission on USART2 */
  char tx_buffer[255];
  int count = 0;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

    if (LCD_pollForWeight(&lcd)) {
      sprintf(tx_buffer,
        "id:%d, weight: %d \n",
        ++count,
        lcd.weight
      );
      HAL_UART_Transmit(&huart2, (uint8_t*) tx_buffer, strlen(tx_buffer), 1000);
    }

//    if (LCD_read(&lcd)) {
//
//      LCD_decodeDigits(&lcd);
//
//      if (lcd.digit1 != 11) {
//
//        sprintf(tx_buffer,
//          "id:%d, d3: %d, d2: %d, d1: %d, d0: %d \n",
//          ++count,
//          lcd.digit3, lcd.digit2, lcd.digit1, lcd.digit0
//        );
//
//  //      char pins_com0_str[33];
//  //      itoa (lcd.pins_com0, pins_com0_str, 2);
//  //
//  //      char pins_com1_str[33];
//  //      itoa (lcd.pins_com1, pins_com1_str, 2);
//  //
//  //      char pins_com2_str[33];
//  //      itoa (lcd.pins_com2, pins_com2_str, 2);
//  //
//  //      char pins_com3_str[33];
//  //      itoa (lcd.pins_com3, pins_com3_str, 2);
//  //
//  //      sprintf(tx_buffer,
//  //        "id:%d, d3: %d, d2: %d, d1: %d, d0: %d \ncom0: %s, com1: %s, com2: %s, com3: %s\n",
//  //        ++count,
//  //        lcd.digit3, lcd.digit2, lcd.digit1, lcd.digit0,
//  //        pins_com0_str, pins_com1_str, pins_com2_str, pins_com3_str
//  //      );
//
//        HAL_UART_Transmit(&huart2, (uint8_t*) tx_buffer, strlen(tx_buffer), 1000);
//        HAL_Delay(250);
//      }
//    }


//    uint8_t pin_values = LCD_getPinValues();
//    char pin_values_str[33];
//    itoa (pin_values, pin_values_str, 2);
//    sprintf(tx_buffer, "id:%d, pins: %s, hex: %X\n", ++count, pin_values_str, pin_values);
//    HAL_UART_Transmit(&huart2, (uint8_t*) tx_buffer, strlen(tx_buffer), 1000);
//    HAL_Delay(2000);

  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_4;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_SYSCLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */

void standby() {
  /* The Following Wakeup sequence is highly recommended prior to each Standby mode entry
    mainly when using more than one wakeup source this is to not miss any wakeup event.
     - Disable all used wakeup sources,
     - Clear all related wakeup flags,
     - Re-enable all used wakeup sources,
     - Enter the Standby mode.
  */

  /* Disable all used wakeup sources: PWR_WAKEUP_PIN3 */
  HAL_PWR_DisableWakeUpPin(PWR_WAKEUP_PIN1);

  /* Clear all related wakeup flags*/
  __HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);

  /* Enable WakeUp Pin PWR_WAKEUP_PIN3 connected to PA.02 (Arduino A7) */
  HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN1);

  /* Enter the Standby mode */
  HAL_PWR_EnterSTANDBYMode();

}

/**
 * Callback for HAL_GPIO_EXTI_IRQHandler()
 * in EXTI0_1_IRQHandler().
 *
 * Handles the external interrupt.
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    //@todo
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void _Error_Handler(char * file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler_Debug */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
