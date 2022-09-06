#include "../Lib/sino_touchkey.h"
#include "../Inc/sino_Timer.h"
#include "../Inc/mcu_sys_regsiter.h"   //MCU头文件加载...
#include "intrins.h"

bit     f_5ms;

#if    chip_sel <	L_chip_sel1XX
#define	time3_intver 11
#elif  chip_sel <   L_chip_sel2XX
#define	time3_intver 11
#else
#define	time3_intver 5
#endif
///////////////////////////////////////
//
// timer3中断程序
//
///////////////////////////////////////
void isr_timer3() interrupt time3_intver
{
_push_(INSCON);
INSCON=0X00;   
	f_5ms  = 1;

_pop_(INSCON);
}



///////////////////////////////////////
//
// timer初始化
//
///////////////////////////////////////
void timerinit()
{
    f_5ms = 0;
#if chip_sel <L_chip_sel1XX
	SETBANK1;
	T3CON = 0x30;
    TL3 = 0xBC; //5ms interrupt for TK
	TH3 = 0xFE;
    TR3 = 1;
    SETBANK0;       
    IEN1 |= 0x10;  //TIMER3 开启   
#elif chip_sel <L_chip_sel2XX   
	T3CON = 0x30;
    TL3 = 0x2B; //5ms interrupt for TK
	TH3 = 0xFE;
    TR3 = 1;
    IEN1=0x10;      
#else
	SETBANK1;
	T3CON = 0x30;
    TL3 = 0x2B;  //5ms interrupt for TK
	TH3 = 0xFE;
    TR3 = 1;
    SETBANK0;
    ET3=1;

#endif
}

