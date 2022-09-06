
#ifndef KEY_V2_0_H
#define KEY_V2_0_H
    
/***************************************************************/
#define TPERSCAN	    20				//调用key_board_waitup函数的周期，根据实际修改
#define TDn_Ct          2               //消抖次数,刚按下的时间长度
    
//!!!!!TPERSCAN*TDn_Ct 不能小于20!!!!!
#define TDN0D2SEC		 200/(TPERSCAN*TDn_Ct)
#define TDN0D5SEC		 500/(TPERSCAN*TDn_Ct)
#define TDN1D0SEC		1000/(TPERSCAN*TDn_Ct)         
#define TDN1D5SEC		1500/(TPERSCAN*TDn_Ct)
#define TDN2D0SEC		2000/(TPERSCAN*TDn_Ct)
#define TDN2D5SEC		2500/(TPERSCAN*TDn_Ct)
#define TDN3D0SEC		3000/(TPERSCAN*TDn_Ct)
#define TDN5D0SEC		5000/(TPERSCAN*TDn_Ct)

/***************************************************************/
//键状态

#define skey_err        0xff
#define skey_none       0x00    
    
#define skey_new 		0x01
#define skey_short_up	0x12		//小于3秒抬起
#define skey_long_up	0x14		//大于3秒抬起

#define skey_1s_dn	    0x05		//按到1秒
#define skey_1s5_dn  0x06		//按到1.5秒
#define skey_2s_dn	    0x07		//按到2秒

#define skey_3s_dn		0x08		//按到3秒
#define skey_5s_dn		0x09		//按到5秒
    
/***************************************************************/
typedef struct{
    u8 key_value;      //键值
    u8 key_state;      //键状态，用来判断是否要处理按键
    u8 key_keep_ct;    //每TPERSCAN*TDn_Ct时间 加1, 大于250停止
    u8 key_interval;   //每TPERSCAN*TDn_Ct时间 加1, 大于0xff变0重新计数
}Key_Inst_t;

/***************************************************************/
//需要修改的接口函数    
u8 key_scan(void);    

//如需要改按下时间
void key_time_count(Key_Inst_t * kb);

/***************************************************************/
//需要修改的键值索引值

#define KEY_START_PIN P2_5

//key val
#define K1    0x0008
#define K2    0x0004
#define K3    0x0002
#define K4    0x0001
#define K5    0x0010
#define K6    0x0040
#define K7    0x0080
#define K8    0x0020

#define K9      0x0400
#define K10    0x0800
#define K11    0x1000
#define K12    0x2000
#define K13    0x4000
#define K14    0x8000
#define K15    0x0100
#define K16    0x0200



#define key_power   1
#define key_linkage    2
#define key_clock 3
#define key_down    4
#define key_up    5
#define key_fried     6
#define key_clean   7
#define key_light   8

#define key_1     9
#define key_2    10
#define key_3    11
#define key_4    12
#define key_5    13
#define key_6    14
#define key_7    15
#define key_8    16

#define key_multi  16   //first multi

/***************************************************************/
//初始化按键，初始化时调用 
void key_board_init(Key_Inst_t * kb);

//键盘检测函数，与key_scan函数调用同步
bool key_board_scan(Key_Inst_t * kb);       //true 有键状态变化，需处理

//需要等待按键全部抬起时调用
void key_board_waitup(Key_Inst_t * kb);

//触摸按键数大于16个时用
void get_scan_value(void);

/***************************************************************/
extern iram Key_Inst_t kb;
extern u16 scan_key;

#endif

/* [] END OF FILE */
