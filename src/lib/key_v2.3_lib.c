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

#define KEY_WAIT    0
#define KEY_ERROR   1
#define KEY_ERROR2  2

extern u8 crom Down_ct;

static u8 scan_state;

/****************************************
 * 函数名：	key_board_init 
 * 说明：	按键初始化
 * 输入：	Key_Inst_t指针 
 * 输出：	--
 ****************************************/
void key_board_init(Key_Inst_t * kb)
{
    kb->key_interval = 0;
    kb->key_keep_ct = 0;
    kb->key_state = 0;
    kb->key_value = 0;

    scan_state = KEY_WAIT;
}

/****************************************
 * 函数名：	key_up_deal 
 * 说明：	按键抬起处理
 * 输入：	Key_Inst_t指针 
 * 输出：	--
 ****************************************/
static void key_up_deal(Key_Inst_t * kb)
{
	if (kb->key_keep_ct >= TDN3D0SEC)				//3000ms/(20ms*TDn_Ct)
		kb->key_state = skey_long_up;				//大于3秒,长按抬起
	else
		kb->key_state = skey_short_up;				//小于1秒,短按抬起

	kb->key_keep_ct = 0;							//2012-4-19
}

/****************************************
 * 函数名：	key_board_scan 
 * 说明：	键盘检测函数，与get_key_pins函数调用同步
 * 输入：	Key_Inst_t指针 
 * 输出：	--
 ****************************************/

bool key_board_scan(Key_Inst_t * kb)
{
    static  u8 old_scan_v = skey_none;
    static  u8 old_key_v  = skey_none;
    static  u8 scan_ct = 0;
    
    unsigned char scanvaltmp;
    
    scanvaltmp = key_scan();
    
    if (old_scan_v != scanvaltmp)
    {
		old_scan_v = scanvaltmp ;				
		scan_ct = 0 ;    
        return false;
    }

	if (++scan_ct < Down_ct)//消抖
        return false;
    scan_ct = 0;
    
    if (scan_state >= KEY_ERROR)
    {//由无效按键到有效按键，只处理复合键,否则复合键变成单键会响应
        old_key_v = skey_none;
        if ((scan_state == KEY_ERROR2) || (scanvaltmp < key_multi))   
        {//key_board_waitup调用，强制等待抬起。或 有无效键按过，变成单键也强制等待抬起。
            if (scanvaltmp == skey_none)
                scan_state = KEY_WAIT;

            goto nokey;
        }

        if (scanvaltmp == skey_err)
            goto nokey;

        //复合键会到这里,有无效键按过，变成单键再变有效复合键也能处理，为了适应3键按下的复合键。
        scan_state = KEY_WAIT;
    }
    
    if ((scanvaltmp == skey_none)&&(old_key_v == skey_none))
    {
    nokey:        
        kb->key_value = skey_none;
        kb->key_state = skey_none;
        kb->key_interval = 0;
        kb->key_keep_ct = 0;
        return false;
    }
    
    if (scanvaltmp == skey_err)
    {
        scan_state = KEY_ERROR;
     	old_key_v = skey_none;
        return false;
    }

    if (scanvaltmp == skey_none)
    {//这里肯定 old_key_v != skey_none
        kb->key_value = old_key_v;
        old_key_v = skey_none;
        key_up_deal(kb);
        return true;
    }
    
    if (scanvaltmp != old_key_v)
    {//
        /*  */
        if (old_key_v == skey_none)
        {//new
            kb->key_value = old_key_v = scanvaltmp;
            key_time_count(kb);
        }
        else
        {//组合键,先抬起一个键
            /* 不响应原来的键抬起动作
            kb->key_value = old_key_v;
            old_key_v = skey_none;
            key_up_deal(kb); */
            kb->key_value = old_key_v;
            old_key_v = skey_none;
            key_up_deal(kb);

//            kb->key_value = old_key_v = scanvaltmp;
//            key_time_count(kb);
        }

        //new 单键 OR 组合键//bug，未抬起直接换成另一个键时!
        /* kb->key_keep_ct = 0;                    
        kb->key_value = old_key_v = scanvaltmp;
        key_time_count(kb); */

    }
    else
    {//keep
        key_time_count(kb);
    }
    
    return true;
}

/****************************************
 * 函数名：	key_board_waitup 
 * 说明：	等待按键全部抬起
 * 输入：	Key_Inst_t指针 
 * 输出：	--
 ****************************************/
void key_board_waitup(Key_Inst_t * kb)
{
    //scan_state = KEY_WAIT;
    scan_state = KEY_ERROR2;
    
    kb->key_value = skey_none;
    kb->key_state = skey_none;
    kb->key_interval = 0;
    kb->key_keep_ct = 0;
}















