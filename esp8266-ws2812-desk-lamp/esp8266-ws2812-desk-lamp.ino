/* *****************************************************************
 *
 * Download latest Blinker library here:
 * https://github.com/blinker-iot/blinker-library/archive/master.zip
 * 
 * 
 * Blinker is a cross-hardware, cross-platform solution for the IoT. 
 * It provides APP, device and server support, 
 * and uses public cloud services for data transmission and storage.
 * It can be used in smart home, data monitoring and other fields 
 * to help users build Internet of Things projects better and faster.
 * 
 * Make sure installed 2.7.4 or later ESP8266/Arduino package,
 * if use ESP8266 with Blinker.
 * https://github.com/esp8266/Arduino/releases
 * 
 * Make sure installed 1.0.5 or later ESP32/Arduino package,
 * if use ESP32 with Blinker.
 * https://github.com/espressif/arduino-esp32/releases
 * 
 * Docs: https://diandeng.tech/doc
 *       
 * 
 * *****************************************************************
 * 
 * Blinker 库下载地址:
 * https://github.com/blinker-iot/blinker-library/archive/master.zip
 * 
 * Blinker 是一套跨硬件、跨平台的物联网解决方案，提供APP端、设备端、
 * 服务器端支持，使用公有云服务进行数据传输存储。可用于智能家居、
 * 数据监测等领域，可以帮助用户更好更快地搭建物联网项目。
 * 
 * 如果使用 ESP8266 接入 Blinker,
 * 请确保安装了 2.7.4 或更新的 ESP8266/Arduino 支持包。
 * https://github.com/esp8266/Arduino/releases
 * 
 * 如果使用 ESP32 接入 Blinker,
 * 请确保安装了 1.0.5 或更新的 ESP32/Arduino 支持包。
 * https://github.com/espressif/arduino-esp32/releases
 * 
 * 文档: https://diandeng.tech/doc
 *       
 * 
 * *****************************************************************/

#define BLINKER_WIFI

#include <Blinker.h>

char auth[] = "";
char ssid[] = "";
char pswd[] = "";

// Download Adafruit_NeoPixel library here:
// https://github.com/adafruit/Adafruit_NeoPixel
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN D1
#define NUMPIXELS 30

typedef struct
{
  int hue;         // [0,65535]
  int saturation;  // [0,255]
  int value;       // [0,255]
} COLOR_HSV;

COLOR_HSV hsv = { 0, 0, 0 };
bool isLightOn = false;  // 灯条开关状态

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
BlinkerButton Btn_Power("btn-power");
BlinkerSlider Ran_Hue("ran-hue");
BlinkerSlider Ran_Saturation("ran-saturation");
BlinkerSlider Ran_Value("ran-value");

String hsvToRGBString(uint32_t rgb) {
  // 从32位颜色值中提取RGB分量（假设格式为0x00RRGGBB）
  uint8_t r = (rgb >> 16) & 0xFF;  // 红色分量
  uint8_t g = (rgb >> 8) & 0xFF;   // 绿色分量
  uint8_t b = rgb & 0xFF;          // 蓝色分量

  char hexBuffer[7] = { 0 };
  snprintf(hexBuffer, sizeof(hexBuffer), "%02X%02X%02X", r, g, b);

  return String("#") + hexBuffer;
}

void set_led_strip() {
  if (isLightOn) {
    pixels.fill(pixels.gamma32(pixels.ColorHSV(hsv.hue, hsv.saturation, hsv.value)));
  } else if (!isLightOn) {
    pixels.clear();  // 关闭灯条
  }

  pixels.show();
}

void blink_builtin_led_once() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(50);
  digitalWrite(LED_BUILTIN, LOW);
}

void ran_hue_callback(int32_t value) {
  BLINKER_LOG("*****DEBUG***** get hue value: ", value);
  blink_builtin_led_once();

  hsv.hue = value;

  uint32_t rgb = pixels.ColorHSV(hsv.hue, 192, 192);
  Ran_Hue.color(hsvToRGBString(rgb));
  Ran_Hue.print();

  set_led_strip();
}

void ran_saturation_callback(int32_t value) {
  BLINKER_LOG("*****DEBUG***** get saturation value: ", value);
  blink_builtin_led_once();

  hsv.saturation = value;

  set_led_strip();
}

void ran_value_callback(int32_t value) {
  BLINKER_LOG("*****DEBUG***** get value value: ", value);
  blink_builtin_led_once();

  hsv.value = value;

  set_led_strip();
}

void btn_power_callback(const String &state) {
  BLINKER_LOG("*****DEBUG***** get button state: ", state);
  blink_builtin_led_once();

  isLightOn = (state == "on") ? true : false;
  Btn_Power.print(state);

  set_led_strip();
}

void setup() {
  Serial.begin(115200);
  BLINKER_DEBUG.stream(Serial);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  Blinker.begin(auth, ssid, pswd);

  Btn_Power.print("off");
  Ran_Hue.print(hsv.hue);
  Ran_Saturation.print(hsv.saturation);
  Ran_Value.print(hsv.value);

  Btn_Power.attach(btn_power_callback);
  Ran_Hue.attach(ran_hue_callback);
  Ran_Saturation.attach(ran_saturation_callback);
  Ran_Value.attach(ran_value_callback);

  pixels.begin();

  pixels.setBrightness(255);
  for (int i = 0; i < NUMPIXELS + 3; i++) {
    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(255, 255, 0));  // 改颜色
    pixels.setPixelColor(i - 3, pixels.Color(0, 0, 0));
    pixels.show();  // This sends the updated pixel color to the hardware.
    delay(30);      // 控制流水灯的速度
  }
  pixels.clear();
  pixels.show();
}

void loop() {
  Blinker.run();
}