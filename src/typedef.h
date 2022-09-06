
#ifndef TYPEDEF_H
#define TYPEDEF_H

#ifdef  __C51__
    typedef bit				  bool;
    typedef unsigned char		  bl8;        //为了结构体

    #include <intrins.h>
    #define   NOP()     _nop_()

    #define iram	idata     // data只能用低128, idata包含data, 指明idata还是可能会分配在低128， SP可用256字节
    #define xram	xdata
    #define crom    code
#else
    typedef unsigned char	  bool;
    typedef unsigned char	  bl8;        //为了结构体
    #define iram	
    #define xram	
    #define crom    const
#endif

typedef unsigned char         u8;
typedef unsigned short int    u16;
typedef unsigned long         u32;

typedef char                  s8;
typedef short int             s16;
typedef long                  s32;

// typedef unsigned char         UINT8;
// typedef unsigned short int    UINT16;
// typedef unsigned long         UINT32;

// typedef char                  INT8;
// typedef short int             INT16;
// typedef long                  INT32;

//typedef unsigned char         uint8_t;
//typedef unsigned short int    uint16_t;
//typedef unsigned long         uint32_t;

//typedef char                  sint8_t;
//typedef short int             sint16_t;
//typedef long                  sint32_t;

//typedef unsigned char         uint8;
//typedef unsigned short int    uint16;
//typedef unsigned long         uint32;

//typedef char                  sint8;
//typedef short int             sint16;
//typedef long                  sint32;

/* These types MUST be 16-bit or 32-bit */
typedef int				INT;
typedef unsigned int	UINT;

/* This type MUST be 8-bit */
typedef unsigned char	BYTE;

/* These types MUST be 16-bit */
typedef short			SHORT;
typedef unsigned short	WORD;
typedef unsigned short	WCHAR;

/* These types MUST be 32-bit */
typedef long			LONG;
typedef unsigned long	DWORD;

/* This type MUST be 64-bit (Remove this for C89 compatibility) */
//typedef unsigned long long QWORD;

#endif
