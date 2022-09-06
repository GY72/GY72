/****************************************************************************
 * buzzer.c
 *
 * 	 Copyright (C) Hiklife. All rights reserved.
 *   Author: Lgx <lgx@hiklife.com>	2019-03
 * 
 *  蜂鸣器相关函数
 *
 ****************************************************************************/

#include "..\include_s.h"

/***************************************************************/
u8 buzz_step;

#if MUSIC_BUZZ	//音乐蜂鸣器
static TONE_t crom * pTone;

/****************************************
 * 函数名：	music_buzz_FrqOff
 * 说明：	音乐蜂鸣器频率输出关
 * 输入：	--
 * 输出：	--
 ****************************************/
void music_buzz_FrqOff(void)
{
	BUZZ_FRQ_OFF();

	PWM0DL = 0;
	PWM0DH = 0;
	PWM0CON = 0;
}

/****************************************
 * 函数名：	music_buzz_SetFreq
 * 说明：	音乐蜂鸣器频率输出设置
 * 输入：	u8 PWM频率/音调频率
 * 			Fpwm 	=   Fsys / PWM分频
 * 			PWM 周期: 	Fpwm / F (目标频率)
 * 输出：	无
 ****************************************/
void music_buzz_SetFreq(u16 f)
{
	PWM0PL = LOBYTE(f);
	PWM0PH = HIBYTE(f);
	PWM0DL = LOBYTE(f>>1);
	PWM0DH = HIBYTE(f>>1);

    PWM0CON = bit10011001;			// 8分频 PWM Out
}

/* crom tone_freq_tbl[] = 
{
//   C7,  CS7,   D7,  DS7,   E7,   F7,  FS7,   G7,  GS7,   A7,  AS7,    B7  
//    1,   #1,    2,   #2,    3,    4,   #4,    5,   #5,    6,   #6,   ##1  
	2093, 2217, 2349, 2489, 2637, 2794, 2960, 3136, 3322, 3520, 3729, 3951
}; */

#define TONE_D5H	 622			//D调 re 高半音 d2#
#define TONE_E5		 659
#define TONE_F5		 698
#define TONE_F5H	 740
#define TONE_G5		 784
#define TONE_G5H	 831
#define TONE_A5		 880
#define TONE_A5H	 932
#define TONE_B5		 987

#define TONE_C6		1046
#define TONE_C6H	1109
#define TONE_D6		1175
#define TONE_D6H	1244
#define TONE_E6		1318
#define TONE_F6		1397
#define TONE_F6H	1480
#define TONE_G6		1568
#define TONE_G6H	1661				//---
#define TONE_A6		1760
#define TONE_A6H	1865
#define TONE_B6		1975

#define TONE_C7		2093
#define TONE_C7H	2217
#define TONE_D7		2349
#define TONE_D7H	2489
#define TONE_E7		2637
#define TONE_F7		2794				//===
#define TONE_F7H	2960
#define TONE_G7		3136
#define TONE_G7H	3322
#define TONE_A7		3520
#define TONE_A7H	3729
#define TONE_B7		3951		

crom TONE_t Tone1[] = {{2000, 60, 140}, {2500, 40, 100},{2000, 50, 120},{1500, 80, 1660},{FREQ_NO, 0, 0}};	//上电和弦音
crom TONE_t Tone2[] = {{1500, 50, 120}, {2000, 40, 100},{2500, 80, 1660},{FREQ_NO, 0, 0}};	//开机和弦音
crom TONE_t Tone3[] = {{2500, 50, 120}, {2000, 40, 100},{1500, 80, 1660},{FREQ_NO, 0, 0}};	//关机和弦音
crom TONE_t Tone4[] = {{2000, 140, 1500},{FREQ_NO, 0, 0}};	// 单音
crom TONE_t Tone5[] = {{2900, 140, 1500},{FREQ_NO, 0, 0}};  //ALARM WARNING
crom TONE_t Tone6[] = {{2500, 100, 240}, {2000, 100, 1260},{FREQ_NO, 0, 0}}; //finish 

crom TONE_t * tone_tbl[] = {Tone1,Tone2,Tone3,Tone4,Tone5,Tone6};
/****************************************
 * 函数名：	music_buzz_start
 * 说明：	音乐蜂鸣器启动输出
 * 输入：	声音类型索引
 * 输出：	--
 ****************************************/ 
void music_buzz_start(u8 type)
{
	buzz_step = 2;

	pTone = tone_tbl[type];

	buzz_step = 0;
}

/****************************************
 * 函数名：	music_buzz_ctrl
 * 说明：	音乐蜂鸣器控制函数 10ms调用一次
 * 输入：	声音类型索引
 * 输出：	--
 ****************************************/ 
