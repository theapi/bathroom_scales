#ifndef __tx_H
#define __tx_H
#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    TXSTATE_OFF,
    TXSTATE_SETUP,
    TXSTATE_INIT,
    TXSTATE_ON,
    TXSTATE_TRANSMITTING,
    TXSTATE_COMPLETE,
} TXState_TypeDef;



TXState_TypeDef TX_StateMachineRun(TXState_TypeDef);
TXState_TypeDef TX_StateOff(TXState_TypeDef);
TXState_TypeDef TX_StateSetup(TXState_TypeDef);
TXState_TypeDef TX_StateInit(TXState_TypeDef);
TXState_TypeDef TX_StateOn(TXState_TypeDef);
TXState_TypeDef TX_StateTranmitting(TXState_TypeDef);
TXState_TypeDef TX_StateComplete(TXState_TypeDef);

#ifdef __cplusplus
}
#endif
#endif /*__ tx_H */
