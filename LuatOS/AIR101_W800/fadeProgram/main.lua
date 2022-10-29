
PROJECT = "fadeProgram"
VERSION = "1.0.1"

log.info("main", PROJECT, VERSION)

_G.sys = require("sys")

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

local intervalRising = 1000
local intervalFalling = 0
local ON = 1
local OFF = 0

function leds(action)
	LEDA(action)
	LEDB(action)
	if P3 and P3 ~= 255 then
		LEDC(action)
	end
end

function delayMicro(seconds)
	for i = 0, seconds, 1 do end
end


-- main function
sys.taskInit(
function()
    while 1 do
		while intervalFalling ~= 0 do
			leds(OFF)
			delayMicro(intervalFalling)
			leds(ON)
			delayMicro(intervalRising)
			intervalFalling = intervalFalling - 1
			intervalRising = intervalRising + 1
		end
		while intervalRising ~= 0 do
			leds(ON)
			delayMicro(intervalRising)
			leds(OFF)
			delayMicro(intervalFalling)
			intervalRising = intervalRising - 1
			intervalFalling = intervalFalling + 1
		end
        sys.wait(30)
		log.info("fadeProgram", "Go Go Go", rtos.bsp())
    end
end
)

sys.run()