void music_buzz_ctrl(void)
{
	static TONE_t Tone;

	switch (buzz_step)
	{
	case 0:
		Tone = *pTone;

		/* Tone.freq == freq_NO */ 			//是结束符
		if ((Tone.freq == FREQ_NO) || ((Tone.PWROFF_time == 0)))
		{
			buzz_step = 2;
			break;	
		}

		music_buzz_SetFreq(BEEP_REATE_FREQ/(Tone.freq));
		Tone.PWRON_time = Tone.PWROFF_time - Tone.PWRON_time;

		buzz_step = 1;
		break;

	case 1:
		if (Tone.PWROFF_time != 0)
		{
			Tone.PWROFF_time--;
			if (Tone.PWROFF_time < Tone.PWRON_time)
			{
				BUZZ_PWR_OFF();	
			}
			else
			{
				BUZZ_PWR_ON();
			}
		}
		else
		{
			pTone++; 				//取下一个音调
			buzz_step = 0;
		}
		break;

	default:
		BUZZ_PWR_OFF();	
		music_buzz_FrqOff();
		break;
	}
}

/****************************************
 * 函数名：	music_buzz_init
 * 说明：	音乐蜂鸣器初始化函数
 * 输入：	--
 * 输出：	--
 ****************************************/ 
void music_buzz_init(void)
{
	BUZZ_PWR_OFF();	
	music_buzz_FrqOff();
	buzz_step = 5;
}

/***************************************************************/
/***************************************************************/
/***************************************************************/
#else	//普通蜂鸣器
static Buzz_t crom * buzz;

/****************************************
 * 函数名：	BEEP_SetFreq
 * 说明：	普通蜂鸣器频率输出设置
 * 输入：	-- 固定4KHZ
 * 			Fpwm 	=   Fsys / PWM分频
 * 			PWM 周期: 	Fpwm / F (目标频率)
 * 输出：	无
 ****************************************/
void buzz_on(void)
{
	PWMP = 255;
	PWMD = 125;
	PWMCON = bit10110001;			// 16分频
}

/****************************************
 * 函数名：	BEEP_Off
 * 说明：	普通蜂鸣器频率输出关
 * 输入：	--
 * 输出：	--
 ****************************************/
void buzz_off(void)
{
	BUZZ_FRQ_OFF();
	PWM1DL = 0;
	PWM1DH = 0;
	PWM1CON = 0;
}

crom Buzz_t buzz0[] = {{ 30, 10}, {  0, 0}};
crom Buzz_t buzz1[] = {{100, 10}, {  0, 0}};
crom Buzz_t buzz2[] = {{300, 10}, {  0, 0}};
crom Buzz_t buzz3[] = {{500, 10}, {  0, 0}};
crom Buzz_t buzz4[] = {{ 10, 5}, { 10, 5},{ 10, 5},{0, 0}};
crom Buzz_t buzz5[] = {{100, 200},{100, 200},{100, 200},{100, 200},{100, 200},{0, 0}};
crom Buzz_t buzz6[] = {{ 10, 5}, { 10, 5},{0, 0}};

crom Buzz_t * buzz_type[] = {buzz0,buzz1,buzz2,buzz3,buzz4,buzz5,buzz6};

/****************************************
 * 函数名：	normal_buzz_start
 * 说明：	普通蜂鸣器启动输出
 * 输入：	声音类型索引
 * 输出：	--
 ****************************************/ 
void normal_buzz_start(u8 type)
{
 	if (type >= TOTAL_BUZZ_N) type = 0;

	buzz	  = buzz_type[type];
	buzz_step = 0;
}

/****************************************
 * 函数名：	buzzctrl
 * 说明：	普通蜂鸣器控制函数 10ms调用一次
 * 输入：	声音类型索引
 * 输出：	--
 ****************************************/ 
void normal_buzz_ctrl(void)
{
	static Buzz_t Tone;

	switch (buzz_step)
	{
	case 0:
		Tone = *buzz;

		//是结束符
		if ((Tone.on_time == 0) && ((Tone.off_time == 0)))
		{
			buzz_step = 3;
			break;	
		}

		buzz_on();
		BUZZ_PWR_ON();
		buzz_step = 1;
		break;

	case 1:
		if (Tone.on_time != 0)
			Tone.on_time--;
		else
			buzz_step = 2;
		break;
	
	case 2:
		BUZZ_PWR_OFF();
		if (Tone.off_time != 0)
		{
			Tone.off_time--;
		}
		else
		{
			buzz++; 				//取下一个音调
			buzz_step = 0;
		}
		break;

	default:
		buzz_off();
		BUZZ_PWR_OFF();
		break;
	}
}

/****************************************
 * 函数名：	buzz_init
 * 说明：	普通蜂鸣器初始化函数
 * 输入：	--
 * 输出：	--
 ****************************************/ 
void normal_buzz_init(void)
{
	buzz_off();
	buzz_step = 5;
}

#endif

















































