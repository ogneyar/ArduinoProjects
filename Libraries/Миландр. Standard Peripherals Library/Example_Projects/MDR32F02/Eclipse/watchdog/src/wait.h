#ifndef TIMER_PWM_WAIT_H
#define TIMER_PWM_WAIT_H

#include <MLDR187_timer.h>
#include <MLDR187_it.h>

#ifdef __cplusplus
extern "C" {
#endif

ErrorStatus wait(double delay, MDR_TIM_TypeDef *timer);

ErrorStatus periodic_task(double period, void (*task)(void *arg), void *arg, MDR_TIM_TypeDef *timer);

ErrorStatus delayed_task(double delay, void (*task)(void *arg), void *arg, MDR_TIM_TypeDef *timer);

void clear_pending_task(MDR_TIM_TypeDef *timer);

#ifdef __cplusplus
} // extern "C"
#endif


#ifdef __cplusplus
template <typename Lambda>
inline ErrorStatus periodic_task(double period, Lambda& task, MDR_TIM_TypeDef *timer) {
    return periodic_task(period, [](void* arg){
        (*(Lambda*)arg)();
    }, &task, timer);
}
#endif


#endif //TIMER_PWM_WAIT_H

