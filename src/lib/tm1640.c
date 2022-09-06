#include "..\include_s.h"

unsigned char Show_Num[]={0x3f,0x18,0x76,0x7c,0x59,0x6d,0x6f,0x38,0x7f,0x79};
COUNT_DOWN Delay_Count;

void delay(void)
{
     _nop_();
     _nop_();
     _nop_();
     _nop_();
     _nop_();
}
//��ʼ�ź�
void tm1640_start(void)
{
     SCLK(0);delay();
     DIN(1);delay();
     SCLK(1);delay();
     DIN(0);delay();
}

//�����ź�
void tm1640_end(void)
{
     SCLK(0);delay();
     DIN(0);delay();
     SCLK(1);delay();
     DIN(1);delay();
}


void tm1640_send_char(unsigned char buff)
{
     unsigned char i;
     
     for(i=0;i<8;i++)
     {
          SCLK(0);delay();
          DIN(0x01&(buff>>i));delay();
          SCLK(1);delay();
     }
}

void tm1640_send_command(unsigned char buff)
{
     tm1640_start();
     tm1640_send_char(buff);
     tm1640_end();
}

void tm1640_send_address(unsigned char buff)
{    
     tm1640_send_char(buff);
}



void tm1640_show_data(unsigned char address,unsigned char buff)
{
     tm1640_start();
     tm1640_send_address(address);
     tm1640_send_char(buff);
     tm1640_end();
}
//����
void tm1640_show_cls(void)
{
     unsigned char i;
     tm1640_send_command(DATA_MODE1);
     tm1640_start();
     tm1640_send_address(0xc0);
     for(i=0;i<16;i++)
     {
          tm1640_send_char(0x00);
     }
     tm1640_end();
     tm1640_send_command(TM1640_OFF);
}
//��ȫ��
void tm1640_show_fully(void)
{
     tm1640_show_num(8888);
     tm1640_show_character(WASH1_CHARACTERC,WASH1_ON);
     tm1640_show_character(WASH2_CHARACTERC,WASH1_ON);
     tm1640_show_character(WASH3_CHARACTERC,WASH1_ON);
     tm1640_show_character(WASH4_CHARACTERC,WASH1_ON);
     tm1640_show_character(WASH5_CHARACTERC,WASH1_ON);
     tm1640_show_icon(BLEACH_ICON|WATER_ICON|SALT_ICON);
}

//�������ʾ
//���룺Ҫ��ʾ����λ����
void tm1640_show_num(unsigned int num)
{
     if(num>9999)num=9999;
     tm1640_send_command(DATA_MODE2);
     tm1640_show_data(NUMBERR1_COM,Show_Num[num/1000]+0x80);
     tm1640_show_data(NUMBERR2_COM,Show_Num[(num/100)%10]+0x80);
     tm1640_show_data(NUMBERR3_COM,Show_Num[(num/10)%10]);
     tm1640_show_data(NUMBERR4_COM,Show_Num[num%10]);
     tm1640_send_command(TM1640_ON);    
}
//�������ʾʱ��
void tm1640_show_time(void)
{
     Delay_Count.hour_cnt=Delay_Count.delay_sec/3600;
     Delay_Count.min_cnt=Delay_Count.delay_sec/60;
     Delay_Count.sec_cnt=Delay_Count.delay_sec%60;
//     tm1640_show_num(Delay_Count.hour_cnt*100+Delay_Count.min_cnt);
     tm1640_show_num(Delay_Count.min_cnt*100+Delay_Count.sec_cnt);
     if(0 ==((Delay_Count.min_cnt*100+Delay_Count.sec_cnt)/1000))//����4λΪ0ʱ����������ʾ
     {
          tm1640_send_command(DATA_MODE2);
          tm1640_show_data(NUMBERR1_COM,0x80);
          tm1640_send_command(TM1640_ON);
     }
     
}

//ϴͼ����ʾ
//���룺Ҫ��ʾ��ͼ�꣬���ؿ���
void tm1640_show_character(unsigned char num,unsigned char on_off)
{
     tm1640_send_command(DATA_MODE2);
     tm1640_show_data(num,on_off);
     tm1640_send_command(TM1640_ON);  
}

//ָʾͼ����ʾ
//���룺Ҫ��ʾ��ͼ��
void tm1640_show_icon(unsigned char num)
{
     tm1640_send_command(DATA_MODE2);
     
     tm1640_show_data(0xc9,num);
     
     tm1640_send_command(TM1640_ON);
}

//������ʾ���������
void tm1640_test(void)
{
     static unsigned char i=0;
     static unsigned int adresee=0xc0;
     tm1640_send_command(DATA_MODE2);
     if(adresee<0xd0)
     {
        if(i<8)
        {
          tm1640_show_data(adresee,0x01<<i);
          i++;
        }
        else
        {
          i=0;
          adresee++;
        }
     }
     else
     {
          adresee=0xc0;
     }
     tm1640_send_command(TM1640_ON);  
}