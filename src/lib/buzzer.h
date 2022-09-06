
#ifndef BUZZER_H
#define BUZZER_H

#define MUSIC_BUZZ 1

extern u8 buzz_step;

#define BEEP_REATE_FREQ          1500000ul    //12Mhz 8分频 PWM Out

#define BUZZ_PWR_PIN   P3_6
#define BUZZ_FRQ_PIN   P3_5

#define BUZZ_PWR_ON()      BUZZ_PWR_PIN = 1;//SETBANK1; BUZZ_PWR_PIN = 1; SETBANK0; 
#define BUZZ_PWR_OFF()     BUZZ_PWR_PIN = 0;//SETBANK1; BUZZ_PWR_PIN = 0; SETBANK0; 

#define BUZZ_FRQ_OFF()     BUZZ_FRQ_PIN = 0;//SETBANK1; BUZZ_FRQ_PIN = 0; SETBANK0;        

#if MUSIC_BUZZ

  #define FREQ_NO 	  0xff

  #define BUZZ_MACHINE_ON 1
  #define BUZZ_POWER_ON   2
  #define BUZZ_POWER_OFF  3
  #define BUZZ_CLICK      4
  #define BUZZ_ALARM      5
  #define BUZZ_FINISH     6

  typedef struct
  {
    u16 freq;                   //频率
    u16 PWRON_time;             //供电持续时间
    u16 PWROFF_time;            //音调总时间，频率持续输出
  }TONE_t;                      //音调结构体

  /***************************************************************/
  //需要修改的接口函数
  void music_buzz_PwrOn(void);      
  void music_buzz_PwrOff(void);
  void music_buzz_FrqOff(void);
  void music_buzz_SetFreq(u16 f);

  /***************************************************************/
  //音乐蜂鸣器启动函数
  void music_buzz_start(u8 type);
  //音乐蜂鸣器控制函数 10ms调用一次
  void music_buzz_ctrl(void);
  //音乐蜂鸣器初始化函数
  void music_buzz_init(void);

  #define buzz_start(mode) music_buzz_start(mode)
  #define buzz_ctrl()      music_buzz_ctrl()
  #define buzz_init()      music_buzz_init()

#else

  /***************************************************************/
  //需要修改的管脚 PWM 4KHz 设置参数
  #define F_4KHZ         255//(PWM_FREQ/4000)	      //(Fpwm/(4*1000))
  /***************************************************************/
  #define TOTAL_BUZZ_N  7

  #define BUZZ_SHORT  0
  #define BUZZ_1S     1
  #define BUZZ_3S     2
  #define BUZZ_5S     3
  #define BUZZ_3ST    4
  #define BUZZ_5LN    5

  #define BUZZ_OK      0
  #define BUZZ_WARNING 4
  #define BUZZ_ALARM   6

  typedef struct
  {
    u16 on_time;               
    u16 off_time;              
  }Buzz_t;   

  /***************************************************************/
  //需要修改的接口函数
  void buzz_on(void);
  void buzz_off(void);

  /***************************************************************/
  //普通蜂鸣器启动函数
  void normal_buzz_start(u8 type);
  //普通蜂鸣器控制函数 10ms调用一次
  void normal_buzz_ctrl(void);
  //普通蜂鸣器初始化函数
  void normal_buzz_init(void);

  #define buzz_start(mode) normal_buzz_start(mode)
  #define buzz_ctrl()      normal_buzz_ctrl()
  #define buzz_init()      normal_buzz_init()

#endif

/***************************************************************/


#endif

































