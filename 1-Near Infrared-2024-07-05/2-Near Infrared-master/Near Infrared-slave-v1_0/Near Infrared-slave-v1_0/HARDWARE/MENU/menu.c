#include "menu.h"
#include "oled.h"
#include "gpio.h"
#include "dinogame.h"
#include "control.h"
#include "DHT11.h"
#include "rtc.h"
//#include "tim.h"
#include "sys.h"
#include "matrix_key.h"

uint8_t key_status = 0;

RTC_DateTypeDef GetData;  //获取日期结构体

RTC_TimeTypeDef GetTime;   //获取时间结构体

//UI界面
//主页
unsigned char gImage_home[294] = {
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,
    0x80,0xC0,0xE0,0xF0,0x70,0x38,0x3C,0x1E,0x1E,0x3C,0x38,0x70,0xF0,0xE0,0xC0,0x80,
    0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x80,0x80,0xC0,0xE0,0xF0,0x70,0x78,0x3C,0x1C,0x0E,0x0F,0x07,
    0x03,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x03,
    0x07,0x0F,0x0E,0x1C,0x3C,0x78,0x70,0xF0,0xE0,0xC0,0x80,0x80,0x00,0x00,0x00,0x00,
    0x00,0x0C,0x0E,0x0F,0x07,0x03,0xF1,0xF1,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0xF1,0xF1,0x03,0x07,0x0F,0x0E,0x0C,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0xF0,0xF0,0xF0,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0xF0,0xF0,0xF0,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,
    0xE0,0xFF,0xFF,0xFF,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xFF,0xFF,0xFF,0xE0,
    0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,
};

unsigned char gImage_left[38] = {
    0x00,0x00,0x00,0x00,0x80,0xC0,0xE0,0xF0,0xF0,0xF8,0xFC,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x01,0x03,0x07,0x07,0x0F,0x1F,0x3F,0x00,0x00,0x00,0x00,0x00,
};
unsigned char gImage_right[38] = {
    0x00,0x00,0x00,0x00,0x00,0xFC,0xF8,0xF0,0xE0,0xE0,0xC0,0x80,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x3F,0x1F,0x0F,0x07,0x07,0x03,0x01,0x00,0x00,0x00,0x00,
};

unsigned char gImage_temp[] = {
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0xF0,0xF8,
    0x78,0x3C,0x1C,0x1C,0x1E,0x1E,0x1E,0x1C,0x3C,0x3C,0xF8,0xF8,0xF0,0xC0,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,
    0x00,0x00,0x00,0xF0,0xF8,0xF8,0xF8,0xF0,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x00,0x6A,
    0x5A,0x5A,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,
    0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x00,0x6B,
    0x6B,0x6B,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xF0,0xFC,0xFE,0x3F,0x0F,0x07,
    0xC0,0xE0,0xF0,0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,0xE0,0xC3,0x07,0x1F,0x3F,0xFC,0xF8,
    0xE0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0xFF,0xFF,0xF0,0x80,0x00,0x1F,
    0x3F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x3F,0x0E,0x00,0xC0,0xFF,0xFF,
    0xFF,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x07,0x0F,0x1F,0x1E,
    0x3C,0x3C,0x38,0x38,0x78,0x79,0x78,0x38,0x38,0x3C,0x3C,0x1E,0x0F,0x0F,0x07,0x01,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};
