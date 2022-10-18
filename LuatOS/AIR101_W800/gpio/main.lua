
-- Lua
PROJECT = "gpiodemo"
VERSION = "1.0.1"

log.info("main", PROJECT, VERSION)

_G.sys = require("sys")

if wdt then
    wdt.init(15000)
    sys.timerLoopStart(wdt.feed, 10000)
end

-- Air101 LEDs PB08/PB09/PB10
-- Air103 LEDs PPB24/PB25/PB26
-- Air105 LEDs PPD14/PD15/PC3

local rtos_bsp = rtos.bsp()
rtos_bsp = rtos_bsp:lower()

function pinx()
    if rtos_bsp =="air101" then
        return pin.PB08, pin.PB09, pin.PB10
    elseif rtos_bsp == "air103" then
        return pin.PB26, pin.PB25, pin.PB24
    elseif rtos_bsp == "air105" then
        return pin.PD14, pin.PD15, pin.PC3
    elseif rtos_bsp == "esp32c3" then
        return 12, 13, 255
    else
        log.info("main", "define led pin in main.lua")
        return 0, 0, 0
    end
end

local P1,P2,P3=pinx()
local LEDA= gpio.setup(P1, 0, gpio.PULLUP)
local LEDB= gpio.setup(P2, 0, gpio.PULLUP)
local LEDC= gpio.setup(P3, 0, gpio.PULLUP)

-- main function
sys.taskInit(
function()
    local count = 0
    while 1 do
        sys.wait(500)
        LEDA(count % 3 == 0 and 1 or 0) -- (count % 3 == 0) ? 1 : 0
        LEDB(count % 3 == 1 and 1 or 0)
        if P3 and P3 ~= 255 then -- if (P3 && P3 !== 255) then
            LEDC(count % 3 == 2 and 1 or 0)
        end
        log.info("GPIO", "Go Go Go", count, rtos.bsp())
        log.info("LuatOS:", "https://wiki.luatos.com")
        count = count + 1
    end
end
)

-- API https://wiki.luatos.com/api/gpio.html

sys.run()
