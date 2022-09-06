
#include "..\include_s.h"

/***************************************************/

#define key_led_power_pin     P3_3                //电源
#define key_led_linkage_pin   P3_2                 //联动
#define key_led_clock_pin      P3_6                //时钟
#define key_led_down_pin      P3_7                 //减档
#define key_led_up_pin           P2_2                   //加档
#define key_led_fried_pin        P2_5                  //爆炒
#define key_led_clean_pin      P2_4                    //清洗
#define key_led_light_pin        P5_2                    //照明

iram Display_T leds;
/***************************************************/
void display_all(void)
{
    tm16xx_all_show();
    leds.icon.byte=0xff;
}

void display_clear(void)
{
     tm16xx_clser();
     leds.icon.byte=0;
}

void dis_digital_screen(void)
{
     
//     Down_Tmer.hour_cnt*
}

void dis_level_light(void)
{
		
}

void wheel_display(void)
{
	
}

void display_drive(void)
{					
     tm16xx_drive();
     key_led_power_pin=key_led_power;
     key_led_linkage_pin=key_led_linkage;
     key_led_clock_pin=key_led_clock;
     key_led_down_pin=key_led_down;
     key_led_up_pin=key_led_up;
     key_led_fried_pin=key_led_fried;
     key_led_clean_pin=key_led_clean;
     SETBANK1;
     key_led_light_pin=key_led_light;
     SETBANK0;
}

/* 
    TB = TSYS*256*DISCOM
    TLED = TB *S

    TB 为 LED 单 COM 扫描宽度， TSYS 为系统时钟宽度, TLED 为 LED 扫描时间宽度
    S  为 LED 扫描的 COM 数量 

    DISCOM = (TLED/S) / (Tsys*256) = (TLED) / (S*Tsys*256)
*/
void sh79f328_led_init(void)
{
//    LEDCON = 0x0;           //模式 1
//    DISCOM = 78;            //设置单 COM 扫描时间 @5ms
//    LEDDZ  = 0x10;          //设置死区时间, 建议LED死区时间设置大于10个系统时钟（LEDDZ > 0AH） 。
//		
//    SEG01  = bit10000000;   //
//    SEG02  = bit00111111;   //LED_S9~LED_S12 复用打开
//    LEDCOM = 0x03;          //LED_C1~LED_C2 复用打开
//		
//    LEDCON |= 0x80; //使能 LED 驱动
}









