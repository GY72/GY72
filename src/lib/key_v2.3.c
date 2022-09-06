/****************************************************************************
 * key.c
 *
 * 	 Copyright (C) Hiklife. All rights reserved.
 *   Author: Lgx <lgx@hiklife.com>	2019-03
 * 
 *  按键相关函数
 *
 ****************************************************************************/

#include "..\include_s.h"

u16 scan_key;

iram Key_Inst_t kb;

u8 crom Down_ct = TDn_Ct;

/****************************************
 * 函数名：	key_scan 
 * 说明：	根据按键采样值返回预定义键值
 * 输入：	-- 
 * 输出：	u16
 ****************************************/
void get_scan_value(void)
{
//    static u8  step = 0;
//    static u32 scan_key0 = 0;

//    if (step == 0)
//    {
//        scan_key0 = get_tk_scanvalue(0);            //max 3ms
//        step = 1;
//        return;
//    }

//    if (step == 1)
//    {
//        scan_key  = get_tk_scanvalue(1);            //max 3ms

//        scan_key += scan_key0;

////        get_tk_slider_pos(scan_key >> 16);          //滑条少，左右两边还要能按，可以用按键来处理。
//        scan_key = (scan_key & 0xffff);// | (0x8000 & (scan_key >> 6));
//        step = 0;
//    }    
}
/****************************************
 * 函数名：	key_scan 
 * 说明：	根据按键采样值返回预定义键值
 * 输入：	-- 
 * 输出：	u16
 ****************************************/
u8 key_scan(void)
{
	u16 keyscanval = 0;

    keyscanval = scan_key;           //按键采样值，一个位代表一个按键，1：按下; 

    if (keyscanval)
	{
	    switch (keyscanval)
		{
            case      K1: return key_power ;					 
            case      K2: return key_linkage  ;				
            case      K3:return key_clock ;					 
            case      K4: return key_down  ;					
            case      K5: return key_up  ;					 
            case      K6: return key_fried   ;
            case      K7: return key_clean ;	
            case      K8:return key_light ;	
            case      K9: return key_1 ;
            case      K10: return key_2  ;				
            case      K11:return key_3 ;		            
            case      K12: return key_4  ;				
            case      K13:return key_5 ;					 
            case      K14: return key_6  ;					
            case      K15: return key_7  ;					 
            case      K16: return key_8  ;
			default:	
				return skey_err;	    
		}
    }

	return skey_none;
}

/****************************************
 * 函数名：	key_time_count 
 * 说明：	按键按下计时
 * 输入：	Key_Inst_t指针 
 * 输出：	--
 ****************************************/
void key_time_count(Key_Inst_t * kb)
{
	kb->key_keep_ct++;								
	if (kb->key_interval < 239)
        kb->key_interval++;
    else
        kb->key_interval = 0;  

    kb->key_state = skey_none;                      //2021-04-07
	switch (kb->key_keep_ct)
	{
		case 1:
			kb->key_state = skey_new;				//
			break;

        case TDN1D0SEC:
			kb->key_state = skey_1s_dn;				//按下1s
			break;
		
        case TDN1D5SEC:
			kb->key_state = skey_1s5_dn;			//按下1.5s
			break;
		
        case TDN2D0SEC:
			kb->key_state = skey_2s_dn;			    //按下2s
			break;

		case TDN3D0SEC:
			kb->key_state = skey_3s_dn;				//按下3.0s
			break;

		case TDN5D0SEC:
			kb->key_state = skey_5s_dn;				//按下5.0s
			break;
		
		default:
            if (kb->key_keep_ct > 250)
				kb->key_keep_ct = 250;		        //t = 250*TPERSCAN*TDn_Ct
	}
}
/* [] END OF FILE */
