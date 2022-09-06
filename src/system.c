#include "include_s.h"

u8 system_state;
KEY_FLAG_T Key_Flag_Sys;
ROBAM_T Robam_info;
DEVICE_IF	device_info;
STATUS_RT	status_info;
u8 pon_2s=200;
u16 pon_3s=300;
u8 robam_state;   //烟机开关状态       
u8 robam_gear;    //烟机档位
u8 robam_gear_old;
u16 robam_delay;  //烟机延时时间
u32 add_50hour_up;   //烟机运行总时间
u8 buzz_mode;
u8 pushrod_state;//推杆状态
u8 hour_twinkle;
u8 minute_twinkle;
u16 clock_eeprom;
//关机状态
static void power_off_task_function(void)
{
     static u8 execute_one=1;
     u8 hv = hg.hand_value;
     u8 kv = kb.key_value;
     //关机一次执行一次
     if(execute_one)
     {
          clear_all_output();
          execute_one=0;
     }
     //按键短按抬起和手势判断
      if (kb.key_state == skey_short_up || hg.hand_state==shand_new)
	{
		kb.key_state = skey_none; 
          hg.hand_state = shand_none;
          
          //开机
          if( (key_power==kv) ||( hand_right==hv && (3!=Key_Flag_Sys.key_power_flag && !Key_Flag_Sys.key_clock_flag)))
          {
                pon_2s=200;
                execute_one=1;
                buzz_mode=BUZZ_POWER_ON;
                system_state=TASK_SETTING;        //设置状态
          }
          //照明灯开
          else if(key_light == kv && 0==Key_Flag_Sys.key_light_flag)
          {
               key_led_light=true;
               Key_Flag_Sys.key_light_flag=1;
               buzz_mode=BUZZ_CLICK;
          }
          //照明灯关
          else if(key_light==kv && 1==Key_Flag_Sys.key_light_flag)
          {
               key_led_light=false;
               Key_Flag_Sys.key_light_flag=0;
               buzz_mode=BUZZ_CLICK;
          }
          //电源键长按3S后的状态
          else if(3==Key_Flag_Sys.key_power_flag && key_power==kv)
          {
               Key_Flag_Sys.key_power_flag=0;
               Key_Flag_Sys.key_down_flag=0;
               Key_Flag_Sys.key_up_flag=0;
               buzz_mode=BUZZ_CLICK;
          }
          //电源键长按3S后，关闭手势
          else if(3==Key_Flag_Sys.key_power_flag && key_down==kv)
          {
               hand_task.mode=0;
               Key_Flag_Sys.key_down_flag=1;
               pon_3s=300;
               buzz_mode=BUZZ_CLICK;
          }
           //电源键长按3S后，开启手势
          else if(3==Key_Flag_Sys.key_power_flag && key_up==kv)
          {
               Key_Flag_Sys.key_up_flag=1;
               hand_task.mode=1;
               pon_3s=300;
               buzz_mode=BUZZ_CLICK;
          }
          //时钟键长按3S后的状态
          else if(key_clock==kv && 1==Key_Flag_Sys.key_clock_flag)
          {
               Key_Flag_Sys.key_clock_flag=2;
               buzz_mode=BUZZ_CLICK;
               hour_twinkle=false;
          }
           //时钟键长按3S后，再按一次的状态
          else if(key_clock==kv && 2==Key_Flag_Sys.key_clock_flag)
          {
               Key_Flag_Sys.key_clock_flag=0;
               key_led_clock=false;
               hour_twinkle=false;
               minute_twinkle=false;
			clock.second=0;
               clock_eeprom=clock.hour*100+clock.minute;
               save_clock_onoff(clock_eeprom);
               buzz_mode=BUZZ_CLICK;
          }
          //时钟键长按3S后，加键改变时钟的小时数
          else if(key_up==kv && 1==Key_Flag_Sys.key_clock_flag)
          {
               if (++clock.hour >= 24)
               {
                    clock.hour = 0;
               }
               buzz_mode=BUZZ_CLICK;
          }
          //时钟键长按3S后，减键改变时钟的小时数
          else if(key_down==kv && 1==Key_Flag_Sys.key_clock_flag)
          {
              if (clock.hour-- <= 0)
               {
                    clock.hour = 23;
               }
               buzz_mode=BUZZ_CLICK;
          }
            //时钟键长按3S后，再按一次，加键改变时钟的分钟数
          else if(key_up==kv && 2==Key_Flag_Sys.key_clock_flag)
          {
               if (++clock.minute >= 60)
			{
				clock.minute = 0;
               } 
                buzz_mode=BUZZ_CLICK;
          }
           //时钟键长按3S后，再按一次，减键改变时钟的分钟数
          else if(key_down==kv && 2==Key_Flag_Sys.key_clock_flag)
          {
              if (clock.minute-- <= 0)
               {
                    clock.minute = 59;
               }
               buzz_mode=BUZZ_CLICK;
          }
     }
    //按键长按3s 
     if(kb.key_state == skey_3s_dn)
     {
          kb.key_state = skey_none; 
          buzz_mode=BUZZ_CLICK;
          //电源键长按3s，且烟机关闭，进入手势设定模式
          if(key_power==kv && 0==robam_state)
          {
               pon_3s=300;
               Key_Flag_Sys.key_power_flag=3;//手势设定状态
               key_led_power=true;
          }
           //时钟键长按3s，进入时钟调节设置，
          else if(key_clock==kv && 0==Key_Flag_Sys.key_clock_flag)
          {
               Key_Flag_Sys.key_clock_flag=1;
               key_led_clock=true;
          }
          //关闭报警
          else if(key_clean==kv && 180000==add_50hour_up)
          {
               add_50hour_up=0;
               key_led_clean=false;
          }
     }
     //手势设定模式无操作3s倒计时
     if(3==Key_Flag_Sys.key_power_flag && false==kv)
     {
          u16_dn(&pon_3s);
     }
      //判断是否关闭手势设定模式
     if(3==Key_Flag_Sys.key_power_flag && 0==pon_3s)
     {
          Key_Flag_Sys.key_power_flag=0;
          Key_Flag_Sys.key_down_flag=0;
          Key_Flag_Sys.key_up_flag=0;
          key_led_up=false;
          key_led_down=false;
          key_led_power=false;
     }
    
}
//设置状态
static void setting_task_function(void)
{
     u8 hv = hg.hand_value;
     u8 kv = kb.key_value;
     //第一次开机状态   
     if(0==Key_Flag_Sys.key_power_flag)
     {
          key_led_power=true;
          key_led_down=true;
          key_led_up=true;
          robam_state=true;        //烟机开启
//          robam_gear=5;            //烟机档位,有记忆档位
          tm16xx_clser();
          Down_Tmer.start=0;
          Down_Tmer.show=0;
          Key_Flag_Sys.key_power_flag=1;
          
     }  
//按键处理    
     if (kb.key_state == skey_short_up||hg.hand_state == shand_new)
	{
		kb.key_state = skey_none; 
          hg.hand_state = shand_none;
/*********************************电源键********************************************/                               
          //烟机延时
          if(key_power==kv && 1==Key_Flag_Sys.key_power_flag)
          {
               robam_delay=180;
               Down_Tmer.start=1;
               Down_Tmer.show=1;
               Down_Tmer.delay_sec=robam_delay;//延时3分钟
               Key_Flag_Sys.key_power_flag=2;//延时状态
               buzz_mode=BUZZ_CLICK;
          }
          //关机
          else if((key_power==kv || hand_left == hv)&& 2==Key_Flag_Sys.key_power_flag)
          {
                system_state=TASK_POWEROFF;        
                robam_state=false;        //烟机关闭
                robam_gear=0;
                Key_Flag_Sys.key_power_flag=0;
                Down_Tmer.show=1;
                Down_Tmer.start=0;
                buzz_mode=BUZZ_POWER_OFF;
          }
          //延时关闭启动时，向右调为6挡
          else if( hand_right == hv && 2==Key_Flag_Sys.key_power_flag)
          {
                robam_gear=6;
                Down_Tmer.start=0;
                Down_Tmer.show=0;
          }
          
/****************************延时关闭未启动时，设置档位***************************************/

/*********************************减档********************************************/ 
          else if((key_down == kv || hand_left == hv) && 1==Key_Flag_Sys.key_power_flag)
          {
                robam_gear--;
                lim_min_8(&robam_gear,0);
                Down_Tmer.start=0;
                Down_Tmer.show=0;
                buzz_mode=BUZZ_CLICK;
                save_level_onoff(robam_gear);
          }
/*********************************加档********************************************/ 
          else if((key_up == kv ||  hand_right == hv) && 1==Key_Flag_Sys.key_power_flag)
          {
               robam_gear++;//风机档位
               lim_max_8(&robam_gear,8);
               Down_Tmer.start=0;
               Down_Tmer.show=0;
               buzz_mode=BUZZ_CLICK;
               save_level_onoff(robam_gear);
          }
/****************************延时关闭启动时，设置延时时间***************************************/ 

/*********************************减档********************************************/ 
          else if((key_down == kv || hand_left == hv) && 2==Key_Flag_Sys.key_power_flag)
          {
                robam_delay-=60;
                Down_Tmer.start=1;
                Down_Tmer.show=1;
                Down_Tmer.delay_sec=robam_delay;
          }
/*********************************加档********************************************/ 
          else if((key_up == kv ||  hand_right == hv) && 2==Key_Flag_Sys.key_power_flag)
          {
               robam_delay+=60;
               Down_Tmer.start=1;
               Down_Tmer.show=1;
               Down_Tmer.delay_sec=robam_delay;
          }
/*********************************爆炒键********************************************/          
          else if(key_fried == kv && 0==Key_Flag_Sys.key_fried_flag )
          {
               key_led_fried=true;
               Down_Tmer.delay_sec=180;//延时3分钟
               Down_Tmer.start=1;
               Down_Tmer.show=1;
               robam_gear_old=robam_gear;
               robam_gear=9;//爆炒档
               Key_Flag_Sys.key_fried_flag=1;
               buzz_mode=BUZZ_CLICK;
          }
          else if(key_fried == kv && 1== Key_Flag_Sys.key_fried_flag)
          {
               Key_Flag_Sys.key_fried_flag=0;
               Down_Tmer.start=0;
               Down_Tmer.show=0;
               robam_gear=robam_gear_old;//风机档位
               key_led_fried=false;
               buzz_mode=BUZZ_CLICK;
          }
/*********************************照明键********************************************/
          else if(key_light == kv && 0==Key_Flag_Sys.key_light_flag)
          {
               key_led_light=true;
               Key_Flag_Sys.key_light_flag=1;
               buzz_mode=BUZZ_CLICK;
          }
          else if(key_light==kv && 1==Key_Flag_Sys.key_light_flag)
          {
               key_led_light=false;
               Key_Flag_Sys.key_light_flag=0;
               buzz_mode=BUZZ_CLICK;
          } 
           
      }
      //延时结束处理
     if (1==Down_Tmer.over )
     {
               Down_Tmer.over=0;
               buzz_mode=BUZZ_FINISH;
               if(1== Key_Flag_Sys.key_fried_flag)
               {
                    Key_Flag_Sys.key_fried_flag=0;
                    Down_Tmer.start=0;
                    Down_Tmer.show=0;
                    robam_gear=robam_gear_old;//风机档位
                    key_led_fried=false;
               }
               else if(2==Key_Flag_Sys.key_power_flag)
               {
                    system_state=TASK_POWEROFF;        //关机
                     Key_Flag_Sys.key_power_flag=0;
                     Down_Tmer.show=1;
                     Down_Tmer.start=0;
               }
     }
/*********************************清洗键********************************************/      
     if (kb.key_state == skey_3s_dn)
     {
          kb.key_state = skey_none; 
          buzz_mode=BUZZ_CLICK;
          if(key_clean==kv && 180000==add_50hour_up)
          {
               add_50hour_up=0;
               key_led_clean=false;
          }
     }
     switch(kv)
     {         
          case  9:robam_gear=1;break;
          case 10:robam_gear=2;break;
          case 11:robam_gear=3;break;
          case 12:robam_gear=4;break;
          case 13:robam_gear=5;break;
          case 14:robam_gear=6;break;
          case 15:robam_gear=7;break;
          case 16:robam_gear=8;break;    
     }
     if(kv>=9&&kv<=16)
     {
          save_level_onoff(robam_gear);//记忆
     }
 //显示光圈
      if( 0==Down_Tmer.show && 0==Down_Tmer.start)
      {
          tm16xx_show_3_num(robam_gear);
      }
     tm16xx_show_stall(robam_gear);  
}

