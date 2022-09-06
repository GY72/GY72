#ifndef APP_TIMER_H
#define APP_TIMER_H

typedef struct{
    u8 hour;
    u8 minute;
    u8 second;
}CLOCK_t;

typedef union
{
    struct {
        char timer_20ms_f   :1 ;
        char timer_50ms_f   :1 ;
        char timer_100ms_f  :1 ;
        char timer_500ms_f  :1 ;
        char timer_second_f :1 ;
    }timer_flags;

    u8 timer_flags_byte;
}SYSTEM_TMR_t;

typedef struct
{
     unsigned int delay_sec;  //倒计时总时间，单位s
     unsigned char hour_cnt;
     unsigned char min_cnt;
     unsigned char sec_cnt;
     unsigned char start;
     unsigned char show;
     unsigned char over;
}COUNT_DOWN_CLOCK;

typedef struct 
{
    u16 tmr;
    u16 width;
}CYCLE_TMR_t;

extern iram CLOCK_t clock;

extern iram SYSTEM_TMR_t system_tmrs;
extern iram CYCLE_TMR_t  cycle_tmr;
extern iram COUNT_DOWN_CLOCK Down_Tmer;
//extern iram bool base_5ms_f;
extern bool base_10ms_f;
extern bool half_sec_f;
extern bool sec_flash_f;

/* extern u8 rtc_err_ct;
extern bool rtc_err_f; */
extern bool rtc_sec_f;

#define system_20ms_f   (system_tmrs.timer_flags.timer_20ms_f)
//#define system_50ms_f   (system_tmrs.timer_flags.timer_50ms_f)
#define system_100ms_f  (system_tmrs.timer_flags.timer_100ms_f)
#define system_500ms_f  (system_tmrs.timer_flags.timer_500ms_f)
#define system_sec_f    (system_tmrs.timer_flags.timer_second_f)
/***************************************************************
 *  接口函数
 ***************************************************************/
//非精确死延时
void delay_10us(u16 i);

//10ms调用一次
void TimerNms_count(void);

//需要24h时钟时，10ms调用一次
void Clock(CLOCK_t * clock);     

//需要24h时钟时，初始化时调用 
void clock_init(CLOCK_t * clock);

//倒计时
void Down_Clock(void);

//烟机运行计时
void robam_task_ctrl(void)	;
														
#endif





















