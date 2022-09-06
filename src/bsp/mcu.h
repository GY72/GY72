
#ifndef _MCU_H_
#define _MCU_H_

#define SYSCLK		24000000	// hz
#define BAUD_RATE   9600		// bps
#define BAUD_FACTOR (SYSCLK/16/BAUD_RATE)

void clear_wdt(void);
void mcu_init(void);
void start_interrupts(void);


//when code option OP_OSC =0000,OSC1CLK is internal MHz RC,OSC2CLK is Disable 
#define	    SET_MCU_CLK_RC_24M   CLKCON = (CLKCON & 0x9F);
#define	    SET_MCU_CLK_RC_12M   CLKCON = (CLKCON & 0x9F) | 0x20;
#define	    SET_MCU_CLK_RC_6M    CLKCON = (CLKCON & 0x9F) | 0x40;    
#define	    SET_MCU_CLK_RC_2M    CLKCON = (CLKCON & 0x9F) | 0x60;

#define     SETBANK0            INSCON &= 0xBF;
#define     SETBANK1            INSCON |= 0x40;

#endif

