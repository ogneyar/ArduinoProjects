#include <pwm.h>
#include <math.h>
#include <MLDR187_gpio.h>

struct ChannelOutPins {
    MDR_GPIO_TypeDef* dirPort;
    MDR_GPIO_TypeDef* invPort;
    uint32_t dirPin;
    uint32_t invPin;
    PORT_FUNC_TypeDef dirFunc;
    PORT_FUNC_TypeDef invFunc;
};

struct ChannelOutPins TIM_CH_PINS[4][4] = {
    {
        {MDR_PORTA, MDR_PORTA, pin0, pin1, PORT_FUNC_MAIN, PORT_FUNC_MAIN},
        {MDR_PORTA, MDR_PORTA, pin2, pin3, PORT_FUNC_MAIN, PORT_FUNC_MAIN},
        {MDR_PORTA, MDR_PORTA, pin4, pin5, PORT_FUNC_MAIN, PORT_FUNC_MAIN},
        {MDR_PORTA, MDR_PORTA, pin6, pin7, PORT_FUNC_MAIN, PORT_FUNC_MAIN}
    }, {
        {MDR_PORTC, MDR_PORTC, pin2, pin3, PORT_FUNC_MAIN, PORT_FUNC_MAIN},
        {MDR_PORTB, MDR_PORTB, pin10, pin11, PORT_FUNC_MAIN, PORT_FUNC_MAIN},
        {MDR_PORTB, MDR_PORTB, pin12, pin13, PORT_FUNC_MAIN, PORT_FUNC_MAIN},
        {MDR_PORTB, MDR_PORTA, pin14, pin11, PORT_FUNC_MAIN, PORT_FUNC_MAIN}
    }, {
        {MDR_PORTB, MDR_PORTB, pin0, pin1, PORT_FUNC_OVERRID, PORT_FUNC_OVERRID},
        {MDR_PORTB, MDR_PORTB, pin2, pin3, PORT_FUNC_OVERRID, PORT_FUNC_OVERRID},
        {MDR_PORTB, MDR_PORTB, pin4, pin5, PORT_FUNC_OVERRID, PORT_FUNC_OVERRID},
        {MDR_PORTB, MDR_PORTB, pin6, pin7, PORT_FUNC_OVERRID, PORT_FUNC_OVERRID}
    }, {
        {MDR_PORTA, MDR_PORTA, pin10, pin11, PORT_FUNC_OVERRID, PORT_FUNC_OVERRID},
        {MDR_PORTA, MDR_PORTA, pin12, pin13, PORT_FUNC_OVERRID, PORT_FUNC_OVERRID},
        {MDR_PORTA, MDR_PORTA, pin14, pin15, PORT_FUNC_OVERRID, PORT_FUNC_OVERRID},
        {MDR_PORTC, MDR_PORTC, pin0, pin1, PORT_FUNC_OVERRID, PORT_FUNC_OVERRID}
    }
};

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

