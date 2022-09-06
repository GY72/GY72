/*##################################################################################
;# History:                                                                       #
;# V1.0        1. Original                                                        #
##################################################################################*/

#ifndef _REGISTER_H_
#define _REGISTER_H_

#include <SH32F9001.H>

//Touch Key
#define  Enable_Touch         TOUCHKEY->CR.BIT.TKCON = 1;
#define  Disable_TK           TOUCHKEY->CR.BIT.TKCON = 0;
#define  TK_GO                TOUCHKEY->CR.BIT.TKGO_DONE=1;
#define  TK_MD_SEL_CNT        TOUCHKEY->CR.BIT.MODE =0;
#define  TK_MD_SEL_TIME       TOUCHKEY->CR.BIT.MODE =1;
#define  TK_SAMP_SEL_1CNT     TOUCHKEY->CR.BIT.FSW=0;
#define  TK_SAMP_SEL_3CNT     TOUCHKEY->CR.BIT.FSW=1;
#define  TK_SAMP_SEL_6CNT     TOUCHKEY->CR.BIT.FSW=2;
#define  TK_SAMP_SEL_10CNT    TOUCHKEY->CR.BIT.FSW=3;

#define  EN_TK_Fre_Random     TOUCHKEY->CR.BIT.TKRANDOM = 1;
#define  DIS_TK_Fre_Random    TOUCHKEY->CR.BIT.TKRANDOM = 0;
#define  EN_TK_Compensate     TOUCHKEY->CR.BIT.TKOFFSET = 1;
#define  DIS_TK_Compensate    TOUCHKEY->CR.BIT.TKOFFSET = 0;
#define  EN_TK_TKOSM		  TOUCHKEY->CR.BIT.TKOSM = 1; //¸úËæ²¹³¥ 
#define  TK_TKHYSW_OFF        TOUCHKEY->CR.BIT.TKHYSW = 0;    
#define  TK_TKHYSW_ON         TOUCHKEY->CR.BIT.TKHYSW = 1;
#define  TK_Fre_RDM_Offset1   TOUCHKEY->CR.BIT.RANDOM = 0;
#define  TK_Fre_RDM_Offset2   TOUCHKEY->CR.BIT.RANDOM = 1;
#define  TK_Fre_RDM_Offset3   TOUCHKEY->CR.BIT.RANDOM = 2;
#define  TK_Fre_RDM_Offset4   TOUCHKEY->CR.BIT.RANDOM = 3;

#define  TK_Data_is_Over     TOUCHKEY->FR.BIT.IFERR==1
#define  TK_GO_is_ERR        TOUCHKEY->FR.BIT.IFGO == 1
#define  TK_Scan_is_End      TOUCHKEY->FR.BIT.IFAVE == 1
#define  TK_Count_is_Over    TOUCHKEY->FR.BIT.IFCOUNT == 1
#define  CLR_ALL_TK_IF       TOUCHKEY->FR.BIT.IFERR=0; TOUCHKEY->FR.BIT.IFGOC=0;TOUCHKEY->FR.BIT.IFAVEC=0;TOUCHKEY->FR.BIT.IFCOUNTC=0;


#define  TK_CMP_Delay_8SCK   TOUCHKEY->CR.BIT.CMPD=0;
#define  TK_CMP_Delay_16SCK  TOUCHKEY->CR.BIT.CMPD=1;
#define  TK_CMP_Delay_32SCK  TOUCHKEY->CR.BIT.CMPD=2;
#define  TK_CMP_Delay_64SCK  TOUCHKEY->CR.BIT.CMPD=3;

#define  TK_Dischg_256SCK    TTOUCHKEY->CR.BIT.TUNE=0;
#define  TK_Dischg_384SCK    TTOUCHKEY->CR.BIT.TUNE=1;
#define  TK_Dischg_512SCK    TTOUCHKEY->CR.BIT.TUNE=2;
#define  TK_Dischg_640SCK    TTOUCHKEY->CR.BIT.TUNE=3;

#define  TK_DATA_RAM_ADDR    0x40023C1C;


#endif