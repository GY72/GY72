
#ifndef DISPLAY_H
#define DISPLAY_H

typedef struct {
    u8 led_level;
    Bit8_ut icon;
}Display_T;

extern iram Display_T leds;
#define key_led_power     leds.icon.bits.bit_0                //��Դ
#define key_led_linkage   leds.icon.bits.bit_1                 //����
#define key_led_clock     leds.icon.bits.bit_2                //ʱ��
#define key_led_down      leds.icon.bits.bit_3                 //����
#define key_led_up        leds.icon.bits.bit_4                   //�ӵ�
#define key_led_fried     leds.icon.bits.bit_5                  //����
#define key_led_clean     leds.icon.bits.bit_6                    //��ϴ
#define key_led_light     leds.icon.bits.bit_7                    //����

/***************************************************************/
void display_drive(void);
void display_all(void);
void display_clear(void);
void sh79f328_led_init(void);

#endif
