
#ifndef _EEPROM_H_
#define _EEPROM_H_

#define EEPROM_MAGIC        0x07
#define EEPROM_CMD          0x55

#define SECTOR_BYTE         512

#define PARA_PAGE           0
#define EEPROM_PAGE1        1
#define EEPROM_PAGE2        2
#define DATA_BLKS           ((2*SECTOR_BYTE)/16)

typedef struct {
    u8 write_cmd;
    u8 erased_page;
}E2Prom_t;

/* ================================================= */
void read_para_block(void);
void save_para_block(void);
bool check_para_block(void);

//读写 PAGE1
void write_e2_bytes(u8 * src, u8 len);
void read_e2_bytes(u8 * dst, u8 len);

//读写 PAGE2
void write_e3_bytes(u8 * src, u8 len);
void read_e3_bytes(u8 * dst, u8 len);

typedef struct {
    // ！！！ 注意改变顺序，初始化程序中也要修改！！！
		u8 wash_infor_b2;					 //
	  u8 wash_infor_b1;				   //
	  u8 wash_infor_b0;          //
}E2Para_t;

extern E2Para_t eeprom_para;

#define save_level_onoff(s)  write_e2_bytes(&s,1)
#define read_level_onoff(s)  read_e2_bytes(&s,1)

#define save_clock_onoff(s)  write_e3_bytes(&s,2)
#define read_clock_onoff(s)  read_e3_bytes(&s,2)

#endif