unsigned char gImage_playgame[] = {
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0xC0,0x80,0x80,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x80,0x80,0x80,0xC0,0x80,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0xE0,0xF8,0xFC,0x3E,0x1F,0x07,0x03,0x03,0x03,0x03,0x07,0x0F,0x1E,
    0x0C,0x00,0x00,0x00,0x0C,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,
    0x0F,0x0F,0x07,0x83,0xC3,0xC3,0xC7,0x8F,0x1F,0x7E,0xFC,0xF0,0xC0,0x00,0x00,0x00,
    0x00,0xE0,0xFF,0xFF,0x7F,0x01,0x00,0x20,0x70,0x70,0xFC,0xFE,0xFE,0xFC,0x70,0x70,
    0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xE0,0xF0,0xF0,
    0xF0,0xE0,0xC3,0x07,0x0F,0x0F,0x0F,0x07,0x03,0x00,0x03,0xFF,0xFF,0xFE,0xC0,0x00,
    0x00,0x0F,0xFF,0xFF,0xF8,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x03,0x01,0x00,0xE0,
    0xF0,0xF8,0x78,0x78,0x78,0x78,0x78,0x78,0x78,0x78,0x78,0x78,0x78,0x79,0xFB,0xF3,
    0xF3,0x81,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFC,0xFF,0xFF,0x1F,0x00,
    0x00,0x00,0x01,0x07,0x1F,0x3F,0x7C,0x78,0x70,0xF0,0x70,0x70,0x78,0x3C,0x1F,0x0F,
    0x07,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,
    0x0F,0x1F,0x3E,0x78,0x70,0x70,0xF0,0x70,0x70,0x7C,0x3F,0x1F,0x07,0x01,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};
unsigned char gImage_setting[] = {
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xE0,0xC0,0x80,0x80,0x00,0x00,0x00,
    0x00,0x00,0x00,0xC0,0xF8,0xFF,0x3F,0x07,0x07,0x3F,0xFF,0xF8,0xC0,0x00,0x00,0x00,
    0x00,0x00,0x00,0x80,0x80,0xC0,0xE0,0xC0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x02,0x0F,0x1F,0x7F,0xF9,0xE1,0x83,0x03,0x07,0x07,0x0E,
    0x0E,0x07,0x07,0x03,0x03,0x01,0x00,0x00,0x00,0x00,0x01,0x03,0x03,0x07,0x07,0x0E,
    0x0E,0x07,0x07,0x03,0x83,0xE1,0xF9,0x7F,0x1F,0x07,0x02,0x00,0x00,0x00,0x00,0x00,
    0xE0,0xE0,0xE0,0x70,0x70,0x70,0x38,0x38,0x3F,0x1F,0x07,0x01,0x00,0x00,0x00,0x00,
    0x00,0xE0,0xF0,0xF8,0x3C,0x1E,0x0E,0x0E,0x0E,0x0E,0x1E,0x3C,0xF8,0xF0,0xE0,0x00,
    0x00,0x00,0x00,0x00,0x01,0x07,0x1F,0x3F,0x38,0x38,0x70,0x70,0x70,0xE0,0xE0,0xE0,
    0x07,0x07,0x07,0x0E,0x0E,0x0E,0x1C,0x1C,0xFC,0xF8,0xE0,0x80,0x00,0x00,0x00,0x00,
    0x00,0x07,0x0F,0x1F,0x3C,0x78,0x70,0x70,0x70,0x70,0x78,0x3C,0x1F,0x0F,0x07,0x00,
    0x00,0x00,0x00,0x00,0x80,0xE0,0xF8,0x7C,0x1C,0x1C,0x0E,0x0E,0x0E,0x07,0x07,0x07,
    0x00,0x00,0x00,0x00,0x00,0x40,0xF0,0xFC,0xFE,0x9F,0x87,0xC1,0xC0,0xE0,0xE0,0x70,
    0xF0,0xE0,0xE0,0xC0,0xC0,0x80,0x00,0x00,0x00,0x00,0x80,0xC0,0xC0,0xE0,0xE0,0x70,
    0x70,0xE0,0xE0,0xC0,0xC1,0x87,0x9F,0xFE,0xF8,0xF0,0x40,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x07,0x03,0x01,0x01,0x00,0x00,0x00,
    0x00,0x00,0x00,0x03,0x1F,0xFF,0xFC,0xE0,0xE0,0xFC,0xFF,0x1F,0x03,0x00,0x00,0x00,
    0x00,0x00,0x00,0x01,0x03,0x03,0x07,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};
