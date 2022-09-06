
#include "..\include_s.h"


#define HAND_WAIT    0
#define HAND_ERROR   1

#define Invilid_tmr     50         //????(500ms):???????????,?????????????,?????????,??????
#define Error_tmr       1000        //????(10s):??????????????????,????????????????

Hand_Inst_t hg;
HAND_t  hand_task;
GESTURE_CHECK_t gc_left,gc_right;

void handtube_ctrl(void)
{
   //static u8 wave_ct = 0;
		static u8 hand0_ct = 0;
	
		static u8 hand1_ct = 0;
	
			if (hand_task.mode)
			{
				if(hand0_ct++>=7)
				{
					hand0_ct = 0;
					Enable_PWM0;
				}
				else
				{
					Disable_PWM0;
					PIN_send1 = 0;
				}
				
				if(hand1_ct++>=7)
				{
					hand1_ct = 0;
					INSCON |= bit01000000;
					Enable_PWM1;
					INSCON &= bit10111111;
				}
				else
				{
					INSCON |= bit01000000;
					Disable_PWM1;
					INSCON &= bit10111111;
					PIN_send2 = 0;
				}
				
			}
}

/****************************************
 * ???:	update_hand_gesture 
 * ??:	????
 * ??:	--
 * ??:	--
 ****************************************/
