#include "../Lib/sino_touchkey.h"
#include "../Inc/mcu_sys_regsiter.h"  
#include "intrins.h"

U8  xdata  Add_function ;	
U8  xdata  Add_Set ;			
//-----------------------------
bit  Duijiangji_flag;
U8   xdata  DuiReaCnt;
U8   xdata  Dui_num;
U8   xdata  L_Inter1;
U8   xdata  L_Inter2;
//-----------------------------基线复位计数
U16 xdata  key_stablecNT[KEY_NUMBER1];
U8  xdata  stable_limit1;
U16 xdata  STcnt_One;
U16 xdata  STcnt_Two;
//------------------------------------
U8  xdata  FLAG_COUNT_set;
U8  xdata  normal_jitter_set;
U8  xdata  init_BaseCnt_set;
U8  xdata  key_fastcounter;			//基线快跟
U8  xdata  key_stablecounter;
U8  xdata  nake_count[KEY_NUMBER1]; //
U16 xdata  nakevalue; 				//
//------------------------------------
bit CSI_flag ;
bit	 key_tkst_flag,key_tkst_flag_pre;
bit	 f_tkErr;
U8  xdata   key_sample_count;
U8  xdata   tk_num;
U32  xdata  sino_key_value;
U32  xdata  sino_key_value_pre;
U16  xdata  key_tkerrCnt;
U8  xdata   multikey_control;
U8  xdata   multikey_control2;
U8  xdata   multikey_control3;
U16 xdata HF_key_baseline[KEY_NUMBER1];
U16 xdata HF_key[KEY_NUMBER1];
U16 xdata HF_key_filter[KEY_NUMBER1];
U16 xdata HF_key_filter2[KEY_NUMBER1];
U8 	xdata HF_baseline_plus_flag[KEY_NUMBER1];
U8 	xdata HF_key_count_sub[KEY_NUMBER1];
U32 xdata HF_keytouch_flag;	//
U8 	data  HF_CSI_cnt;

U16 xdata LF_key_baseline[KEY_NUMBER1];
U16 xdata LF_key[KEY_NUMBER1];
U16 xdata LF_key_filter[KEY_NUMBER1];
U16 xdata LF_key_filter2[KEY_NUMBER1];
U8 	xdata LF_baseline_plus_flag[KEY_NUMBER1]; //
U8 	xdata LF_key_count_sub[KEY_NUMBER1];	  //
U32 xdata LF_keytouch_flag; //
U8 	data  LF_CSI_cnt;

U8 	xdata LF_key_count_fastsub[KEY_NUMBER1];  //高低频共用
U8 	xdata LF_key_flag[KEY_NUMBER1];			  //高低频共用
U8  xdata datasub_counter;
U8  xdata dataplus_counter;
U8  xdata line;  
U8  xdata R_downCnt;
U8  xdata R_downCnt2;
U8  xdata R_maxlimit;
U16 xdata R_nakelimit;
U16 code  *key_max;
U16 xdata *key_baseline;
U16 code  *key_threshold;
U16 xdata *key;
U16 xdata *key_filter;
U16 xdata *key_filter2;
U8 	xdata *key_flag;
U8 	xdata *baseline_plus_flag;
U8 	xdata *key_count_sub;
U8 	xdata *key_count_fastsub;
U32 xdata *keytouch_flag;
U8 	data  *CSI_cnt;
U8 	xdata *stblecount;
U8  xdata *R_DATA_RAM_ADDR;          
bit	 tkst_flag,tkst_flag_pre;
bit  tk_init_req;
bit  tk_adjust_flag,fre_switch_flag;

bit	 TK_GO_ERR_flag;
bit	 TK_Count_Over_flag;
bit  TK_Data_Over_flag;
bit  LED_Start_TK_Going_flag;
bit	 TK_going_flag;
bit	 TK_Scan_End_flag;

#if chip_sel<L_chip_sel1XX
#define	L_tkIntVec   0
#elif chip_sel<L_chip_sel2XX
#define	L_tkIntVec   1 //1622xx
#else
#define	L_tkIntVec   1 //326xx
#endif
///////////////////////////////////////
// Touch Key Interrupt 
///////////////////////////////////////
void isr_TK (void) interrupt  L_tkIntVec
{
	  _push_(INSCON);
	  INSCON=0X00;
	  if(TK_Scan_is_End) 				//触摸扫描结束
	  {
		CLR_ALL_TK_IF;					//清触摸按键中断标志
		line++;
		if(line>=KEY_NUMBER1)
		{
		  line=0;
		  key_tkerrCnt = 0;
		  TK_Scan_End_flag = 1;
		}
		else
		{
		      if(tkst_flag == TKST_IS_High_Fre)
			  {
					TKST = HF_TKST;
					TKDIV04 = (U8)(Tab_HF_DIV[line]>>8);   
					TKDIV03 = (U8)(Tab_HF_DIV[line]);  
			  }
			  else
			  {
					TKST = LF_TKST;
					TKDIV04 = (U8)(Tab_LF_DIV[line]>>8);   
					TKDIV03 = (U8)(Tab_LF_DIV[line]);			   
			 }
			 DisTk();
			 EnTk(Tab_Chn[line]);
			 TK_GO;		 			 
	    }
	  }
	  else
	  {
	        if(tk_init_req)
			{
			    key_tkerrCnt++;	        //上电错误计数
			}	        
			if(TK_Data_is_Over)	   		//运算结果溢出
	        {
			    TK_going_flag = 0;
	        	TK_Data_Over_flag = 1;
	        }
	        else
	        {
	            if(TK_Count_is_Over) 	//按键扫描计数溢出
	            {
				    TK_going_flag = 0;
	            	TK_Count_Over_flag = 1;				
	            }
	            else
	            {
	                if(TK_GO_is_ERR)  	//启动信号错误
	                {
					    TK_going_flag = 0;
	                	TK_GO_ERR_flag = 1;					
	                }
	            }
	        }
			CLR_ALL_TK_IF;					  	//清触摸按键中断标志
	   }

	_pop_(INSCON);
}

