
#include "..\include_s.h"

/***************************************************/
#define TM16xx_DIO    P2_7
#define TM16xx_CLK    P2_6
#define TM16xx_STB    P4_1

/***************************************************/
// 8 + n * 18

u16 num_value=0;
u8 colon_overturn=2;
crom u16 Led_Num[]=
{
     LED_A|LED_B|LED_C|LED_D|LED_E|LED_F,
     LED_B|LED_C,
     LED_A|LED_B|LED_D|LED_E|LED_G,
     LED_A|LED_B|LED_C|LED_D|LED_G,
     LED_B|LED_C|LED_F|LED_G,
     LED_A|LED_C|LED_D|LED_F|LED_G,
     LED_A|LED_C|LED_D|LED_E|LED_F|LED_G,
     LED_A|LED_B|LED_C,
     LED_A|LED_B|LED_C|LED_D|LED_E|LED_F|LED_G,
     LED_A|LED_B|LED_C|LED_D|LED_F|LED_G,
     0,
     LED_A|LED_B|LED_E|LED_F|LED_G,                              //P
     LED_A|LED_B|LED_C|LED_E|LED_F|LED_G,   //A
     LED_A|LED_C|LED_D|LED_F|LED_G,   //S
};

crom u16 Led_Circle[]=
{
     0x00,
     LED_A|LED_B,
     LED_A|LED_B|LED_C|LED_D,
     LED_A|LED_B|LED_C|LED_D|LED_E|LED_F,
     LED_A|LED_B|LED_C|LED_D|LED_E|LED_F|LED_G|LED_H,
};

u8 Led_Show[14];
static void n_nop(u8 n)
{
    while(n--);
}

static void send_byte(u8 dat)
{
    u8 i;

    for (i = 0; i < 8; i++)
    {
        TM16xx_DIO = (1 & dat) ? 1 : 0;
        dat >>= 1;
        
        TM16xx_CLK = 0;
        NOP();
        NOP();
        TM16xx_CLK = 1;
        NOP();
        NOP();
   }
}

/****************************************
 * 函数名：	tm16xx_drive
 * 说明：	更新TM1628显示数据
 * 输入：	--
 * 输出：	--
 ****************************************/
void tm16xx_drive(void)
{
     static u8 i;

    TM16xx_STB = 0;
    _nop_();
    _nop_();
    send_byte(0x03);                    //7 位 10 段
    
    TM16xx_STB = 1;
    _nop_();
    _nop_();
    TM16xx_STB = 0;
    _nop_();
    _nop_();
    send_byte(0x40);                    //地址自动加一
    TM16xx_STB = 1;
    _nop_();
    _nop_();
    TM16xx_STB = 0;
    _nop_();
    _nop_();
    send_byte(0xC0);               //起始地址
    
    for(i=0;i<14;i++)
    {
        send_byte(Led_Show[i]);
    }
    
    
    TM16xx_STB = 1;    
    _nop_();
    _nop_();

    TM16xx_STB = 0;
    _nop_();
    _nop_();
    send_byte(0x88+3);                    //开启显示0~7显示亮度
    
    TM16xx_STB = 1;
    
}

/****************************************
 * 函数名：	tm16xx_show_num
 * 说明：    四位数码管显示，配合tm16xx_drive函数使用
 * 输入：	0~9999
 * 输出：	--
 ****************************************/
void tm16xx_show_num(unsigned int num)
{      
    if(num<10000)
    {
         if(minute_twinkle)
         {
              Led_Show[6] =0;
              Led_Show[7] =0;
              Led_Show[8] =colon_overturn;               
              Led_Show[9] =0;
         }         
         else
         {
              Led_Show[6] =(u8)(Led_Num[num%10]);               
              Led_Show[7] =(u8)(Led_Num[num%10]>>8);              
              Led_Show[8] =(u8)(Led_Num[(num/10)%10]+colon_overturn);               
              Led_Show[9] =(u8)(Led_Num[(num/10)%10]>>8);
         }
         if(hour_twinkle)
         {
               Led_Show[10] =colon_overturn;
               Led_Show[11] =0;
               Led_Show[12] =0;               
               Led_Show[13] =0;
         }
         else
         {
               Led_Show[10] =(u8)(Led_Num[(num/100)%10]+colon_overturn);     //加二显示冒号          
               Led_Show[11] =(u8)(Led_Num[(num/100)%10]>>8); 
               Led_Show[12] =(u8)(Led_Num[num/1000]);               
               Led_Show[13] =(u8)(Led_Num[num/1000]>>8);
         }
         
    }
}
/****************************************
 * 函数名：	tm16xx_show_hex
 * 说明：    16进制数显示，配合tm16xx_drive函数使用
 * 输入：	0~0xffff
 * 输出：	--
 ****************************************/
