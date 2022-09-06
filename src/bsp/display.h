
#ifndef DISPLAY_H
#define DISPLAY_H

typedef struct {
    u8 led_level;
    Bit8_ut icon;
}Display_T;

extern iram Display_T leds;
#define key_led_power     leds.icon.bits.bit_0                //电源
#define key_led_linkage   leds.icon.bits.bit_1                 //联动
#define key_led_clock     leds.icon.bits.bit_2                //时钟
#define key_led_down      leds.icon.bits.bit_3                 //减档
#define key_led_up        leds.icon.bits.bit_4                   //加档
#define key_led_fried     leds.icon.bits.bit_5                  //爆炒
#define key_led_clean     leds.icon.bits.bit_6                    //清洗
#define key_led_light     leds.icon.bits.bit_7                    //照明

/***************************************************************/
void display_drive(void);
void display_all(void);
void display_clear(void);
void sh79f328_led_init(void);

#endif
