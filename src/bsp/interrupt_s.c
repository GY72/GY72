
#include "..\include_s.h"

u8 time_10ms_ct;
bool run_sec_f;

/***************************************************************/
//500ms的时基
void Timer3_INT() interrupt	5
{
	static u8 t_1s_ct = 0;
	_push_(INSCON);
     SETBANK1;
//     TOGGLE_TEST_PIN = ~TOGGLE_TEST_PIN;
     SETBANK0;
	if(t_1s_ct++ >= 1)
	{
		t_1s_ct = 0;
		run_sec_f = true;
	}

    _pop_(INSCON);
}
/***************************************************************/
//500us的时基
void Timer4_INT() interrupt	9				
{
	static u8 t10ms_ct = 0,t1ms_ct = 0;
	
	_push_(INSCON); 
     
	SETBANK0;
	if (t10ms_ct++ >= 20)
	{
		t10ms_ct = 0;
		base_10ms_f = true;
	}
	
	t1ms_ct++;
	if(t1ms_ct>=2)
	{
		t1ms_ct = 0;
		
		uart_byte_tmr_dn(&panel_comm);//中断中调用字节接收超时函数
	}
	
	handtube_ctrl();//发送载波
	_pop_(INSCON);
}

/***************************************************************/
//100us的时基
void Timer5_INT() interrupt	3
{   
     _push_(INSCON); 
     
     update_hand_gesture();
     
    _pop_(INSCON);
}

/***************************************************************/
void UART2_INT() interrupt 16
{
    _push_(INSCON);     
    SETBANK1;

    if (RI2 == 1)
    {
        RI2 = 0;  
        uart_recv_byte_isr(&panel_comm);
    }
    
    if (TI2 == 1)
    {
        TI2 = 0;  
        uart_send_byte_isr(&panel_comm);
    }

    _pop_(INSCON);      
}


/*******************************************
void ext_int4(void ) interrupt 10
{
    _push_(INSCON);   
    
    if (EXF1 & bit10000000)
    {
        rf_bit_int();
    }

    EXF1 = 0;

    _pop_(INSCON);   
}
********************/


