unsigned char gImage_info[] = {
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xE0,0xF0,0x70,0x38,0x38,0x1C,0x1C,
    0x0E,0x0E,0x0E,0x0E,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x0E,0x0E,0x0E,0x0E,
    0x1C,0x1C,0x38,0x38,0x70,0xF0,0xE0,0xC0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0xE0,0xF0,0xFC,0x3E,0x0F,0x07,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x1E,0x3E,0x3E,0x1C,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x07,0x0F,0x3E,0xFC,0xF0,0xE0,0x00,0x00,
    0xF8,0xFF,0xFF,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x18,0x38,0x1C,0x1C,0x1C,0xDC,0xFE,0xFE,0x3E,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0xFF,0xFF,0xF8,
    0x1F,0xFF,0xFF,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0xC0,0xFC,0xFF,0x3F,0x03,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0xFF,0xFF,0x1F,
    0x00,0x00,0x07,0x0F,0x3F,0x7C,0xF0,0xE0,0xC0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x7C,0x7F,0x7F,0x3B,0x38,0x38,0x38,0x1C,0x18,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xE0,0xF0,0x7C,0x3F,0x0F,0x07,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x07,0x0F,0x0E,0x1C,0x3C,0x38,0x38,
    0x70,0x70,0x70,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0x70,0x70,0x70,
    0x38,0x38,0x3C,0x1C,0x0E,0x0F,0x07,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};

/*信号图标*/
unsigned char signal_BMP[] =
{
    0x00,0x04,0x0C,0x14,0x24,0xFC,0x24,0x14,0x0C,0x04,0x00,0x00,0x00,0x00,0x00,0x00,
    0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0x00,0x60,0x60,0x00,0x78,0x78,
    0x00,0x7E,0x7E,0x00,0x7F,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};

/*蓝牙图标*/
unsigned char bluetooth_BMP[] =
{
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x44,0x28,0xFF,0x11,0xAA,0x44,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};

unsigned char gImage_yes[38] = {
    0x00,0xF8,0xFC,0x04,0x04,0x04,0x04,0x04,0x04,0x84,0xC4,0x64,0x24,0xFC,0xF8,0x00,
    0x00,0x3F,0x7F,0x40,0x41,0x43,0x46,0x46,0x43,0x41,0x40,0x40,0x40,0x7F,0x3F,0x00,
};
unsigned char gImage_back[38] = {
    0x00,0x00,0x38,0x7C,0x7E,0x5E,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0xF8,0xF0,0x00,
    0x00,0x00,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x1F,0x1F,0x00,
};
unsigned char gImage_engery[38] = {
    0x00,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0x20,0x20,0x20,0x20,0xE0,0x80,0x80,0x00,
    0x00,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x04,0x04,0x04,0x04,0x07,0x01,0x01,0x00,
};
unsigned char gImage_bulethouch[100] = {
    0x00,0x00,0x00,0x00,0x00,0x20,0x40,0x80,0xFC,0x48,0x30,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x04,0x02,0x01,0x3F,0x12,0x0C,0x00,0x00,0x00,0x00,0x00,
};


void (*current_operation_index)();

Menu_table  table[30]=
{
    {0,0,0,1,0,(*home)},	//一级界面（主页面） 索引，向下一个，向上一个，确定，退出

    {1,2,4,5,0,(*Temperature)},	//二级界面 温湿度
    {2,3,1,6,0,(*Palygame)},	//二级界面 游戏
    {3,4,2,7,0,(*Setting)},	//二级界面 设置
    {4,1,3,8,0,(*Info)},	//二级界面 信息

    {5,5,5,5,1,(*TestTemperature)},		//三级界面：DHT11测量温湿度
    {6,6,6,6,2,(*ConrtolGame)},				//三级界面：谷歌小恐龙Dinogame
    {7,7,7,9,3,(*Set)},								//三级界面：设置普通外设状态 LED
    {8,8,8,10,4,(*Information)},				//三级界面：作者和相关项目信息

    {9,9,9,7,3,(*LED)},		//LED控制
	
	{10,10,10,10,8,(*Information1)},             //三级界面：作者和相关项目信息
	
	
};

