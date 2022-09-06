#ifndef _INCLUDE_S_H_
#define	_INCLUDE_S_H_

/****************************/

/****************************/
#define TOGGLE_TEST_PIN P5_3

#define UART2_OPEN

/****************************/

#include "typedef.h"
#include "define.h"
#include <string.h>
#include <stdlib.h>     //atoi
#include <stdio.h>

#include <SH79F328.h>

#include "bsp\inputs.h"
#include "bsp\outputs.h"
#include "bsp\interrupt_s.h"
#include "bsp\mcu.h"
#include "bsp\gesture.h"
#include "bsp\display.h"


#include "lib\app_timer.h"
#include "lib\key_v2.3.h"
#include "lib\tm1640.h"
#include "lib\tm16xx.h"
#include "lib\buzzer.h"
#include "lib\misc.h"
#include "lib\uart.h"
#include "lib\protocol.h"
#include "lib\handgesture.h"
#include "lib\eeprom.h"
#include "sino_touchkey\Lib\sino_touchkey.h"


#include "system.h"



#endif

