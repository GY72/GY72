
/****************************************************************************
 * misc.c
 *
 * 	 Copyright (C) Hiklife. All rights reserved.
 *   Author: Lgx <lgx@hiklife.com>	2019-03
 * 
 *  杂项函数
 *
 ****************************************************************************/

#include "..\include_s.h"

/****************************************
 * 函数名：	get_pin_state1 
 * 说明：	禁用函数指针
 * C51函数局部变量用寄存器传递，ARM用的是堆栈，C51一般函数不能重入。
 * 函数指针还是不要用了！！！
 * 函数指针的非再入函数的副作用，在执行中出现问题。
 * 当调用树不能正确的建立，函数指针将带来问题。因为连接器不能决定函数之间的引用。
 * 在这个问题上，没有自动的解决方法。
 * 输入：	PIN_FUNC_t , old  
 * 输出：	当前引脚状态
 * 
bool get_pin_state1(PIN_FUNC_t pin_func, bool old)
{
	volatile bool s1,s2;

	s1 = (bool) pin_func();
	delay_10us(50);								// 500us 
	s2 = (bool) pin_func();

	if (s1 != s2)
		return old;
	
	delay_10us(50);								// 500us 
	s1 = (bool) pin_func();
	if (s1 != s2)
		return old;

	return s1;
}
 ****************************************/

/****************************************
 * 函数名：	get_pin_state2 
 * 说明：	引脚信号消抖函数
 * 输入：	now: 当前引脚状态，old: 上次调用输出状态 *ct: 计数指针 
 * 输出：	bool 引脚状态
 ****************************************/
bool get_pin_state2(u8 *ct, bool now, bool old)
{
	if (now == old)
	{
		*ct = 0;
		return old;
	}
	else
	{
		if ((*ct)++  > 1)
		{
			*ct = 0;
            return now;  
		}
	}

	return old;
}

/****************************************
 * 函数名：	bubble_sort 
 * 说明：	改进型排序  
 * 输入：	x: 需要排序首地址，n: 数据长度
 * 输出：	--
 ****************************************/
void bubble_sort(u16 *x, u8 n)
{
	u8 j, k, h;
	u16 t;

	for (h = n-1; h > 0; h = k)				/*循环到没有比较范围*/
	{
		for (j = 0,k = 0; j < h; j++)		/*每次预置k=0，循环扫描后更新k*/
		{
			if (*(x+j) > *(x+j+1))			/*大的放在后面，小的放到前面*/
			{
				t = *(x+j);
				*(x+j) = *(x+j+1);
				*(x+j+1) = t;				/*完成交换*/
				k = j;						/*保存最后下沉的位置。这样k后面的都是排序排好了的。*/
			}
		}
	}
}

/****************************************
 * 函数名：	
 * 说明：	修改数值函数
 * 输入：	val: 需要修改数据地址，d_min: 下限，d_max: 上限
 * 输出：	true: 成功，false: 到上限或下限值，数值未修改
 ****************************************/
bool inc_data_8(u8 *val, u8 d_max)
{
	if (*val < d_max)
	{
		*val= 1 + *val;
		return true;
	}

	return false;	
}

bool inc_data_16(u16 *val, u16 d_max)
{
	if (*val < d_max)
	{
		*val= 1 + *val;
		return true;
	}

	return false;	
}

bool dec_data_8(u8 *val, u8 d_min)
{
	if (*val > d_min)
	{
		*val = *val - 1;
		return true;
	}

	return false;	
}

bool dec_data_16(u16 *val, u16 d_min)
{
	if (*val > d_min)
	{
		*val = *val - 1;
		return true;
	}

	return false;	
}
/****************************************
 * 函数名：	
 * 说明：	上下限值
 * 输入：	val: 需要修改数据地址，d_min: 下限，d_max: 上限
 * 输出：	true: 成功，false: 到上限或下限值，数值未修改
 ****************************************/
bool lim_max_8(u8 *val, u8 d_max)
{
	if (*val >= d_max)
	{
		*val= d_max;
		return true;
	}

	return false;	
}

bool lim_max_16(u16 *val, u16 d_max)
{
	if (*val >= d_max)
	{
		*val= d_max;
		return true;
	}

	return false;	
}

bool lim_min_8(u8 *val, u8 d_min)
{
	if (*val <= d_min||*val == 0xff)
	{
		*val = d_min;
		return true;
	}

	return false;	
}

