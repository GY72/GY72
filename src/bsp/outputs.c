/****************************************************************************
 * misc.c
 *
 * 	 Copyright (C) Hiklife. All rights reserved.
 *   Author: Lgx <lgx@hiklife.com>	2019-03
 * 
 *
 ****************************************************************************/

#include "..\include_s.h"
  

/***************************
* 清输出控制
*/
void clear_all_output(void)
{
     display_clear();
}

/***************************
* 输出控制刷新  
*/
void update_all_output(void)
{
    display_drive();
    send_panel_comm();//每100ms发送控制包
}






