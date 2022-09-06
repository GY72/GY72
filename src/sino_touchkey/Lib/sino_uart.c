#include "../Lib/sino_touchkey.h"
#include "../Lib/sino_uart.h"
#include "../Inc/mcu_sys_regsiter.h"   //MCU头文件加载...
#include "intrins.h"

U8 xdata chk_sum,Tx_Cnt;
U8 xdata ch_N,bl_H,bl_L,rd_H,rd_L;
U8 xdata tk_count;
bit  gbUartTran;

#if EN_DataAdjust
/////////////////////////////////////////////////////////////////////////////
//
// UART初始化程序，115200波特率，1位起始位，1位停止位
//
/////////////////////////////////////////////////////////////////////////////
#if (Touch_Adjust || UART_EN )
void uartinit(void)
{
#if(UART_Sel == 2)
  	SETBANK1
  	SCON2 = 0x50;
  	SBRTH2 = 0xFF;
  	SBRTL2 = 0xF3;       //d9:38400     64:9600   F3: 115200
  	SFINE2=0x01;
	#if Touch_Adjust 
  	REN2 = 1;
	#else
	REN2 = 0;
	#endif
  	RI2 = 0;
  	SETBANK0
	//-------UART2 Port-------
	P2CR |= 0x02; 
	P2 |= 0x02;	  //TXD P2.1 OUTPUT HIGH
	#if Touch_Adjust 
	P2CR &= 0x0FE;//RXD P2.0 INPUT
	#endif	  
	//-----------------------
	#if(L_Send !=7 || Touch_Adjust)	
  	 	IEN2|=0x02;  //enable uart 2 
	#endif 
#endif
//---------------------------------------------------------------------------	  
#if(UART_Sel == 1)
  	SETBANK1
  	UART1CR = UART1_PIN;
  	SCON1 = 0x50;
  	SBRTH1 = 0xFF;
  	SBRTL1 = 0xF3;       //d9:38400     64:9600   F3: 115200
  	SFINE1=0x01;
	#if Touch_Adjust 
  	REN1 = 1;
	#else
	REN1 = 0;
	#endif
  	RI1 = 0;
  	SETBANK0
  	//-------UART1 Port-------
  	switch(UART1_PIN&0x0F0)
  	{
	  #if (chip_sel !=13)
  		case 0x00: P2CR |= 0x40; P2 |= 0x40; break; //TXD P2.6 OUTPUT HIGH
		case 0x10: P2CR |= 0x80; P2 |= 0x80; break; //TXD P2.7 OUTPUT HIGH
	  #endif
		case 0x20: P4CR |= 0x01; P4 |= 0x01; break; //TXD P4.0 OUTPUT HIGH
		case 0x30: P4CR |= 0x02; P4 |= 0x02; break; //TXD P4.1 OUTPUT HIGH
		case 0x40: P4CR |= 0x04; P4 |= 0x04; break; //TXD P4.2 OUTPUT HIGH
		case 0x50: P4CR |= 0x08; P4 |= 0x08; break; //TXD P4.3 OUTPUT HIGH
		case 0x60: SETBANK1; P5CR |= 0x01; P5 |= 0x01; SETBANK0; break;//TXD P5.0 OUTPUT HIGH
		case 0x70: SETBANK1; P5CR |= 0x02; P5 |= 0x02; SETBANK0; break;//TXD P5.1 OUTPUT HIGH
		default:    break;
  	}
	#if Touch_Adjust 
  	switch(UART1_PIN&0x0F)
  	{
	  #if (chip_sel !=13)
  		case 0x00: P2CR &= 0x0BF; break; //RXD P2.6 INPUT 
		case 0x01: P2CR &= 0x7F;  break; //RXD P2.7 INPUT 
	  #endif
		case 0x02: P4CR &= 0x0FE; break; //RXD P4.0 INPUT 
		case 0x03: P4CR &= 0x0FD; break; //RXD P4.1 INPUT 
		case 0x04: P4CR &= 0x0FB; break; //RXD P4.2 INPUT 
		case 0x05: P4CR &= 0x0F7; break; //RXD P4.3 INPUT 
		case 0x06: SETBANK1; P5CR &= 0x0FE; SETBANK0; break;//RXD P5.0 INPUT 
		case 0x07: SETBANK1; P5CR &= 0x0FD; SETBANK0; break;//RXD P5.1 INPUT 
		default:    break;
  	}
	#endif 	
  	#if(L_Send !=7 || Touch_Adjust) 	
  		IEN2|=0x01;  //enable uart 1 	*/
	#endif
#endif
//---------------------------------------------------------------------------
#if(UART_Sel ==0)
	 #if chip_sel<L_chip_sel1XX
		#if Touch_Adjust 
		P0CR &= 0x7F;
		#endif
	  	SETBANK0
	//========TX/RX CMOS Mode===== // add 20181123 zl
		P1OS = 0X03;
		P1 |= 0x01;
		P1CR |= 0x01; 
	//============================
	  	SCON = 0x50;
	  	SBRTH = 0xFF;
	  	SBRTL = 0xF7;       //F7: 115200
	  	SFINE=0x01;
		#if Touch_Adjust 
	  	REN = 1;
		#else
		REN = 0;
		#endif
	  	RI = 0;
	  	#if(L_Send !=7 || Touch_Adjust)
	  		IEN0|=0x10;  //enable uart 0  */
		#endif
	  	SETBANK0
		#warning "该型号IC的UART pin--> TX-P10/RX-P07*******************" 
		#warning "该型号IC的UART pin--> TX-P10/RX-P07*******************" 	 
	 #elif  chip_sel<L_chip_sel2XX

	  	SCON = 0x50;
	  	SBRTH = 0xFF;
	  	SBRTL = 0xF2;       //d9:38400     64:9600   F3: 115200
	  	SFINE=0x0A;
		#if Touch_Adjust 
	  	REN = 1;
		#else
		REN = 0;
		#endif
	  	RI = 0;
	   	//-------UART0 Port-------
	  	P1CR |= 0x80; 
		P1 |= 0x80; //TXD P1.7 OUTPUT HIGH	
		#if Touch_Adjust 
	    P3CR &= 0x0FE; //RXD P3.0 INPUT 
		P3PCR |= 0x01;
		#endif
	  	#if(L_Send !=7 || Touch_Adjust)
	  		IEN0|=0x10;  //enable uart 0  */
		#endif
		#warning "该型号IC的UART pin--> TX-P17/RX-P30*******************" 
		#warning "该型号IC的UART pin--> TX-P17/RX-P30*******************" 
	 #else
 		SETBANK1
	  	UART0CR = UART0_PIN;
	  	SETBANK0
	  	SCON = 0x50;
	  	SBRTH = 0xFF;
	  	SBRTL = 0xF3;       //d9:38400     64:9600   F3: 115200
	  	SFINE=0x01;
		#if Touch_Adjust 
	  	REN = 1;
		#else
		REN = 0;
		#endif
	  	RI = 0;
	   	//-------UART0 Port-------
	  	switch(UART0_PIN&0x0F0)
	  	{
	  		case 0x00: P0CR |= 0x01; P0 |= 0x01; break; //TXD P0.0 OUTPUT HIGH
			case 0x10: P0CR |= 0x02; P0 |= 0x02; break; //TXD P0.1 OUTPUT HIGH
			case 0x20: P0CR |= 0x04; P0 |= 0x04; break; //TXD P0.2 OUTPUT HIGH
			case 0x30: P0CR |= 0x08; P0 |= 0x08; break; //TXD P0.3 OUTPUT HIGH
		    #if (chip_sel !=13)
			case 0x40: P2CR |= 0x40; P2 |= 0x40; break; //TXD P2.6 OUTPUT HIGH
			case 0x50: P2CR |= 0x80; P2 |= 0x80; break; //TXD P2.7 OUTPUT HIGH
		    #endif
			case 0x60: SETBANK1; P5CR |= 0x04; P5 |= 0x04; SETBANK0; break;//TXD P5.2 OUTPUT HIGH
			case 0x70: SETBANK1; P5CR |= 0x08; P5 |= 0x08; SETBANK0; break;//TXD P5.3 OUTPUT HIGH
			default:    break;
	  	}
		#if Touch_Adjust 
	    switch(UART0_PIN&0x0F)
	  	{
	  		case 0x00: P0CR &= 0x0FE; break; //RXD P0.0 INPUT 
			case 0x01: P0CR &= 0x0FD; break; //RXD P0.1 INPUT 
			case 0x02: P0CR &= 0x0FB; break; //RXD P0.2 INPUT
			case 0x03: P0CR &= 0x0F7; break; //RXD P0.3 INPUT
			#if (chip_sel !=13) 
			case 0x04: P2CR &= 0x0BF; break; //RXD P2.6 INPUT 
			case 0x05: P2CR &= 0x7F;  break; //RXD P2.7 INPUT
			#endif 
			case 0x06: SETBANK1; P5CR &= 0x0FB; SETBANK0; break;//RXD P5.2 INPUT
			case 0x07: SETBANK1; P5CR &= 0x0F7; SETBANK0; break;//RXD P5.3 INPUT
			default:    break;
	  	}
		#endif
	  	#if(L_Send !=7 || Touch_Adjust)
	  		IEN0|=0x10;  //enable uart 0  */
		#endif
	  	SETBANK0
	 #endif 	
  #endif
}
#endif
#if EN_DataAdjust
#if(Touch_Adjust || UART_EN)
#if((L_Send != 7 && L_Send != 0)||Touch_Adjust)
void start_send(void)
{
	#if (UART_Sel ==0)
		SETBANK0 
    	TI=1;
	#endif
	#if (UART_Sel ==1)
		SETBANK1
		TI1 = 1;
		SETBANK0
	#endif
	#if (UART_Sel ==2)
		SETBANK1
		TI2 = 1;
		SETBANK0
	#endif
}
#endif
#endif
#endif


