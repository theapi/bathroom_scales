#include "tx.h"
#include "scales.h"
#include "usart.h"
#include "lcd.h"

TXState_TypeDef TX_StateMachineRun(TXState_TypeDef state, UART_HandleTypeDef *huart2, LCD_TypeDef *lcd) {
  switch (state) {
    case TXSTATE_OFF:
      return TX_StateOff(state);
    case TXSTATE_SETUP:
      return TX_StateSetup(state);
    case TXSTATE_STARTING:
      return TX_StateStarting(state);
    case TXSTATE_ON:
      return TX_StateOn(state, huart2, lcd->weight);
    case TXSTATE_TRANSMITTING:
      return TX_StateTranmitting(state);
    case TXSTATE_SENT:
      return TX_StateSent(state, huart2);
    case TXSTATE_COMPLETE:
      return TX_StateComplete(state);
    default:
      return TX_StateOff(state);
  }
  return state;
}

TXState_TypeDef TX_StateOff(TXState_TypeDef state) {
  /* Do nothing, start of the sequence. */
  return state;
}

TXState_TypeDef TX_StateSetup(TXState_TypeDef state) {
  /* Turn on the transmitter */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_SET);
  state = TXSTATE_STARTING;
  return state;
}

TXState_TypeDef TX_StateStarting(TXState_TypeDef state) {
  GPIO_PinState radio = GPIO_PIN_SET;

  /* Wait for the transmitter to turn on */
  /* The radio will pull this low when it is ready for the serial data */
  radio = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_15);
  if (radio == GPIO_PIN_RESET) {
    state = TXSTATE_ON;
  }
  return state;
}

TXState_TypeDef TX_StateOn(TXState_TypeDef state, UART_HandleTypeDef *huart2, uint16_t weight) {
  /* Send the data */
  /* Configure and turn on the uart */
  HAL_UART_MspInit(huart2);

  /* Buffer used for transmission on USART2 */
  char tx1_buffer[4];
  tx1_buffer[0] = '#';
  tx1_buffer[1] = (weight >> 8);
  tx1_buffer[2] = weight;
  tx1_buffer[3] = '\n';

  HAL_UART_Transmit(huart2, (uint8_t*) tx1_buffer, 4, 1000);

  state = TXSTATE_TRANSMITTING;
  return state;
}

TXState_TypeDef TX_StateTranmitting(TXState_TypeDef state) {
  GPIO_PinState radio = GPIO_PIN_RESET;

  radio = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_15);
  if (radio == GPIO_PIN_SET) {
    /* Transmitter finished */
    state = TXSTATE_SENT;
  }
  //@todo send again after no response for a certain time.
  return state;
}

TXState_TypeDef TX_StateSent(TXState_TypeDef state, UART_HandleTypeDef *huart2) {
  /* Disable the uart */
  HAL_UART_MspDeInit(huart2);
  /* Turn off the transmitter */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_RESET);
  state = TXSTATE_COMPLETE;
  return state;
}

TXState_TypeDef TX_StateComplete(TXState_TypeDef state) {
  /* Nothing left to do. */
  return state;
}
