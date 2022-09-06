
#ifndef __TK_ADJUST_H
#define	__TK_ADJUST_H

#define	TK_GO_ERR			0x01
#define	TK_Count_Over		0x02
#define	TK_Data_Over		0x03
#define	TK_Going			0x05
#define	TK_Scan_End			0x06
#define  TK_BL_Collecting	0x07
#define	TK_Diff_Collecting	0x08
#define	TK_Adjust_Success	0x09
#define	TK_Data_Over1		0x0A
#define	TK_Adjust_Fail			0x0B
#define	TK_New_BL_Collecting	0x0C
#define	TK_New_Diff_Collecting	0x0D

void touchkey_scan();
void tk_para_auto_adjust();


#endif