bool lim_min_16(u16 *val, u16 d_min)
{
	if (*val <= d_min)
	{
		*val = d_min;
		return true;
	}

	return false;	
}
/****************************************
 * 函数名：u8_up u8_dn	u16_up u16_dn
 * 说明：	修改数值函数，到0xff 0xffff 或 0 停止
 * 输入：	xp: 需要修改数据地址
 * 输出：	--
 ****************************************/
void u8_up(u8 *xp)
{			
	if(*xp < 0xff)
	{						
		(*xp)++;							
	}
}

void u8_dn(u8 *xp)
{				
	if(*xp != 0x00)
	{					
		(*xp)--;						
	}
}

void u16_up(u16 *xp)
{
	if(*xp < 0xffff)
	{
		(*xp)++;
	}
}

void u16_dn(u16 *xp)
{
	if(*xp != 0)
	{
		(*xp)--;
	}
}

/****************************************
 * 函数名： write_u16_int51	read_u16_int51
 * 说明：	同步读写51 u16类型数值
 * 输入：	addr: 需要修改数据地址 , val: 读写的数值
 * 输出：	--
 ****************************************/
void write_u16_int51(u16 * addr, u16 val)
{
    do{  
		* addr = val;
    }while (val != * addr);    
}

u16 read_u16_int51(u16 * addr)
{
    volatile u16 temp;

    do{ temp = * addr;
    }while (temp != * addr);
    
    return temp;
}

/****************************************
 * 函数名： get_check_sum
 * 说明：	累加和计算
 * 输入：	buf: 需要计算数据首地址, len: 数据长度
 * 		    数据长度包含了累加和
 * 输出：	u8
 ****************************************/
u8 get_check_sum(u8 *buf, u16 len)
{
	u16 i;
	u8 r = 0;
	
	for (i = 0; i < (len-1); i++)
	{
		r += buf[i];
	}
	
	return r;
}

/****************************************
 * 函数名： verify_check_sum
 * 说明：	累加校验
 * 输入：	buf: 需要计算数据首地址, len: 数据长度
 * 		    数据长度包含了累加和
 * 输出：	true: 一致 false: 不一致
 ****************************************/
bool verify_check_sum(u8 *buf, u16 len)
{
	return (get_check_sum(buf,len) == buf[len-1]) ? true : false;
}

/****************************************
 * 函数名： crc16_cal
 * 说明：	crc16 计算函数
 * CRC16_CCITT_FALSE：多项式x16+x12+x5+1（0x1021），初始值0xFFFF，低位在后，高位在前，结果与0x0000异或
 * 输入：	buf: 需要计算数据首地址, len: 数据长度
 * 		    数据长度包含了crc 2byte
 * 输出：	
 ****************************************/



