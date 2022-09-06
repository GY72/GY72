

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

    u8  mode;						//����ģʽ
		u8  set;						//�趨
		u16 key_waittmr;		//�ȴ�ʱ��
		u8  temp_mode;			//
	
    u8  useless1_ct;
    u8  useless2_ct;
}HAND_t;

typedef struct{   //																   H2
	u8 high_ct;			//���Ƹ�Ӧ �ߵ�ƽʱ��     ----     -------     -----
	u8 low_ct;			//���Ƹ�Ӧ �͵�ƽʱ��        |     |     |     |
															//						   |		 |     |     |
	u8 rise_flag;		//�����ر�־λ							 |     |     |     |
	u8 fall_flag;		//�½��ر�־λ               -------     -------
									//														 L1					 L3
	u8 rise_cn;			//			
	u8 fall_cn;		  //
	
	u8 rise_ct;			//�����ؼ���
	u8 fall_ct;			//�½��ؼ���
	
	u8 L1;					//�����жϵĵ͵�ƽ��һ��ʱ��
	u8 H2;					//�����жϵĸߵ�ƽ��һ��ʱ��
	u8 L3;					//�����жϵĵ͵�ƽ�ڶ���ʱ��														//�ж�2�������غ�2���½����м�͸ߵ͵ĳ��� ����������
	
	u8 mode;				//������������
}GESTURE_CHECK_t;


/***************************************************************/
extern Hand_Inst_t hg;
extern HAND_t  hand_task;
extern GESTURE_CHECK_t gc_left,gc_right;

/***************************************************************/
//��ʼ����������ʼ��ʱ����
void hand_gesture_init(Hand_Inst_t * hg);

//���,10msѭ������
bool hand_gesture_scan(Hand_Inst_t * hg);

//����Թ��������,5ms�жϵ���
void handtube_ctrl(void);

//���,1ms�жϵ���
void update_hand_gesture(void);















#endif 