void tm16xx_show_hex(unsigned int num)
{      
              Led_Show[6] =(u8)(Led_Num[num%16]);               
              Led_Show[7] =(u8)(Led_Num[num%16]>>8);              
              Led_Show[8] =(u8)(Led_Num[(num/16)%16]+colon_overturn);               
              Led_Show[9] =(u8)(Led_Num[(num/16)%16]>>8);
         
               Led_Show[10] =(u8)(Led_Num[(num/256)%16]+colon_overturn);     //加二显示冒号          
               Led_Show[11] =(u8)(Led_Num[(num/256)%16]>>8); 
               Led_Show[12] =(u8)(Led_Num[num/4096]);               
               Led_Show[13] =(u8)(Led_Num[num/4096]>>8);
}
/****************************************
 * 函数名：	tm16xx_show_3_num
 * 说明：    从左数第三个数码管显示，其余不显示，配合tm16xx_drive函数使用
 * 输入：	0~9999
 * 输出：	--
 ****************************************/
void tm16xx_show_3_num(unsigned char num)
{      
    Led_Show[6] =0;
    Led_Show[7] =0;
    Led_Show[8] =(u8)(Led_Num[num]);             
    Led_Show[9] =(u8)(Led_Num[num]>>8); 
    Led_Show[10] =0;
    Led_Show[11] =0;
    Led_Show[12] =0;               
    Led_Show[13] =0;
}

/****************************************
 * 函数名：	tm16xx_show_stall
 * 说明：	圆圈亮的范围，配合tm16xx_drive函数使用
 * 输入：	0~8
 * 输出：	--
 ****************************************/
