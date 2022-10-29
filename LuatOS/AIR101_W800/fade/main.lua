
PROJECT = "fade"
VERSION = "1.0.1"

log.info("main", PROJECT, VERSION)

_G.sys = require("sys")

if wdt then
    wdt.init(15000)
    sys.timerLoopStart(wdt.feed, 10000)
end

-- PWM4 --> PA7-7
-- PWM3 --> PB3-19
-- PWM2 --> PB2-18
-- PWM1 --> PB1-17
-- PWM0 --> PB0-16

-- contact PB8 with PWM1 (PB1)

sys.taskInit(function()
    while 1 do
        log.info("pwm", ">>>>>")
        for i = 100,1,-1 do -- for (int i = 10; i != 1; i--)
            pwm.open(1, 1000, i) -- 1000hz on PWM1
            sys.wait(10)
        end
        for i = 1,100,1 do 
            pwm.open(1, 1000, i)
            sys.wait(10)
        end
        --sys.wait(500)
    end
end)

sys.run()
