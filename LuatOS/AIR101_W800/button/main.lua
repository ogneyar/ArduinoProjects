
-- Lua
PROJECT = "button"
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

local button_timer_outtime = 10 --按键定时器: 10ms
local button_shake_time = 1     --按键消抖时间: button_shake_time*button_timer_outtime
local button_long_time = 100    --按键长按时间: button_shake_time*button_timer_outtime

local button_detect = true
local button_state = false
local button_cont = 0

local BTN_PIN = pin.PB02 -- 按实际开发板选取

-- 若固件支持防抖, 启用防抖
if gpio.debounce then
    gpio.debounce(BTN_PIN, 5)
end

button = gpio.setup(BTN_PIN, function() 
        if not button_detect then return end
        button_detect = false
        button_state = true
    end, 
    gpio.PULLUP,
    gpio.FALLING)
	
local wait = 700

button_timer = sys.timerLoopStart(
function()
    if button_state then
        if button() == 0 then
            button_cont = button_cont + 1
            if button_cont > button_long_time then
                print("long pass")
				print("button_cont",button_cont)
				wait = 50
            end
        else 
            if button_cont < button_shake_time then
            else
                if button_cont < button_long_time then
                    print("pass")
					print("button_cont",button_cont)
					if wait == 50 then
						wait = 700
					elseif wait == 700 then 
						wait = 250
					else 
						wait = 700
					end
                else
                    print("long pass")
					print("button_cont",button_cont)
					wait = 50
                end
            end
            button_cont = 0
            button_state = false
            button_detect = true
        end
    end
end,
button_timer_outtime
) 


sys.taskInit(
function()
    local count = 0
    while 1 do
        sys.wait(wait)
        LEDA(count % 2 == 0 and 1 or 0) -- (count % 2 == 0) ? 1 : 0
        LEDB(count % 2 == 0 and 1 or 0)
        if P3 and P3 ~= 255 then -- if (P3 && P3 !== 255) then
            LEDC(count % 2 == 0 and 1 or 0)
        end
        --log.info("GPIO", "Go Go Go", count, rtos.bsp())
        --log.info("LuatOS:", "https://wiki.luatos.com")
        count = count + 1
    end
end
)

sys.run()
-- sys.run()之后后面不要加任何语句!!!!!
