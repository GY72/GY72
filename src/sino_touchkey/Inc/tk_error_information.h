#ifndef __TK_ERROR_INFORMATION_H 
#define	__TK_ERROR_INFORMATION_H

#include "../Inc/tk_conf_add.h"
///*----------------------------------------------------*/
///*          1.  按键个数参数设置错误                  */
///*----------------------------------------------------*/
#if(KEY_NUMBER1 <  multikey_num)
	#error"按键总數小于多按键數,请在配置界面(tk_conf_add.h)中修改按键总个數或多按键个數"
#endif
/*----------------------------------------------------------------------------------------------------------*/
/*            2.  按键通道配置错误                    												        */
/*----------------------------------------------------------------------------------------------------------*/
//add  new

//****************************************************************************************************
//*****************************************16tk*******************************************************
//****************************************************************************************************
#if(chip_sel==10 || chip_sel==12 ||chip_sel==19 || chip_sel==20 || chip_sel==23 )
   #if 	KEY_NUMBER1>16
	  #error "此芯片最多支持16个按键,请在配置界面(tk_conf_add.h)中重新配置按键个數"
   #endif

	#if(KEY_NUMBER1 > 0)
		#if (key0 == 0 || key0 == 12 || key0 == 13 || key0 == 14 || key0 == 19 || key0 == 20)
			#error "key0选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key0对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 1)
		#if (key1 == 0 || key1 == 12 || key1 == 13 || key1 == 14 || key1 == 19 || key1 == 20)
			#error " key1选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key1对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 2)
		#if (key2 == 0|| key2 == 12 || key2 == 13 || key2 == 14 || key2 == 19 || key2 == 20)
			#error "key2选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key2对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 3)
		#if (key3 == 0|| key3 == 12 || key3 == 13 || key3 == 14 || key3 == 19 || key3 == 20)
			#error "key3选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key3对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 4)
		#if (key4 == 0|| key4 == 12 || key4 == 13 || key4 == 14 || key4 == 19 || key4 == 20)
			#error "key4选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key4对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 5)
		#if (key5 == 0|| key5 == 12 || key5 == 13 || key5 == 14 || key5 == 19 || key5 == 20)
			#error "key5选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key5对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 6)
		#if (key6 == 0|| key6 == 12 || key6 == 13 || key6 == 14 || key6 == 19 || key6 == 20)
			#error "key6选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key6对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 7)
		#if (key7 == 0|| key7 == 12 || key7 == 13 || key7 == 14 || key7 == 19 || key7 == 20)
			#error "key7选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key7对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 8)
		#if (key8 == 0|| key8 == 12 || key8 == 13 || key8 == 14 || key8 == 19 || key8 == 20)
			#error "key8选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key8对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 9)
		#if (key9 == 0|| key9 == 12 || key9 == 13 || key9 == 14 || key9 == 19 || key9 == 20)
			#error "key9选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key9对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 10)
		#if (key10 == 0|| key10 == 12 || key10 == 13 || key10 == 14 || key10 == 19 || key10 == 20)
			#error "key10选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key10对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 11)
		#if (key11 == 0|| key11 == 12 || key11 == 13 || key11 == 14 || key11 == 19 || key11 == 20)
			#error "key11选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key11对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 12)
		#if (key12 == 0|| key12 == 12 || key12 == 13 || key12 == 14 || key12 == 19 || key12 == 20)
			#error "key12选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key12对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 13)
		#if (key13 == 0|| key13 == 12 || key13 == 13 || key13 == 14 || key13 == 19 || key13 == 20)
			#error "key13选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key13对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 14)
		#if (key14 == 0|| key14 == 12 || key14 == 13 || key14 == 14 || key14 == 19 || key14 == 20)
			#error "key14选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key14对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 15)
		#if (key15 == 0|| key15 == 12 || key15 == 13 || key15 == 14 || key15 == 19 || key15 == 20)
			#error "key15选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key15对应的Touch脚！"
		#endif
	#endif