void update_hand_gesture(void)//100us
{
		if (!hand_task.mode)    return;
		
		if(gc_left.rise_flag)				//上升沿标志位开启，计算高电平时间
		{
			gc_left.high_ct++;
			if(gc_left.high_ct>=50)			//超过50*100us=5ms清0说明手势结束了
			{
				gc_left.rise_flag = 0;
				gc_left.high_ct = 0;
				hand_task.Left_status = 0;
			}
		}
		
		if(gc_left.fall_flag)						//下降沿标志位开启，计算低电平时间
		{
			gc_left.low_ct++;
		}
		
		if((gc_left.rise_ct == 2) && (gc_left.fall_ct == 2) )		//上升沿和下降沿皆为2个后 则为完整的低高低信号
		{
			gc_left.rise_ct = 0;
			gc_left.fall_ct = 0;
			
			if( (gc_left.L1>=3)&&(gc_left.L1 <=7) && (gc_left.H2>=30)&&(gc_left.H2<=40) && (gc_left.L3>=3)&&(gc_left.L3<=7) )		//低高低的长度在范围内 则触发手势
			{
				hand_task.Left_status = 1;
			}
			else
			{
				gc_left.L1 = 0;
				gc_left.H2 = 0;
				gc_left.L3 = 0;
			}
		}
		
		if (PIN_recvL)									//检测到高电平
		{
			gc_left.rise_cn = 1;
			if(gc_left.fall_cn)						//为上升沿 上升沿标志位开启 ，下降沿标志位关闭 ，取低电平的长度
			{
				gc_left.high_ct = 0;
				gc_left.fall_cn = 0;
				gc_left.rise_flag = 1;
				gc_left.fall_flag = 0;
				
				if(gc_left.rise_ct>2)
					gc_left.rise_ct = 0;
				else
					gc_left.rise_ct++;
				
				if(gc_left.rise_ct == 1)					//把低电平第一段时间取出来
					gc_left.L1 = gc_left.low_ct;
				else if(gc_left.rise_ct == 2)			//把低电平第二段时间取出来
					gc_left.L3 = gc_left.low_ct;
				/*if(i<=7)
				{
					i++;
					temp[i] = gesture_check->low_ct;
				}*/
			}
		}
		else															//检测到低电平
		{
			gc_left.fall_cn = 1;
			
			if(gc_left.rise_cn)							//为下降沿	下降沿标志位开启，上升沿标志位关闭，取高电平的长度
			{
				gc_left.low_ct = 0;
				gc_left.rise_cn= 0;
				gc_left.H2 = gc_left.high_ct;
				gc_left.fall_flag = 1;
				gc_left.rise_flag = 0;
				if(gc_left.fall_ct>2)
					gc_left.fall_ct = 0;
				else
					gc_left.fall_ct++;
			}

		}
		
		if(gc_right.rise_flag)						//上升沿标志位开启，计算高电平时间
		{
			gc_right.high_ct++;
			if(gc_right.high_ct>=50)			//超过50*100us=5ms清0说明手势结束了
			{
				gc_right.rise_flag = 0;
				gc_right.high_ct = 0;
				hand_task.Right_status = 0;
			}
		}
		
		if(gc_right.fall_flag)						//下降沿标志位开启，计算低电平时间
		{
			gc_right.low_ct++;
		}
		
		if((gc_right.rise_ct == 2) && (gc_right.fall_ct == 2) )		//上升沿和下降沿皆为2个后 则为完整的低高低信号
		{
			gc_right.rise_ct = 0;
			gc_right.fall_ct = 0;
			
			if( (gc_right.L1>=3)&&(gc_right.L1 <=7) && (gc_right.H2>=30)&&(gc_right.H2<=40) && (gc_right.L3>=3)&&(gc_right.L3<=7) )		//低高低的长度在范围内 则触发手势
			{
				hand_task.Right_status = 1;
			}
			else
			{
				gc_right.L1 = 0;
				gc_right.H2 = 0;
				gc_right.L3 = 0;
			}
		}
		
		if (PIN_recvR)									//检测到高电平
		{
			gc_right.rise_cn = 1;//上升沿
			if(gc_right.fall_cn)						//为上升沿 上升沿标志位开启 ，下降沿标志位关闭 ，取低电平的长度
			{
				gc_right.high_ct = 0;
				gc_right.fall_cn = 0;
				gc_right.rise_flag = 1;
				gc_right.fall_flag = 0;
				
				if(gc_right.rise_ct>2)
					gc_right.rise_ct = 0;
				else
					gc_right.rise_ct++;
				
				if(gc_right.rise_ct == 1)					//把低电平第一段时间取出来
					gc_right.L1 = gc_right.low_ct;
				else if(gc_right.rise_ct == 2)			//把低电平第二段时间取出来
					gc_right.L3 = gc_right.low_ct;
				/*if(i<=7)
				{
					i++;
					temp[i] = gesture_check->low_ct;
				}*/
			}
		}
		else															//检测到低电平
		{
			gc_right.fall_cn = 1;
			
			if(gc_right.rise_cn)							//为下降沿	下降沿标志位开启，上升沿标志位关闭，取高电平的长度
			{
				gc_right.low_ct = 0;
				gc_right.rise_cn= 0;
				gc_right.H2 = gc_right.high_ct;
				gc_right.fall_flag = 1;
				gc_right.rise_flag = 0;
				if(gc_right.fall_ct>2)
					gc_right.fall_ct = 0;
				else
					gc_right.fall_ct++;
			}

		}
}

/****************************************
 * ???:	hand_gesture_init 
 * ??:	?????
 * ??:	Hand_Inst_t?? 
 * ??:	--
 ****************************************/
void hand_gesture_init(Hand_Inst_t * hg)
{
    hg->hand_interval = 0;
    hg->hand_keep_ct = 0;
    hg->hand_state = 0;
    hg->hand_value = 0;
}

/****************************************
 * ???:	hand_up_deal 
 * ??:	??????
 * ??:	Hand_Inst_t?? 
 * ??:	--
 ****************************************/
static void hand_up_deal(Hand_Inst_t * hg)
{
	if (hg->hand_keep_ct >= HDS3D0SEC)				
		hg->hand_state = shand_long_up;				//??3?,????
	else if(hg->hand_keep_ct < HDS3D0SEC)
		hg->hand_state = shand_short_up;		    //??3?,????

	hg->hand_keep_ct = 0;							
}

/****************************************
 * ???:	hand_time_count 
 * ??:	??????
 * ??:	Hand_Inst_t?? 
 * ??:	--
 ****************************************/
