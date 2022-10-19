#ifndef __HASH_H
#define __HASH_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "MDR32FxQI_config.h"

uint32_t Crc( uint8_t* arr, uint32_t len );
uint64_t CalcHash (MDR_ETHERNET_TypeDef* ETHERNETx, uint8_t* mac);

#ifdef __cplusplus
}
#endif

#endif