#endif
//-----------------------------------------
//***************************************16tk-2*************************************************************
//********************************************************************************************************
//***************************************16tk-2*************************************************************
#if(chip_sel == 21) 
   #if 	KEY_NUMBER1>16
	  #error "此芯片最多支持16个按键,请在配置界面(tk_conf_add.h)中重新配置按键"
   #endif

	#if(KEY_NUMBER1 > 0)
		#if (key0 == 0||key0 == 12 || key0 == 13 || key0 == 14 || key0 == 15 || key0 == 18 || key0==19 || key0==20 || key0==21)
			#error "key0选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key0对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 1)
		#if (key1 == 0||key1 == 12 || key1 == 13 || key1 == 14 || key1 == 15 || key1 == 18 || key1==19 || key1==20 || key1==21)
			#error " key1选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key1对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 2)
		#if (key2 == 0||key2 == 12 || key2 == 13 || key2 == 14 || key2 == 15 || key2 == 18 || key2==19 || key2==20 || key2==21)
			#error "key2选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key2对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 3)
		#if (key3 == 0||key3 == 12 || key3 == 13 || key3 == 14 || key3 == 15 || key3 == 18 || key3==19 || key3==20 || key3==21)
			#error "key3选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key3对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 4)
		#if (key4 == 0||key4 == 12 || key4 == 13 || key4 == 14 || key4 == 15 || key4 == 18 || key4==19 || key4==20 || key4==21)
			#error "key4选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key4对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 5)
		#if (key5 == 0||key5 == 12 || key5 == 13 || key5 == 14 || key5 == 15 || key5 == 18 || key5==19 || key5==20 || key5==21)
			#error "key5选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key5对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 6)
		#if (key6 == 0||key6 == 12 || key6 == 13 || key6 == 14 || key6 == 15 || key6 == 18 || key6==19 || key6==20 || key6==21)
			#error "key6选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key6对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 7)
		#if (key7 == 0||key7 == 12 || key7 == 13 || key7 == 14 || key7 == 15 || key7 == 18 || key7==19 || key7==20 || key7==21)
			#error "key7选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key7对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 8)
		#if (key8 == 0||key8 == 12 || key8 == 13 || key8 == 14 || key8 == 15 || key8 == 18 || key8==19 || key8==20 || key8==21)
			#error "key8选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key8对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 9)
		#if (key9 == 0||key9 == 12 || key9 == 13 || key9 == 14 || key9 == 15 || key9 == 18 || key9==19 || key9==20 || key9==21)
			#error "key9选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key9对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 10)
		#if (key10 == 0||key10 == 12 || key10 == 13 || key10 == 14 || key10 == 15 || key10 == 18 || key10==19 || key10==20 || key10==21)
			#error "key10选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key10对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 11)
		#if (key11 == 0||key11 == 12 || key11 == 13 || key11 == 14 || key11 == 15 || key11 == 18 || key11==19 || key11==20 || key11==21)
			#error "key11选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key11对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 12)
		#if (key12 == 0||key12 == 12 || key12 == 13 || key12 == 14 || key12 == 15 || key12 == 18 || key12==19 || key12==20 || key12==21)
			#error "key12选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key12对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 13)
		#if (key13 == 0||key13 == 12 || key13 == 13 || key13 == 14 || key13 == 15 || key13 == 18 || key13==19 || key13==20 || key13==21)
			#error "key13选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key13对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 14)
		#if (key14 == 0||key14 == 12 || key14 == 13 || key14 == 14 || key14 == 15 || key14 == 18 || key14==19 || key14==20 || key14==21)
			#error "key14选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key14对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 15)
		#if (key15 == 0||key15 == 12 || key15 == 13 || key15 == 14 || key15 == 15 || key15 == 18 || key15==19 || key15==20 || key15==21)
			#error "key15选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key15对应的Touch脚！"
		#endif
	#endif