/* 直接计算
u16 CRC16_CCITT_FALSE(u8 *puchMsg, u32 usDataLen)
{
	u16 wCRCin = 0xFFFF;
	u16 wCPoly = 0x1021;
	u8 wChar = 0;
	u16 i;

	while (usDataLen--)
	{
		wChar = *(puchMsg++);
		wCRCin ^= (wChar << 8);
		for (i = 0; i < 8; i++)
		{
			if (wCRCin & 0x8000)
				wCRCin = (wCRCin << 1) ^ wCPoly;
			else
				wCRCin = wCRCin << 1;
		}
	}
	return (wCRCin);
}

u16 crc16_cal(u8 *buff, u16 len)
{
    u8 i;
    u16 crc = 0xffff;        // Initial value
    while(len--)
    {
        crc ^= *buff++;        // crc ^= *data; data++;
        for (i = 0; i < 8; ++i)
        {
            if (crc & 1)
                crc = (crc >> 1) ^ 0x8408;        // 0xA001 = reverse 0x8005
            else
                crc = (crc >> 1);
        }
    }
    return ~crc;
}
*/
#if CRC16_ENABLE
/*  */
crom u16 crc16_table[256]=
{
	0X0000, 0X1021, 0X2042, 0X3063, 0X4084, 0X50A5, 0X60C6, 0X70E7,
	0X8108, 0X9129, 0XA14A, 0XB16B, 0XC18C, 0XD1AD, 0XE1CE, 0XF1EF,
	0X1231, 0X0210, 0X3273, 0X2252, 0X52B5, 0X4294, 0X72F7, 0X62D6,
	0X9339, 0X8318, 0XB37B, 0XA35A, 0XD3BD, 0XC39C, 0XF3FF, 0XE3DE,
	0X2462, 0X3443, 0X0420, 0X1401, 0X64E6, 0X74C7, 0X44A4, 0X5485,
	0XA56A, 0XB54B, 0X8528, 0X9509, 0XE5EE, 0XF5CF, 0XC5AC, 0XD58D,
	0X3653, 0X2672, 0X1611, 0X0630, 0X76D7, 0X66F6, 0X5695, 0X46B4,
	0XB75B, 0XA77A, 0X9719, 0X8738, 0XF7DF, 0XE7FE, 0XD79D, 0XC7BC,
	0X48C4, 0X58E5, 0X6886, 0X78A7, 0X0840, 0X1861, 0X2802, 0X3823,
	0XC9CC, 0XD9ED, 0XE98E, 0XF9AF, 0X8948, 0X9969, 0XA90A, 0XB92B,
	0X5AF5, 0X4AD4, 0X7AB7, 0X6A96, 0X1A71, 0X0A50, 0X3A33, 0X2A12,
	0XDBFD, 0XCBDC, 0XFBBF, 0XEB9E, 0X9B79, 0X8B58, 0XBB3B, 0XAB1A,
	0X6CA6, 0X7C87, 0X4CE4, 0X5CC5, 0X2C22, 0X3C03, 0X0C60, 0X1C41,
	0XEDAE, 0XFD8F, 0XCDEC, 0XDDCD, 0XAD2A, 0XBD0B, 0X8D68, 0X9D49,
	0X7E97, 0X6EB6, 0X5ED5, 0X4EF4, 0X3E13, 0X2E32, 0X1E51, 0X0E70,
	0XFF9F, 0XEFBE, 0XDFDD, 0XCFFC, 0XBF1B, 0XAF3A, 0X9F59, 0X8F78,
	0X9188, 0X81A9, 0XB1CA, 0XA1EB, 0XD10C, 0XC12D, 0XF14E, 0XE16F,
	0X1080, 0X00A1, 0X30C2, 0X20E3, 0X5004, 0X4025, 0X7046, 0X6067,
	0X83B9, 0X9398, 0XA3FB, 0XB3DA, 0XC33D, 0XD31C, 0XE37F, 0XF35E,
	0X02B1, 0X1290, 0X22F3, 0X32D2, 0X4235, 0X5214, 0X6277, 0X7256,
	0XB5EA, 0XA5CB, 0X95A8, 0X8589, 0XF56E, 0XE54F, 0XD52C, 0XC50D,
	0X34E2, 0X24C3, 0X14A0, 0X0481, 0X7466, 0X6447, 0X5424, 0X4405,
	0XA7DB, 0XB7FA, 0X8799, 0X97B8, 0XE75F, 0XF77E, 0XC71D, 0XD73C,
	0X26D3, 0X36F2, 0X0691, 0X16B0, 0X6657, 0X7676, 0X4615, 0X5634,
	0XD94C, 0XC96D, 0XF90E, 0XE92F, 0X99C8, 0X89E9, 0XB98A, 0XA9AB,
	0X5844, 0X4865, 0X7806, 0X6827, 0X18C0, 0X08E1, 0X3882, 0X28A3,
	0XCB7D, 0XDB5C, 0XEB3F, 0XFB1E, 0X8BF9, 0X9BD8, 0XABBB, 0XBB9A,
	0X4A75, 0X5A54, 0X6A37, 0X7A16, 0X0AF1, 0X1AD0, 0X2AB3, 0X3A92,
	0XFD2E, 0XED0F, 0XDD6C, 0XCD4D, 0XBDAA, 0XAD8B, 0X9DE8, 0X8DC9,
	0X7C26, 0X6C07, 0X5C64, 0X4C45, 0X3CA2, 0X2C83, 0X1CE0, 0X0CC1,
	0XEF1F, 0XFF3E, 0XCF5D, 0XDF7C, 0XAF9B, 0XBFBA, 0X8FD9, 0X9FF8,
	0X6E17, 0X7E36, 0X4E55, 0X5E74, 0X2E93, 0X3EB2, 0X0ED1, 0X1EF0
};