void tm16xx_show_stall(u8 stall)
{
      if(stall)
      {
          Led_Show[2]&=~(u8)(LED_A|LED_B|LED_C|LED_D|LED_E|LED_F|LED_G|LED_H);
          Led_Show[3]&=~(u8)((LED_A|LED_B|LED_C|LED_D|LED_E|LED_F|LED_G|LED_H)>>8);
          Led_Show[4]&=~(u8)(LED_A|LED_B|LED_C|LED_D|LED_E|LED_F|LED_G|LED_H);
          Led_Show[5]&=~(u8)((LED_A|LED_B|LED_C|LED_D|LED_E|LED_F|LED_G|LED_H)>>8);
          
          Led_Show[0]&=~(u8)(LED_A|LED_B|LED_C|LED_D|LED_E|LED_F|LED_G|LED_H);
          Led_Show[1]&=~(u8)((LED_A|LED_B|LED_C|LED_D|LED_E|LED_F|LED_G|LED_H)>>8);
          Led_Show[0]&=~(u8)(LED_I);
          Led_Show[2]&=~(u8)(LED_I);
          Led_Show[4]&=~(u8)(LED_I);
          Led_Show[6]&=~(u8)(LED_I);
          Led_Show[8]&=~(u8)(LED_I);
          Led_Show[10]&=~(u8)(LED_I);
          Led_Show[6]&=~(u8)(LED_H);
          Led_Show[12]&=~(u8)(LED_I);
      }
         switch(stall)
         {
               case 0:   Led_Show[2]&=~(u8)(LED_A|LED_B|LED_C|LED_D|LED_E|LED_F|LED_G|LED_H);
                         Led_Show[3]&=~(u8)((LED_A|LED_B|LED_C|LED_D|LED_E|LED_F|LED_G|LED_H)>>8);
                         Led_Show[4]&=~(u8)(LED_A|LED_B|LED_C|LED_D|LED_E|LED_F|LED_G|LED_H);
                         Led_Show[5]&=~(u8)((LED_A|LED_B|LED_C|LED_D|LED_E|LED_F|LED_G|LED_H)>>8);
                         
                         Led_Show[0]&=~(u8)(LED_A|LED_B|LED_C|LED_D|LED_E|LED_F|LED_G|LED_H);
                         Led_Show[1]&=~(u8)((LED_A|LED_B|LED_C|LED_D|LED_E|LED_F|LED_G|LED_H)>>8);
                         Led_Show[0]&=~(u8)(LED_I);
                         Led_Show[2]&=~(u8)(LED_I);
                         Led_Show[4]&=~(u8)(LED_I);
                         Led_Show[6]&=~(u8)(LED_I);
                         Led_Show[8]&=~(u8)(LED_I);
                         Led_Show[10]&=~(u8)(LED_I);
                         Led_Show[6]&=~(u8)(LED_H);
                         Led_Show[12]&=~(u8)(LED_I);break;
               case 1:   
                         Led_Show[2]|=(u8)((LED_A|LED_B));
                         Led_Show[3]|=(u8)((LED_A|LED_B)>>8);
                         Led_Show[4]|=(u8)((LED_A|LED_B));
                         Led_Show[5]|=(u8)((LED_A|LED_B)>>8);
                         break;
                         
               case 2:   Led_Show[2]|=(u8)(LED_A|LED_B|LED_C|LED_D);
                         Led_Show[3]|=(u8)((LED_A|LED_B|LED_C|LED_D)>>8);
                         Led_Show[4]|=(u8)(LED_A|LED_B|LED_C|LED_D);
                         Led_Show[5]|=(u8)((LED_A|LED_B|LED_C|LED_D)>>8);
                         break;
                         
          case 3:   Led_Show[2]|=(u8)(LED_A|LED_B|LED_C|LED_D|LED_E|LED_F);
                         Led_Show[3]|=(u8)((LED_A|LED_B|LED_C|LED_D|LED_E|LED_F)>>8);
                         Led_Show[4]|=(u8)(LED_A|LED_B|LED_C|LED_D|LED_E|LED_F);
                         Led_Show[5]|=(u8)((LED_A|LED_B|LED_C|LED_D|LED_E|LED_F)>>8);
                         break;
                         
          case 4:   Led_Show[2]|=(u8)(LED_A|LED_B|LED_C|LED_D|LED_E|LED_F|LED_G|LED_H);
                         Led_Show[3]|=(u8)((LED_A|LED_B|LED_C|LED_D|LED_E|LED_F|LED_G|LED_H)>>8);
                         Led_Show[4]|=(u8)(LED_A|LED_B|LED_C|LED_D|LED_E|LED_F|LED_G|LED_H);
                         Led_Show[5]|=(u8)((LED_A|LED_B|LED_C|LED_D|LED_E|LED_F|LED_G|LED_H)>>8);
                         break;
                         
          case 5:   Led_Show[2]|=(u8)(LED_A|LED_B|LED_C|LED_D|LED_E|LED_F|LED_G|LED_H);
                         Led_Show[3]|=(u8)((LED_A|LED_B|LED_C|LED_D|LED_E|LED_F|LED_G|LED_H)>>8);
                         Led_Show[4]|=(u8)(LED_A|LED_B|LED_C|LED_D|LED_E|LED_F|LED_G|LED_H);
                         Led_Show[5]|=(u8)((LED_A|LED_B|LED_C|LED_D|LED_E|LED_F|LED_G|LED_H)>>8);
                         
                         Led_Show[0]|=(u8)(LED_A|LED_B);
                         Led_Show[1]|=(u8)((LED_A|LED_B)>>8);
                         Led_Show[6]|=(u8)(LED_H);
                         Led_Show[12]|=(u8)(LED_I);
                         break;
                         
          case 6:   Led_Show[2]|=(u8)(LED_A|LED_B|LED_C|LED_D|LED_E|LED_F|LED_G|LED_H);
                         Led_Show[3]|=(u8)((LED_A|LED_B|LED_C|LED_D|LED_E|LED_F|LED_G|LED_H)>>8);
                         Led_Show[4]|=(u8)(LED_A|LED_B|LED_C|LED_D|LED_E|LED_F|LED_G|LED_H);
                         Led_Show[5]|=(u8)((LED_A|LED_B|LED_C|LED_D|LED_E|LED_F|LED_G|LED_H)>>8);
                         
                         Led_Show[0]|=(u8)(u8)(LED_A|LED_B|LED_C|LED_D);
                         Led_Show[1]|=(u8)((LED_A|LED_B|LED_C|LED_D)>>8);
                         Led_Show[8]|=(u8)(LED_I);
                         Led_Show[10]|=(u8)(LED_I);
                         Led_Show[6]|=(u8)(LED_H);
                         Led_Show[12]|=(u8)(LED_I);
                         break;
                         
          case 7:   Led_Show[2]|=(u8)(LED_A|LED_B|LED_C|LED_D|LED_E|LED_F|LED_G|LED_H);
                         Led_Show[3]|=(u8)((LED_A|LED_B|LED_C|LED_D|LED_E|LED_F|LED_G|LED_H)>>8);
                         Led_Show[4]|=(u8)(LED_A|LED_B|LED_C|LED_D|LED_E|LED_F|LED_G|LED_H);
                         Led_Show[5]|=(u8)((LED_A|LED_B|LED_C|LED_D|LED_E|LED_F|LED_G|LED_H)>>8);
                         
                         Led_Show[0]|=(u8)(u8)(LED_A|LED_B|LED_C|LED_D|LED_E|LED_F);
                         Led_Show[1]|=(u8)((LED_A|LED_B|LED_C|LED_D|LED_E|LED_F)>>8);
                         Led_Show[4]|=(u8)(LED_I);
                         Led_Show[6]|=(u8)(LED_I);
                         Led_Show[8]|=(u8)(LED_I);
                         Led_Show[10]|=(u8)(LED_I);
                         Led_Show[6]|=(u8)(LED_H);
                         Led_Show[12]|=(u8)(LED_I);
                         break;
               
          case 8:   Led_Show[2]|=(u8)(LED_A|LED_B|LED_C|LED_D|LED_E|LED_F|LED_G|LED_H);
                         Led_Show[3]|=(u8)((LED_A|LED_B|LED_C|LED_D|LED_E|LED_F|LED_G|LED_H)>>8);
                         Led_Show[4]|=(u8)(LED_A|LED_B|LED_C|LED_D|LED_E|LED_F|LED_G|LED_H);
                         Led_Show[5]|=(u8)((LED_A|LED_B|LED_C|LED_D|LED_E|LED_F|LED_G|LED_H)>>8);
                         
                         Led_Show[0]|=(u8)(LED_A|LED_B|LED_C|LED_D|LED_E|LED_F|LED_G|LED_H);
                         Led_Show[1]|=(u8)((LED_A|LED_B|LED_C|LED_D|LED_E|LED_F|LED_G|LED_H)>>8);
                         Led_Show[0]|=(u8)(LED_I);
                         Led_Show[2]|=(u8)(LED_I);
                         Led_Show[4]|=(u8)(LED_I);
                         Led_Show[6]|=(u8)(LED_I);
                         Led_Show[8]|=(u8)(LED_I);
                         Led_Show[10]|=(u8)(LED_I);
                         Led_Show[6]|=(u8)(LED_H);
                         Led_Show[12]|=(u8)(LED_I);
                         break;
          case 9:   Led_Show[2]|=(u8)(LED_A|LED_B|LED_C|LED_D|LED_E|LED_F|LED_G|LED_H);
                         Led_Show[3]|=(u8)((LED_A|LED_B|LED_C|LED_D|LED_E|LED_F|LED_G|LED_H)>>8);
                         Led_Show[4]|=(u8)(LED_A|LED_B|LED_C|LED_D|LED_E|LED_F|LED_G|LED_H);
                         Led_Show[5]|=(u8)((LED_A|LED_B|LED_C|LED_D|LED_E|LED_F|LED_G|LED_H)>>8);
                         
                         Led_Show[0]|=(u8)(LED_A|LED_B|LED_C|LED_D|LED_E|LED_F|LED_G|LED_H);
                         Led_Show[1]|=(u8)((LED_A|LED_B|LED_C|LED_D|LED_E|LED_F|LED_G|LED_H)>>8);
                         Led_Show[0]|=(u8)(LED_I);
                         Led_Show[2]|=(u8)(LED_I);
                         Led_Show[4]|=(u8)(LED_I);
                         Led_Show[6]|=(u8)(LED_I);
                         Led_Show[8]|=(u8)(LED_I);
                         Led_Show[10]|=(u8)(LED_I);
                         Led_Show[6]|=(u8)(LED_H);
                         Led_Show[12]|=(u8)(LED_I);
                         break;
               default:      stall=0 ;break;
         }
}