//====================================================================
//     触摸按键信道配置表
//====================================================================
U8  code  Tab_Chn[KEY_NUMBER1] = 
{
#if KEY_NUMBER1 >= 1
  #if chip_sel<L_chip_sel1XX
  	   key0,
  #else
       key0-1, 
  #endif
#endif
#if KEY_NUMBER1 >= 2
  #if chip_sel<L_chip_sel1XX
  	   key1,
  #else
       key1-1, 
  #endif
#endif
#if KEY_NUMBER1 >= 3
  #if chip_sel<L_chip_sel1XX
  	   key2,
  #else
       key2-1, 
  #endif
#endif
#if KEY_NUMBER1 >= 4
  #if chip_sel<L_chip_sel1XX
  	   key3,
  #else
       key3-1, 
  #endif
#endif
#if KEY_NUMBER1 >= 5
  #if chip_sel<L_chip_sel1XX
  	   key4,
  #else
       key4-1, 
  #endif
#endif
#if KEY_NUMBER1 >= 6
   #if chip_sel<L_chip_sel1XX
  	   key5,
  #else
       key5-1, 
  #endif
#endif
#if KEY_NUMBER1 >= 7
  #if chip_sel<L_chip_sel1XX
  	   key6,
  #else
       key6-1, 
  #endif
#endif
#if KEY_NUMBER1 >= 8
  #if chip_sel<L_chip_sel1XX
  	   key7,
  #else
       key7-1, 
  #endif
#endif
#if KEY_NUMBER1 >= 9
  key8-1,
#endif
#if KEY_NUMBER1 >= 10
  key9-1,
#endif
#if KEY_NUMBER1 >= 11
  key10-1,
#endif
#if KEY_NUMBER1 >= 12
  key11-1,
#endif
#if KEY_NUMBER1 >= 13
  key12-1,
#endif
#if KEY_NUMBER1 >= 14
  key13-1,
#endif
#if KEY_NUMBER1 >= 15
  key14-1,
#endif
#if KEY_NUMBER1 >= 16
  key15-1,
#endif
#if KEY_NUMBER1 >= 17
  key16-1,
#endif
#if KEY_NUMBER1 >= 18
  key17-1,
#endif
#if KEY_NUMBER1 >= 19
  key18-1,
#endif
#if KEY_NUMBER1 >= 20
  key19-1,
#endif
#if KEY_NUMBER1 >= 21
  key20-1,
#endif
#if KEY_NUMBER1 >= 22
  key21-1,
#endif
#if KEY_NUMBER1 >= 23
  key22-1,
#endif
#if KEY_NUMBER1 >= 24
  key23-1,
#endif  
};
//====================================================================
//     触摸按键最大差值配置表
//====================================================================
U16 code  HF_key_max[KEY_NUMBER1] = 
{
  #if KEY_NUMBER1 >= 1
    HF_diff0 ,  //key0
  #endif
  #if KEY_NUMBER1 >= 2
    HF_diff1 ,  //key1
  #endif
  #if KEY_NUMBER1 >= 3
    HF_diff2 ,  //key2
  #endif
  #if KEY_NUMBER1 >= 4
    HF_diff3 ,  //key3
  #endif
  #if KEY_NUMBER1 >= 5
    HF_diff4 ,  //key4
  #endif
  #if KEY_NUMBER1 >= 6
    HF_diff5 ,  //key5
  #endif
  #if KEY_NUMBER1 >= 7
    HF_diff6 ,  //key6
  #endif
  #if KEY_NUMBER1 >= 8
    HF_diff7 ,  //key7
  #endif
  #if KEY_NUMBER1 >= 9
    HF_diff8 ,  //key8
  #endif
  #if KEY_NUMBER1 >= 10
    HF_diff9 ,  //key9
  #endif
  #if KEY_NUMBER1 >= 11
    HF_diff10,  //key10
  #endif
  #if KEY_NUMBER1 >= 12
    HF_diff11,  //key11
  #endif
  #if KEY_NUMBER1 >= 13
    HF_diff12,  //key12
  #endif
  #if KEY_NUMBER1 >= 14
    HF_diff13,  //key13
  #endif
  #if KEY_NUMBER1 >= 15
    HF_diff14,  //key14
  #endif
  #if KEY_NUMBER1 >= 16
    HF_diff15,  //key15
  #endif
  #if KEY_NUMBER1 >= 17
    HF_diff16,  //key16
  #endif
  #if KEY_NUMBER1 >= 18
    HF_diff17,  //key17
  #endif
  #if KEY_NUMBER1 >= 19
    HF_diff18,  //key18
  #endif
  #if KEY_NUMBER1 >= 20
    HF_diff19,  //key19
  #endif
  #if KEY_NUMBER1 >= 21
    HF_diff20,  //key20
  #endif
  #if KEY_NUMBER1 >= 22
    HF_diff21,  //key21
  #endif
  #if KEY_NUMBER1 >= 23
    HF_diff22,  //key22
  #endif
  #if KEY_NUMBER1 >= 24
    HF_diff23,  //key23
  #endif
};
//--------------------------------------------------------------------
//	  
//--------------------------------------------------------------------
U16 code  HF_key_threshold[KEY_NUMBER1] =
{
  #if KEY_NUMBER1 >= 1
    (HF_diff0>>2)*Thrd_Per0/25,  //key0
  #endif
  #if KEY_NUMBER1 >= 2
    (HF_diff1>>2)*Thrd_Per1/25,  //key1
  #endif
  #if KEY_NUMBER1 >= 3
    (HF_diff2>>2)*Thrd_Per2/25,  //key2
  #endif
  #if KEY_NUMBER1 >= 4
    (HF_diff3>>2)*Thrd_Per3/25,  //key3
  #endif
  #if KEY_NUMBER1 >= 5
    (HF_diff4>>2)*Thrd_Per4/25,  //key4
  #endif
  #if KEY_NUMBER1 >= 6
    (HF_diff5>>2)*Thrd_Per5/25,  //key5
  #endif
  #if KEY_NUMBER1 >= 7
    (HF_diff6>>2)*Thrd_Per6/25,  //key6
  #endif
  #if KEY_NUMBER1 >= 8
    (HF_diff7>>2)*Thrd_Per7/25,  //key7
  #endif
  #if KEY_NUMBER1 >= 9
    (HF_diff8>>2)*Thrd_Per8/25,  //key8
  #endif
  #if KEY_NUMBER1 >= 10
    (HF_diff9>>2)*Thrd_Per9/25,  //key9
  #endif
  #if KEY_NUMBER1 >= 11
    (HF_diff10>>2)*Thrd_Per10/25, //key10
  #endif
  #if KEY_NUMBER1 >= 12
    (HF_diff11>>2)*Thrd_Per11/25, //key11
  #endif
  #if KEY_NUMBER1 >= 13
    (HF_diff12>>2)*Thrd_Per12/25,  //key12
  #endif
  #if KEY_NUMBER1 >= 14
    (HF_diff13>>2)*Thrd_Per13/25,  //key13
  #endif
  #if KEY_NUMBER1 >= 15
    (HF_diff14>>2)*Thrd_Per14/25,  //key14
  #endif
  #if KEY_NUMBER1 >= 16
    (HF_diff15>>2)*Thrd_Per15/25,  //key15
  #endif
  #if KEY_NUMBER1 >= 17
    (HF_diff16>>2)*Thrd_Per16/25,  //key16
  #endif
  
  #if KEY_NUMBER1 >= 18
    (HF_diff17>>2)*Thrd_Per17/25,  //key17
  #endif
  #if KEY_NUMBER1 >= 19
    (HF_diff18>>2)*Thrd_Per18/25,  //key18
  #endif
  #if KEY_NUMBER1 >= 20
    (HF_diff19>>2)*Thrd_Per19/25,  //key19
  #endif
  #if KEY_NUMBER1 >= 21
    (HF_diff20>>2)*Thrd_Per20/25,  //key20
  #endif
  #if KEY_NUMBER1 >= 22
    (HF_diff21>>2)*Thrd_Per21/25,  //key21
  #endif
  #if KEY_NUMBER1 >= 23
    (HF_diff22>>2)*Thrd_Per22/25,  //key22
  #endif  
  #if KEY_NUMBER1 >= 24
    (HF_diff23>>2)*Thrd_Per23/25,  //key23
  #endif   	
};
//====================================================================
//     LF_diff
//====================================================================
U16 code  LF_key_max[KEY_NUMBER1] = 
{
  #if KEY_NUMBER1 >= 1
    LF_diff0 ,  //key0
  #endif
  #if KEY_NUMBER1 >= 2
    LF_diff1 ,  //key1
  #endif
  #if KEY_NUMBER1 >= 3
    LF_diff2 ,  //key2
  #endif
  #if KEY_NUMBER1 >= 4
    LF_diff3 ,  //key3
  #endif
  #if KEY_NUMBER1 >= 5
    LF_diff4 ,  //key4
  #endif
  #if KEY_NUMBER1 >= 6
    LF_diff5 ,  //key5
  #endif
  #if KEY_NUMBER1 >= 7
    LF_diff6 ,  //key6
  #endif
  #if KEY_NUMBER1 >= 8
    LF_diff7 ,  //key7
  #endif
  #if KEY_NUMBER1 >= 9
    LF_diff8 ,  //key8
  #endif
  #if KEY_NUMBER1 >= 10
    LF_diff9 ,  //key9
  #endif
  #if KEY_NUMBER1 >= 11
    LF_diff10,  //key10
  #endif
  #if KEY_NUMBER1 >= 12
    LF_diff11,  //key11
  #endif
  #if KEY_NUMBER1 >= 13
    LF_diff12,  //key12
  #endif
  #if KEY_NUMBER1 >= 14
    LF_diff13,  //key13
  #endif
  #if KEY_NUMBER1 >= 15
    LF_diff14,  //key14
  #endif
  #if KEY_NUMBER1 >= 16
    LF_diff15,  //key15
  #endif
  #if KEY_NUMBER1 >= 17
    LF_diff16,  //key16
  #endif
  #if KEY_NUMBER1 >= 18
    LF_diff17,  //key17
  #endif
  #if KEY_NUMBER1 >= 19
    LF_diff18,  //key18
  #endif
  #if KEY_NUMBER1 >= 20
    LF_diff19,  //key19
  #endif
  #if KEY_NUMBER1 >= 21
    LF_diff20,  //key20
  #endif
  #if KEY_NUMBER1 >= 22
    LF_diff21,  //key21
  #endif
  #if KEY_NUMBER1 >= 23
    LF_diff22,  //key22
  #endif
  #if KEY_NUMBER1 >= 24
    LF_diff23,  //key23
  #endif
};
U16 code  LF_key_threshold[KEY_NUMBER1] =
{
  #if KEY_NUMBER1 >= 1
    (LF_diff0>>2)*Thrd_Per0/25,  //key0
  #endif
  #if KEY_NUMBER1 >= 2
    (LF_diff1>>2)*Thrd_Per1/25,  //key1
  #endif
  #if KEY_NUMBER1 >= 3
    (LF_diff2>>2)*Thrd_Per2/25,  //key2
  #endif
  #if KEY_NUMBER1 >= 4
    (LF_diff3>>2)*Thrd_Per3/25,  //key3
  #endif
  #if KEY_NUMBER1 >= 5
    (LF_diff4>>2)*Thrd_Per4/25,  //key4
  #endif
  #if KEY_NUMBER1 >= 6
    (LF_diff5>>2)*Thrd_Per5/25,  //key5
  #endif
  #if KEY_NUMBER1 >= 7
    (LF_diff6>>2)*Thrd_Per6/25,  //key6
  #endif
  #if KEY_NUMBER1 >= 8
    (LF_diff7>>2)*Thrd_Per7/25,  //key7
  #endif
  #if KEY_NUMBER1 >= 9
    (LF_diff8>>2)*Thrd_Per8/25,  //key8
  #endif
  #if KEY_NUMBER1 >= 10
    (LF_diff9>>2)*Thrd_Per9/25,  //key9
  #endif
  #if KEY_NUMBER1 >= 11
    (LF_diff10>>2)*Thrd_Per10/25, //key10
  #endif
  #if KEY_NUMBER1 >= 12
    (LF_diff11>>2)*Thrd_Per11/25, //key11
  #endif
  #if KEY_NUMBER1 >= 13
    (LF_diff12>>2)*Thrd_Per12/25,  //key12
  #endif
  #if KEY_NUMBER1 >= 14
    (LF_diff13>>2)*Thrd_Per13/25,  //key13
  #endif
  #if KEY_NUMBER1 >= 15
    (LF_diff14>>2)*Thrd_Per14/25,  //key14
  #endif
  #if KEY_NUMBER1 >= 16
    (LF_diff15>>2)*Thrd_Per15/25,  //key15
  #endif
  
  #if KEY_NUMBER1 >= 17
    (LF_diff16>>2)*Thrd_Per16/25,  //key16
  #endif
  
  #if KEY_NUMBER1 >= 18
    (LF_diff17>>2)*Thrd_Per17/25,  //key17
  #endif
  #if KEY_NUMBER1 >= 19
    (LF_diff18>>2)*Thrd_Per18/25,  //key18
  #endif
  #if KEY_NUMBER1 >= 20
    (LF_diff19>>2)*Thrd_Per19/25,  //key19
  #endif
  #if KEY_NUMBER1 >= 21
    (LF_diff20>>2)*Thrd_Per20/25,  //key20
  #endif
  #if KEY_NUMBER1 >= 22
    (LF_diff21>>2)*Thrd_Per21/25,  //key21
  #endif
  #if KEY_NUMBER1 >= 23
    (LF_diff22>>2)*Thrd_Per22/25,  //key22
  #endif  
  #if KEY_NUMBER1 >= 24
    (LF_diff23>>2)*Thrd_Per23/25,  //key23
  #endif   	  
  	
};
//====================================================================
//    TKDIV
//====================================================================
U16 code  Tab_HF_DIV[KEY_NUMBER1] = 
{
  #if KEY_NUMBER1 >= 1
    HF_DIV0,    //key_group0
  #endif
  #if KEY_NUMBER1 >= 2
    HF_DIV1,    //key_group1
  #endif
  #if KEY_NUMBER1 >= 3
    HF_DIV2,    //key_group2
  #endif
  #if KEY_NUMBER1 >= 4
    HF_DIV3,    //key_group3
  #endif
  #if KEY_NUMBER1 >= 5
    HF_DIV4,    //key_group4
  #endif
  #if KEY_NUMBER1 >= 6
    HF_DIV5,    //key_group5
  #endif
  #if KEY_NUMBER1 >= 7
    HF_DIV6,    //key_group6
  #endif
  #if KEY_NUMBER1 >= 8
    HF_DIV7,    //key_group7
  #endif
  #if KEY_NUMBER1 >= 9
    HF_DIV8,    //key_group8
  #endif
  #if KEY_NUMBER1 >= 10
    HF_DIV9,    //key_group9
  #endif
  #if KEY_NUMBER1 >= 11
    HF_DIV10,   //key_group10
  #endif
  #if KEY_NUMBER1 >= 12
    HF_DIV11,   //key_group11
  #endif
  #if KEY_NUMBER1 >= 13
    HF_DIV12,   //key_group12
  #endif
  #if KEY_NUMBER1 >= 14
    HF_DIV13,   //key_group13
  #endif
  #if KEY_NUMBER1 >= 15
    HF_DIV14,   //key_group14
  #endif
  #if KEY_NUMBER1 >= 16
    HF_DIV15,   //key_group15
  #endif

  #if KEY_NUMBER1 >= 17
    HF_DIV16,   //key_group15
  #endif
  #if KEY_NUMBER1 >= 18
    HF_DIV17,   //key_group15
  #endif
  #if KEY_NUMBER1 >= 19
    HF_DIV18,   //key_group15
  #endif
  #if KEY_NUMBER1 >= 20
    HF_DIV19,   //key_group15
  #endif
  #if KEY_NUMBER1 >= 21
    HF_DIV20,   //key_group15
  #endif
  #if KEY_NUMBER1 >= 22
    HF_DIV21,   //key_group15
  #endif
  #if KEY_NUMBER1 >= 23
    HF_DIV22,   //key_group15
  #endif
  #if KEY_NUMBER1 >= 24
    HF_DIV23,   //key_group15
  #endif

};
//==========================================================
//
//==========================================================
U16 code  Tab_LF_DIV[KEY_NUMBER1] = 
{
  #if KEY_NUMBER1 >= 1
    LF_DIV0,    //key_group0
  #endif
  #if KEY_NUMBER1 >= 2
    LF_DIV1,    //key_group1
  #endif
  #if KEY_NUMBER1 >= 3
    LF_DIV2,    //key_group2
  #endif
  #if KEY_NUMBER1 >= 4
    LF_DIV3,    //key_group3
  #endif
  #if KEY_NUMBER1 >= 5
    LF_DIV4,    //key_group4
  #endif
  #if KEY_NUMBER1 >= 6
    LF_DIV5,    //key_group5
  #endif
  #if KEY_NUMBER1 >= 7
    LF_DIV6,    //key_group6
  #endif
  #if KEY_NUMBER1 >= 8
    LF_DIV7,    //key_group7
  #endif
  #if KEY_NUMBER1 >= 9
    LF_DIV8,    //key_group8
  #endif
  #if KEY_NUMBER1 >= 10
    LF_DIV9,    //key_group9
  #endif
  #if KEY_NUMBER1 >= 11
    LF_DIV10,   //key_group10
  #endif
  #if KEY_NUMBER1 >= 12
    LF_DIV11,   //key_group11
  #endif
  #if KEY_NUMBER1 >= 13
    LF_DIV12,   //key_group12
  #endif
  #if KEY_NUMBER1 >= 14
    LF_DIV13,   //key_group13
  #endif
  #if KEY_NUMBER1 >= 15
    LF_DIV14,   //key_group14
  #endif
  #if KEY_NUMBER1 >= 16
    LF_DIV15,   //key_group15
  #endif

  #if KEY_NUMBER1 >= 17
    LF_DIV16,   //key_group16
  #endif
  #if KEY_NUMBER1 >= 18
    LF_DIV17,   //key_group17
  #endif
  #if KEY_NUMBER1 >= 19
    LF_DIV18,   //key_group18
  #endif
  #if KEY_NUMBER1 >= 20
    LF_DIV19,   //key_group19
  #endif
  #if KEY_NUMBER1 >= 21
    LF_DIV20,   //key_group20
  #endif
  #if KEY_NUMBER1 >= 22
    LF_DIV21,   //key_group21
  #endif
  #if KEY_NUMBER1 >= 23
    LF_DIV22,   //key_group22
  #endif
  #if KEY_NUMBER1 >= 24
    LF_DIV23,   //key_group23
  #endif

};
///////////////////////////////////////////////////////////////
///////////// 触摸按键阈值百分比配置表 (0~100)/////////////////
////（建议根据实际触感调整该配置，从而调整各按键灵敏度）///////
///////////////////////////////////////////////////////////////
U8  code  key_threshold_per[KEY_NUMBER1] = 
{
#if KEY_NUMBER1 >= 1
  Thrd_Per0,  //key0
#endif
#if KEY_NUMBER1 >= 2
  Thrd_Per1,  //key1
#endif
#if KEY_NUMBER1 >= 3
  Thrd_Per2,  //key2
#endif
#if KEY_NUMBER1 >= 4
  Thrd_Per3,  //key3
#endif
#if KEY_NUMBER1 >= 5
  Thrd_Per4,  //key4
#endif
#if KEY_NUMBER1 >= 6
  Thrd_Per5,  //key5
#endif
#if KEY_NUMBER1 >= 7
  Thrd_Per6,  //key6
#endif
#if KEY_NUMBER1 >= 8
  Thrd_Per7,  //key7
#endif
#if KEY_NUMBER1 >= 9
  Thrd_Per8,  //key8
#endif
#if KEY_NUMBER1 >= 10
  Thrd_Per9,  //key9
#endif
#if KEY_NUMBER1 >= 11
  Thrd_Per10, //key10
#endif
#if KEY_NUMBER1 >= 12
  Thrd_Per11, //key11
#endif
#if KEY_NUMBER1 >= 13
  Thrd_Per12, //key12
#endif
#if KEY_NUMBER1 >= 14
  Thrd_Per13, //key13
#endif
#if KEY_NUMBER1 >= 15
  Thrd_Per14, //key14
#endif
#if KEY_NUMBER1 >= 16
  Thrd_Per15, //key15
#endif
#if KEY_NUMBER1 >= 17
  Thrd_Per16, //key16
#endif
#if KEY_NUMBER1 >= 18
  Thrd_Per17, //key17
#endif
#if KEY_NUMBER1 >= 19
  Thrd_Per18, //key18
#endif
#if KEY_NUMBER1 >= 20
  Thrd_Per19, //key19
#endif
#if KEY_NUMBER1 >= 21
  Thrd_Per20, //key20
#endif
#if KEY_NUMBER1 >= 22
  Thrd_Per21, //key21
#endif
#if KEY_NUMBER1 >= 23
  Thrd_Per22, //key22
#endif
#if KEY_NUMBER1 >= 24
  Thrd_Per23, //key23
#endif
};