uint8_t  func_index = 0;	//主程序此时所在程序的索引值

void  Menu_key_set(void)
{
//    if((KEY_Scan(1) == 1) && (func_index != 6))
//    {
//        func_index=table[func_index].next;	//按键next按下后的索引号
////		beep_cnt = 25;
//        OLED_Clear();
//    }
//	if((KEY_Scan(1) == 4) && (func_index != 6))
//    {
//        func_index=table[func_index].up;	//按键next按下后的索引号
////		beep_cnt = 25;
//        OLED_Clear();
//    }

//    if((KEY_Scan(1) == 2) && (func_index != 6))
//    {
//        func_index=table[func_index].enter;	//按键enter按下后的索引号
////		beep_cnt = 25;
//        OLED_Clear();
//    }

//    if(KEY_Scan(1) == 3)
//    {
//        func_index=table[func_index].back;	//按键back按下后的索引号
////		beep_cnt = 25;
//        OLED_Clear();
//    }

    if((keyboard_scan() == 6) && (func_index != 11))
    {
        func_index=table[func_index].next;	//按键next按下后的索引号
//		beep_cnt = 25;
        OLED_Clear();
    }
	
	if((keyboard_scan() == 2) && (func_index != 11))
    {
        func_index=table[func_index].up;	//按键next按下后的索引号
//		beep_cnt = 25;
        OLED_Clear();
    }
	
	if((keyboard_scan() == 7) && (func_index != 11))
    {
        func_index=table[func_index].enter;	//按键next按下后的索引号
//		beep_cnt = 25;
        OLED_Clear();
    }
	
	if((keyboard_scan() == 5) && (func_index != 11))
    {
        func_index=table[func_index].back;	//按键next按下后的索引号
//		beep_cnt = 25;
        OLED_Clear();
    }

		
    current_operation_index=table[func_index].current_operation;	//执行当前索引号所对应的功能函数
    (*current_operation_index)();//执行当前操作函数
}


void home()
{
    RTC_display();
    OLED_DrawBMP(0,0,20,3,signal_BMP);
    OLED_DrawBMP(20,0,36,2,gImage_bulethouch);
    OLED_DrawBMP(112,0,128,2,gImage_engery);
    OLED_DrawBMP(4,6,20,8,gImage_yes);
    OLED_DrawBMP(12,4,28,6,gImage_left);
    OLED_DrawBMP(40,2,88,8,gImage_home);
    OLED_DrawBMP(99,4,115,6,gImage_right);
    OLED_DrawBMP(107,6,123,8,gImage_back);
}


void Temperature()
{
    RTC_display();
    OLED_DrawBMP(0,0,20,3,signal_BMP);
    OLED_DrawBMP(20,0,36,2,gImage_bulethouch);
    OLED_DrawBMP(112,0,128,2,gImage_engery);
    OLED_DrawBMP(4,6,20,8,gImage_yes);
    OLED_DrawBMP(12,4,28,6,gImage_left);
    OLED_DrawBMP(40,2,88,8,gImage_temp);
    OLED_DrawBMP(99,4,115,6,gImage_right);
    OLED_DrawBMP(107,6,123,8,gImage_back);
}

void Palygame()
{
    RTC_display();
    OLED_DrawBMP(0,0,20,3,signal_BMP);
    OLED_DrawBMP(20,0,36,2,gImage_bulethouch);
    OLED_DrawBMP(112,0,128,2,gImage_engery);
    OLED_DrawBMP(4,6,20,8,gImage_yes);
    OLED_DrawBMP(12,4,28,6,gImage_left);
    OLED_DrawBMP(40,2,88,8,gImage_playgame);
    OLED_DrawBMP(99,4,115,6,gImage_right);
    OLED_DrawBMP(107,6,123,8,gImage_back);
}

