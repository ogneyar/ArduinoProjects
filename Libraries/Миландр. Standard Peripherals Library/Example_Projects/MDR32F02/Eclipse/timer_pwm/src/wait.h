#ifndef TIMER_PWM_WAIT_H
#define TIMER_PWM_WAIT_H

#include <MLDR187_timer.h>
#include <MLDR187_it.h>

ErrorStatus wait(double delay, MDR_TIM_TypeDef *timer);

ErrorStatus periodic_task(double period, void (*task)(void *arg), void *arg, MDR_TIM_TypeDef *timer);

ErrorStatus delayed_task(double delay, void (*task)(void *arg), void *arg, MDR_TIM_TypeDef *timer);

void clear_pending_task(MDR_TIM_TypeDef *timer);


#endif //TIMER_PWM_WAIT_H

