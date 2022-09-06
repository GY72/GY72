
#ifndef _UART_H_
#define _UART_H_

/***************************************************************/
//根据实际修改
#define UART_RX_BYTES 	20                  // 必须设置正确！！！  
#define UART_TX_BYTES 	20                  // 必须设置正确！！！
/***************************************************************/
#define ID_UART0        0
#define ID_UART1        1
#define ID_UART2        2
#define ID_UART_PANEL   ID_UART2

#define RX_RST_TIME		30					//字节接收超时，字节超时时间加数据包总时间必须小于发送周期，大于1字节发送时间！
#define RX_ERR_TIME		250					//连续 RX_ERR_TIME*10ms 未收到数据包，故障
#define RX_ERR_CLR      100                 //RX_ERR_CLR * 发送间隔时间复位故障

typedef struct{
    u8 uart_id;
  
    u8 tx_buf[UART_TX_BYTES];
    u8 rx_buf[UART_RX_BYTES];

    u8 rx_byte_tmr;
    u8 err_tmr_ct;
    u8 err_clr_ct;
    
    u8 rx_ct;
    u8 tx_ct;

    u8 sending_f;
    u8 recved_f;
    
    u8 cmd;
}UART_t;

/***************************************************************/
//uart初始化
void uart_init(UART_t * c_uart, u8 uart_id);

//定时器中断中调用 
void uart_byte_tmr_dn(UART_t * c_uart);

//接收中断中调用
void uart_recv_byte_isr(UART_t * c_uart);

//发送中断中调用 
void uart_send_byte_isr(UART_t * c_uart);

//发送数据时调用 
void uart_send_byte(u8 id, u8 da);            //51重入

//10ms调用一次
void uart_packet_deal(UART_t * c_uart);

#endif