#endif
//***************************************20tk*************************************************************
//********************************************************************************************************
//***************************************20tk*************************************************************
#if(chip_sel == 13) 
   #if 	KEY_NUMBER1>20
	  #error "此芯片最多支持20个按键,请在配置界面(tk_conf_add.h)中重新配置按键"
   #endif
	#if(KEY_NUMBER1 > 0)
		#if (key0 == 0||key0 == 18 || key0 == 19 || key0 == 20 || key0 == 21 )
			#error "key0选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key0对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 1)
		#if (key1 == 0||key1 == 18 || key1 == 19 || key1 == 20 || key1 == 21 )
			#error " key1选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key1对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 2)
		#if (key2 == 0||key2 == 18 || key2 == 19 || key2 == 20 || key2 == 21 )
			#error "key2选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key2对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 3)
		#if (key3 == 0||key3 == 18 || key3 == 19 || key3 == 20 || key3 == 21 )
			#error "key3选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key3对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 4)
		#if (key4 == 0||key4 == 18 || key4 == 19 || key4 == 20 || key4 == 21 )
			#error "key4选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key4对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 5)
		#if (key5 == 0||key5 == 18 || key5 == 19 || key5 == 20 || key5 == 21 )
			#error "key5选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key5对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 6)
		#if (key6 == 0||key6 == 18 || key6 == 19 || key6 == 20 || key6 == 21 )
			#error "key6选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key6对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 7)
		#if (key7 == 0||key7 == 18 || key7 == 19 || key7 == 20 || key7 == 21 )
			#error "key7选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key7对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 8)
		#if (key8 == 0||key8 == 18 || key8 == 19 || key8 == 20 || key8 == 21 )
			#error "key8选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key8对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 9)
		#if (key9 == 0||key9 == 18 || key9 == 19 || key9 == 20 || key9 == 21 )
			#error "key9选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key9对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 10)
		#if (key10 == 0||key10 == 18 || key10 == 19 || key10 == 20 || key10 == 21 )
			#error "key10选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key10对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 11)
		#if (key11 == 0||key11 == 18 || key11 == 19 || key11 == 20 || key11 == 21 )
			#error "key11选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key11对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 12)
		#if (key12 == 0||key12 == 18 || key12 == 19 || key12 == 20 || key12 == 21 )
			#error "key12选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key12对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 13)
		#if (key13 == 0||key13 == 18 || key13 == 19 || key13 == 20 || key13 == 21 )
			#error "key13选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key13对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 14)
		#if (key14 == 0||key14 == 18 || key14 == 19 || key14 == 20 || key14 == 21 )
			#error "key14选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key14对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 15)
		#if (key15 == 0||key15 == 18 || key15 == 19 || key15 == 20 || key15 == 21 )
			#error "key15选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key15对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 16)
		#if (key16 == 0||key16 == 18 || key16 == 19 || key16 == 20 || key16 == 21 )
			#error "key16选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key16对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 17)
		#if (key17 == 0||key17 == 18 || key17 == 19 || key17 == 20 || key17 == 21 )
			#error "key17选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key17对应的Touch脚！"
		#endif
	#endif

