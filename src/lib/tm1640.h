#ifndef _TM1640__H_
#define _TM1640__H_

/**********TM1640************/
#define DIN(x)      P2_5=(x)
#define SCLK(x)     P2_4=(x)

#define DATA_MODE1     0x40    //��ַ�Զ���1ģʽ
#define DATA_MODE2     0x44    //�̶���ַģʽ

#define LUM         6//���ȷ�Χ(0~7)7����

#define TM1640_ON      (0x88+LUM)   //��ʾ��
#define TM1640_OFF     0x80    //��ʾ��

#define NUMBERR1_COM     0xc0   //�����1�ĵ�ַ
#define NUMBERR2_COM     0xc1   //�����2�ĵ�ַ   
#define NUMBERR3_COM     0xc2   //�����3�ĵ�ַ
#define NUMBERR4_COM     0xc3   //�����4�ĵ�ַ

#define WASH1_CHARACTERC     0xc4   //ǿ��ϴͼ���ַ
#define WASH2_CHARACTERC     0xc5   //�ճ�ϴͼ���ַ
#define WASH3_CHARACTERC     0xc6   //��ʱϴͼ���ַ
#define WASH4_CHARACTERC     0xc7   //����ϴͼ���ַ
#define WASH5_CHARACTERC     0xc8   //����ϴͼ���ַ
#define WASH1_OFF            0x00   //����ʾϴͼ��
#define WASH1_ON             0x0f   //��ʾϴͼ��

#define SALT_ICON        0x20      //ȱ��ָʾͼ��
#define WATER_ICON       0x08      //ȱˮָʾͼ��
#define BLEACH_ICON      0x10      //ȱƯϴ��ָʾͼ��
#define OFF_ICON        0x00      //����ʾָʾͼ��

typedef struct
{
     unsigned int delay_sec;//����ʱʱ�䵥λs
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