void hand_time_count(Hand_Inst_t * hg)
{   
	hg->hand_keep_ct++;								
	hg->hand_interval++;

	switch (hg->hand_keep_ct)
	{
		case 1:
			hg->hand_state = shand_new;				//??
			break;

    case HDS1D0SEC:
			hg->hand_state = shand_1s_dn;			//??1s
			break;
		
    case HDS1D5SEC:
			hg->hand_state = shand_1s5_dn;			//??1.5s
			break;

		default:
      if (hg->hand_keep_ct > 500)
				hg->hand_keep_ct = 500;		        //
	}
}


u8 hand_scan(void)
{
    static u16 clear_wait_tmr = 0;
    static u8  first_one = 0;       //1:??????,2:??????
    static u8  gesture = 0;
    static u16 err_tmr = 0;
    static u8  shake_ct = 0;
    
    u16_dn(&clear_wait_tmr);
    
    if (hand_task.Left_status && hand_task.Right_status && !first_one)//左右手势都有第一次进入
    {
        first_one = 3;
        clear_wait_tmr = Invilid_tmr;
    }
    
    if (hand_task.Left_status)
    {
         if (!hand_task.Right_status)
         {
            if (first_one == 2 && clear_wait_tmr)
            {
                gesture = hand_left;
            }
            else if (first_one != 3)
            {
                first_one = 1;
            }
         }
				
         clear_wait_tmr = Invilid_tmr;
    }
    else if (first_one == 3 && hand_task.Right_status && clear_wait_tmr)
    {
        gesture = hand_right;
    }
    

    if (hand_task.Right_status)
    {
			 if (!hand_task.Left_status)
			 {
					if (first_one == 1 && clear_wait_tmr)
					{
							gesture = hand_right;
					}
					else if (first_one != 3)
					{
							first_one = 2;
					}
			 }
        
       clear_wait_tmr = Invilid_tmr;
			 
    }
    else if (first_one == 3 && hand_task.Left_status && clear_wait_tmr)
    {
        gesture = hand_left;
    }

    // if (!clear_wait_tmr)
    // {
    //     first_one = 0;
    // }
    
    if (!(hand_task.Left_status || hand_task.Right_status))//左右手势都没有为真
    {
        u8_up(&shake_ct);          //消抖两次
        if (shake_ct > 2)
        {
            if (gesture)
            {
                first_one = 0;
            }
            
            gesture = 0;
            err_tmr = 0;
        }
    }
    else
    {
        shake_ct = 0;
        u16_up(&err_tmr);
        if (err_tmr > Error_tmr)
        {
            gesture = shand_err;
            first_one = 0;
        }
    }

    return gesture;
}

bool hand_gesture_scan(Hand_Inst_t * hg)
{
    static  u8 old_scan_v = shand_none;
    static  u8 old_hand_v = shand_none;
    static  u8 scan_status = HAND_WAIT;

    unsigned char scanvaltmp;

    scanvaltmp = hand_scan();

    if (old_scan_v != scanvaltmp)
    {
        old_scan_v = scanvaltmp;
        return false;
    }
    
    if (scan_status == HAND_ERROR)
    {
        old_hand_v = shand_none;
        if (scanvaltmp == shand_none)
            scan_status = HAND_WAIT;
        
        goto nohand;
    }
    
    if ((scanvaltmp == shand_none)&&(old_hand_v == shand_none))
    {
    nohand:
        hg->hand_value = shand_none;
        hg->hand_state = shand_none;
        hg->hand_interval = 0;
        hg->hand_keep_ct = 0;
        return false;
    }

    if (scanvaltmp == shand_err)
    {
        scan_status = HAND_ERROR;
     	old_hand_v = shand_none;
        return false;
    }
    
    
    if (scanvaltmp == shand_none)
    {
        hg->hand_value = old_hand_v;
        old_hand_v = shand_none;
        //hand_up_deal(hg);
        return false;
    }
    
    if (scanvaltmp != old_hand_v)
    {
        hg->hand_keep_ct = 0;
        hg->hand_value = old_hand_v = scanvaltmp;
        hand_time_count(hg);
    }
    else
    {
        hand_time_count(hg);
    }
    
    return true;
}




