
-- LuaTools需要PROJECT和VERSION这两个信息
PROJECT = "gpiodemo"
VERSION = "1.0.1"

log.info("main", PROJECT, VERSION)

-- sys库是标配
_G.sys = require("sys")

if wdt then
    --添加硬狗防止程序卡死，在支持的设备上启用这个功能
    wdt.init(15000)--初始化watchdog设置为15s
    sys.timerLoopStart(wdt.feed, 10000)--10s喂一次狗
end

--下面的GPIO引脚编号，请根据实际需要进行更改！
-- Air101开发板的3个LED分别为 PB08/PB09/PB10
-- Air103开发板的3个LED分别为 PB24/PB25/PB26
-- Air105开发板的3个LED分别为 PD14/PD15/PC3

-- 若下载到设备后提示pin库不存在,请升级固件到V0006或以上


--【HaoSir2022】于2022年4月21日增加
local rtos_bsp = rtos.bsp()
rtos_bsp = rtos_bsp:lower()
function pinx()--根据不同开发板，给LED赋值不同的gpio引脚编号

    if rtos_bsp =="air101" then--Air101开发板LED引脚编号
        return pin.PB08, pin.PB09, pin.PB10
    elseif rtos_bsp == "air103" then--Air103开发板LED引脚编号
        return pin.PB26, pin.PB25, pin.PB24
    elseif rtos_bsp == "air105" then--Air105开发板LED引脚编号
        return pin.PD14, pin.PD15, pin.PC3
    elseif rtos_bsp == "esp32c3" then -- ESP32C3开发板的引脚
        return 12, 13, 255 -- 开发板上就2个灯
    else
        log.info("main", "define led pin in main.lua")
        return 0, 0, 0
    end
end
--LED引脚判断赋值结束

local P1,P2,P3=pinx()--赋值开发板LED引脚编号
local LEDA= gpio.setup(P1, 0, gpio.PULLUP)
local LEDB= gpio.setup(P2, 0, gpio.PULLUP)
local LEDC= gpio.setup(P3, 0, gpio.PULLUP)


sys.taskInit(function()
--开始流水灯
    local count = 0
    while 1 do
    --流水灯程序
        sys.wait(500) --点亮时间
        -- 轮流点灯
        LEDA(count % 3 == 0 and 1 or 0)
        LEDB(count % 3 == 1 and 1 or 0)
        if P3 and P3 ~= 255 then
            LEDC(count % 3 == 2 and 1 or 0)
        end
        log.info("GPIO", "Go Go Go", count, rtos.bsp())
        log.info("LuatOS:", "https://wiki.luatos.com")
        count = count + 1
    end
end)

-- API文档 https://wiki.luatos.com/api/gpio.html

-- 用户代码已结束---------------------------------------------
-- 结尾总是这一句
sys.run()
-- sys.run()之后后面不要加任何语句!!!!!
