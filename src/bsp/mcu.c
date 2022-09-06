
#include "..\include_s.h"


void clear_wdt(void)
{
  	u8 val = RSTSTAT;
	RSTSTAT = bit00000001;				//1024ms
}

/***************************
 * Company   Hiklife
 * author 	 LGX
 * date 	 2017-12-06
 * param 
 * return  
 *     
 */
void mcu_init(void)
{
	clear_wdt();

	/*	IO set 
	 *  PxCR	   0: input   1: output
	 */
	P0    = bit00000001;		// P0_6设置为输入
     P0CR  = bit10111111;                 
	P0PCR = bit00000000;

	P1    = bit00000000;   	    //
     P1CR  = bit00000000;       
	P1PCR = bit11111111;   

	P2        = bit00000011;		//P2.1TXD   P2.0RXD
     P2CR  = bit11111110;       
	P2PCR = bit00000011;  

	P3    = bit00000000;		//// P3_4设置为输入
     P3CR  = bit11101111;	    //
     P3PCR = bit00000000; 

	P4    = bit00001111;		//
     P4CR  = bit11100111;	    //
	P4PCR = bit00001100; 		// 

    SETBANK1;
  	P5    = bit00000000;		//
     P5CR  = bit11111111;	    //
     P5PCR = bit00000000;	    //
    
     
	UART0CR = bit00000000;		//P4.2 txd	P4.3 rxd  SH79F9403 在bank0
	UART1CR = bit00000000;	//
     
     SETBANK0;
	

	/***************************************************************/
	// oscsclk 系统时钟  24Mhz
	//CLKCON = bit00100000;			//12mHz
	//SET_MCU_CLK_RC_12M;
	/*  当代码选项OP_OSC为0011， 1010时， OSCXCLK为内建24MHzRC；
		当代码选项OP_OSC为0110时， 	OSCXCLK为从XTALX输入的晶体谐振器或陶瓷谐振器； */
//	SET_MCU_CLK_RC_24M;

     CLKCON = bit10001000;
	delay_10us(100);
	CLKCON |= bit10001100;


	/*timer set*/
	//标准51是12T的,就是说12个时钟周期(晶振周期,例如12M的,周期是1/12M,单位秒),机器做一个指令周期,刚好就是1/12M*12=1uS
/***************************************************************/
	// TIM3	
     SETBANK1;
	T3CON |= bit00000010;         //选用32.768khz外部振荡器
	
	TL3 = LOBYTE(65536 - 16384);					// 
     TH3 = HIBYTE(65536 - 16384);					// 0.5s
	SETBANK0;
     
     ET3=1;
     
/***************************************************************/
	// TIM4	
     SETBANK1;
	
	TL4 = LOBYTE(65535 - 12000);	 		// 
     TH4 = HIBYTE(65535 - 12000);			// 500us
	SETBANK0;
     
     IEN1|=bit00000100;
/***************************************************************/
	// TIM5	     
     SETBANK1;
     TL5 = LOBYTE(65535 - 2400);
	TH5 = HIBYTE(65535 - 2400);				// 100us
     
	SETBANK0;
     
     ET5=1;
/***************************************************************/
	// PWM引脚复用
     SETBANK1;
     PWMCR   = bit00110101;	// pwm0: P35  	// pwm1: P05  
     SETBANK0;
/***************************************************************/
	// PWM0
     
	PWM0PL = LOBYTE(158);					
	PWM0PH = HIBYTE(158);
     PWM0DL = (LOBYTE(158/2));					
	PWM0DH = (HIBYTE(158/2));
	PWM0CON = bit00010001;        //系统时钟/4
/***************************************************************/
	// PWM1
     SETBANK1;
	PWM1PL = LOBYTE(158);					
	PWM1PH = HIBYTE(158);
     PWM1DL = (LOBYTE(158/2));					
	PWM1DH = (HIBYTE(158/2));
	PWM1CON = bit00010001;
     SETBANK0;
	/***************************************************************/
	// ============ uart0 ============
	/* 这货自带波特率发生器
	 baudrate = fsys/[16*(32768-SBRT1) + SFINE1]

	 FACTOR = FSYS/16/baudrate = 12000000/16/9600 = 78.125					[2400] = 313
	 baudrate = FSYS/(16*78.125 + SFINE1)	
	 
	 *** SBRT  = 32768 - 78.125												
	 *** SFINE = FSYS/baudrate - 16*78.125 = 12000000/9600 - 16*78.125 = 2	[2400] = 5000 - 16*313 = 8
	 */
#ifdef      UART0_OPEN
	 SCON  = bit01010000;								// 允许接收，方式1， 8位异步方式，可变波特率
	 SBRTH = (32768 - BAUD_FACTOR) / 256;
	 SBRTL = (32768 - BAUD_FACTOR) % 256;
	 SFINE = SYSCLK / BAUD_RATE - 16 * BAUD_FACTOR;
	 SBRTH |= bit7;										// EUART0波特率发生器使能控制位
	
 	 ES0 = 1;											// 允许uart0中断
#endif
	// ============ uart1 ============
	/* 	*/
#ifdef      UART1_OPEN
     
	 SETBANK1;
 
	 SCON1  = bit01010000;								// 允许接收，方式1， 8位异步方式，可变波特率
	 SBRTH1 = (32768 - BAUD_FACTOR) / 256;
	 SBRTL1 = (32768 - BAUD_FACTOR) % 256;
	 SFINE1 = SYSCLK / BAUD_RATE - 16 * BAUD_FACTOR;
	 SBRTH1 |= bit7;									// EUART1波特率发生器使能控制位
 
	 SETBANK0; 
 
	 IEN2 |= bit00000001;								// 允许uart1中断
#endif      
// ============ uart2============
	/* 	*/
#ifdef      UART2_OPEN
	 SETBANK1;
 
	 SCON2  = bit01010000;								// 允许接收，方式1， 8位异步方式，可变波特率
	 SBRTH2 = (32768 - BAUD_FACTOR) / 256;
	 SBRTL2 = (32768 - BAUD_FACTOR) % 256;
	 SFINE2 = SYSCLK / BAUD_RATE - 16 * BAUD_FACTOR;
	 SBRTH2 |= bit7;									// EUART2波特率发生器使能控制位
 
	 SETBANK0; 
 
	 IEN2 |= bit00000010;								// 允许uart2中断
#endif
	/***************************************************************/
	//ext ints
	// IEN1 	|= bit00001000;			// 使能外部中断4 
	// IENC 	= bit10000000;			// int47
	// EXF0		= bit11000000;			// 外部中断4 触发方式 双沿触发
	// EXCON    = bit00110000;			// 4次采样

	//adc_init();
}

void start_interrupts(void)
{
	/*	 
	 IPL1 = bit00000010;
	 IPH1 = bit00000010; 

	 IPL0 = bit00100000;
	 IPH0 = bit00100000; */

	/***************************************************************/
	//开中断，启动定时器
     EA = 1;
	SETBANK1;
	TR3 = 1;
     TR4 = 1;
     TR5 = 1;
     PWM1CON|=0x80;
	SETBANK0;
     PWM0CON|=0x80;

}



























