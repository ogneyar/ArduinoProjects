
-- 

PROJECT = "rtcdemo"
VERSION = "1.0.1"

log.info("main", PROJECT, VERSION)

_G.sys = require("sys")

if wdt then
    wdt.init(9000)
    sys.timerLoopStart(wdt.feed, 3000)
end

sys.taskInit(function()
    log.info("os.date()", os.date())
    local t = rtc.get()
    log.info("rtc", json.encode(t))
    sys.wait(2000)
    rtc.set({year=2023,mon=4,day=17,hour=10,min=24,sec=42})
    log.info("os.date()", os.date())
	
    while 1 do
        log.info("os.date()", os.date())
        local t = rtc.get()
        log.info("rtc", json.encode(t))
        sys.wait(1000)
    end
end)

sys.run()