u16 crc16_cal(u8 * ptr, u16 cnt)
{
	u8  da;
	u16 crc = 0xffff;

	while (cnt--)							
	{
		da = crc >> 8;  					// CRC(h)
		crc <<= 8;
		crc ^= crc16_table[da ^ *ptr++];
	}

	return crc;
}

bool verify_check_crc16(u8 *buf, u16 len)
{
	u16 temp;

	temp = MAKEWORD(buf[len-2],buf[len-1]);
	
	return (crc16_cal(buf,len-2) == temp) ? true : false;
}

#endif

#if CRC8_ENABLE
/***************************************************** 
    描    述：  CRC8校验子程序 x^8+x^5+x^4+x^0 
    入口参数：  指向数组指针，校验字节个数 
    出口参数：  8位CRC校验码 
******************************************************/  
  
crom char CRC8Table[]={  
  0, 94, 188, 226, 97, 63, 221, 131, 194, 156, 126, 32, 163, 253, 31, 65,  
  157, 195, 33, 127, 252, 162, 64, 30, 95, 1, 227, 189, 62, 96, 130, 220,  
  35, 125, 159, 193, 66, 28, 254, 160, 225, 191, 93, 3, 128, 222, 60, 98,  
  190, 224, 2, 92, 223, 129, 99, 61, 124, 34, 192, 158, 29, 67, 161, 255,  
  70, 24, 250, 164, 39, 121, 155, 197, 132, 218, 56, 102, 229, 187, 89, 7,  
  219, 133, 103, 57, 186, 228, 6, 88, 25, 71, 165, 251, 120, 38, 196, 154,  
  101, 59, 217, 135, 4, 90, 184, 230, 167, 249, 27, 69, 198, 152, 122, 36,  
  248, 166, 68, 26, 153, 199, 37, 123, 58, 100, 134, 216, 91, 5, 231, 185,  
  140, 210, 48, 110, 237, 179, 81, 15, 78, 16, 242, 172, 47, 113, 147, 205,  
  17, 79, 173, 243, 112, 46, 204, 146, 211, 141, 111, 49, 178, 236, 14, 80,  
  175, 241, 19, 77, 206, 144, 114, 44, 109, 51, 209, 143, 12, 82, 176, 238,  
  50, 108, 142, 208, 83, 13, 239, 177, 240, 174, 76, 18, 145, 207, 45, 115,  
  202, 148, 118, 40, 171, 245, 23, 73, 8, 86, 180, 234, 105, 55, 213, 139,  
  87, 9, 235, 181, 54, 104, 138, 212, 149, 203, 41, 119, 244, 170, 72, 22,  
  233, 183, 85, 11, 136, 214, 52, 106, 43, 117, 151, 201, 74, 20, 246, 168,  
  116, 42, 200, 150, 21, 75, 169, 247, 182, 232, 10, 84, 215, 137, 107, 53  
};  
  
/****************************************
 * 函数名： crc8_calc
 * 说明：	crc8 计算函数
 * CRC-8/MAXIM	x8 + x5 + x4 + 1，初始值0,http://www.ip33.com/crc.html
 * 输入：	buf: 需要计算数据首地址, len: 数据长度
 * 		    数据长度包含了累加和
 * 输出：	u8
 ****************************************/
u8 crc8_calc(u8 *p, u8 cnt)  
{  
    unsigned char crc8 = 0;		//crc8 = 0xff时; eeprom加新数据结构，第一次计算为0

	for (; cnt > 0; cnt--)
	{
		crc8 = CRC8Table[crc8 ^ *p];
		p++;
	}
	return (crc8);
}   

/*
	u8 crc8_calc(u8 *message, u8 len)
	{
		u8 crc;
		u8 i;
		crc = 0xff;
		while (len--)
		{
			crc ^= *message++;
			for (i = 0; i < 8; i++)
			{
				if (crc & 0x01)
				{
					crc = (crc >> 1) ^ 0x8c;
				}
				else
					crc >>= 1;
			}
		}
		return crc;
	} 
*/

#endif

void simple_itoa(char * str, u16 n)
{
	u8 i = 0,j;
	char ptr[6];

	while (n)
	{
		ptr[i++] = '0' + (n%10);
		n /= 10;
	}
	
	for (j = 0; j < i; j++)
	{
		*str++ = ptr[i-j-1] ;
	}
	
	*str = '\0';
}





