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

typedef enum {
    TX_STATE_SETUP,
    TX_STATE_INIT,
    TX_STATE_ON,
    TX_STATE_OFF,
    TX_STATE_TRANSMITTING,
    TX_STATE_SLEEP,
} TX_StateTypeDef;

TX_StateTypeDef tx_state = TX_STATE_OFF;

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
  HAL_UART_MspDeInit(&huart2);

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


    int count = 0;

    HAL_ADCEx_Calibration_Start(&hadc, ADC_SINGLE_ENDED);
    HAL_ADC_Start(&hadc);

    uint32_t com1 = 0;
    uint16_t weight = 1234;
    uint8_t pins = 0;
    GPIO_PinState radio = GPIO_PIN_SET;



  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */


      switch (tx_state) {
        case TX_STATE_OFF:
            // Do the measuring


            //HAL_Delay(30000);

            //HAL_ADC_Start(&hadc);
            HAL_ADC_PollForConversion(&hadc, 100);
            com1 = HAL_ADC_GetValue(&hadc);
            //HAL_ADC_Stop(&hadc);

//            uint8_t pin5 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1);
//            uint8_t pin6 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2);
//            uint8_t pin7 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3);
//            uint8_t pin8 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4);
//            uint8_t pin9 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5);
//            uint8_t pin10 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6);
//            uint8_t pin11 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7);
//            uint8_t pin12 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10);
//
//            uint32_t pin_values = GPIOA->IDR;
//            char pin_values_str[33];
//            itoa(pin_values, pin_values_str, 2);
//            //sprintf(tx1_buffer, "id:%d, pins: %s, hex: %X\n", count, pin_values_str, pin_values);

            pins = LCD_getPinValues();




            /* Got a measurement so initialise the tranmission. */
            tx_state = TX_STATE_SETUP;
            break;

        case TX_STATE_SETUP:
            /* Turn on the transmitter */
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_SET);
            tx_state = TX_STATE_INIT;
            break;

        case TX_STATE_INIT:
            /* Wait for the transmitter to turn on */
            /* The radio will pull this high when it is ready for the serial data */
            radio = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_15);
            if (radio == GPIO_PIN_RESET) {
                tx_state = TX_STATE_ON;
            }
            break;

        case TX_STATE_ON:
            /* Send the data */
            /* Configure and turn on the uart */
            HAL_UART_MspInit(&huart2);

            //char pins_str[9];
            //itoa(pins, pins_str, 2);
            /* Buffer used for transmission on USART2 */
            char tx1_buffer[4];
            tx1_buffer[0] = '#';
            tx1_buffer[1] = (weight >> 8);
            tx1_buffer[2] = weight;
            tx1_buffer[3] = '\n';
            //sprintf(tx1_buffer, "#%d\n", weight);

            HAL_UART_Transmit(&huart2, (uint8_t*) tx1_buffer, 4, 1000);


            tx_state = TX_STATE_TRANSMITTING;
            break;

        case TX_STATE_TRANSMITTING:
//            HAL_Delay(5000);
//            tx_state = TX_STATE_SLEEP;
            radio = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_15);
            if (radio == GPIO_PIN_SET) {
                /* Transmitter finished */
                tx_state = TX_STATE_SLEEP;


            } else {
                // send again
                HAL_Delay(1000);
                tx_state = TX_STATE_ON;
            }
            break;

        case TX_STATE_SLEEP:



            /* Turn off the transmitter */
                HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_RESET);


                /* Disable the uart */
                HAL_UART_MspDeInit(&huart2);

                HAL_Delay(60000);
            /* After standby, setup (main) is run again */
            standby();
            break;
      }





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
