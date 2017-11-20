/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __bit_H
#define __bit_H
#ifdef __cplusplus
extern "C" {
#endif

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))


#ifdef __cplusplus
}
#endif
#endif /*__ bit_H */
