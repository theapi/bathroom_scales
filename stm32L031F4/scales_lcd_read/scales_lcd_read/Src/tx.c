
#include "tx.h"

TXState_TypeDef TX_StateMachineRun(TXState_TypeDef state) {
    switch (state) {
        case TXSTATE_OFF: return TX_StateOff(state);
        case TXSTATE_SETUP: return TX_StateSetup(state);
        case TXSTATE_INIT: return TX_StateInit(state);
        case TXSTATE_ON: return TX_StateOn(state);
        case TXSTATE_TRANSMITTING: return TX_StateTranmitting(state);
        case TXSTATE_COMPLETE: return TX_StateComplete(state);
    }
    return state;
}

TXState_TypeDef TX_StateOff(TXState_TypeDef state) {

    return state;
}

TXState_TypeDef TX_StateSetup(TXState_TypeDef state) {

    return state;
}

TXState_TypeDef TX_StateInit(TXState_TypeDef state) {

    return state;
}

TXState_TypeDef TX_StateOn(TXState_TypeDef state) {

    return state;
}

TXState_TypeDef TX_StateTranmitting(TXState_TypeDef state) {

    return state;
}

TXState_TypeDef TX_StateComplete(TXState_TypeDef state) {

    return state;
}
