
#include "..\include_s.h"


UART_t  panel_comm;
//static
u16 discont_tmr;

u8 fct_cont_tmr;
u8 fct_state;

/***************************
 * 接收包解析
 */
void process_packet(UART_t * c_uart)
{
     if (c_uart->uart_id == ID_UART_PANEL)
	 {
		 if (c_uart->rx_buf[2] == 0xfc)
		 {
			 fct_state=0x55;
                fct_cont_tmr=250;
                return;
		 }        
          fct_state=0;
		 if(c_uart->rx_buf[2] == 0x41)
		 {
				panel_comm.cmd = FZKZ_FLAG;
				device_info.soft_edition = c_uart->rx_buf[3];
				device_info.hard_edition = c_uart->rx_buf[4];
				device_info.beep_type	 = c_uart->rx_buf[5];	
				device_info.fffan_level  = c_uart->rx_buf[6];
				return;
		 }

		 if (c_uart->rx_buf[2] == 0x47 || c_uart->rx_buf[2] == 0x48)
		 {
			 status_info.light_level	= c_uart->rx_buf[3];
			 status_info.ffan_level	= c_uart->rx_buf[4];
			 status_info.error_code	= c_uart->rx_buf[5];
			 status_info.fb_current	= c_uart->rx_buf[6] * 10;
			 status_info.reserve1	= c_uart->rx_buf[7];
			 status_info.fan_power	= c_uart->rx_buf[8] * 2;
			 status_info.fan_speed	= c_uart->rx_buf[9] * 10;
			 status_info.ipm_temp	= c_uart->rx_buf[10];
			 status_info.boost	= c_uart->rx_buf[11];
			 
			 return;
		 }	
	 }
}

/***************************
 * 两次发送间隔减去发送时间必须>10ms!!!
 * 10ms per called
 */

void send_panel_comm(void)
{
static u8 send_t = 0;
	
	u16 temp;
	
	if(++send_t >= 10)
	{
		send_t = 0;
		if (panel_comm.cmd == FZKZ_FLAG)//负载控制命令
		{
			panel_comm.tx_buf[0] = LEAD_BYTE;
			panel_comm.tx_buf[1] = 0x0d;
			panel_comm.tx_buf[2] = 0x07;

			panel_comm.tx_buf[3] = TG_RUN_TIME;
			panel_comm.tx_buf[4] = TG_DZ_CURRENT;

			panel_comm.tx_buf[5] = (pushrod_state << 4) | (robam_state & 0x01);
			panel_comm.tx_buf[6] = key_led_light;
			panel_comm.tx_buf[7] = robam_gear;      //烟机档位
			panel_comm.tx_buf[8] = buzz_mode;       
			
			panel_comm.tx_buf[9] = 0xff;			//电加热
			
               panel_comm.tx_buf[10] = 0xff;			//预留
               
			temp = crc16_cal(panel_comm.tx_buf, panel_comm.tx_buf[1] - 2);
               
			panel_comm.tx_buf[11] = HIBYTE(temp);
			panel_comm.tx_buf[12] = LOBYTE(temp); 

			panel_comm.sending_f = true;
               panel_comm.tx_ct = 0;
			uart_send_byte(panel_comm.uart_id,panel_comm.tx_buf[0]);
               	
			buzz_mode = 0;
			
			return;
		}
		
		if (panel_comm.cmd == CXSB_FLAG)//查询设备
		{
			panel_comm.tx_buf[0] = LEAD_BYTE;
			panel_comm.tx_buf[1] = 0x08;
			panel_comm.tx_buf[2] = 0x01;
			panel_comm.tx_buf[3] = 0x00;
			panel_comm.tx_buf[4] = 0x00;
			panel_comm.tx_buf[5] = 0x00;

			temp = crc16_cal(panel_comm.tx_buf, panel_comm.tx_buf[1] - 2);
			panel_comm.tx_buf[6] = HIBYTE(temp);
			panel_comm.tx_buf[7] = LOBYTE(temp); 

			panel_comm.sending_f = true;
			uart_send_byte(panel_comm.uart_id,panel_comm.tx_buf[0]);
			return;
		}
		
		if (panel_comm.cmd == ZTCX_FLAG)//状态查询
		{
			panel_comm.tx_buf[0] = LEAD_BYTE;
			panel_comm.tx_buf[1] = 0x08;
			panel_comm.tx_buf[2] = 0x08;
			panel_comm.tx_buf[3] = 0x00;
			panel_comm.tx_buf[4] = 0x00;
			panel_comm.tx_buf[5] = 0x00;
			
			temp = crc16_cal(panel_comm.tx_buf, panel_comm.tx_buf[1] - 2);
			panel_comm.tx_buf[6] = HIBYTE(temp);
			panel_comm.tx_buf[7] = LOBYTE(temp); 
			
			panel_comm.sending_f = true;
			uart_send_byte(panel_comm.uart_id,panel_comm.tx_buf[0]);
			return;
		}
		
		if(panel_comm.cmd == FCT_FLAG)
		{
			panel_comm.tx_buf[0] = LEAD_BYTE;
			panel_comm.tx_buf[1] = 0x08;
			panel_comm.tx_buf[2] = 0xfc;
			panel_comm.tx_buf[3] = 0x00;
			
			panel_comm.tx_buf[4] = 0x00;
			panel_comm.tx_buf[5] = 0x00;
			
			temp = crc16_cal(panel_comm.tx_buf, panel_comm.tx_buf[1] - 2);
			panel_comm.tx_buf[6] = HIBYTE(temp);
			panel_comm.tx_buf[7] = LOBYTE(temp); 
			panel_comm.sending_f = true;
			uart_send_byte(panel_comm.uart_id,panel_comm.tx_buf[0]);
			buzz_mode = 0;
			return;
		}
	}

}

/***************************
 * 
 * disconnected alarm

bool is_comm_discont(void)
{
    if (!discont_tmr)
        return true;

    return false;
} */

/*********************************************************/
/******************** 协议模块初始化 **********************/
/*********************************************************/
void protocol_init(void)
{
    discont_tmr = 20*100;
    uart_init(&panel_comm,ID_UART_PANEL);

}