#endif
//***************************************15tk*************************************************************
//********************************************************************************************************
//***************************************15tk*************************************************************
#if(chip_sel == 18)
   #if 	KEY_NUMBER1>15
	  #error "此芯片最多支持15个按键,请在配置界面(tk_conf_add.h)中重新配置按键"
   #endif

	#if(KEY_NUMBER1 > 0)
		#if (key0 == 0||key0 == 9 || key0 == 10 || key0 == 11 ||key0 == 12 || key0 == 13 || key0 == 14 || key0 == 15 || key0 == 19 || key0 == 20)
			#error "key0选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key0对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 1)
		#if (key1 == 0||key1 == 9 || key1 == 10 || key1 == 11 ||key1 == 12 || key1 == 13 || key1 == 14 || key1 == 15||  key1 == 19 || key1 == 20)
			#error " key1选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key1对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 2)
		#if (key2 == 0||key2 == 9 || key2 == 10 || key2 == 11 ||key2 == 12 || key2 == 13 || key2 == 14 || key2 == 15||  key2 == 19 || key2 == 20)
			#error "key2选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key2对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 3)
		#if (key3 == 0||key3 == 9 || key3 == 10 || key3 == 11 ||key3 == 12 || key3 == 13 || key3 == 14 || key3 == 15 || key3 == 19 || key3 == 20)
			#error "key3选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key3对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 4)
		#if (key4 == 0||key4 == 9 || key4 == 10 || key4 == 11 ||key4 == 12 || key4 == 13 || key4 == 14 || key4 == 15||  key4 == 19 || key4 == 20)
			#error "key4选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key4对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 5)
		#if (key5 == 0||key5 == 9 || key5 == 10 || key5 == 11 ||key5 == 12 || key5 == 13 || key5 == 14 || key5 == 15 ||  key5 == 19 || key5 == 20)
			#error "key5选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key5对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 6)
		#if (key6 == 0||key6 == 9 || key6 == 10 || key6 == 11 ||key6 == 12 || key6 == 13 || key6 == 14 || key6 == 15 || key6 == 19 || key6 == 20)
			#error "key6选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key6对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 7)
		#if (key7 == 0||key7 == 9 || key7 == 10 || key7 == 11 ||key7 == 12 || key7 == 13 || key7 == 14 || key7 == 15 || key7 == 19 || key7 == 20)
			#error "key7选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key7对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 8)
		#if (key8 == 0||key8 == 9 || key8 == 10 || key8 == 11 ||key8 == 12 || key8 == 13 || key8 == 14 || key8 == 15 || key8 == 19 || key8 == 20)
			#error "key8选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key8对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 9)
		#if (key9 == 0||key9 == 9 || key9 == 10 || key9 == 11 ||key9 == 12 || key9 == 13 || key9 == 14 || key9 == 15 || key9 == 19 || key9 == 20)
			#error "key9选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key9对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 10)
		#if (key10 == 0||key10 == 9 || key10 == 10 || key10 == 11 ||key10 == 12 || key10 == 13 || key10 == 14 || key10 == 15 || key10 == 19 || key10 == 20)
			#error "key10选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key10对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 11)
		#if (key11 == 0||key11 == 9 || key11 == 10 || key11 == 11 ||key11 == 12 || key11 == 13 || key11 == 14 || key11 == 15 || key11 == 19 || key11 == 20)
			#error "key11选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key11对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 12)
		#if (key12 == 0||key12 == 9 || key12 == 10 || key12 == 11 ||key12 == 12 || key12 == 13 || key12 == 14 || key12 == 15 || key12 == 19 || key12 == 20)
			#error "key12选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key12对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 13)
		#if (key13 == 0||key13 == 9 || key13 == 10 || key13 == 11 ||key13 == 12 || key13 == 13 || key13 == 14 || key13 == 15 || key13 == 19 || key13 == 20)
			#error "key13选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key13对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 14)
		#if (key14 == 0||key14 == 9 || key14 == 10 || key14 == 11 ||key14 == 12 || key14 == 13 || key14 == 14 || key14 == 15 || key14 == 19 || key14 == 20)
			#error "key14选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key14对应的Touch脚！"
		#endif
	#endif
