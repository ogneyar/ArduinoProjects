#include <MLDR187_adcui.h>
#include <MLDR187_lib.h>
#include <MLDR187_it.h>

#include <stdio.h>

#include <init.h>
#include <adcui_dma.h>

#define __ahbram __attribute__((section (".ahbram_data")))

__ahbram MDR_DMAChannel_TypeDef DMA_CONFIG_BASE[32] = {};
__ahbram MDR_DMAChannel_TypeDef DMA_CONFIG_ALTER[32] = {};

#define CHANNEL adcuiCh0
#define BUF_STEP 32
#define N_STEPS 8
#define CYCLE_MODE ENABLE

__ahbram uint32_t buf[3][BUF_STEP * N_STEPS] = {};

uint32_t current_step = 0;
BitStatus transfer_complete = RESET;

void DMA_IRQHandler() {
    BitStatus complete = ADCUI_DMAIsComplete(CHANNEL);

    if (CYCLE_MODE) {
        if (complete && current_step == N_STEPS) {
            ADCUI_DMAFinish(CHANNEL);
            transfer_complete = SET;
        } else {
            uint32_t offset = BUF_STEP * current_step;
            ADCUI_DMACycleModeRefresh(CHANNEL, buf[0] + offset, buf[1] + offset, buf[2] + offset, BUF_STEP);
        }

        if (complete)
            current_step++;
    } else {
        if (complete) {
            ADCUI_DMAFinish(CHANNEL);
            transfer_complete = SET;
        }
    }
}

int main() {
    init_clock();
    init_uart();
    init_adc();
    init_interrupts();
    init_dma();

    /* start ADCUI DMA transfer */
    uint32_t n_samples = CYCLE_MODE ? BUF_STEP : BUF_STEP * N_STEPS;
    ADCUI_DMAReceive(CHANNEL, buf[0], buf[1], buf[2], n_samples, CYCLE_MODE, IRQn_priority_low);

    /* block until transfer is complete */
    while (!transfer_complete);

    /* print data to uart */
    for (int i = 0; i < BUF_STEP * N_STEPS; i++) {
        printf("%ld\t%ld\t%ld\n",
               (int32_t)buf[0][i] << 8 >> 8,
               (int32_t)buf[1][i] << 8 >> 8,
               (int32_t)buf[2][i] << 8 >> 8
           );
    }

    return 0;
}

