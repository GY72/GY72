
#ifndef __TOUCHKEY_H
#define	__TOUCHKEY_H
	
#include "../Inc/c51_type.h"
#include "../Inc/tk_conf_add.h"
#include "../Lib/tk_para.h"

extern void Get_TK_Baseline();
void touchkey_go();
void touchkey_ad_go();	//
void EnTk(U8 n);
void EnIO(U8 n);
void tk_para_init();
void tk_samp_fre_set();
void DisTk(void);
extern bit key_tkst_flag_pre;
void GetTouchkeyData();
void key_judge();
extern void touchkeyinit();
extern void Get_TK_States();
void GetInitialTouchkeyData();
extern void touchkey_samp_fre_set();//
extern void TK_start();
void Rst_WDT();
void init_tkErrchk();
void tk_resetChk(); 

#endif

