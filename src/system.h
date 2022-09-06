
#ifndef _SYSTEM_H_
#define _SYSTEM_H_


//面板 软硬件版本，供FCT读取
#define SOFTWAER_VERSION    0x10
#define HARDWAER_VERSION    0x10

//系统状态
#define TASK_POWEROFF     0
#define TASK_SETTING      1
#define TASK_WORK         2
#define TASK_ERROR        3
#define TASK_DEBUG        4

//待机设置状态
#define SET_NORMAL        0
#define SET_MULTI         1
#define SET_COOKMENU      2
#define SET_LINK          3

//工作状态
#define WORK_PREHEAT      0
#define WORK_PAUSE        1
#define WORK_FINISH       2



typedef struct{
	u8  light_level;	//照明档位
	u8  ffan_level;	    //风机运行档位
	u8  error_code;	    //故障代码
	u16 fb_current;	    //翻板电机采样电流
	u8  reserve1;		//预留1
	u16 fan_power;		//风机功率
	u16 fan_speed;		//风机转速
	u8  ipm_temp;		//IPM温度
	u8  boost;		//是否增压
}STATUS_RT;			    //返回数据包		

typedef struct {
     u8 push_t;          //推杆运行时间
     u8 push_i;          //推杆堵转电流
     u8 push_control;      //推杆控制
     u8 robam_control;   //烟机控制
    u8  light_control;		//照明控制
    u8  robam_level;		//风机档位
    u8 buzzer_control;        //蜂鸣器控制
	u8	warm_elec;		     //电加热
	u8  reserved;	     //预留
}ROBAM_T;

typedef struct{
	u8	soft_edition;	//软件版本
	u8	hard_edition;	//硬件版本
	u8	beep_type;		//蜂鸣器种类
	u8	fffan_level;	//风机档位
}DEVICE_IF;

typedef struct {
    u8  powon_tmr;
    u8  state;      
    u16 state_tmr;
}TASK_POWOFF_t;


typedef struct {
    u8  key_power_flag;              
    u8  key_linkage_flag;
    u8  key_clock_flag;
    u8  key_down_flag;
    u8  key_up_flag;
    u8  key_fried_flag;
    u8  key_clean_flag;
    u8  key_light_flag;
}KEY_FLAG_T;


extern KEY_FLAG_T Key_Flag_Sys;
extern DEVICE_IF device_info;
extern STATUS_RT status_info;
extern ROBAM_T Robam_info;
extern u8 pon_2s;
extern u8 robam_state;   //烟机开关状态 
extern u8 robam_gear;    //烟机档位      
extern u32 add_50hour_up;   //烟机运行总时间
extern u8 buzz_mode;//蜂鸣器
extern u8 pushrod_state;//推杆状态
extern u8 hour_twinkle;
extern u8 minute_twinkle;
extern u16 clock_eeprom;
void system_init(void);
void system_tasks(void);
void reset_para_value(void);
void buzz_daemon_out(void);

void product_task(void);

#endif

