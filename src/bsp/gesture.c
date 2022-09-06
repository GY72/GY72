#include "..\include_s.h"


u16 gesture_left_count=0,gesture_right_count=0;
void gesture_pwm_off(void)
{
	PWM0CON &=~(1<<7) ;
     
     SETBANK1;
	PWM1CON &=~(1<<7);
     SETBANK0;
}

void gesture_pwm_on(void)
{
	PWM0CON |=(1<<7);
     
     SETBANK1;
	PWM1CON |=(1<<7);
     SETBANK0;
}


//500us调用一次
void gesture_ctrl(void)
{
     static u8 gesture_time=8;
     static u8 gesture_off_time=7;
     
     if ( gesture_time!=0 )
     {
          gesture_time--;
          if (gesture_time < gesture_off_time)
          {
               gesture_pwm_off();
          }
          else
          {
               gesture_pwm_on();
          }
     }
     else
     {
          gesture_time=8;
          gesture_off_time=7;
     }
}