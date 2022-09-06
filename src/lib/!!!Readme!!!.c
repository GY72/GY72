

/*******************************
* 1、 buzzer 模块需要修改的地方：
********************************/
#define MUSIC_BUZZ 0        //0: 普能蜂鸣器  1：音乐蜂鸣器

/***********************音乐蜂鸣器*******************************/
//需要修改的管脚 PWM工作频率
#define BUZZ_PWR_PIN   P3_1       //音乐蜂鸣器电源控制脚
#define BUZZ_FRQ_PIN   P3_0       //音乐蜂鸣器频率控制脚
#define PWM_FREQ       375000     //PWM工作频率

//需要修改的接口函数
void music_buzz_PwrOn(void);      
void music_buzz_PwrOff(void);
void music_buzz_FrqOff(void);
void music_buzz_SetFreq(u8 f);

/************************普通蜂鸣器******************************/
//需要修改的管脚 PWM 4KHz 设置参数
#define BUZZ_FRQ_PIN   P3_3
#define F_4KHZ         3000	      //(Fpwm/(4*1000))

//需要修改的接口函数
void buzz_on(void);
void buzz_off(void);

/*******************************
    buzzer 模块使用步骤：
********************************/
//a、配置   
    #define MUSIC_BUZZ 0/1
  
//b、初始化
    normal_buzz_init();

//c、调用
    10ms调用一次 normal_buzz_ctrl();

    需要响的地方：normal_buzz_start(BUZZ_WARNING);  等







/*******************************
 * 2、key 模块需要修改的地方：
********************************/
#define TPERSCAN	    25		  //调用key_board_waitup函数的周期，根据实际修改

/***************************************************************/
//需要修改的接口函数:    
u8 key_scan(void);    

/***************************************************************/
//根据实际修改键值索引值
#define key_onoff    1
#define key_door     2
#define key_qxx      3
#define key_ckx      4
#define key_jnx      5
#define key_gsx      6
#define key_hxx      7
#define key_hg       8
#define key_zjj      9
#define key_rest     10
#define key_start    10
#define key_seth     11 
#define key_selfchk  12
#define key_aging    13

/*******************************
    key 模块使用步骤：
********************************/
//a、初始化
    key_board_init(&kb);

//b、主循环中调用
    key_board_scan(&kb);

//c、键处理注意事项
    键处理可参考:
    work_task_key_deal();
    standby_key_deal();
    setting_key_deal();











/********************************
 * 3、uart 模块需要修改的地方：
*********************************/
//uart发送，写入sbuf
void uart_send_byte(u8 id, u8 da);

//接收uart，读sbuf
static u8 uart_recv_byte(u8 id);

//设置UART接收故障标志
static void set_rx_error(u8 id, bool f);

/*******************************
    uart 模块使用步骤：
********************************/

//a、分配uart
#define ID_UART_PANEL ID_UART1
#define ID_UART_MOTOR ID_UART0

//b、定义
UART_t  panel_comm,motor_comm;

//c、初始化
    uart_init(&panel_comm,ID_UART_PANEL);
    uart_init(&motor_comm,ID_UART_MOTOR);

//d、数据包处理回调函数
void process_packet(UART_t * c_uart)
{
    static u8 motor_err_ct = 0;
    u16 temp;

    if (c_uart->uart_id == ID_UART_PANEL)
    {
        if (c_uart->rx_buf[2] == 'P')
        {//Panel 面板数据包
            comm_rs_err     = (c_uart->rx_buf[3] == 0x55) ? true : false;	//发送端接收故障
            key_pins        = MAKEWORD(c_uart->rx_buf[4],c_uart->rx_buf[5]) ;
            key_board_scan(&kb);

            return;
        }

        return;
    }

    if (c_uart->uart_id == ID_UART_MOTOR)
    {
        if (c_uart->rx_buf[2] == 'M')
        {//motor 数据包
            motor_rs_err        = (c_uart->rx_buf[3] == 0x55) ? true : false;	//发送端接收故障
            temp                = MAKEWORD(c_uart->rx_buf[4],c_uart->rx_buf[5]) ;

            return;
        }

        return;
    }
}

//e、10ms调用一次包处理函数
    uart_packet_deal(&panel_comm);
    uart_packet_deal(&motor_comm);

//f、ms中断中调用字节接收超时函数
    uart_byte_tmr_dn(&panel_comm);
    uart_byte_tmr_dn(&motor_comm);

//g、uart中断中调用接收发送函数
    //...
    RI = 0;          
    uart_recv_byte_isr(&motor_comm);
    //...

    //...
    TI = 0; 
    uart_send_byte_isr(&motor_comm);
    //...
























