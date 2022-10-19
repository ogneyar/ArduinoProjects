#include <wait.h>
#include <math.h>

void *task_pending[4] = {};
void *task_pending_arg[4] = {};
int repeat[4] = {};

static int get_timer_id(MDR_TIM_TypeDef* timer) {
    if (timer == MDR_TIMER1) {
        return 0;
    } else if (timer == MDR_TIMER2) {
        return 1;
    } else if (timer == MDR_TIMER3) {
        return 2;
    } else if (timer == MDR_TIMER4) {
        return 3;
    } else {
        return 0;
    }
}

void Timer_IRQHandler(MDR_TIM_TypeDef* timer) {
    int timer_id = get_timer_id(timer);

    if (TIMER_GetFlagStatus(timer, timEventCntArr)) {
        TIMER_ClearFlag(timer, timEventCntArr);

        void (*task)(void *) = task_pending[timer_id];
        void *arg = task_pending_arg[timer_id];
        if (task != 0) {
            task(arg);
        }

        if (!repeat[timer_id]) {
            TIMER_ItSetNewState(timer, timEventCntArr, DISABLE);
            task_pending[timer_id] = 0;

            TIMER_Cmd(timer, DISABLE);
        }
    }
}

void Timer1_IRQHandler() {
    Timer_IRQHandler(MDR_TIMER1);
}

void Timer2_IRQHandler() {
    Timer_IRQHandler(MDR_TIMER2);
}

void Timer3_IRQHandler() {
    Timer_IRQHandler(MDR_TIMER3);
}

void Timer4_IRQHandler() {
    Timer_IRQHandler(MDR_TIMER4);
}

int check_period(double period_seconds) {
    double period_ticks = RST_CLK_PER1C2_Speed * period_seconds;
    if (period_ticks > 2.8e14 || period_ticks <= 10) {
        // Can't set so big or small period
        return ERROR;
    }
    return SUCCESS;
}

ErrorStatus setup_timer_period(double period_seconds, MDR_TIM_TypeDef* timer) {
    double period_ticks = RST_CLK_PER1C2_Speed * period_seconds;

    if (!check_period(period_seconds)) {
        return ERROR;
    }

    uint16_t prescaler = ceil(period_ticks / 0x100000000);
    uint32_t period = period_ticks / prescaler;

    TIMER_CntInitTypeDef timInit = {
            .perClkDiv = RST_CLK_Div1,
            .iniCounter = 0,
            .prescaler = prescaler - 1,
            .period = period,
            .cntMode = timModeClkFixedDir,
            .cntDirection = timCntUp,
            .filterSampling = timFdtsDiv1,
            .ARRupdateMode = timArrUpdateImmediate,
            .ETR_FilterConf = timFltr_1_clk,
            .ETR_Prescaler = timPrescaler_1,
            .ETR_Inversion = DISABLE,
            .BRK_Inversion = DISABLE
    };
    TIMER_DeInit(timer);
    TIMER_Init(timer, &timInit);

    TIMER_ItSetNewState(timer, timEventCntArr, ENABLE);

    int timers_IRQ[4] = {TIM1_IRQn, TIM2_IRQn, TIM3_IRQn, TIM4_IRQn};
    int timer_id = get_timer_id(timer);
    int timer_IRQ = timers_IRQ[timer_id];

    PLIC_SetMinPermPriority(0);
    PLIC_ReleaseIRQ(timer_IRQ);
    PLIC_SetPriority(timer_IRQ, 1);
    PLIC_EnableIRQ(timer_IRQ);
    enable_irq_extm();

    TIMER_Cmd(timer, ENABLE);

    return SUCCESS;
}

ErrorStatus delayed_task(double delay, void (*task)(void* arg), void* arg, MDR_TIM_TypeDef *timer) {
    if (!check_period(delay)) {
        return ERROR;
    }

    int timer_id = get_timer_id(timer);
    task_pending[timer_id] = task;
    task_pending_arg[timer_id] = arg;
    repeat[timer_id] = 0;
    setup_timer_period(delay, timer);

    return SUCCESS;
}

ErrorStatus periodic_task(double period, void (*task)(void* arg), void* arg, MDR_TIM_TypeDef *timer) {
    if (!check_period(period)) {
        return ERROR;
    }

    int timer_id = get_timer_id(timer);
    task_pending[timer_id] = task;
    task_pending_arg[timer_id] = arg;
    repeat[timer_id] = 1;
    setup_timer_period(period, timer);

    return SUCCESS;
}

int spin_lock_flag = 0;

void exit_spin_lock(void* arg) {
	(void)arg;
    spin_lock_flag = 0;
}

void spin_lock() {
    while (spin_lock_flag);
}

ErrorStatus wait(double delay, MDR_TIM_TypeDef *timer) {
    if (!check_period(delay)) {
        return ERROR;
    }

    spin_lock_flag = 1;
    delayed_task(delay, exit_spin_lock, 0, timer);
    spin_lock();

    return SUCCESS;
}

void clear_pending_task(MDR_TIM_TypeDef *timer) {
    int timer_id = get_timer_id(timer);
    task_pending[timer_id] = 0;
    task_pending_arg[timer_id] = 0;
    repeat[timer_id] = 0;

    TIMER_DeInit(timer);
}

