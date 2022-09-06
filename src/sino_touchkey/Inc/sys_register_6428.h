/*##################################################################################
;# History:                                                                       #
;# V1.0        1. Original                                                        #
##################################################################################*/

#ifndef _REGISTER_H_
#define _REGISTER_H_

#include <SH79F6428.H>

#define  SETBANK0             INSCON &= 0xBF;
#define  SETBANK1             INSCON |= 0x40;

#define  POWER_ON_RSET        (RSTSTAT & 0x20) == 0x20
#define  CLR_POR_FLAG         RSTSTAT &= 0xDF;
#define  LOW_VOLTAGE_RSET     (RSTSTAT & 0x10) == 0x10
#define  CLR_LVR_FLAG         RSTSTAT &= 0xEF;
#define  RSET_WATCHDOG        RSTSTAT &= 0x78;
#define  WDT_SET_1024ms       RSTSTAT = (RSTSTAT & 0xF8) | 0x01;
#define  WDT_SET_256ms        RSTSTAT = (RSTSTAT & 0xF8) | 0x02;
#define  WDT_SET_128ms        RSTSTAT = (RSTSTAT & 0xF8) | 0x03;
#define  WDT_SET_64ms         RSTSTAT = (RSTSTAT & 0xF8) | 0x04;
#define  WDT_SET_16ms         RSTSTAT = (RSTSTAT & 0xF8) | 0x05;
#define  WDT_SET_4ms          RSTSTAT = (RSTSTAT & 0xF8) | 0x06;
#define  WDT_SET_1ms          RSTSTAT = (RSTSTAT & 0xF8) | 0x07;

//when code option OP_OSC =0000,OSC1CLK is internal 24MHz RC,OSC2CLK is Disable
#define  SET_MCU_CLK_RC_24M   CLKCON = (CLKCON & 0x9F);
#define  SET_MCU_CLK_RC_12M   CLKCON = (CLKCON & 0x9F) | 0x20;
#define  SET_MCU_CLK_RC_6M    CLKCON = (CLKCON & 0x9F) | 0x40;
#define  SET_MCU_CLK_RC_2M    CLKCON = (CLKCON & 0x9F) | 0x60;

//Touch Key
#define  Enable_Touch         TKCON1 |= 0x80;
#define  Disable_TK           TKCON1 &= 0x7F;
#define  TK_GO                TKCON1 |= 0x20;
#define  TK_DONE              (TKCON1 & 0x20) == 0
#define  TK_MD_SEL_CNT        TKCON1 &= 0xF7;
#define  TK_MD_SEL_TIME       TKCON1 |= 0x08;
#define  TK_SAMP_SEL_1CNT     TKCON1 = (TKCON1 & 0xFC);
#define  TK_SAMP_SEL_3CNT     TKCON1 = (TKCON1 & 0xFC) | 0x01;
#define  TK_SAMP_SEL_6CNT     TKCON1 = (TKCON1 & 0xFC) | 0x02;
#define  TK_SAMP_SEL_10CNT    TKCON1 = (TKCON1 & 0xFC) | 0x03;

#define  EN_TK_Fre_Random     TKRANDOM |= 0x80;
#define  DIS_TK_Fre_Random    TKRANDOM &= 0x7F;
#define  EN_TK_Compensate     TKRANDOM |= 0x40;
#define  DIS_TK_Compensate    TKRANDOM &= 0xBF;
#define  TK_TKHYSW_OFF        TKRANDOM &= 0xDF;  //≥Ÿ÷Õ πƒ‹  
#define  TK_TKHYSW_ON         TKRANDOM |= 0x20;
#define  TK_Comp_Squ          TKRANDOM &= 0xFB;
#define  TK_Comp_Foll         TKRANDOM |= 0x04;
#define  TK_Fre_RDM_Offset1   TKRANDOM = (TKRANDOM & 0xFC);
#define  TK_Fre_RDM_Offset2   TKRANDOM = (TKRANDOM & 0xFC) | 0x01;
#define  TK_Fre_RDM_Offset3   TKRANDOM = (TKRANDOM & 0xFC) | 0x02;
#define  TK_Fre_RDM_Offset4   TKRANDOM = (TKRANDOM & 0xFC) | 0x03;

