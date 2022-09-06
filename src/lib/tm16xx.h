
#ifndef TM16XX_H
#define TM16XX_H

#define LED_A  0x0100
#define LED_B  0x0080
#define LED_C  0x0040
#define LED_D  0x0020
#define LED_E  0x0010
#define LED_F  0x0008
#define LED_G  0x0004
#define LED_H  0x0002
#define LED_I  0x0001
extern u16 num_value;
extern u8 colon_overturn;
void tm16xx_clser(void);
void tm16xx_all_show(void);
void tm16xx_show_num(unsigned int num);
void tm16xx_show_hex(unsigned int num);
void tm16xx_show_3_num(unsigned char num);
void tm16xx_show_stall(u8 stall);
void tm16xx_show_num_stall(u16 num,u8 stall);
void tm16xx_drive(void);
void tm16xx_get_key_value(void);
void tm16xx_show_colon(void);

#endif
