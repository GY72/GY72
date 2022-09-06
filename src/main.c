#include "include_s.h"

void main(void)
{
     u8 pon_1s=100;//上电1s后才启用手势，原因是有块板子上电的时候会有手势信号
     EA=0;
     mcu_init();
     read_level_onoff(robam_gear);//读取烟机档位
     read_clock_onoff(clock_eeprom);
	read_para_block();//读取烟机运行总时间
     system_init();
     start_interrupts();
     while(1)
     {
          clear_wdt();
          if(base_10ms_f)
          {
               base_10ms_f=0;
               Down_Clock();
               Clock(&clock);
               TimerNms_count();
               robam_task_ctrl();  //烟机运行时间计时
               uart_packet_deal(&panel_comm);
               update_all_inputs();          //输入控制数据更新
               if(!pon_1s)
               {
                    if (hand_task.mode)
                    {
                         hand_gesture_scan(&hg);	
                    }
               }
               else
               {
                    pon_1s--;
               }
               if (pon_2s)
               {
                    pon_2s--;
                    leds.icon.byte=0xff;
                    if(!pon_2s)
                    leds.icon.byte=0;
               }
               else
               {
                    product_task();     //逻辑处理  
               }
               
               
               update_all_output();//输出控制数据，进行控制
          
          }
     }
}

static void fct_test_task(void)
{
    static u8 step = 0;
    static u16 step_tmr = 100;

    u8 kv = kb.key_value;
    u8 hv = hg.hand_value;
    u8_dn(&fct_cont_tmr);
    u16_dn(&step_tmr);
    if (step == 0)
    {   
        step_tmr = 200;
        step++;
        display_all();
        return;
    }

    if (step == 1)
    {
        display_all();
        if (step_tmr == 0)
        {    
            step_tmr = 60;
            step++;
        }

        return;
    }

    display_clear();
    if (step < (2+4))
    {
        if (step_tmr == 0)
        {    
            step_tmr = 60;
            step++;
            colon_overturn=2;
        }
        switch (step-2)
        {
             case 0: tm16xx_show_hex(0x8aaa); break;
             case 1: tm16xx_show_hex(0xa8aa); break;
             case 2: tm16xx_show_hex(0xaa8a); break;
             case 3: tm16xx_show_hex(0xaaa8); break;
        }
        return;
    }

    if (step < (2+4+10))
    {
        if (step_tmr == 0)
        {    
            step_tmr = 60;
            step++;
        }

        tm16xx_show_num((step-6)*1111);
        return;
    } 

    if (step < (2+4+10+8))
    {
        if (step_tmr == 0)
        {    
            step_tmr = 60;
            step++;
        }
        switch (step-16)
        {
             case 0: key_led_power = true; break;
             case 1: key_led_linkage = true; break;
             case 2: key_led_clock = true; break;
             case 3: key_led_down  = true; break;
             case 4: key_led_up  = true; break;
             case 5: key_led_fried  = true; break;
             case 6: key_led_clean  = true; break;
             case 7: key_led_light = true; break;   
        }
        return;
    }
    if (step < (2+4+10+8+9))
    {
        if (step_tmr == 0)
        {    
            step_tmr = 60;
            step++;
        }
        tm16xx_show_stall(step-24); 
        return;
    }    
    if (hv == hand_right)  key_led_power  = true;
    if (hv == hand_left)  key_led_light  = true;     
    if (kv == key_power)  key_led_power  = true; 
    if (kv == key_linkage)key_led_linkage    = true; 
    if (kv == key_clock)  key_led_clock    = true;
    if (kv == key_down)   key_led_down    = true;
    if (kv == key_up)     key_led_up    = true;
    if (kv == key_fried)  key_led_fried    = true;
    if (kv == key_clean)  key_led_clean    = true;
    if (kv == key_light)  key_led_light    = true;
    if (kv == key_1  )    tm16xx_show_stall(key_1-8);
    if (kv == key_2  )    tm16xx_show_stall(key_2-8);
    if (kv == key_3  )    tm16xx_show_stall(key_3-8);
    if (kv == key_4  )    tm16xx_show_stall(key_4-8);
    if (kv == key_5  )    tm16xx_show_stall(key_5-8);
    if (kv == key_6  )    tm16xx_show_stall(key_6-8);
    if (kv == key_7  )    tm16xx_show_stall(key_7-8);
    if (kv == key_8  )    tm16xx_show_stall(key_8-8);		
    if(0==fct_cont_tmr)
    {
        colon_overturn=0;
        tm16xx_show_hex(0xbcdd);//显示PASS
    }
}

void product_task(void)
{
     
     if (0x55 == fct_state)
    {
        fct_test_task();
        return;
    }
    system_tasks();                                         //产品控制逻辑代码
}