
PROJECT = "blink"
VERSION = "1.0.1"

local sys = require "sys"

local wait = 50

sys.taskInit(
    function()
        local LED_D4 = gpio.setup(12, 0)
        local LED_D5 = gpio.setup(13, 0)
        while 1 do
            LED_D4(0)
            LED_D5(1)
            sys.wait(wait)
            LED_D4(1)
            LED_D5(0)
            sys.wait(wait)
            log.info("main", "code", "https://gitee.com/dreamcmi/LuatOS-ESP32")
            log.info("main", "wiki", "https://wiki.luatos.com")
        end
    end
)

sys.run()
