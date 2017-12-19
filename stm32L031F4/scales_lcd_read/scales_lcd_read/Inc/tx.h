#ifndef __tx_H
#define __tx_H
#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"
#include "usart.h"
#include "lcd.h"

typedef enum {
    TXSTATE_OFF,
    TXSTATE_SETUP,
    TXSTATE_STARTING,
    TXSTATE_ON,
    TXSTATE_TRANSMITTING,
    TXSTATE_SENT,
    TXSTATE_COMPLETE,
} TXState_TypeDef;

TXState_TypeDef TX_StateMachineRun(TXState_TypeDef, UART_HandleTypeDef *huart2, LCD_TypeDef *lcd);
TXState_TypeDef TX_StateOff(TXState_TypeDef);
TXState_TypeDef TX_StateSetup(TXState_TypeDef);
TXState_TypeDef TX_StateStarting(TXState_TypeDef);
TXState_TypeDef TX_StateOn(TXState_TypeDef, UART_HandleTypeDef *huart2, uint16_t weight);
TXState_TypeDef TX_StateTranmitting(TXState_TypeDef);
TXState_TypeDef TX_StateSent(TXState_TypeDef, UART_HandleTypeDef *huart2);
TXState_TypeDef TX_StateComplete(TXState_TypeDef);

#ifdef __cplusplus
}
#endif
#endif /*__ tx_H */