/****************************************
 * 函数名：	tm16xx_clser
 * 说明：	清屏，配合tm16xx_drive函数使用
 * 输入：	--
 * 输出：	--
 ****************************************/
void tm16xx_clser(void)
{
    static u8 i;  
    for(i=0;i<14;i++)
    {
        Led_Show[i]=0x00;
    }
}
/****************************************
 * 函数名：	tm16xx_clser
 * 说明：	全亮，配合tm16xx_drive函数使用
 * 输入：	--
 * 输出：	--
 ****************************************/
void tm16xx_all_show(void)
{
    static u8 i;  
    for(i=0;i<14;i++)
    {
        Led_Show[i]=0xff;
    }
}
/****************************************
 * 函数名：	tm16xx_show_num_stall
 * 说明：	显示数字和光环长度，配合tm16xx_drive函数使用
 * 输入：	--
 * 输出：	--
 ****************************************/
void tm16xx_show_num_stall(u16 num,u8 stall)
{
     tm16xx_show_num(num);
     tm16xx_show_stall(stall);
}
/****************************************
 * 函数名：	tm16xx_show_colon
 * 说明：	调用该函数实现数码管冒号的亮灭翻转
 * 输入：	--
 * 输出：	--
 ****************************************/
void tm16xx_show_colon(void)
{
     if(colon_overturn)
     {
         colon_overturn=0;
     }
     else
     {
          colon_overturn=2;
     }     
}
