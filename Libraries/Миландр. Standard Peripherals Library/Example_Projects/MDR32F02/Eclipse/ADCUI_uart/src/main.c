#include <init.h>
#include <MLDR187_adcui.h>
#include <MLDR187_lib.h>
#include <stdio.h>

#define SHIFT 13

#define N 512
int32_t buf[N][2];
uint32_t buf2[N][4];


int main() {
    init_clock();
    init_uart();
    init_ADC();

    for (int i = 0; i < N; i++) {
        while (ADCUI_GetFlag(adcuiCh0, adcuiFlagVoltageFifoEmpty));
        while (ADCUI_GetFlag(adcuiCh0, adcuiFlagCurrentFifoEmpty));
        buf[i][0] = (int32_t)ADCUI_GetNextVoltageFifoValue(adcuiCh0) << 8 >> 8;
        buf[i][1] = (int32_t)ADCUI_GetNextCurrentFifoValue(adcuiCurCh0) << 8 >> 8;
        buf2[i][0] = ADCUI_GetEnergyAccumulator(adcuiCh0, adcuiActivePositiveEnergy) >> SHIFT;
        buf2[i][1] = ADCUI_GetEnergyAccumulator(adcuiCh0, adcuiActiveNegativeEnergy) >> SHIFT;
        buf2[i][2] = ADCUI_GetEnergyAccumulator(adcuiCh0, adcuiReactivePositiveEnergy) >> SHIFT;
        buf2[i][3] = ADCUI_GetEnergyAccumulator(adcuiCh0, adcuiReactiveNegativeEnergy) >> SHIFT;
    }

    for (int i = 0; i < N; i++)
        printf("%ld\t%ld\t%lu\t%lu\t%lu\t%lu\n",
               buf[i][0], buf[i][1],
               buf2[i][0], buf2[i][1],
               buf2[i][2], buf2[i][3]
        );

    return 0;
}

