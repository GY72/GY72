/*##################################################################################
;# History:                                                                       #
;# V1.0        1. Original                                                        #
##################################################################################*/

#ifndef _REGISTER_H_
#define _REGISTER_H_

#include <SH79F1622.H>

#define  SETBANK0             INSCON &= 0xBF;

#define  POWER_ON_RSET        (RSTSTAT & 0x20) == 0x20
#define  CLR_POR_FLAG         RSTSTAT &= 0xDF;
#define  LOW_VOLTAGE_RSET     (RSTSTAT & 0x10) == 0x10
#define  CLR_LVR_FLAG         RSTSTAT &= 0xEF;
#define  RSET_WATCHDOG        RSTSTAT &= 0x78;
#define  WDT_SET_4096ms       RSTSTAT &= 0xF8;
#define  WDT_SET_1024ms       RSTSTAT = (RSTSTAT & 0xF8) | 0x01;
#define  WDT_SET_256ms        RSTSTAT = (RSTSTAT & 0xF8) | 0x02;
#define  WDT_SET_128ms        RSTSTAT = (RSTSTAT & 0xF8) | 0x03;
#define  WDT_SET_64ms         RSTSTAT = (RSTSTAT & 0xF8) | 0x04;
#define  WDT_SET_16ms         RSTSTAT = (RSTSTAT & 0xF8) | 0x05;
#define  WDT_SET_4ms          RSTSTAT = (RSTSTAT & 0xF8) | 0x06;
#define  WDT_SET_1ms          RSTSTAT = (RSTSTAT & 0xF8) | 0x07;

//when code option OP_OSC =0000,OSC1CLK is internal 24MHz RC,OSC2CLK is Disable
#define  SET_MCU_CLK_RC_27M   CLKCON = (CLKCON & 0x9F);
#define  SET_MCU_CLK_RC_13P5M CLKCON = (CLKCON & 0x9F) | 0x20;
#define  SET_MCU_CLK_RC_6P75M CLKCON = (CLKCON & 0x9F) | 0x40;
#define  SET_MCU_CLK_RC_2P25M  CLKCON = (CLKCON & 0x9F) | 0x60;

//Touch Key
#define  Enable_Touch         TKCON1 |= 0x80;
#define  Disable_TK           TKCON1 &= 0x7F;
#define  TK_GO                TKCON1 |= 0x20;
#define  TK_DONE              (TKCON1 & 0x20) == 0
#define  EN_TK_LED_Share      TKCON1 |= 0x10;
#define  DIS_TK_LED_Share     TKCON1 &= 0xEF;
#define  TK_MD_SEL_CNT        TKCON1 &= 0xF7;
#define  TK_MD_SEL_TIME       TKCON1 |= 0x08;
#define  CHG_POW_SEL_OP       TKCON1 &= 0xFB;
#define  CHG_POW_SEL_VDD      TKCON1 |= 0x04;
#define  TK_SAMP_SEL_1CNT     TKCON1 = (TKCON1 & 0xFC);
#define  TK_SAMP_SEL_3CNT     TKCON1 = (TKCON1 & 0xFC) | 0x01;
#define  TK_SAMP_SEL_6CNT     TKCON1 = (TKCON1 & 0xFC) | 0x02;
#define  TK_SAMP_SEL_10CNT    TKCON1 = (TKCON1 & 0xFC) | 0x03;

#define  EN_TK_Fre_Random     TKRANDOM |= 0x80;
#define  DIS_TK_Fre_Random    TKRANDOM &= 0x7F;
#define  EN_TK_Compensate     TKRANDOM |= 0x40;
#define  DIS_TK_Compensate    TKRANDOM &= 0xBF;
#define  TK_Comp_POW_SEL_OP   TKRANDOM &= 0xDF;
#define  TK_Comp_POW_SEL_VDD  TKRANDOM |= 0x20;
#define  TK_Comp_POW_Weak     TKRANDOM &= 0xEF;
#define  TK_Comp_POW_Strong   TKRANDOM |= 0x10;
#define  TK_Fre_RDM_Offset1   TKRANDOM = (TKRANDOM & 0xFC);
#define  TK_Fre_RDM_Offset2   TKRANDOM = (TKRANDOM & 0xFC) | 0x01;
#define  TK_Fre_RDM_Offset3   TKRANDOM = (TKRANDOM & 0xFC) | 0x02;
#define  TK_Fre_RDM_Offset4   TKRANDOM = (TKRANDOM & 0xFC) | 0x03;

#define  TK_Data_is_Over       (TKF0 & 0x40) != 0x00
#define  TK_GO_is_ERR          (TKF0 & 0x20) != 0x00
#define  TK_Scan_is_End        (TKF0 & 0x10) != 0x00
#define  TK_Count_is_Over      (TKF0 & 0x08) != 0x00
#define  LED_Start_TK_is_Going (TKF0 & 0x04) != 0x00 
#define  CLR_ALL_TK_IF       TKF0 = 0x00;
#define  ALL_TK_IF_is_Clear  TKF0 == 0x00
//#define  TK_is_Going         (TKF0 & 0x78) == 0x00

#define  TK_VREF_SEL_2P5V    TKVREF = (TKVREF & 0x3F);
#define  TK_VREF_SEL_2V      TKVREF = (TKVREF & 0x3F) | 0x40;
#define  TK_VREF_SEL_1P5V    TKVREF = (TKVREF & 0x3F) | 0x80;
#define  TK_VREF_SEL_1V      TKVREF = (TKVREF & 0x3F) | 0xC0;
#define  TK_CMP_Delay_4SCK   TKVREF = (TKVREF & 0xCF);
#define  TK_CMP_Delay_8SCK   TKVREF = (TKVREF & 0xCF) | 0x10;
#define  TK_CMP_Delay_16SCK  TKVREF = (TKVREF & 0xCF) | 0x20;
#define  TK_CMP_Delay_32SCK  TKVREF = (TKVREF & 0xCF) | 0x30;
#define  TK_OP_SEL_4V        TKVREF = (TKVREF & 0xF3);
#define  TK_OP_SEL_3V        TKVREF = (TKVREF & 0xF3) | 0x04;
#define  TK_OP_SEL_2P5V      TKVREF = (TKVREF & 0xF3) | 0x08;
#define  TK_OP_SEL_2V        TKVREF = (TKVREF & 0xF3) | 0x0C;
#define  TK_Dischg_128SCK    TKVREF = (TKVREF & 0xFC);
#define  TK_Dischg_256SCK    TKVREF = (TKVREF & 0xFC) | 0x01;
#define  TK_Dischg_384SCK    TKVREF = (TKVREF & 0xFC) | 0x02;
#define  TK_Dischg_512SCK    TKVREF = (TKVREF & 0xFC) | 0x03;

#define  TK_DATA_RAM_ADDR    0x0500

#endif