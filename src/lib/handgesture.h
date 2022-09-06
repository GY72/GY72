

#ifndef _HANDGESTURE_H_
#define _HANDGESTURE_H_

/***************************************************************/
#define HANDSCAN	    10				//??hand_gesture_scan?????,??????
    
#define HDS0D2SEC		 200/(HANDSCAN)
#define HDS0D5SEC		 500/(HANDSCAN)
#define HDS1D0SEC		1000/(HANDSCAN)         
#define HDS1D5SEC		1500/(HANDSCAN)
#define HDS2D0SEC		2000/(HANDSCAN)
#define HDS2D5SEC		2500/(HANDSCAN)
#define HDS3D0SEC		3000/(HANDSCAN)
#define HDS5D0SEC		5000/(HANDSCAN)

/***************************************************************/
#define shand_none      0x00  
#define shand_err       0xff

#define shand_new 		0x01

#define shand_1s_dn	    0x05		//??1?
#define shand_1s5_dn	0x06		//??1.5?
#define shand_2s_dn	    0x07		//??2?

#define shand_3s_dn		0x08		//??3?
#define shand_5s_dn		0x09		//??5?

#define shand_short_up	0x12		//??3???
#define shand_long_up	0x14		//??3???

#define hand_left       1    
#define hand_right      2 

/***************************************************************/
//????
#define Period_time     25      //??:/ms
#define Period_time3     75      //??:/ms
// #define High_time       15      //??:/ms
// #define Low_time        5       //??:/ms

#define High1_max        23      //??:/ms     ???
#define High1_min        17      //??:/ms     ???
#define Low1_max         8       //??:/ms     ???
#define Low1_min         2       //??:/ms     ???

#define High2_max        23//18      //??:/ms     ???
#define High2_min        17//12      //??:/ms     ???
#define Low2_max         8 //13      //??:/ms     ???
#define Low2_min         2 //7       //??:/ms     ???

//??????
#define PIN_recvL           (P3_4)
#define PIN_recvR           (P0_6)

//??????
#define PIN_send1           (P3_5)
#define PIN_send2           (P0_5)



#define Disable_PWM0            PWM0CON &= 0xfe	    //??PWM0
#define Enable_PWM0             PWM0CON |= 0x01	    //??PWM0
#define Disable_PWM1            PWM1CON &= 0xfe     //??PWM1
#define Enable_PWM1             PWM1CON |= 0x01     //??PWM1



/***************************************************************/
typedef struct{
    u8  hand_value;      //??
    u8  hand_state;      //???,???????????
    u16 hand_keep_ct;    //?TPERSCAN?? ?1, ??500??
    u16 hand_interval;   //?TPERSCAN?? ?1, ??0xffff?0????
}Hand_Inst_t;

typedef struct {
    u8  state_step;
    u16 state_tmr;

    u8  Left_status;
    u8  Left_ct;
    u8  Right_status;
    u8  Right_ct;

    u8  gesture;        //1:?->?,??; 2:?->?,??

    u8  mode;						//工作模式
		u8  set;						//设定
		u16 key_waittmr;		//等待时间
		u8  temp_mode;			//
	
    u8  useless1_ct;
    u8  useless2_ct;
}HAND_t;

typedef struct{   //																   H2
	u8 high_ct;			//手势感应 高电平时间     ----     -------     -----
	u8 low_ct;			//手势感应 低电平时间        |     |     |     |
															//						   |		 |     |     |
	u8 rise_flag;		//上升沿标志位							 |     |     |     |
	u8 fall_flag;		//下降沿标志位               -------     -------
									//														 L1					 L3
	u8 rise_cn;			//			
	u8 fall_cn;		  //
	
	u8 rise_ct;			//上升沿计数
	u8 fall_ct;			//下降沿计数
	
	u8 L1;					//用于判断的低电平第一段时间
	u8 H2;					//用于判断的高电平第一段时间
	u8 L3;					//用于判断的低电平第二段时间														//判断2个上升沿和2个下降沿中间低高低的长度 来控制手势
	
	u8 mode;				//区分左右手势
}GESTURE_CHECK_t;


/***************************************************************/
extern Hand_Inst_t hg;
extern HAND_t  hand_task;
extern GESTURE_CHECK_t gc_left,gc_right;

/***************************************************************/
//初始化按键，初始化时调用
void hand_gesture_init(Hand_Inst_t * hg);

//检测,10ms循环调用
bool hand_gesture_scan(Hand_Inst_t * hg);

//红外对管输出控制,5ms中断调用
void handtube_ctrl(void);

//检测,1ms中断调用
void update_hand_gesture(void);















#endif 