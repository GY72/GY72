
#ifndef __MCU_SYS_REGSITER_H
#define	__MCU_SYS_REGSITER_H

#define	L_chip_sel1XX	6			  
#define	L_chip_sel2XX	10			  
#define	L_chip_sel3XX	10  		  	

#if chip_sel ==0
#include "../Inc/sys_register_3212.h"
#elif chip_sel ==1
#include "../Inc/sys_register_6412.h"  //
#elif chip_sel ==2
#include "../Inc/sys_register_3218.h"  //
#elif chip_sel ==3
#include "../Inc/sys_register_9660.h"  //
#elif chip_sel ==4
#include "../Inc/sys_register_9662.h"  //
#elif chip_sel ==5
#include "../Inc/sys_register_1634.h"  //
#elif chip_sel ==6
#include "../Inc/sys_register_1622.h"  //
#elif chip_sel ==7
#include "../Inc/sys_register_1631.h"  //
#elif chip_sel ==8
#include "../Inc/sys_register_1622.h"  //
#elif chip_sel ==9
#include "../Inc/sys_register_1622.h"  //
#elif chip_sel ==10
#include "../Inc/sys_register_326.h"   //326о╣ап
#elif chip_sel ==11
#include "../Inc/sys_register_328.h"
#elif chip_sel ==12
#include "../Inc/sys_register_3221.h"
#elif chip_sel ==13
#include "../Inc/sys_register_1640.h"
#elif chip_sel ==14
#include "../Inc/sys_register_3281.h"
#elif chip_sel ==15
#include "../Inc/sys_register_6428.h"
#elif chip_sel ==16
#include "../Inc/sys_register_6481.h"
#elif chip_sel ==17
#include "../Inc/sys_register_6482.h"
#elif chip_sel ==18
#include "../Inc/sys_register_9260.h"
#define L_n_p0SS
#elif chip_sel ==19
#include "../Inc/sys_register_9262.h"
#elif chip_sel ==20
#include "../Inc/sys_register_9263.h"
#elif chip_sel ==21
#include "../Inc/sys_register_9661.h"
#elif chip_sel ==22
#include "../Inc/sys_register_9461.h"
#elif chip_sel ==23
#include "../Inc/sys_register_9462.h"
#elif chip_sel ==24
#include "../Inc/sys_register_9280.h"

#endif
#include "../Inc/tk_error_information.h"

#endif