#endif
//***************************************24tk*************************************************************
//********************************************************************************************************
//***************************************24tk*************************************************************
#if ((chip_sel ==11) ||(chip_sel==14)||(chip_sel==15)||(chip_sel ==16)||(chip_sel==17)||(chip_sel==22)||(chip_sel==24)) 
  #if(KEY_NUMBER1 > 0)
     #if (key0 ==0)
	    #error "key0选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key0对应的Touch脚！"
	 #endif 
  #endif
  #if(KEY_NUMBER1 > 1)
     #if (key1 ==0)
	    #error "key1选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key1对应的Touch脚！"
	 #endif 
  #endif
  #if(KEY_NUMBER1 > 2)
     #if (key2 ==0)
	    #error "key2选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key2对应的Touch脚！"
	 #endif 
  #endif
  #if(KEY_NUMBER1 > 3)
     #if (key3 ==0)
	    #error "key3选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key3对应的Touch脚！"
	 #endif 
  #endif
  #if(KEY_NUMBER1 > 4)
     #if (key4 ==0)
	    #error "key4选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key4对应的Touch脚！"
	 #endif 
  #endif
  #if(KEY_NUMBER1 > 5)
     #if (key5 ==0)
	    #error "key5选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key5对应的Touch脚！"
	 #endif 
  #endif
  #if(KEY_NUMBER1 > 6)
     #if (key6 ==0)
	    #error "key6选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key6对应的Touch脚！"
	 #endif 
  #endif
  #if(KEY_NUMBER1 > 7)
     #if (key7 ==0)
	    #error "key7选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key7对应的Touch脚！"
	 #endif 
  #endif
  #if(KEY_NUMBER1 > 8)
     #if (key8 ==0)
	    #error "key8选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key8对应的Touch脚！"
	 #endif 
  #endif
  #if(KEY_NUMBER1 > 9)
     #if (key9 ==0)
	    #error "key9选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key9对应的Touch脚！"
	 #endif 
  #endif
  #if(KEY_NUMBER1 > 10)
     #if (key10 ==0)
	    #error "key10选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key10对应的Touch脚！"
	 #endif 
  #endif
  #if(KEY_NUMBER1 > 11)
     #if (key11 ==0)
	    #error "key11选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key11对应的Touch脚！"
	 #endif 
  #endif
  #if(KEY_NUMBER1 > 12)
     #if (key12 ==0)
	    #error "key12选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key12对应的Touch脚！"
	 #endif 
  #endif
  #if(KEY_NUMBER1 > 13)
     #if (key13 ==0)
	    #error "key13选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key13对应的Touch脚！"
	 #endif 
  #endif
  #if(KEY_NUMBER1 > 14)
     #if (key14 ==0)
	    #error "key14选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key14对应的Touch脚！"
	 #endif 
  #endif
  #if(KEY_NUMBER1 > 15)
     #if (key15 ==0)
	    #error "key15选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key15对应的Touch脚！"
	 #endif 
  #endif
  #if(KEY_NUMBER1 > 16)
     #if (key16 ==0)
	    #error "key16选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key16对应的Touch脚！"
	 #endif 
  #endif
  #if(KEY_NUMBER1 > 17)
     #if (key17 ==0)
	    #error "key17选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key17对应的Touch脚！"
	 #endif 
  #endif
//------------------------------------------
#endif
//***************************************uart*************************************************************
//********************************************************************************************************
//***************************************uart*************************************************************
#if (chip_sel==10|| chip_sel==12 || chip_sel==13 || chip_sel==19|| chip_sel==20|| chip_sel==21|| chip_sel==23) 
	  #if ((Touch_Adjust==1 || UART_EN==1) &&(EN_DataAdjust==1))
	     #if UART_Sel >1
		    #error "UART 配置錯誤,请在配置界面(tk_conf_add.h)中重新设置！"
		 #endif
	  #endif
#endif
//***************************************SH79F1622*************************************************************
//************************************************************************************************************
//***************************************SH79F1622*************************************************************
#if((chip_sel >=L_chip_sel1XX)&&(chip_sel <L_chip_sel2XX))
    #if 	KEY_NUMBER1>20
	   #error "此芯片最多支持20个按键,请在配置界面(tk_conf_add.h)中重新配置按键"
    #endif
