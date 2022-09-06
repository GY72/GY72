#ifndef _APP_MISC_H_
#define _APP_MISC_H_

#define CRC16_ENABLE    1
#define CRC8_ENABLE     1

typedef bool (* PIN_FUNC_t) (void);

/****************************************
 * 函数名：	get_pin_state2 
 * 说明：	引脚信号消抖函数
 * 输入：	now: 当前引脚状态，old: 上次调用输出状态 *ct: 计数指针 
 * 输出：	bool 引脚状态
 ****************************************/
bool get_pin_state2(u8 *ct, bool now, bool old);

/****************************************
 * 函数名：	bubble_sort 
 * 说明：	改进型排序  
 * 输入：	x: 需要排序首地址，n: 数据长度
 * 输出：	--
 ****************************************/
void bubble_sort(u16 *x, u8 n);

/****************************************
 * 函数名：	
 * 说明：	修改数值函数
 * 输入：	val: 需要修改数据地址，d_min: 下限，d_max: 上限
 * 输出：	true: 成功，false: 到上限或下限值，数值未修改
 ****************************************/
bool inc_data_8(u8 *val, u8 d_max);
bool dec_data_8(u8 *val, u8 d_min);
bool inc_data_16(u16 *val, u16 d_max);
bool dec_data_16(u16 *val, u16 d_min);

/****************************************
 * 函数名：	
 * 说明：	上下限值
 * 输入：	val: 需要修改数据地址，d_min: 下限，d_max: 上限
 * 输出：	true: 成功，false: 到上限或下限值，数值未修改
 ****************************************/
bool lim_min_8(u8 *val, u8 d_max);
bool lim_max_8(u8 *val, u8 d_min);
bool lim_min_16(u16 *val, u16 d_max);
bool lim_max_16(u16 *val, u16 d_min);

/****************************************
 * 函数名：u8_up u8_dn	u16_up u16_dn
 * 说明：	修改数值函数，到0xff 0xffff 或 0 停止
 * 输入：	xp: 需要修改数据地址
 * 输出：	--
 ****************************************/
void u8_up(u8 *xp);
void u8_dn(u8 *xp);

void u16_up(u16 *xp);
void u16_dn(u16 *xp);

/****************************************
 * 函数名： write_u16_int51	read_u16_int51
 * 说明：	同步读写51 u16类型数值
 * 输入：	addr: 需要修改数据地址 , val: 读写的数值
 * 输出：	--
 ****************************************/
void write_u16_int51(u16 * addr, u16 val);
u16 read_u16_int51(u16 * addr);

/****************************************
 * 函数名： get_check_sum
 * 说明：	累加和计算
 * 输入：	buf: 需要计算数据首地址, len: 数据长度
 * 		    数据长度包含了累加和
 * 输出：	u8
 ****************************************/
u8 get_check_sum(u8 *buf, u16 len);

/****************************************
 * 函数名： verify_check_sum
 * 说明：	判断一数据包的累加校验和是否正确
 * 输入：	buf: 需要计算数据首地址, len: 数据长度
 * 		    数据长度包含了累加和
 * 输出：	true: 一致 false: 不一致
 ****************************************/
bool verify_check_sum(u8 *buf, u16 len);

/****************************************
 * 函数名： crc16_cal
 * 说明：	crc16 计算函数
 * CRC16_CCITT_FALSE：多项式x16+x12+x5+1（0x1021），初始值0xFFFF，低位在后，高位在前，结果与0x0000异或
 * 输入：	buf: 需要计算数据首地址, len: 数据长度
 * 		    数据长度没有包含累加和！！！
 * 输出：	u16
 ****************************************/
#if CRC16_ENABLE
u16 crc16_cal(u8 * ptr, u16 cnt);
bool verify_check_crc16(u8 *buf, u16 len);
#endif

/****************************************
 * 函数名： crc8_calc
 * 说明：	crc8 计算函数
 * CRC16_CCITT_FALSE：多项式x16+x12+x5+1（0x1021），初始值0xFFFF，低位在后，高位在前，结果与0x0000异或
 * 输入：	buf: 需要计算数据首地址, len: 数据长度
 * 		    数据长度没有包含累加和！！！
 * 输出：	u8
 ****************************************/
#if CRC8_ENABLE
u8 crc8_calc(u8 *p, u8 cnt); 
#endif

void simple_itoa(char * str, u16 n);

#endif /* APP_MISC_H_ */