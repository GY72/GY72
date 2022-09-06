/****************************************************************************
 * uart.c
 *
 * 	 Copyright (C) Hiklife. All rights reserved.
 *   Author: Lgx <lgx@hiklife.com>	2019-03
 * 
 *  uart处理函数
 *
 ****************************************************************************/
#include "..\include_s.h"

//回调的数据包处理函数
extern void process_packet(UART_t * c_uart);

/* ！！！！！！！！！！！！！！！！！！！！！！！！*/
/* ！！！要用这些函数各UART中断优先级必须一样！！！*/
/* ！！！！！！！！！！！！！！！！！！！！！！！！*/

/****************************************
 * 函数名：	uart_send_byte 
 * 说明：	uart发送，写入sbuf
 * 			非中断中掉用时需要确保发送中断不会发生，因为不可重入！
 * 输入：	id: uart id, da: 发送的数据
 * 输出：	--
 ****************************************/
void uart_send_byte(u8 id, u8 da)
{
	if (id == ID_UART0)
		SBUF = da;
	
	if (id == ID_UART1)
	{
		_push_(INSCON);     
          SETBANK1;

		SBUF1 = da;
          
          SETBANK0;
		_pop_(INSCON);    
	}
     if (id == ID_UART2)
	{
		_push_(INSCON);     
          
          SETBANK1;

		SBUF2 = da;
          
          SETBANK0;
          
		_pop_(INSCON);    
	}
}
/****************************************
 * 函数名：	uart_recv_byte 
 * 说明：	uart接收，读取sbuf
 * 输入：	id: uart id
 * 输出：	接收到的数据
 ****************************************/
static u8 uart_recv_byte(u8 id)
{
	volatile u8 da;

	if (id == ID_UART0)
		da = SBUF;

	if (id == ID_UART1)
	{
		_push_(INSCON);
		SETBANK1;

		da = SBUF1;
          
          SETBANK0;
		_pop_(INSCON);
	}
     if (id == ID_UART2)
	{
		_push_(INSCON);
		SETBANK1;

		da = SBUF2;
          
          SETBANK0;
		_pop_(INSCON);
	}
	return da;
}


/* ！！！！！！！！！！！！！！！！！！！！！！！！*/
/* ！！！！！下面几个函数一般不需要修改 ！！！！！!*/
/* ！！！！！！！！！！！！！！！！！！！！！！！！*/

/****************************************
 * 函数名：	uart_packet_deal
 * 说明：	查询是否有一包数据要处理，调用process_packet包处理函数，及通讯故障计数
 * 			10ms调用一次
 * 输入：	UART_t 指针
 * 输出：	--
 ****************************************/
static bool panel_packet_check(UART_t * c_uart)
{
	u8 len, sum;
	bool check;

	len = c_uart->rx_buf[1];
	check = verify_check_crc16(c_uart->rx_buf,len-1);
	if (check) return true;

	sum = get_check_sum(c_uart->rx_buf,len-2);
	if (sum == c_uart->rx_buf[len-1])
		return true;
	
	return false;
}

void uart_packet_deal(UART_t * c_uart)
{
	bool check;

	if (c_uart->recved_f)
	{
		check = panel_packet_check(c_uart);
		if (check)
		{
			process_packet(c_uart);						//数据包处理
		}

		c_uart->recved_f = false;
	}
}

/****************************************
 * 函数名：	uart_send_byte_isr
 * 说明：	一字节发送完成，发送下一个，发送中断中调用
 * 输入：	UART_t 指针
 * 输出：	--
 ****************************************/
void uart_send_byte_isr(UART_t * c_uart)
{
	u8 len;

	if (c_uart->sending_f)
	{//没有发送中断或发送中断有问题时，在循环中发送帧内数据
		len = c_uart->tx_buf[1];

		c_uart->tx_ct++;
		if (c_uart->tx_ct < len)
		{
			uart_send_byte(c_uart->uart_id, c_uart->tx_buf[c_uart->tx_ct]); //51重入警告
		}
		else
		{
			c_uart->tx_ct = 0;
			c_uart->sending_f = false; 					//一帧数据发送完成
		}

		return;
 	}

    c_uart->tx_ct = 0;
}

/****************************************
 * 函数名：	uart_recv_byte_isr
 * 说明：	收到一个字节, 一般在中断中调用
 * 输入：	UART_t 指针
 * 输出：	--
 ****************************************/
void uart_recv_byte_isr(UART_t * c_uart)
{
	u8 uart_rx_data;
	u8 packet_len = 0;

	/* Receive one date */
	uart_rx_data = uart_recv_byte(c_uart->uart_id);		//51重入
	
  	if(!c_uart->rx_byte_tmr) 							//收到一帧数据必须在超时时间内处理！！！
		  c_uart->rx_ct = 0;			                //last recv byte timeout! reset recv!!!
	c_uart->rx_byte_tmr = RX_RST_TIME;
	
	if (c_uart->recved_f)
		return;
 		
  	if(!c_uart->rx_ct)
  	{
  		if (uart_rx_data != LEAD_BYTE)
  			return;
	}

	if(c_uart->rx_ct == 1)
	{
		if ((uart_rx_data > UART_RX_BYTES) || (uart_rx_data == 0))
		{//err
			c_uart->rx_ct = 0;
			return;
		}
	}

	c_uart->rx_buf[c_uart->rx_ct] = uart_rx_data;
	c_uart->rx_ct++;	

	if (c_uart->rx_ct >= 2)
		packet_len = c_uart->rx_buf[1];
	else
		return;

	if (c_uart->rx_ct >= packet_len)
	{
		c_uart->rx_ct = 0;   		//收到一帧
		c_uart->recved_f = true;    //isr_send_signal(CTRL_TASK_ID);给任务 CTRL_TASK_ID 发信号, 为了使用而使用		
	}
}

/****************************************
 * 函数名：	uart_byte_tmr_dn
 * 说明：	ms中断中调用 , 经过RX_RST_TIME每接收到1个字节，复位接收.
 * 输入：	UART_t 指针
 * 输出：	--
 ****************************************/
void uart_byte_tmr_dn(UART_t * c_uart)
{
    //u8_dn(&c_uart->rx_byte_tmr);					//51重入警告
	if (c_uart->rx_byte_tmr)
		c_uart->rx_byte_tmr--;
}

/****************************************
 * 函数名：	uart_init
 * 说明：	uart初始化函数
 * 输入：	UART_t 指针, uart_id分配给UART_t指针对应的uart
 * 输出：	--
 ****************************************/
void uart_init(UART_t * c_uart, u8 uart_id)
{
	c_uart->uart_id   = uart_id;
    c_uart->sending_f = false;
    c_uart->recved_f  = false;
}
