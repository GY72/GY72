/****************************************************************************
 * app_timer.c
 *
 * 	 Copyright (C) Hiklife. All rights reserved.
 *   Author: Lgx <lgx@hiklife.com>	2019-03
 * 
 *  系统时钟相关函数
 *
 ****************************************************************************/


#include "..\include_s.h"

/****************************************************************************
 * 全局变量
 ****************************************************************************/
iram CLOCK_t clock;
iram COUNT_DOWN_CLOCK Down_Tmer;
iram SYSTEM_TMR_t system_tmrs;
iram CYCLE_TMR_t cycle_tmr;

//iram bool base_5ms_f;
bool base_10ms_f;
bool half_sec_f;
bool sec_flash_f;

/* u8 rtc_err_ct;
bool rtc_err_f; */

bool rtc_sec_f;
/****************************************************************************
 * 内部变量
 ****************************************************************************/


/****************************************
 * 函数名：	delay_10us 
 * 说明：	不精确短延时
 * 输入：	u16 
 * 输出：	无
 ****************************************/
void delay_10us(u16 i)
{
	while(i--);
}

void robam_task_ctrl(void)															
{	
	static u16 add_15min_up = 0;
	if(robam_state)
	{
		if(system_sec_f)
		{
			add_50hour_up++;
			add_15min_up++;
		}
		if(add_50hour_up >= 180000)		//50小时
		{
			if(system_500ms_f)
			add_50hour_up = 180000;
		}
		
		if(add_15min_up>=900)
		{
			add_15min_up = 0;
			save_para_block();
		}
	}		
}
/****************************************
 * 函数名：	Down_Clock 
 * 说明：	倒计时时钟函数
 * 输入：	无
 * 输出：	无
 ****************************************/
 void Down_Clock(void)
 {
         if(Down_Tmer.start)
         {
                if (system_sec_f)
               {
                    Down_Tmer.hour_cnt=Down_Tmer.delay_sec/3600;
                    Down_Tmer.min_cnt=Down_Tmer.delay_sec/60;
                    Down_Tmer.sec_cnt=Down_Tmer.delay_sec%60;
                    num_value=Down_Tmer.min_cnt*100+Down_Tmer.sec_cnt;
                    if(0==Down_Tmer.delay_sec)
                    {
                          Down_Tmer.start=0;
                          Down_Tmer.show=0;
                          Down_Tmer.over=1;
                    }
                    else
                    {
                         Down_Tmer.over=0;
                         Down_Tmer.delay_sec--;
                    } 
              }
         }
          else
          {
               num_value=clock.hour*100+clock.minute;
          }
          if(Down_Tmer.show)
          {  
               tm16xx_show_num(num_value); 
          }
          
 }
 
/****************************************
 * 函数名：	Clock 
 * 说明：	24H时钟函数
 * 输入：	CLOCK_t 指针
 * 输出：	无
 ****************************************/
void Clock(CLOCK_t * clock)
{	
	if (run_sec_f)
	{//1S
		run_sec_f=0;
		if (++clock->second >= 60)
		{
			clock->second = 0;
               clock_eeprom=clock->hour*100+clock->minute;
               save_clock_onoff(clock_eeprom);
			if (++clock->minute >= 60)
			{
				clock->minute = 0;			//1分钟到

				if (++clock->hour >= 24)
				{
					clock->hour = 0;
				}
			}
		}
	}
    
}

/****************************************
 * 函数名：	clock_init 
 * 说明：	24H时钟初始化函数
 * 输入：	CLOCK_t 指针
 * 输出：	无
 ****************************************/
void clock_init(CLOCK_t * clock)
{
	clock->hour   = clock_eeprom/100;
	clock->minute = clock_eeprom%100;
	clock->second = 0;
}

/****************************************
 * 函数名：	TimerNms_count 
 * 说明：	系统定时标志函数，心跳时钟10ms
 * 输入：	无
 * 输出：	无
 ****************************************/
void TimerNms_count(void)
{//10ms调用一次
	static u8 nms_ct = 0;

	if (++cycle_tmr.tmr >= cycle_tmr.width) cycle_tmr.tmr = 0;

	system_tmrs.timer_flags_byte = 0;
    
	if (++nms_ct >= 100)
		nms_ct = 0;
	
	if (nms_ct & 1)							
		system_20ms_f = true;

	if ((nms_ct % 10) == 0)	
		system_100ms_f = true;

	if ((nms_ct == 0) || (nms_ct == 50))	
	{
		system_500ms_f = true;
		half_sec_f ^= 1;
	}

	if (nms_ct == 0) 
	{
		system_sec_f = true; 
		sec_flash_f ^= 1;
	}

//	system_sec_f = rtc_sec_f;
//	rtc_sec_f = false;

	/* if (rtc_err_f == false)	
	{
		system_sec_f = rtc_sec_f;

		if (system_100ms_f)
			u8_up(&rtc_err_ct);

		if (rtc_err_ct > 100)
			rtc_err_f = true;
	} */

	//	TOGGLE_TEST_PIN;
}