#define  TK_Data_is_Over     (TKF0 & 0x40) != 0x00
#define  TK_GO_is_ERR        (TKF0 & 0x20) != 0x00
#define  TK_Scan_is_End      (TKF0 & 0x10) != 0x00
#define  TK_Count_is_Over    (TKF0 & 0x08) != 0x00
#define  CLR_ALL_TK_IF       TKF0 = 0x00;
#define  ALL_TK_IF_is_Clear  TKF0 == 0x00
//#define  TK_is_Going         (TKF0 & 0x78) == 0x00

#define  TK_VREF_SEL_2V      TKVREF = (TKVREF & 0x3F);
#define  TK_VREF_SEL_1P5V    TKVREF = (TKVREF & 0x3F) | 0x40;
#define  TK_VREF_SEL_1V      TKVREF = (TKVREF & 0x3F) | 0x80;
#define  TK_VREF_SEL_0P6V    TKVREF = (TKVREF & 0x3F) | 0xC0;
#define  TK_CMP_Delay_8SCK   TKVREF = (TKVREF & 0xCF);
#define  TK_CMP_Delay_16SCK  TKVREF = (TKVREF & 0xCF) | 0x10;
#define  TK_CMP_Delay_32SCK  TKVREF = (TKVREF & 0xCF) | 0x20;
#define  TK_CMP_Delay_64SCK  TKVREF = (TKVREF & 0xCF) | 0x30;
#define  TK_OP_SEL_4V        TKVREF = (TKVREF & 0xF3);
#define  TK_OP_SEL_3V        TKVREF = (TKVREF & 0xF3) | 0x04;
#define  TK_OP_SEL_2V        TKVREF = (TKVREF & 0xF3) | 0x08;
#define  TK_OP_SEL_1P2V      TKVREF = (TKVREF & 0xF3) | 0x0C;
#define  TK_Dischg_256SCK    TKVREF = (TKVREF & 0xFC);
#define  TK_Dischg_384SCK    TKVREF = (TKVREF & 0xFC) | 0x01;
#define  TK_Dischg_512SCK    TKVREF = (TKVREF & 0xFC) | 0x02;
#define  TK_Dischg_640SCK    TKVREF = (TKVREF & 0xFC) | 0x03;

//#define  DIS_ALL_TK_Chn      P0SS = 0x00;P1SS = 0x00;P4SS = 0x00;P5SS = 0x00;  TKU1 = 0x00;TKU2 = 0x00;TKU3 = 0x00;

#define  TK_DATA_RAM_ADDR    0x0500


 #define       Enable_TK1              {P1SS 	|= BIT0;	TKU1 |= BIT0;}
 #define       Enable_TK2              {P1SS 	|= BIT1;	TKU1 |= BIT1;}
 #define       Enable_TK3              {P1SS 	|= BIT2;	TKU1 |= BIT2;}
 #define       Enable_TK4              {P1SS 	|= BIT3;	TKU1 |= BIT3;}
 #define       Enable_TK5              {P1SS 	|= BIT4;	TKU1 |= BIT4;}
 #define       Enable_TK6              {P1SS 	|= BIT5;	TKU1 |= BIT5;}
 #define       Enable_TK7              {P1SS 	|= BIT6;	TKU1 |= BIT6;}
 #define       Enable_TK8              {P1SS 	|= BIT7;	TKU1 |= BIT7;}
 #define       Enable_TK15             {P0SS    |= BIT6;    TKU2 |=	BIT6;}
 #define       Enable_TK16             {P5SS    |= BIT0;    TKU2 |=	BIT7;}
 #define       Enable_TK17             {P5SS    |= BIT1;    TKU3 |=	BIT0;}
 #define       Enable_TK18             {P5SS    |= BIT2;    TKU3 |=	BIT1;}
 #define       Enable_TK21             {P4SS    |= BIT4;    TKU3 |=	BIT4;}
 #define       Enable_TK22             {P4SS    |= BIT3;    TKU3 |=	BIT5;}
 #define       Enable_TK23             {P4SS    |= BIT2;    TKU3 |=	BIT6;}
 #define       Enable_TK24             {P4SS    |= BIT1;    TKU3 |=	BIT7;}

#endif