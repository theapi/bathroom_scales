#ifndef __scales_H
#define __scale_H
#ifdef __cplusplus
extern "C" {
#endif

#include "stm32l0xx_hal.h"
#include "main.h"
#include "stdint.h"
#include "tx.h"



/**
  * @brief Scales_TypeDef
  */
typedef struct
{
    uint16_t weight;
    TXState_TypeDef state;
} Scales_TypeDef;


extern Scales_TypeDef scales;


#ifdef __cplusplus
}
#endif
#endif /*__ scales_H */