ErrorStatus enable_pwm
(
    MDR_TIM_TypeDef* timer, timChannel channel,
    double frequency, double duty, double dead_time,
    FunctionalState direct_enable, FunctionalState direct_invert,
    FunctionalState inverted_enable, FunctionalState inverted_invert
)
{
    double period_ticks = RST_CLK_PER1C2_Speed / frequency;
    double dead_time_ticks = RST_CLK_PER1C2_Speed * dead_time;

    if (period_ticks > 2.8e14 || period_ticks <= 2) {
        // Can't set so big or small period
        return ERROR;
    }

    if (dead_time_ticks >= 16*256) {
        return ERROR;
    }

    if (duty < 0 || duty > 1) {
        return ERROR;
    }

    FunctionalState enable_dead_time = dead_time != 0;
    uint32_t dtg_prescaler = enable_dead_time ? ceil(dead_time_ticks / 256) : 0;
    uint32_t dtg_divisor = enable_dead_time ? dead_time_ticks / dtg_prescaler : 0;

    uint16_t prescaler = ceil(period_ticks / 0x100000000);
    uint32_t period = period_ticks / prescaler;
    uint32_t CCR = period * duty;


    TIMER_CntInitTypeDef timInit = {
            .perClkDiv = RST_CLK_Div1,
            .iniCounter = 0,
            .prescaler = prescaler - 1,
            .period = period - 1,
            .cntMode = timModeClkFixedDir,
            .cntDirection = timCntUp,
            .filterSampling = timFdtsDiv1,
            .ARRupdateMode = timArrUpdateImmediate,
            .ETR_FilterConf = timFltr_1_clk,
            .ETR_Prescaler = timPrescaler_1,
            .ETR_Inversion = DISABLE,
            .BRK_Inversion = DISABLE
    };
    TIMER_Init(timer, &timInit);

    TIMER_ChannelInitTypeDef chnInit = {
            .chMode			= timChPWM,
            .ETRresetEn		= DISABLE,
            .BRKresetEn		= DISABLE,
            .REFformat		= enable_dead_time ? timChOCCM_fmt7 : timChOCCM_fmt6,
            .ETRenable		= DISABLE,
            .EVTsrcCCR		= timChEvPositiveEdge,
            .inputPrescaler	= timPrescaler_1,
            .ChFilterConf	= timFltr_1_clk,
            .CCR1enable		= DISABLE,
            .EVTsrcCCR1		= timChEvPositiveEdge,
            .CCRreload		= timArrUpdateImmediate,
            .EVTdelay		= DISABLE,

            .DTGdivisor     = enable_dead_time ? dtg_divisor : 0,
            .DTGprescaler   = enable_dead_time ? (dtg_prescaler - 1): 0
    };
    TIMER_ChnInit(timer, channel, &chnInit);
    TIMER_SetChCCR(timer, channel, timCCR, CCR);

    struct ChannelOutPins outPins = TIM_CH_PINS[get_timer_id(timer)][channel - 1];

    PORT_InitTypeDef PORT_InitStructure = {
        .PORT_OE = PORT_OE_OUT,
        .PORT_MODE  = PORT_MODE_DIGITAL,
        .PORT_PULL_DOWN = PORT_PULL_DOWN_OFF,
        .PORT_SPEED = PORT_SPEED_SLOW_4mA
    };

    if (direct_enable) {
        TIMER_OuputInitTypeDef outInit = {
            .outEn = timChOutAlwaysOn,
            .inversion = direct_invert,
            .outSrc = enable_dead_time ? timChOutDtg : timChOutRef
        };
        TIMER_ChnOutInit(timer, channel, timChOutDirect, &outInit);

        PORT_InitStructure.PORT_FUNC = outPins.dirFunc;
        PORT_Init(outPins.dirPort, outPins.dirPin, &PORT_InitStructure);
    }
    if (inverted_enable) {
        TIMER_OuputInitTypeDef outInit = {
            .outEn = timChOutAlwaysOn,
            .inversion = inverted_invert,
            .outSrc = enable_dead_time ? timChOutDtg : timChOutRef
        };
        TIMER_ChnOutInit(timer, channel, timChOutInv, &outInit);

        PORT_InitStructure.PORT_FUNC = outPins.invFunc;
        PORT_Init(outPins.invPort, outPins.invPin, &PORT_InitStructure);
    }

    TIMER_Cmd(timer, ENABLE);

    return SUCCESS;
}

ErrorStatus set_pwm_duty(MDR_TIM_TypeDef *timer, timChannel channel, double duty) {
    if (duty < 0 || duty > 1) {
        return ERROR;
    }

    uint32_t period = timer->ARR + 1;
    uint32_t CCR = period * duty;

    TIMER_SetChCCR(timer, channel, timCCR, CCR);

    return SUCCESS;
}

void disable_pwm(MDR_TIM_TypeDef *timer, timChannel channel, timChannelOutput output) {
    PORT_InitTypeDef PORT_InitStructure = {
        .PORT_OE = PORT_OE_IN,
    };

    struct ChannelOutPins outPins = TIM_CH_PINS[get_timer_id(timer)][channel - 1];

    if (output == timChOutDirect) {
        PORT_InitStructure.PORT_FUNC = outPins.dirFunc;
        PORT_Init(outPins.dirPort, outPins.dirPin, &PORT_InitStructure);
    } else {
        PORT_InitStructure.PORT_FUNC = outPins.invFunc;
        PORT_Init(outPins.invPort, outPins.invPin, &PORT_InitStructure);
    }

    TIMER_OuputInitTypeDef outInit = {};
    TIMER_ChnOutInit(timer, channel, output, &outInit);
}