void Setting()
{
    RTC_display();
    OLED_DrawBMP(0,0,20,3,signal_BMP);
    OLED_DrawBMP(20,0,36,2,gImage_bulethouch);
    OLED_DrawBMP(112,0,128,2,gImage_engery);
    OLED_DrawBMP(4,6,20,8,gImage_yes);
    OLED_DrawBMP(12,4,28,6,gImage_left);
    OLED_DrawBMP(40,2,88,8,gImage_setting);
    OLED_DrawBMP(99,4,115,6,gImage_right);
    OLED_DrawBMP(107,6,123,8,gImage_back);
	key_status =0;
}

void Info()
{
    RTC_display();
    OLED_DrawBMP(0,0,20,3,signal_BMP);
    OLED_DrawBMP(20,0,36,2,gImage_bulethouch);
    OLED_DrawBMP(112,0,128,2,gImage_engery);
    OLED_DrawBMP(4,6,20,8,gImage_yes);
    OLED_DrawBMP(12,4,28,6,gImage_left);
    OLED_DrawBMP(40,2,88,8,gImage_info);
    OLED_DrawBMP(99,4,115,6,gImage_right);
    OLED_DrawBMP(107,6,123,8,gImage_back);
}


//按键函数，不支持连按
u8 KEY_Scan(u8 mode)
{
    static u8 key_up=1;
    if(mode)key_up=1;
    if(key_up&&(KEY0==0||KEY1==0||KEY2==0||KEY_UP==1))
    {
        HAL_Delay(10);		//消抖
        key_up=0;
        if(KEY0==0)return 1;   //按键执行下一个next
		else if(KEY_UP==1)return 4; //按键执行上一个up
        else if(KEY1==0)return 2;  //按键执行确定
        else if(KEY2==0)return 3;  //按键执行返回
    } 
	else if(KEY0==1&&KEY1==1&&KEY2==1&&KEY_UP==0)key_up=1;
    return 0;
}
void TestTemperature()
{
    DHT11();
	OLED_DrawBMP(4,6,20,8,gImage_yes);
	OLED_DrawBMP(107,6,123,8,gImage_back);	
}

void ConrtolGame()
{
    Game_control();
}

void Set()
{
    OLED_ShowString(0,0,"Peripherals: Lights",16);
    OLED_ShowString(0,2,"Status: Closed",16);
	key_status =1;
	
}

void Information()
{
    OLED_ShowString(0,0,"Author:123",16);
    OLED_ShowString(0,2,"Date:2024/1/1",16);
    OLED_ShowString(0,4,"Lab: Multi-level",16);
	OLED_DrawBMP(4,6,20,8,gImage_yes);
	OLED_DrawBMP(107,6,123,8,gImage_back);
}

void LED()
{
    OLED_ShowString(0,0,"Peripherals: Lights",16);
    OLED_ShowString(0,2,"Status: Open",16);
//    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
	 key_status =2;
}

//四级界面函数
void Information1()
{
    OLED_ShowString(0,0,"Author:123",16);
    OLED_ShowString(0,2,"Date:2024/1/1",16);
    OLED_ShowString(0,4,"Lab: 123",16);
	OLED_DrawBMP(4,6,20,8,gImage_yes);
	OLED_DrawBMP(107,6,123,8,gImage_back);
}


void RTC_display()				//RTC时间
{
    /* Get the RTC current Time */
    HAL_RTC_GetTime(&hrtc, &GetTime, RTC_FORMAT_BIN);
    /* Get the RTC current Date */
    HAL_RTC_GetDate(&hrtc, &GetData, RTC_FORMAT_BIN);

    /* Display date Format : yy/mm/dd */

    /* Display time Format : hh:mm:ss */
    OLED_ShowNum(40,0,GetTime.Hours,2,16);				//hour
    OLED_ShowString(57,0,":",16);
    OLED_ShowNum(66,0,GetTime.Minutes,2,16);			//min
    OLED_ShowString(83,0,":",16);
    OLED_ShowNum(93,0,GetTime.Seconds,2,16);			//seconds
}

