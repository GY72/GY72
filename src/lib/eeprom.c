
#include "../include_s.h"


/*
 * 2K eeprom 256*8扇区 只使用前面 扇区
 * FALSH/类 EEPROM 烧写/擦除的超级抗干扰措施：
 * 1） 在程序下载时，选择代码选项中的“enable LVR function”。
 * 2） 设置扇区时，对 XPAGE 写立即数。
 * 3） 在调用烧写或擦除函数前，置一个标志，比如 0A5H；在烧写或擦除函数中判断此标志是否为 0A5H，否则清零此标志，退出函数。
 *
 */
#define EEPROM_EMPTY 0xaa

E2Prom_t eeprom;
E2Para_t eeprom_para;

u8 para_pos;

/***************************
 * 
 * Ssp_Erase: ;擦除子程序
 */
void eeprom_erase(u8 n)
{
    bool ea_f;

    ea_f = EA;

    EA = 0;
    FLASHCON = 1;

    IB_CON1 = 0xE6;
    IB_CON2 = 0x05;
    IB_CON3 = 0x0A;
    IB_CON4 = 0x09;   

    if (eeprom.write_cmd == EEPROM_CMD)
    {
        XPAGE   = (n<<1);       //XPAGE bit0是512字节地址的高位！
        IB_CON5 = 0x06;
        NOP();
        NOP();
        NOP();
        NOP();
    }

    eeprom.write_cmd = 0;

    IB_CON1 = 0x00;
    IB_CON2 = 0x00;
    IB_CON3 = 0x00;
    IB_CON4 = 0x00;
    IB_CON5 = 0x00;
    XPAGE   = 0;

    FLASHCON = 0;
    EA = ea_f;
}

/***************************
 * 
 * 写入子程序
 */

void eeprom_write(u8 * src, u8 len, u16 addr)
{
    u8 i;
    bool ea_f;

    ea_f = EA;

    EA = 0;
    FLASHCON = 1;

    for (i = 0; i < len; i++)
    {
        IB_OFFSET   = addr;         //烧写地址低位
        XPAGE       = (addr >> 8);  //烧写地址高位
        IB_DATA     = *src++;

        IB_CON1     = 0x6E;
        IB_CON2     = 0x05;
        IB_CON3     = 0x0A;
        IB_CON4     = 0x09;

        if (eeprom.write_cmd == EEPROM_CMD)
        {
            IB_CON5 = 0x06;
            NOP();
            NOP();
            NOP();
            NOP();
        }
        else
            break;

        addr++;
    }

    eeprom.write_cmd = 0;

    IB_CON1 = 0x00;
    IB_CON2 = 0x00;
    IB_CON3 = 0x00;
    IB_CON4 = 0x00;
    IB_CON5 = 0x00;
    XPAGE   = 0;

    FLASHCON = 0;
    EA = ea_f;
}

/***************************
 * 
 * 写入子程序
 */

void save_para_block(void)
{
    eeprom.write_cmd = EEPROM_CMD;
    eeprom_erase(PARA_PAGE);
		
		eeprom_para.wash_infor_b2  = (add_50hour_up & 0x0000ff0000) >>16;
		
		eeprom_para.wash_infor_b1  = (add_50hour_up & 0x000000ff00) >>8;
		
		eeprom_para.wash_infor_b0  = (add_50hour_up & 0xff);
		
    eeprom.write_cmd   = EEPROM_CMD;
    eeprom_write((u8 *)&eeprom_para, sizeof(E2Para_t), 16+0);
}

void read_para_block(void)
{
    u8 j, len = sizeof(E2Para_t);
    u8 check_sum = 0;
		
    u8 crom * ptr  = (u8 crom *)(16+0);
    u8 * para      = (u8  *)&eeprom_para;
		
    FLASHCON = 1;
    for (j = 0; j < len; j++)
        *para++ = *ptr++;
    FLASHCON = 0;
		
     add_50hour_up = ( (eeprom_para.wash_infor_b2 & 0xffffffff) << 16) | ( (eeprom_para.wash_infor_b1 & 0xffffffff) << 8) | (eeprom_para.wash_infor_b0);
		
}

/***************************
 * 
 * 读写 PAGE1
 */
void write_e2_bytes(u8 * src, u8 len)
{
    eeprom.write_cmd = EEPROM_CMD;
    eeprom_erase(EEPROM_PAGE1);

    eeprom.write_cmd = EEPROM_CMD;
    eeprom_write(src, len, EEPROM_PAGE1*SECTOR_BYTE+0); 
}

void read_e2_bytes(u8 * dst, u8 len)
{
    u8 j;

    u8 crom * ptr  = (u8 crom *)(EEPROM_PAGE1*SECTOR_BYTE+0);

    FLASHCON = 1;
    for (j = 0; j < len; j++)
        *dst++ = *ptr++;
    FLASHCON = 0;
}


/***************************
 * 
 * 读写 PAGE2
 */
void write_e3_bytes(u8 * src, u8 len)
{
    eeprom.write_cmd = EEPROM_CMD;
    eeprom_erase(EEPROM_PAGE2);

    eeprom.write_cmd = EEPROM_CMD;
    eeprom_write(src, len, EEPROM_PAGE2*SECTOR_BYTE+0); 
}

void read_e3_bytes(u8 * dst, u8 len)
{
    u8 j;

    u8 crom * ptr  = (u8 crom *)(EEPROM_PAGE2*SECTOR_BYTE+0);

    FLASHCON = 1;
    for (j = 0; j < len; j++)
        *dst++ = *ptr++;
    FLASHCON = 0;
}
//CRC8 初始值00，原记录：a5 00 03 00 01 5b，新加两变量，第一次读 a5 00 03 00 01 5b 00 00，CRC8刚好为00!!!