#if UART_EN
//------------------------------------------------------
#if ((L_Send>0) && (L_Send<7))
///////////////////////////////////////
//
// UART中断服务程序
//
///////////////////////////////////////
#if (UART_Sel ==0)
void Uart0Isr(void) interrupt 4
{
    U8  Tx_buf;
	_push_(INSCON);
	SETBANK0
	if(TI)
	{		
		TI = 0;
	    if(1)	  
		{
			if(Tx_Cnt == 11)
            {
				chk_sum = 0;
                Tx_Cnt = 0;
                ch_N++;
			 #if (L_Send<5)
                if(ch_N == tk_num)
                {
					ch_N = 0;
                    gbUartTran = 0;
                }
			 #endif
			 #if (L_Send >4)
			    #if(KEY_NUMBER1 >12)
		  	       if(ch_N == 24)
	               {
					  ch_N = 0;
	                  gbUartTran = 0;
	               }
				#endif
				#if (KEY_NUMBER1 <13)   
	               if(ch_N == tk_num*2)
	               {
					  ch_N = 0;
	                  gbUartTran = 0;
	               }
				#endif
			 #endif
                else
                {
					#if(L_Send ==1)	//发送低频 基线值+滤波后的值
			 			bl_H = (U8)(LF_key_baseline[ch_N]>>8);
                   		bl_L = (U8)(LF_key_baseline[ch_N]);
                    	rd_H = (U8)(LF_key[ch_N]>>8);
                    	rd_L = (U8)(LF_key[ch_N]);	
					#endif
					#if(L_Send ==2)	//发送低频 基线值+滤波前的值
				        bl_H = (U8)(LF_key_baseline[ch_N]>>8);
        				bl_L = (U8)(LF_key_baseline[ch_N]);
        				rd_H = (U8)(LF_key_filter[ch_N]>>8);
        				rd_L = (U8)(LF_key_filter[ch_N]);
					#endif
					#if(L_Send ==3)	//发送高频 基线值+滤波后的值
					    bl_H = (U8)(HF_key_baseline[ch_N]>>8);
        				bl_L = (U8)(HF_key_baseline[ch_N]);
        				rd_H = (U8)(HF_key[ch_N]>>8);
        				rd_L = (U8)(HF_key[ch_N]);
					#endif
					#if(L_Send ==4)	 //发送高频 基线值+滤波前的值
					    bl_H = (U8)(HF_key_baseline[ch_N]>>8);
        				bl_L = (U8)(HF_key_baseline[ch_N]);
        				rd_H = (U8)(HF_key_filter[ch_N]>>8);
        				rd_L = (U8)(HF_key_filter[ch_N]);
					#endif
					#if(L_Send ==5)	 //发送高频/低频基线值+滤波后的值

					   if(ch_N < tk_num)
					   {
						bl_H = (U8)(HF_key_baseline[ch_N]>>8);
        				bl_L = (U8)(HF_key_baseline[ch_N]);
        				rd_H = (U8)(HF_key[ch_N]>>8);
        				rd_L = (U8)(HF_key[ch_N]);
					   }
					   else
					   {
						bl_H = (U8)(LF_key_baseline[ch_N-tk_num]>>8);
                   		bl_L = (U8)(LF_key_baseline[ch_N-tk_num]);
                    	rd_H = (U8)(LF_key[ch_N-tk_num]>>8);
                    	rd_L = (U8)(LF_key[ch_N-tk_num]);
					   }

					#endif
					#if(L_Send ==6)
					  if(ch_N < tk_num)
					  {
					   	bl_H = (U8)(HF_key_baseline[ch_N]>>8);
        				bl_L = (U8)(HF_key_baseline[ch_N]);
        				rd_H = (U8)(HF_key_filter[ch_N]>>8);
        				rd_L = (U8)(HF_key_filter[ch_N]);
					  }
					  else
					  {
					 	bl_H = (U8)(LF_key_baseline[ch_N-tk_num]>>8);
        				bl_L = (U8)(LF_key_baseline[ch_N-tk_num]);
        				rd_H = (U8)(LF_key_filter[ch_N-tk_num]>>8);
        				rd_L = (U8)(LF_key_filter[ch_N-tk_num]);
					  }
					#endif
                }
			}
	        if(gbUartTran == 1)
	        {
				switch(Tx_Cnt)
	            {
					case 0:     Tx_buf = 0x69;      chk_sum += 0x69;      break;
	                case 1:	    Tx_buf = 0x09;      chk_sum += 0x09;      break;
	                case 2:	    Tx_buf = 0x02;      chk_sum += 0x02;      break;
	                case 3:	    Tx_buf = ch_N;   	chk_sum += ch_N;      break;
	                case 4:	    Tx_buf = bl_H;      chk_sum += bl_H;      break;
	                case 5:	    Tx_buf = bl_L;      chk_sum += bl_L;      break;
	                case 6:	    Tx_buf = 0x12;      chk_sum += 0x12;      break;
	                case 7:	    Tx_buf = ch_N;      chk_sum += ch_N;      break;
	                case 8:	    Tx_buf = rd_H;      chk_sum += rd_H;      break;
	                case 9:	    Tx_buf = rd_L;      chk_sum += rd_L;      break;
	                case 10:	Tx_buf = chk_sum;   break;
	                default:	break;
	             }
	             SBUF = Tx_buf;
	             Tx_Cnt++;
	          }

	    }	        	    
	}
	SETBANK0
	_pop_(INSCON);
}
#endif
#if (UART_Sel ==1)
void Uart1Isr(void) interrupt 15
{
    U8  Tx_buf;
	_push_(INSCON);
	SETBANK1
	if(TI1)
	{		
		TI1 = 0;
	    if(1)	       
		{
			if(Tx_Cnt == 11)
            {
				chk_sum = 0;
                Tx_Cnt = 0;
                ch_N++;
			 #if (L_Send<5)
                if(ch_N == tk_num)
                {
					ch_N = 0;
                    gbUartTran = 0;
                }
			 #endif
			 #if (L_Send >4)
			    #if(KEY_NUMBER1 >12)
		  	       if(ch_N == 24)
	               {
					  ch_N = 0;
	                  gbUartTran = 0;
	               }
				#endif
				#if (KEY_NUMBER1 <13)
	               if(ch_N == tk_num*2)
	               {
					  ch_N = 0;
	                  gbUartTran = 0;
	               }
				#endif
			 #endif
                else
                {
					#if(L_Send ==1)	//发送低频 基线值+滤波后的值
			 			bl_H = (U8)(LF_key_baseline[ch_N]>>8);
                   		bl_L = (U8)(LF_key_baseline[ch_N]);
                    	rd_H = (U8)(LF_key[ch_N]>>8);
                    	rd_L = (U8)(LF_key[ch_N]);	
					#endif
					#if(L_Send ==2)	//发送低频原始值+滤波后的值
				        bl_H = (U8)(LF_key_baseline[ch_N]>>8);
        				bl_L = (U8)(LF_key_baseline[ch_N]);
        				rd_H = (U8)(LF_key_filter[ch_N]>>8);
        				rd_L = (U8)(LF_key_filter[ch_N]);
					#endif
					#if(L_Send ==3)	//发送高频基线值+滤波后的值
					    bl_H = (U8)(HF_key_baseline[ch_N]>>8);
        				bl_L = (U8)(HF_key_baseline[ch_N]);
        				rd_H = (U8)(HF_key[ch_N]>>8);
        				rd_L = (U8)(HF_key[ch_N]);
					#endif
					#if(L_Send ==4)	 //发送高频原始值+滤波后的值
					    bl_H = (U8)(HF_key_baseline[ch_N]>>8);
        				bl_L = (U8)(HF_key_baseline[ch_N]);
        				rd_H = (U8)(HF_key_filter[ch_N]>>8);
        				rd_L = (U8)(HF_key_filter[ch_N]);
					#endif
					#if(L_Send ==5)	 //发送高频/低频基线值+滤波后的值

					   if(ch_N < tk_num)
					   {
						bl_H = (U8)(HF_key_baseline[ch_N]>>8);
        				bl_L = (U8)(HF_key_baseline[ch_N]);
        				rd_H = (U8)(HF_key[ch_N]>>8);
        				rd_L = (U8)(HF_key[ch_N]);
					   }
					   else
					   {
						bl_H = (U8)(LF_key_baseline[ch_N-tk_num]>>8);
                   		bl_L = (U8)(LF_key_baseline[ch_N-tk_num]);
                    	rd_H = (U8)(LF_key[ch_N-tk_num]>>8);
                    	rd_L = (U8)(LF_key[ch_N-tk_num]);
					   }

					#endif
					#if(L_Send ==6)
					  if(ch_N < tk_num)
					  {
					   	bl_H = (U8)(HF_key_baseline[ch_N]>>8);
        				bl_L = (U8)(HF_key_baseline[ch_N]);
        				rd_H = (U8)(HF_key_filter[ch_N]>>8);
        				rd_L = (U8)(HF_key_filter[ch_N]);
					  }
					  else
					  {
					 	bl_H = (U8)(LF_key_baseline[ch_N-tk_num]>>8);
        				bl_L = (U8)(LF_key_baseline[ch_N-tk_num]);
        				rd_H = (U8)(LF_key_filter[ch_N-tk_num]>>8);
        				rd_L = (U8)(LF_key_filter[ch_N-tk_num]);
					  }
					#endif
                }
			}
	        if(gbUartTran == 1)
	        {
				switch(Tx_Cnt)
	            {
					case 0:     Tx_buf = 0x69;      chk_sum += 0x69;      break;
	                case 1:	    Tx_buf = 0x09;      chk_sum += 0x09;      break;
	                case 2:	    Tx_buf = 0x02;      chk_sum += 0x02;      break;
	                case 3:	    Tx_buf = ch_N;   	chk_sum += ch_N;      break;
	                case 4:	    Tx_buf = bl_H;      chk_sum += bl_H;      break;
	                case 5:	    Tx_buf = bl_L;      chk_sum += bl_L;      break;
	                case 6:	    Tx_buf = 0x12;      chk_sum += 0x12;      break;
	                case 7:	    Tx_buf = ch_N;      chk_sum += ch_N;      break;
	                case 8:	    Tx_buf = rd_H;      chk_sum += rd_H;      break;
	                case 9:	    Tx_buf = rd_L;      chk_sum += rd_L;      break;
	                case 10:	Tx_buf = chk_sum;   break;
	                default:	break;
	             }
	             SBUF1 = Tx_buf;
	             Tx_Cnt++;
	          }

	    }	        	    
	}
	SETBANK0
	_pop_(INSCON);
}
#endif
#if (UART_Sel ==2)
void Uart2Isr(void) interrupt 16
{
 U8  Tx_buf;
	_push_(INSCON);
	SETBANK1
	if(TI2)
	{		
		TI2 = 0;
	    if(1)	       
		{
			if(Tx_Cnt == 11)
            {
				chk_sum = 0;
                Tx_Cnt = 0;
                ch_N++;
			 #if (L_Send<5)
                if(ch_N == tk_num)
                {
					ch_N = 0;
                    gbUartTran = 0;
                }
			 #endif
			 #if (L_Send >4)
			    #if(KEY_NUMBER1 >12)
		  	       if(ch_N == 24)
	               {
					  ch_N = 0;
	                  gbUartTran = 0;
	               }
				#endif
				#if (KEY_NUMBER1 <13)
	               if(ch_N == tk_num*2)
	               {
					  ch_N = 0;
	                  gbUartTran = 0;
	               }
				#endif
			 #endif
                else
                {
					#if(L_Send ==1)	//发送低频 基线值+滤波后的值
			 			bl_H = (U8)(LF_key_baseline[ch_N]>>8);
                   		bl_L = (U8)(LF_key_baseline[ch_N]);
                    	rd_H = (U8)(LF_key[ch_N]>>8);
                    	rd_L = (U8)(LF_key[ch_N]);	
					#endif
					#if(L_Send ==2)	//发送低频原始值+滤波后的值
				        bl_H = (U8)(LF_key_baseline[ch_N]>>8);
        				bl_L = (U8)(LF_key_baseline[ch_N]);
        				rd_H = (U8)(LF_key_filter[ch_N]>>8);
        				rd_L = (U8)(LF_key_filter[ch_N]);
					#endif
					#if(L_Send ==3)	//发送高频基线值+滤波后的值
					    bl_H = (U8)(HF_key_baseline[ch_N]>>8);
        				bl_L = (U8)(HF_key_baseline[ch_N]);
        				rd_H = (U8)(HF_key[ch_N]>>8);
        				rd_L = (U8)(HF_key[ch_N]);
					#endif
					#if(L_Send ==4)	 //发送高频原始值+滤波后的值
					    bl_H = (U8)(HF_key_baseline[ch_N]>>8);
        				bl_L = (U8)(HF_key_baseline[ch_N]);
        				rd_H = (U8)(HF_key_filter[ch_N]>>8);
        				rd_L = (U8)(HF_key_filter[ch_N]);
					#endif
					#if(L_Send ==5)	 //发送高频/低频基线值+滤波后的值

					   if(ch_N < tk_num)
					   {
						bl_H = (U8)(HF_key_baseline[ch_N]>>8);
        				bl_L = (U8)(HF_key_baseline[ch_N]);
        				rd_H = (U8)(HF_key[ch_N]>>8);
        				rd_L = (U8)(HF_key[ch_N]);
					   }
					   else
					   {
						bl_H = (U8)(LF_key_baseline[ch_N-tk_num]>>8);
                   		bl_L = (U8)(LF_key_baseline[ch_N-tk_num]);
                    	rd_H = (U8)(LF_key[ch_N-tk_num]>>8);
                    	rd_L = (U8)(LF_key[ch_N-tk_num]);
					   }

					#endif
					#if(L_Send ==6)
					  if(ch_N < tk_num)
					  {
					   	bl_H = (U8)(HF_key_baseline[ch_N]>>8);
        				bl_L = (U8)(HF_key_baseline[ch_N]);
        				rd_H = (U8)(HF_key_filter[ch_N]>>8);
        				rd_L = (U8)(HF_key_filter[ch_N]);
					  }
					  else
					  {
					 	bl_H = (U8)(LF_key_baseline[ch_N-tk_num]>>8);
        				bl_L = (U8)(LF_key_baseline[ch_N-tk_num]);
        				rd_H = (U8)(LF_key_filter[ch_N-tk_num]>>8);
        				rd_L = (U8)(LF_key_filter[ch_N-tk_num]);
					  }
					#endif
                }
			}
	        if(gbUartTran == 1)
	        {
				switch(Tx_Cnt)
	            {
					case 0:     Tx_buf = 0x69;      chk_sum += 0x69;      break;
	                case 1:	    Tx_buf = 0x09;      chk_sum += 0x09;      break;
	                case 2:	    Tx_buf = 0x02;      chk_sum += 0x02;      break;
	                case 3:	    Tx_buf = ch_N;   	chk_sum += ch_N;      break;
	                case 4:	    Tx_buf = bl_H;      chk_sum += bl_H;      break;
	                case 5:	    Tx_buf = bl_L;      chk_sum += bl_L;      break;
	                case 6:	    Tx_buf = 0x12;      chk_sum += 0x12;      break;
	                case 7:	    Tx_buf = ch_N;      chk_sum += ch_N;      break;
	                case 8:	    Tx_buf = rd_H;      chk_sum += rd_H;      break;
	                case 9:	    Tx_buf = rd_L;      chk_sum += rd_L;      break;
	                case 10:	Tx_buf = chk_sum;   break;
	                default:	break;
	             }
	             SBUF2 = Tx_buf;
	             Tx_Cnt++;
	          }

	    }	        	    
	}
	SETBANK0
	_pop_(INSCON);
}
#endif
/////////////////////////////////////////////////////////////////
//
// UART发送触摸按键基值和键值
//
////////////////////////////////////////////////////////////////
void UartTxd(void)	 
{
	if(gbUartTran == 0)
	{
        chk_sum = 0;
        Tx_Cnt =0;
        ch_N = 0;

		#if(L_Send ==1)	  //发送低频 基线值+滤波后的值
			bl_H = (U8)(LF_key_baseline[ch_N]>>8);
            bl_L = (U8)(LF_key_baseline[ch_N]);
            rd_H = (U8)(LF_key[ch_N]>>8);
            rd_L = (U8)(LF_key[ch_N]);
		#endif
		#if (L_Send ==2)  //发送低频原始值+滤波后的值
        	bl_H = (U8)(LF_key_baseline[ch_N]>>8);
        	bl_L = (U8)(LF_key_baseline[ch_N]);
        	rd_H = (U8)(LF_key_filter[ch_N]>>8);
        	rd_L = (U8)(LF_key_filter[ch_N]);
		#endif
		#if (L_Send ==3)  //发送高频基线值+滤波后的值
        	bl_H = (U8)(HF_key_baseline[ch_N]>>8);
        	bl_L = (U8)(HF_key_baseline[ch_N]);
        	rd_H = (U8)(HF_key[ch_N]>>8);
        	rd_L = (U8)(HF_key[ch_N]);
		#endif
		#if (L_Send ==4)  //发送高频原始值+滤波后的值
        	bl_H = (U8)(HF_key_baseline[ch_N]>>8);
        	bl_L = (U8)(HF_key_baseline[ch_N]);
        	rd_H = (U8)(HF_key_filter[ch_N]>>8);
        	rd_L = (U8)(HF_key_filter[ch_N]);
		#endif
		#if (L_Send ==5)  //发送高频/低频基线值+滤波后的值
        	bl_H = (U8)(HF_key_baseline[ch_N]>>8);
        	bl_L = (U8)(HF_key_baseline[ch_N]);
        	rd_H = (U8)(HF_key[ch_N]>>8);
        	rd_L = (U8)(HF_key[ch_N]);
		#endif
		#if (L_Send ==6)  //发送高频/低频原始值+滤波后的值
        	bl_H = (U8)(HF_key_baseline[ch_N]>>8);
        	bl_L = (U8)(HF_key_baseline[ch_N]);
        	rd_H = (U8)(HF_key_filter[ch_N]>>8);
        	rd_L = (U8)(HF_key_filter[ch_N]);
		#endif
	    gbUartTran = 1;
	 //-----------------------------------------
	 	start_send(); 
	 //-----------------------------------------		
    }
}
#endif
//------------------------------------------------------		

#endif //line 122

#endif