//----------------------------------------------------------------------------
	#if(KEY_NUMBER1 > 0)
		#if (key0 == 0 || key0 == 21 || key0 == 22 || key0 == 23 || key0 == 24)
			#error "key0选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key0对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 1)
		#if (key1 == 0 || key1 == 21 || key1 == 22 || key1 == 23 || key1 == 24)
			#error " key1选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key1对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 2)
		#if (key2 == 0 || key2 == 21 || key2 == 22 || key2 == 23 || key2 == 24)
			#error "key2选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key2对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 3)
		#if (key3 == 0 || key3 == 21 || key3 == 22 || key3 == 23 || key3 == 24)
			#error "key3选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key3对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 4)
		#if (key4 == 0 || key4 == 21 || key4 == 22 || key4 == 23 || key4 == 24)
			#error "key4选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key4对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 5)
		#if (key5 == 0 || key5 == 21 || key5 == 22 || key5 == 23 || key5 == 24)
			#error "key5选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key5对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 6)
		#if (key6 == 0 || key6 == 21 || key6 == 22 || key6 == 23 || key6 == 24)
			#error "key6选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key6对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 7)
		#if (key7 == 0 || key7 == 21 || key7 == 22 || key7 == 23 || key7 == 24)
			#error "key7选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key7对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 8)
		#if (key8 == 0 || key8 == 21 || key8 == 22 || key8 == 23 || key8 == 24)
			#error "key8选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key8对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 9)
		#if (key9 == 0 || key9 == 21 || key9 == 22 || key9 == 23 || key9 == 24)
			#error "key9选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key9对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 10)
		#if (key10 == 0 || key10 == 21 || key10 == 22 || key10 == 23 || key10 == 24)
			#error "key10选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key10对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 11)
		#if (key11 == 0 || key11 == 21 || key11 == 22 || key11 == 23 || key11 == 24)
			#error "key11选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key11对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 12)
		#if (key12 == 0 || key12 == 21 || key12 == 22 || key12 == 23 || key12 == 24)
			#error "key12选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key12对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 13)
		#if (key13 == 0 || key13 == 21 || key13 == 22 || key13 == 23 || key13 == 24)
			#error "key13选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key13对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 14)
		#if (key14 == 0 || key14 == 21 || key14 == 22 || key14 == 23 || key14 == 24)
			#error "key14选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key14对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 15)
		#if (key15 == 0 || key15 == 21 || key15 == 22 || key15 == 23 || key15 == 24)
			#error "key15选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key15对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 16)
		#if (key16 == 0 || key16 == 21 || key16 == 22 || key16 == 23 || key16 == 24)
			#error "key16选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key16对应的Touch脚！"
		#endif
	#endif
	#if(KEY_NUMBER1 > 17)
		#if (key17 == 0 || key17 == 21 || key17 == 22 || key17 == 23 || key17 == 24)
			#error "key17选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key17对应的Touch脚！"
		#endif
	#endif

	#if ((Touch_Adjust==1 || UART_EN==1) &&(EN_DataAdjust==1))
	    #if UART_Sel >0
		    #error "UART错误,请在配置界面(tk_conf_add.h)中选择UART0！"
		#endif
	#endif

#endif
//***************************************SH79F3212************************************************************
//************************************************************************************************************
//***************************************SH79F3212************************************************************
#if(chip_sel <L_chip_sel1XX)
   #if 	KEY_NUMBER1>8
	  #error "此芯片最多支持8个按键,请在配置界面(tk_conf_add.h)中重新配置按键"
   #endif

  #if(KEY_NUMBER1 > 0)
     #if (key0>7)
	    #error "key0选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key0对应的Touch脚！"
	 #endif 
  #endif
  #if(KEY_NUMBER1 > 1)
     #if (key1>7)
	    #error "key1选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key1对应的Touch脚！"
	 #endif 
  #endif
  #if(KEY_NUMBER1 > 2)
     #if (key2>7)
	    #error "key2选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key2对应的Touch脚！"
	 #endif 
  #endif
  #if(KEY_NUMBER1 > 3)
     #if (key3>7)
	    #error "key3选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key3对应的Touch脚！"
	 #endif 
  #endif
  #if(KEY_NUMBER1 > 4)
     #if (key4>7)
	    #error "key4选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key4对应的Touch脚！"
	 #endif 
  #endif
  #if(KEY_NUMBER1 > 5)
     #if (key5>7)
	    #error "key5选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key5对应的Touch脚！"
	 #endif 
  #endif
  #if(KEY_NUMBER1 > 6)
     #if (key6>7)
	    #error "key6选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key6对应的Touch脚！"
	 #endif 
  #endif
  #if(KEY_NUMBER1 > 7)
     #if (key7>7)
	    #error "key7选择错误：此芯片不包含该Touch脚，请在配置界面(tk_conf_add.h)中更换key7对应的Touch脚！"
	 #endif 
  #endif
//----------------------------------------------------------------------------
  #if ((Touch_Adjust==1 || UART_EN==1) &&(EN_DataAdjust==1))
     #if UART_Sel >0
	    #error "UART错误,请在配置界面(tk_conf_add.h)中选择UART0！"
	 #endif
  #endif
#endif
//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
#if( Vop==0x0c)
   #if Vref == 0x00 || Vref == 0x40
      #error "VOP电压必须大于VREF电压,请在配置界面(tk_conf_add.h)中重新设置！"
   #endif
#endif

#if( Vop==0x08)
   #if Vref == 0x00 
      #error "VOP电压必须大于VREF电压,请在配置界面(tk_conf_add.h)中重新设置！"
   #endif
#endif



#endif



