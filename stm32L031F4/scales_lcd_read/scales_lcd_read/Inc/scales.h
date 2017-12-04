#ifndef __scales_H
#define __scale_H
#ifdef __cplusplus
extern "C" {
#endif

#include "stm32l0xx_hal.h"
#include "main.h"
#include "stdint.h"

/**
  * @brief Scales_TypeDef
  */
typedef struct
{
    uint16_t weight;
    uint8_t pins;
    TXState_TypeDef state;
} Scales_TypeDef;

typedef enum {
    SCALESSTATE_OFF,
    SCALESSTATE_FRAME_START,
    SCALESSTATE_COM0,
    SCALESSTATE_COM1,
    SCALESSTATE_COM2,
    SCALESSTATE_COM3,
} ScalesState_TypeDef;

extern Scales_TypeDef scales;
extern ADC_HandleTypeDef hadc;

ScalesState_TypeDef SCALES_StateMachineRun(ScalesState_TypeDef);

#ifdef __cplusplus
}
#endif
#endif /*__ scales_H */