U8 xdata HF_stblecount[KEY_NUMBER1]={0};	 
U8 xdata LF_stblecount[KEY_NUMBER1]={0};	 
//====================================================================
//
// 触摸按键初始化
//
//====================================================================
void tk_para_init()
{
U8  i;
	tk_num = KEY_NUMBER1;
	key_tkst_flag	    =	TKST_IS_High_Fre;
	key_tkst_flag_pre   =	TKST_IS_High_Fre;
	tkst_flag 		    = 	TKST_IS_High_Fre;
	tkst_flag_pre 	    = 	TKST_IS_High_Fre;

    key_max             =   HF_key_max           ;
    key_baseline        =   HF_key_baseline      ;
    key_threshold       =   HF_key_threshold     ;
    key                 =   HF_key               ;
	stblecount          =   HF_stblecount        ;		

    keytouch_flag       =   &(HF_keytouch_flag)     ;
    key_flag            =   LF_key_flag          ;
    baseline_plus_flag  =   HF_baseline_plus_flag;
	key_count_sub       =   HF_key_count_sub     ;
    CSI_cnt             =   &(HF_CSI_cnt)        ;
    
	nakevalue = Nake_Value;  			//
	Add_function = Function;			//
	multikey_control = multikey_num + 1;//
	multikey_control2 = multikey_num + 1;
	multikey_control3 = multikey_num + 1;
	Add_Set = OtherSet;//lmy0115
	L_Inter1 = L_Inter1_set;
	L_Inter2 = L_Inter2_set;
	Dui_num = Dui_num_set;
	stable_limit1 = StableLimit_set1;
	STcnt_One =	STcnt_One_set;
	STcnt_Two = STcnt_Two_set;
	R_downCnt = L_downCnt;
	R_downCnt2 = L_downCnt2;
	R_maxlimit = L_maxlimit;
	R_nakelimit = L_nakelimit;
	FLAG_COUNT_set = FLAG_COUNT;
	init_BaseCnt_set = L_BaseCnt_set;
	normal_jitter_set = normal_jitter;
	key_fastcounter = key_fastcounter_set;
	key_stablecounter = key_stablecounter_set;

	R_DATA_RAM_ADDR = TK_DATA_RAM_ADDR;
	tk_init_req = 1;
	TK_going_flag =0;
	line=0;
    sino_key_value = 0;

    for(i=0;i<KEY_NUMBER1;i++)
	{			
		EnIO(Tab_Chn[i]);
	}
    EnTk(Tab_Chn[0]);
	tk_samp_fre_set();
	//--参数配置--//
	EN_TK_Fre_Random;
	TK_Fre_RDM_Offset4
    EN_TK_Compensate;	
#if (chip_sel<L_chip_sel1XX)  //3212系列
	TK_Comp_POW_Weak;
  	TK_Comp_POW_SEL_OP;
#endif
	TKVREF = (TKVREF & 0x3F);
	TKVREF |= Vref;
	TKVREF = (TKVREF & 0xF3);
	TKVREF |= Vop;     
#if (Function&0x04)	    
    TK_SAMP_SEL_3CNT;
#else
	TK_SAMP_SEL_1CNT;
#endif
    TK_MD_SEL_CNT;
	//------------------------------//
#if  chip_sel <L_chip_sel1XX
 	TK_CMP_Delay_32SCK;
	TK_Dischg_512SCK;  
	IEN0 |= 0x01;
	Enable_TK
#elif chip_sel<L_chip_sel2XX
  	TK_CMP_Delay_32SCK;
	TK_Dischg_512SCK; 
 	IEN0 |= 0x02;
    Enable_Touch;
#else
 	TK_CMP_Delay_64SCK;
	TK_Dischg_640SCK;  
	IEN0 |= 0x02;
    Enable_Touch;
#endif

}   
//====================================================================
//
// 触摸按键扫描信道开启
//
//====================================================================
#if chip_sel<L_chip_sel1XX
void EnTk(U8 n)
{	
	switch(n)
	{
		case 0:   P2SS |= BIT0;  TKU1 |= BIT0;  break;
    	case 1:   P2SS |= BIT1;  TKU1 |= BIT1;  break;
    	case 2:   P2SS |= BIT2;  TKU1 |= BIT2;  break;
    	case 3:   P2SS |= BIT3;  TKU1 |= BIT3;  break;
    	case 4:   P2SS |= BIT4;  TKU1 |= BIT4;  break;
    	case 5:   P2SS |= BIT5;  TKU1 |= BIT5;  break;
    	case 6:   P2SS |= BIT6;  TKU1 |= BIT6;  break;
    	case 7:   P2SS |= BIT7;  TKU1 |= BIT7;  break;
	}
}
#elif	chip_sel<L_chip_sel2XX
void EnTk(U8 n)
{	
	switch(n)
	{
		case 0:		P0SS 	|= BIT0;	TKU1 |= BIT0;		break;
		case 1:		P0SS 	|= BIT1;	TKU1 |= BIT1;		break;
		case 2:		P0SS 	|= BIT2;	TKU1 |= BIT2;		break;
		case 3:		P0SS 	|= BIT3;	TKU1 |= BIT3;		break;
		case 4:		P0SS 	|= BIT4;	TKU1 |= BIT4;		break;
		case 5:		P0SS 	|= BIT5;	TKU1 |= BIT5;		break;
		case 6:		P0SS 	|= BIT6;	TKU1 |= BIT6;		break;
		case 7:		P0SS 	|= BIT7;	TKU1 |= BIT7;		break;

		case 8:     P2SS    |= BIT0;    TKU2 |=	BIT0;		break;
		case 9:     P2SS    |= BIT1;    TKU2 |=	BIT1;		break;
		case 10:    P2SS    |= BIT2;    TKU2 |=	BIT2;		break;
		case 11:    P2SS    |= BIT3;    TKU2 |=	BIT3;		break;
		case 12:    P2SS    |= BIT4;    TKU2 |=	BIT4;		break;
		case 13:    P2SS    |= BIT5;    TKU2 |=	BIT5;		break;
		case 14:    P2SS    |= BIT6;    TKU2 |=	BIT6;		break;
		case 15:    P2SS    |= BIT7;    TKU2 |=	BIT7;		break;

		case 16:    P1SS    |= BIT1;    TKU3 |=	BIT0;		break;
		case 17:    P1SS    |= BIT2;    TKU3 |=	BIT1;		break;
		case 18:    P1SS    |= BIT3;    TKU3 |=	BIT2;		break;
		case 19:    P1SS    |= BIT4;    TKU3 |=	BIT3;		break;
	}
}
#else	  //326xx
void EnTk(U8 n)
{	
	switch(n)
	{
		case 0:		P1SS 	|= BIT0;	TKU1 |= BIT0;		break;
		case 1:		P1SS 	|= BIT1;	TKU1 |= BIT1;		break;
		case 2:		P1SS 	|= BIT2;	TKU1 |= BIT2;		break;
		case 3:		P1SS 	|= BIT3;	TKU1 |= BIT3;		break;
		case 4:		P1SS 	|= BIT4;	TKU1 |= BIT4;		break;
		case 5:		P1SS 	|= BIT5;	TKU1 |= BIT5;		break;
		case 6:		P1SS 	|= BIT6;	TKU1 |= BIT6;		break;
		case 7:		P1SS 	|= BIT7;	TKU1 |= BIT7;		break;
	   #ifndef L_n_p0SS
		case 8:     P0SS    |= BIT0;    TKU2 |=	BIT0;		break;
		case 9:     P0SS    |= BIT1;    TKU2 |=	BIT1;		break;
		case 10:    P0SS    |= BIT2;    TKU2 |=	BIT2;		break;
		case 11:    P0SS    |= BIT3;    TKU2 |=	BIT3;		break;
		case 12:    P0SS    |= BIT4;    TKU2 |=	BIT4;		break;
		case 13:    P0SS    |= BIT5;    TKU2 |=	BIT5;		break;
		case 14:    P0SS    |= BIT6;    TKU2 |=	BIT6;		break;
	   #endif
		case 15:    P5SS    |= BIT0;    TKU2 |=	BIT7;		break;
		case 16:    P5SS    |= BIT1;    TKU3 |=	BIT0;		break;
		case 17:    P5SS    |= BIT2;    TKU3 |=	BIT1;		break;
		case 18:    P5SS    |= BIT3;    TKU3 |=	BIT2;		break;
		case 19:    P4SS    |= BIT5;    TKU3 |=	BIT3;		break;
		case 20:    P4SS    |= BIT4;    TKU3 |=	BIT4;		break;
		case 21:    P4SS    |= BIT3;    TKU3 |=	BIT5;		break;
		case 22:    P4SS    |= BIT2;    TKU3 |=	BIT6;		break;
		case 23:    P4SS    |= BIT1;    TKU3 |=	BIT7;		break;
	}
}
#endif
//====================================================================
//
// 触摸按键扫描信道IO设置
//
//====================================================================
#if chip_sel<L_chip_sel1XX
void EnIO(U8 n)
{	
	switch(n)
	{
		case 0:		P1CR	|= BIT7;	P1 &= 0x7F;		    break;
		case 1:		P2CR 	|= BIT0;	P2 &= 0xFE;		    break;
		case 2:		P2CR 	|= BIT1;	P2 &= 0xFD;		    break;
		case 3:		P2CR 	|= BIT2;	P2 &= 0xFB;		    break;
		case 4:		P2CR 	|= BIT3;	P2 &= 0xF7;		    break;
		case 5:		P2CR	|= BIT4;	P2 &= 0xEF;		    break;
		case 6:		P2CR 	|= BIT5;	P2 &= 0xDF;		    break;
		case 7:		P2CR 	|= BIT6;	P2 &= 0XBF;	     	break;
	}
}
#elif	chip_sel<L_chip_sel2XX
void EnIO(U8 n)
{	
	switch(n)
	{
		case 0:		P0CR	|= BIT0;	P0 &= 0xFE;		    break;
		case 1:		P0CR 	|= BIT1;	P0 &= 0xFD;		    break;
		case 2:		P0CR 	|= BIT2;	P0 &= 0xFB;		    break;
		case 3:		P0CR 	|= BIT3;	P0 &= 0xF7;		    break;
		case 4:		P0CR 	|= BIT4;	P0 &= 0xEF;		    break;
		case 5:		P0CR	|= BIT5;	P0 &= 0xDF;		    break;
		case 6:		P0CR 	|= BIT6;	P0 &= 0xBF;		    break;
		case 7:		P0CR 	|= BIT7;	P0 &= 0X7F;	     	break;
	    case 8:     P2CR    |= BIT0;    P2 &= 0xFE;	    	break;
		case 9:     P2CR    |= BIT1;    P2 &= 0xFD; 		break;
		case 10:    P2CR    |= BIT2;    P2 &= 0xFB; 		break;
		case 11:    P2CR    |= BIT3;    P2 &= 0xF7; 		break;
		case 12:    P2CR    |= BIT4;    P2 &= 0xEF; 		break;
		case 13:    P2CR    |= BIT5;    P2 &= 0xDF;			break;
		case 14:    P2CR    |= BIT6;    P2 &= 0xBF;	    	break;
		case 15:    P2CR    |= BIT7;    P2 &= 0X7F;	    	break;
		case 16:    P1CR    |= BIT1;    P1 &= 0xFD; 		break;
		case 17:    P1CR    |= BIT2;    P1 &= 0xFB; 		break;
		case 18:    P1CR    |= BIT3;    P1 &= 0xF7; 		break;
		case 19:    P1CR    |= BIT4;    P1 &= 0xEF; 		break;
	}
}
#else	 //326xx
void EnIO(U8 n)
{	
	switch(n)
	{
		case 0:		P1CR	|= BIT0;	P1 &= 0xFE;		    break;
		case 1:		P1CR 	|= BIT1;	P1 &= 0xFD;		    break;
		case 2:		P1CR 	|= BIT2;	P1 &= 0xFB;		    break;
		case 3:		P1CR 	|= BIT3;	P1 &= 0xF7;		    break;
		case 4:		P1CR 	|= BIT4;	P1 &= 0xEF;		    break;
		case 5:		P1CR	|= BIT5;	P1 &= 0xDF;		    break;
		case 6:		P1CR 	|= BIT6;	P1 &= 0xBF;		    break;
		case 7:		P1CR 	|= BIT7;	P1 &= 0X7F;	     	break;
	    case 8:     P0CR    |= BIT0;    P0 &=0xFE;	    	break;
		case 9:     P0CR    |= BIT1;    P0 &= 0xFD; 		break;
		case 10:    P0CR    |= BIT2;    P0 &= 0xFB; 		break;
		case 11:    P0CR    |= BIT3;    P0 &= 0xF7; 		break;
		case 12:    P0CR    |= BIT4;    P0 &= 0xEF; 		break;
		case 13:    P0CR    |= BIT5;    P0 &= 0xDF;			break;
		case 14:    P0CR    |= BIT6;    P0 &= 0xBF;	    	break;
		case 15:    INSCON=0x40;        P5CR |= BIT0;       P5 |= 0x01;	INSCON=0x00;   	break;
		case 16:    INSCON=0x40;        P5CR |= BIT1;       P5 |= 0x02; INSCON=0x00;  	break;
		case 17:    INSCON=0x40;        P5CR |= BIT2;       P5 &= 0xFB;	INSCON=0x00; 	break;
		case 18:    INSCON=0x40;        P5SS |= BIT3;       P5 &= 0xF7;	INSCON=0x00;	break;
		case 19:    P4CR    |= BIT5;    P4 &= 0xDF; 		break;
		case 20:    P4CR    |= BIT4;    P4 &= 0xEF; 		break;
		case 21:    P4CR    |= BIT3;    P4 &= 0xF7; 		break;
		case 22:    P4CR    |= BIT2;    P4 &= 0xFB; 		break;
		case 23:    P4CR    |= BIT1;    P4 &= 0xFD; 		break;
	}
}

