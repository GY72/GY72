#ifndef _TM1640__H_
#define _TM1640__H_

/**********TM1640************/
#define DIN(x)      P2_5=(x)
#define SCLK(x)     P2_4=(x)

#define DATA_MODE1     0x40    //地址自动加1模式
#define DATA_MODE2     0x44    //固定地址模式

#define LUM         6//亮度范围(0~7)7最亮

#define TM1640_ON      (0x88+LUM)   //显示开
#define TM1640_OFF     0x80    //显示关

#define NUMBERR1_COM     0xc0   //数码管1的地址
#define NUMBERR2_COM     0xc1   //数码管2的地址   
#define NUMBERR3_COM     0xc2   //数码管3的地址
#define NUMBERR4_COM     0xc3   //数码管4的地址

#define WASH1_CHARACTERC     0xc4   //强力洗图标地址
#define WASH2_CHARACTERC     0xc5   //日常洗图标地址
#define WASH3_CHARACTERC     0xc6   //即时洗图标地址
#define WASH4_CHARACTERC     0xc7   //节能洗图标地址
#define WASH5_CHARACTERC     0xc8   //快速洗图标地址
#define WASH1_OFF            0x00   //不显示洗图标
#define WASH1_ON             0x0f   //显示洗图标

#define SALT_ICON        0x20      //缺盐指示图标
#define WATER_ICON       0x08      //缺水指示图标
#define BLEACH_ICON      0x10      //缺漂洗剂指示图标
#define OFF_ICON        0x00      //不显示指示图标

typedef struct
{
     unsigned int delay_sec;//倒计时时间单位s
     unsigned char hour_cnt;
     unsigned char min_cnt;
     unsigned char sec_cnt;
}COUNT_DOWN;
extern COUNT_DOWN Delay_Count;
void tm1640_show_cls(void);
void tm1640_show_fully(void);
void tm1640_show_num(unsigned int num);
void tm1640_show_time(void);
void tm1640_show_character(unsigned char num,unsigned char on_off);
void tm1640_show_icon(unsigned char num);
void tm1640_test(void);


#endif