static void run_task_function(void)
{
//     system_state=TASK_POWEROFF;
}
static void error_task_function(void)
{
//     system_state=TASK_POWEROFF;
}
static void toggle_task(void)
{
     if(system_500ms_f)
     {
          if(1==Down_Tmer.show)
          {
               tm16xx_show_colon();//冒号闪烁
          }
          if(180000==add_50hour_up)//清洗指示灯闪烁
          {
               if(key_led_clean) key_led_clean=false;
               else key_led_clean=true;
          }
          if(1==Key_Flag_Sys.key_up_flag)//加档指示灯闪烁
          {
               if(key_led_up) key_led_up=false;
               else key_led_up=true;
          }
          if(1==Key_Flag_Sys.key_down_flag)//键档指示灯闪烁
          {
               if(key_led_down) key_led_down=false;
               else key_led_down=true;
          }
          if(1==Key_Flag_Sys.key_clock_flag)//时钟小时闪烁
          {
                 if(hour_twinkle) hour_twinkle=false;
                 else hour_twinkle=true;
          }
          if(2==Key_Flag_Sys.key_clock_flag)//时钟分钟闪烁
          {
                 if(minute_twinkle) minute_twinkle=false;
                 else minute_twinkle=true;
          }
		if(2==Key_Flag_Sys.key_power_flag)//电源键闪烁
          {
               if(key_led_power) key_led_power=false;
               else key_led_power=true;
          }
     }
}
/******************************************************/
/******************************************************/
/******************** 系统任务调度 *********************/
/******************************************************/
/******************************************************/
void system_tasks(void)
{
    toggle_task();//翻转状态
    switch(system_state)
    {
    case TASK_POWEROFF:       //关机状态
        power_off_task_function();
        break;
    
    case TASK_SETTING:          //设置状态 
        
        setting_task_function();
        break;

    case TASK_WORK:                //工作状态
        run_task_function();
        break;
    
    case TASK_ERROR:               //错误状态
        error_task_function();
        break;

    default:
        system_state = TASK_POWEROFF;
    }


}

