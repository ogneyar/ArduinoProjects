#include <init.h>
#include <stdlib.h>
#include <math.h>

#include <pwm.h>
#include <wait.h>
#include <stdbool.h>

#define PWM_FREQUENCY   8e4
#define SIN_FREQUENCY   0.5
#define SIN_FRACTION    1e-3
#define SIN_PERIODS     10
#define TASK_TIMER      MDR_TIMER3

struct {MDR_TIM_TypeDef* timer; timChannel channel; int inverted; FunctionalState invert;}
//LED_PINS[] = {
//    {MDR_TIMER2, timCh2, true, DISABLE},
//    {MDR_TIMER2, timCh3, false, ENABLE},
//    {MDR_TIMER2, timCh4, false, ENABLE},
//};

LED_PINS[] = {
    {MDR_TIMER4, timCh4, false, ENABLE},
    {MDR_TIMER1, timCh1, false, ENABLE},
    {MDR_TIMER1, timCh2, false, ENABLE},
    {MDR_TIMER1, timCh3, false, ENABLE},
};

#define N_LEDS ((int)(sizeof(LED_PINS) / sizeof(LED_PINS[0])))

struct task_data {
    double t;
    bool finish;
};

void control_power(void* arg) {
    double phase_shift = 1.0 / N_LEDS;

    double * tp = &(((struct task_data*) arg)->t);
    bool * finishp = &(((struct task_data*) arg)->finish);

    for (int i = 0; i < N_LEDS; i++) {
        double ti = *tp + phase_shift * i;
        double duty = 0.5 - 0.5 * cos(2 * M_PI * ti);
        set_pwm_duty(LED_PINS[i].timer, LED_PINS[i].channel, duty);
    }

    *tp += SIN_FRACTION;

    if (*tp >= SIN_PERIODS) {
        clear_pending_task(TASK_TIMER);
        *finishp = true;
    }
}

int main() {
    init_clock();

    for (int i = 0; i < N_LEDS; i++) {
        TIMER_DeInit(LED_PINS[i].timer);
    }

    for (int i = 0; i < N_LEDS; i++) {
        enable_pwm(
            LED_PINS[i].timer, LED_PINS[i].channel, PWM_FREQUENCY, 0, 0,
            !LED_PINS[i].inverted, LED_PINS[i].inverted ? DISABLE : LED_PINS[i].invert,
            LED_PINS[i].inverted, LED_PINS[i].inverted ? LED_PINS[i].invert : DISABLE
        );
    }

    for (;;)
    {
        struct task_data data = { .t = 0, .finish = false };

        periodic_task(SIN_FRACTION / SIN_FREQUENCY, control_power, &data, TASK_TIMER);

        while (!data.finish);
    }

    for (int i = 0; i < N_LEDS; i++) {
        disable_pwm(LED_PINS[i].timer, LED_PINS[i].channel, LED_PINS[i].inverted ? timChOutInv : timChOutDirect);
        TIMER_DeInit(LED_PINS[i].timer);
    }

    return 0;
}

