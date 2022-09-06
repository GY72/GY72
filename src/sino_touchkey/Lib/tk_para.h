#ifndef __TK_PARA_H
#define	__TK_PARA_H

#include "../Lib/tk_conf.h"
#include "../Inc/tk_conf_add.h"

#define Filter_Index	2
#define Filter_Deg      4		//(1 << Filter_Index)

#define SPEAK_VOLUME	0x88	 //0x88 0xCC 0xFF 

#define TKST_IS_High_Fre	1
#define TKST_IS_Low_Fre		0

#define	BIT0	0x01
#define	BIT1	0x02
#define	BIT2	0x04
#define	BIT3	0x08
#define	BIT4	0x10
#define	BIT5	0x20
#define	BIT6	0x40
#define	BIT7	0x80

#define TK0   0 
#define TK1   1 
#define TK2   2 
#define TK3   3 
#define TK4   4 
#define TK5   5 
#define TK6   6 
#define TK7   7 
#define TK8   8 
#define	TK9	  9		
#define	TK10  10		
#define	TK11  11		
#define	TK12  12		
#define	TK13  13	
#define	TK14  14		
#define	TK15  15	
#define	TK16  16	
#define TK17  17
#define TK18  18
#define TK19  19
#define TK20  20
#define TK21  21
#define TK22  22
#define TK23  23
#define TK24  24

#define L_tkErrCnt          50	 //上电错误次数

#define key_fastcounter_set 3    //小于等于15
#define key_stablecounter_set 40 // 在无触摸的情况下，数据稳定多少次，把当前值给基线值(maxvalue-200)
#define L_BaseCnt_set   	10
#define L_downCnt            3
#define L_downCnt2           10
#define L_maxlimit           30  //
#define L_nakelimit          800 

extern U8  xdata  Add_function;
extern U8  xdata  Add_Set;//lmy0115
extern U8  xdata  FLAG_COUNT_set;
extern U8  xdata  normal_jitter_set;
extern U8  xdata  multikey_control;
extern U8  xdata  multikey_control2;
extern U8  xdata  multikey_control3;
extern U8  xdata  init_BaseCnt_set;
extern U8  xdata  key_fastcounter;//基线快跟
extern U8  xdata  key_stablecounter;

//------------对讲机
extern bit  Duijiangji_flag;	   //lmy0115
extern U8   xdata  DuiReaCnt;
extern U8   xdata  Dui_num;
extern U8   xdata  L_Inter1;
extern U8   xdata  L_Inter2;
//-----lmy
extern U16 xdata  key_stablecNT[KEY_NUMBER1];  //20190115
extern U8  xdata  nake_count[KEY_NUMBER1]; //lmy1115
extern U16 xdata  nakevalue; //lmy1115
extern U8  xdata  stable_limit1;  //lmy0115
extern U16 xdata  STcnt_One;
extern U16 xdata  STcnt_Two;

extern bit CSI_flag ;
extern bit key_tkst_flag,key_tkst_flag_pre;
extern bit  f_tkErr;
extern U8  code  Tab_Chn[KEY_NUMBER1];
extern U8  xdata  key_sample_count;
extern U8  xdata  tk_num;

extern U32 xdata  sino_key_value;
extern U32 xdata  sino_key_value_pre;
extern U16 xdata  key_tkerrCnt;


extern U8  xdata line;  //分组变量
extern U16 code  Tab_HF_DIV[KEY_NUMBER1];
extern U16 code  Tab_LF_DIV[KEY_NUMBER1];
extern U8  code  key_threshold_per[KEY_NUMBER1];

extern U16 code  HF_key_max[KEY_NUMBER1];
extern U16 xdata HF_key_baseline[KEY_NUMBER1];
extern U16  code HF_key_threshold[KEY_NUMBER1];
extern U16 xdata HF_key[KEY_NUMBER1];
extern U16 xdata HF_key_filter[KEY_NUMBER1];
extern U16 xdata HF_key_filter2[KEY_NUMBER1];
extern U32 xdata HF_keytouch_flag;
//extern U8  xdata HF_key_flag[KEY_NUMBER1];
extern U8  xdata HF_baseline_plus_flag[KEY_NUMBER1];
extern U8  xdata HF_key_count_sub[KEY_NUMBER1];
//extern U8  xdata HF_key_count_fastsub[KEY_NUMBER1];
extern U8  xdata datasub_counter;
extern U8  xdata dataplus_counter;
extern U8  data  HF_CSI_cnt;
extern U8 xdata  HF_stblecount[KEY_NUMBER1];	 
extern U8 xdata  LF_stblecount[KEY_NUMBER1];	 

extern U16 code  LF_key_max[KEY_NUMBER1];
extern U16 xdata LF_key_baseline[KEY_NUMBER1];
extern U16 code  LF_key_threshold[KEY_NUMBER1];
extern U16 xdata LF_key[KEY_NUMBER1];
extern U16 xdata LF_key_filter[KEY_NUMBER1];
extern U16 xdata LF_key_filter2[KEY_NUMBER1];
extern U32  xdata LF_keytouch_flag;
extern U8  xdata LF_key_flag[KEY_NUMBER1];
extern U8  xdata LF_baseline_plus_flag[KEY_NUMBER1];
extern U8 	xdata LF_key_count_sub[KEY_NUMBER1];
extern U8 	xdata LF_key_count_fastsub[KEY_NUMBER1];
extern U8  data  LF_CSI_cnt;
extern U8  xdata R_downCnt;
extern U8  xdata R_downCnt2;
extern U8  xdata R_maxlimit;
extern U16 xdata R_nakelimit;
extern U16 code  *key_max;
extern U16 xdata *key_baseline;
extern U16 code  *key_threshold;
extern U16 xdata *key;
extern U16 xdata *key_filter;
extern U16 xdata *key_filter2;
extern U32 xdata *keytouch_flag;
extern U8  xdata *key_flag;
extern U8  xdata *baseline_plus_flag;
extern U8  xdata *key_count_sub;
extern U8  xdata *key_count_fastsub;
extern U8  data  *CSI_cnt;
extern U8  xdata *stblecount;
extern U8  xdata *R_DATA_RAM_ADDR;

extern bit	tkst_flag,tkst_flag_pre;
extern bit	tk_init_req;
extern bit 	tk_adjust_flag,fre_switch_flag;

extern bit	tkst_flag,tkst_flag_pre;
extern bit	TK_GO_ERR_flag;
extern bit	TK_Count_Over_flag;
extern bit  TK_Data_Over_flag;
extern bit  LED_Start_TK_Going_flag;
extern bit	TK_going_flag;
extern bit	TK_Scan_End_flag;

#endif