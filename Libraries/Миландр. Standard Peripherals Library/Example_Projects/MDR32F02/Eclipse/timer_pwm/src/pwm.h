#ifndef TIMER_PWM_PWM_H
#define TIMER_PWM_PWM_H

#include <MLDR187_rst_clk.h>
#include <MLDR187_timer.h>
#include <MLDR187.h>

ErrorStatus enable_pwm
(
    MDR_TIM_TypeDef *timer, timChannel channel,
    double frequency, double duty, double dead_time,
    FunctionalState direct_enable, FunctionalState direct_invert,
    FunctionalState inverted_enable, FunctionalState inverted_invert
);

ErrorStatus set_pwm_duty(MDR_TIM_TypeDef *timer, timChannel channel, double duty);

void disable_pwm(MDR_TIM_TypeDef* timer, timChannel channel, timChannelOutput output);

#endif //TIMER_PWM_PWM_H