#endif
//====================================================================
//
// Disable touch key 
//
//====================================================================
#if chip_sel<L_chip_sel1XX
void DisTk(void)
{
   TKU1=0;
   P2SS=0;
}
#elif chip_sel<L_chip_sel2XX
void DisTk(void)
 {
   TKU1=0;
   TKU2=0;
   TKU3=0;
   P0SS=0;
   P1SS=0;
   P2SS=0;
}
#else
void DisTk(void)
 {
   TKU1=0;
   TKU2=0;
   TKU3=0;
#ifndef L_n_p0SS
   P0SS=0;
#endif
   P1SS=0;
   P4SS=0;
   P5SS=0;
}
#endif
//====================================================================
//
// 触摸按键开关频率及放大系数设定
//
//====================================================================
void tk_samp_fre_set()	
{   
	TKDIV01 = 0x00;
	TKDIV02 = 0x00;		// 放大系数寄存器
//扫完最后一个通道，在开始下一次（轮）扫描前将参数切换至第一通道
	DisTk();
	EnTk(Tab_Chn[line]);	   
    if(tkst_flag == TKST_IS_High_Fre)
	{
		TKST = HF_TKST;
		TKDIV04 = (U8)(Tab_HF_DIV[line]>>8);   
		TKDIV03 = (U8)(Tab_HF_DIV[line]);  
	}
	else
	{
		TKST = LF_TKST;
		TKDIV04 = (U8)(Tab_LF_DIV[line]>>8);   
		TKDIV03 = (U8)(Tab_LF_DIV[line]);			   
	}
}

void TK_start()
{
	TK_GO;
}
void Rst_WDT()
{
	RSET_WATCHDOG;
}

void init_tkErrchk()
{
   if(key_tkerrCnt > L_tkErrCnt)
   {
   	  tk_init_req = 0;  //exit
	  f_tkErr     = 1;
	  key_sample_count = 0;	
   }	
}

void tk_resetChk()
{
  	if(tk_init_req)
	{
	   GetInitialTouchkeyData();
	}
	if(tk_init_req ==0)
	{//基线重新获取完成
	  f_tkErr = 0;
	}	
}