/******************************************************/
/******************************************************/
/***********************系统初始化**********************/
/******************************************************/
/******************************************************/
void reset_para_value(void)
{
     hand_task.mode=1;                 //手势开关
     Down_Tmer.start=0;         //倒计时开关
     Down_Tmer.show=1;       //显示开关
     hour_twinkle=false;          //时钟小时闪烁
     minute_twinkle=false;       //时钟分钟闪烁
     Key_Flag_Sys.key_power_flag=0;
     Key_Flag_Sys.key_linkage_flag=0;
     Key_Flag_Sys.key_clock_flag=0;
     Key_Flag_Sys.key_down_flag=0;
     Key_Flag_Sys.key_up_flag=0;
     Key_Flag_Sys.key_fried_flag=0;
     Key_Flag_Sys.key_clean_flag=0;
     Key_Flag_Sys.key_light_flag=0;
}

void system_init(void)
{
    clear_all_output();
    system_state=TASK_POWEROFF;
    panel_comm.cmd =FZKZ_FLAG;          //发送负载控制数据包
    buzz_mode=BUZZ_MACHINE_ON;      //上电
    protocol_init();
    touchkeyinit();
    clock_init(&clock);
    key_board_init(&kb);   
    Get_TK_Baseline(); 
    hand_gesture_init(&hg);
    reset_para_value();
}





