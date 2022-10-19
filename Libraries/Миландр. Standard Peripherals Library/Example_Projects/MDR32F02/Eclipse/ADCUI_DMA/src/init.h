//
// Created by panukov.a on 17.03.2021.
//

#ifndef USE_INIT_H
#define USE_INIT_H

#include <MLDR187_lib.h>

extern MDR_DMAChannel_TypeDef DMA_CONFIG_BASE[32];
extern MDR_DMAChannel_TypeDef DMA_CONFIG_ALTER[32];

void init_clock();

void init_uart();

void init_interrupts();

void init_dma();

void init_adc();

#endif //USE_INIT_H

