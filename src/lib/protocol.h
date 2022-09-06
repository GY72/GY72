
#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

//device types
#define DISI_BOX    1
#define STEAM_BOX   2
#define BAKE_BOX    3
#define MWAVE_STEAM_BOX 4

#define LEAD_BYTE   0xa5      //包头魔数

#define CXSB_FLAG   0x01
#define FZKZ_FLAG   0x07
#define ZTCX_FLAG   0x08
#define FCT_FLAG	0x02

#define TG_RUN_TIME		       0x0C			    //推杆运行时间
#define TG_DZ_CURRENT           0x40			    //推杆堵转电流
#define TG_DZ_CURRENT_1         0x60		         //正转堵转电流


#define DEVICE_TYPE        MWAVE_STEAM_BOX         //panel可控制设备



extern UART_t  panel_comm;
extern u16 discont_tmr;
extern u8 fct_cont_tmr;
extern u8 fct_state;

void process_packet(UART_t * c_uart);
void send_panel_comm(void);
void protocol_init(void);

//bool is_comm_discont(void);
#endif