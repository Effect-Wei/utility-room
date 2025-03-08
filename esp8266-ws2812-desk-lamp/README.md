# esp8266-ws2812-desk-lamp

使用 NodeMCU ESP8266 作为主控控制 WS2812 灯条并接入了 [Blinker](https://diandeng.tech/doc) 以实现手机 APP 控制灯光。

使用了 [Adafruit_NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel) 和 [Blinker](https://diandeng.tech/doc) 依赖库。

点灯 APP 界面配置：
```
{¨config¨{¨headerColor¨¨transparent¨¨headerStyle¨¨dark¨¨background¨{¨img¨¨assets/img/bg/1.jpg¨}}¨dashboard¨|{¨type¨¨ran¨¨t0¨¨色相¨¨clr¨¨#595959¨¨max¨¢H31¨min¨É¨bg¨É¨cols¨Ñ¨rows¨Ê¨key¨¨ran-hue¨´x´É´y´Ï¨lstyle¨Ì¨rt¨«}{ß9¨btn¨¨ico¨¨fal fa-power-off¨¨mode¨ÊßB¨电源¨¨t1¨¨文本2¨ßHÊßIÍßJÍßK¨btn-power¨´x´Ë´y´ËßMËßD¨#FBA613¨}{ß9ßAßB¨明度¨ßDßWßF¢47ßGÉßHÉßIÑßJÊßK¨ran-value¨´x´É´y´ÑßN«ßMÌ}{ß9ßAßB¨饱和度¨ßD¨#076EEF¨ßFº1ßGÉßHÉßIÑßJÊßK¨ran-saturation¨´x´É´y´ÐßN«ßMÌ}{ß9¨col¨ßB¨颜色拾取¨ßD¨#389BEE¨ßHÉßIÏßJÏßK¨col-xx3¨´x´Ê´y´ÒßMË}÷¨actions¨|÷¨triggers¨|÷ßN|÷}
```