/***************************Copyright (c)**************************************
*                      ***************************
*                      ***************************
***************************FILEINFO.*******************************************
*	NAME    :	mbfuncholding.c
* 	VERSION :	V1.0
* 	DATE    :	2023.09.23
* 	AUTHOR  :	forbit Liang
*	DESP.   :	
******************************************************************************/

/* ----------------------- System includes ----------------------------------*/
#include "stdlib.h"
#include "string.h"

/* ----------------------- Platform includes --------------------------------*/

/* ----------------------- Modbus includes ----------------------------------*/
#include "../include/mb.h"

/* ----------------------- Defines ------------------------------------------*/                        
#define     MB_PDU_FUNC_READ_ADDR_OFF                                   ( 1 )
#define     MB_PDU_FUNC_READ_REGCNT_OFF                                 ( 3 )
#define     MB_PDU_FUNC_READ_REGCNT_MIN                                 ( 0x0001 )
#define     MB_PDU_FUNC_READ_REGCNT_MAX                                 ( 0x007D )

#define     MB_PDU_FUNC_WRITE_ADDR_OFF                                  ( 1 )
#define     MB_PDU_FUNC_WRITE_VALUE_OFF                                 ( 3 )
#define     MB_PDU_FUNC_WRITE_VALUE_MIN                                 ( 0x0000 )
#define     MB_PDU_FUNC_WRITE_VALUE_MAX                                 ( 0xFFFF )
#define     MB_PDU_FUNC_WRITE_SIZE                                      ( 4 )

#define     MB_PDU_FUNC_WRITE_MUL_ADDR_OFF                              ( 1 )
#define     MB_PDU_FUNC_WRITE_MUL_REGCNT_OFF                            ( 3 )
#define     MB_PDU_FUNC_WRITE_MUL_BYTECNT_OFF                           ( 5 )
#define     MB_PDU_FUNC_WRITE_MUL_VALUES_OFF                            ( 6 )
#define     MB_PDU_FUNC_WRITE_MUL_SIZE_MIN                              ( 6 )
#define     MB_PDU_FUNC_WRITE_MUL_REGCNT_MIN                            ( 0x0001 )
#define     MB_PDU_FUNC_WRITE_MUL_REGCNT_MAX                            ( 0x0078 )

#define     MB_PDU_FUNC_READWRITE_READ_ADDR_OFF                         ( 1 )
#define     MB_PDU_FUNC_READWRITE_READ_REGCNT_OFF                       ( 3 )
#define     MB_PDU_FUNC_READWRITE_WRITE_ADDR_OFF                        ( 5 )
#define     MB_PDU_FUNC_READWRITE_WRITE_REGCNT_OFF                      ( 7 )
#define     MB_PDU_FUNC_READWRITE_BYTECNT_OFF                           ( 9 )
#define     MB_PDU_FUNC_READWRITE_WRITE_VALUES_OFF                      ( 10 )
#define     MB_PDU_FUNC_READWRITE_READ_REGCNT_MIN                       ( 0x0001)
#define     MB_PDU_FUNC_READWRITE_READ_REGCNT_MAX                       ( 0x007D)
#define     MB_PDU_FUNC_READWRITE_WRITE_REGCNT_MIN                      ( 0x0001)
#define     MB_PDU_FUNC_READWRITE_WRITE_REGCNT_MAX                      ( 0x0079)

#define     MB_PDU_FUNC_READWRITE_SIZE_MIN                              ( 9 )



/********************************************************************************
*   PROTO.  :  	Enum_MBExceptionCode    eMBFuncReadHoldingRegister(Stru_MB *pStru_MB)
*   PARAM.  :  	Stru_MB *pStru_MB)
*   RETURN  :   exception code 
*   DESP.   :	function: read holding register, function code 0x03.
********************************************************************************/
Enum_MBExceptionCode    eMBFuncReadHoldingRegister(Stru_MB *pStru_MB)
{
    USHORT                  RegAddress;
    USHORT                  RegCtrlAddress;
    USHORT                  RegCount;
    SHORT 					i;

    RegCount = ( (USHORT)( pStru_MB->MBHandle.pMBFrame_PDU[MB_PDU_FUNC_READ_REGCNT_OFF]) << 8 ) \
                   | (USHORT)( pStru_MB->MBHandle.pMBFrame_PDU[MB_PDU_FUNC_READ_REGCNT_OFF + 1] );

    RegAddress = ( (USHORT)( pStru_MB->MBHandle.pMBFrame_PDU[MB_PDU_FUNC_READ_ADDR_OFF]) << 8 ) \
                     | (USHORT)( pStru_MB->MBHandle.pMBFrame_PDU[MB_PDU_FUNC_READ_ADDR_OFF + 1] );

/* # judgement the count of read register */  
    if( RegCount < MB_PDU_FUNC_READ_REGCNT_MIN || RegCount > MB_PDU_FUNC_READ_REGCNT_MAX )
    {
        return enum_MB_EX_ILLEGAL_DATA_VALUE;
    }

/* # judgement register address */
    if( ( RegAddress < pStru_MB->UserIF.pxUserReg.usRegHoldStart ) \
     || ( ( RegAddress + RegCount -1 ) > ( pStru_MB->UserIF.pxUserReg.usRegHoldStart + pStru_MB->UserIF.pxUserReg.usRegHoldNum - 1 ) )  )
    {
        return enum_MB_EX_ILLEGAL_DATA_ADDRESS;
    }

/* # handle request */
    /* ## read */ /*and*/ /* generate PDU */
    pStru_MB->MBHandle.SndBuff[MB_PDU_DATA_OFF] = 0x03;
    pStru_MB->MBHandle.SndBuffCount += 1;

    pStru_MB->MBHandle.SndBuff[MB_PDU_DATA_OFF+1] = RegCount*2;
    pStru_MB->MBHandle.SndBuffCount += 1;

    RegCtrlAddress = RegAddress - pStru_MB->UserIF.pxUserReg.usRegHoldStart;
    for(i=0; i<RegCount; i++)
    {
        pStru_MB->MBHandle.SndBuff[ ( MB_PDU_DATA_OFF + pStru_MB->MBHandle.SndBuffCount ) + ( i * 2 ) ] = (UCHAR)(pStru_MB->UserIF.pxUserReg.pusRegHoldBuf[RegCtrlAddress] >> 8) ;
        pStru_MB->MBHandle.SndBuff[ ( MB_PDU_DATA_OFF + pStru_MB->MBHandle.SndBuffCount ) + ( i * 2 ) + 1] = (UCHAR)(pStru_MB->UserIF.pxUserReg.pusRegHoldBuf[RegCtrlAddress] & 0xFF );
        RegCtrlAddress++;
    }
    pStru_MB->MBHandle.SndBuffCount += RegCount*2;     

/* # callback function(Data has been updated, user can do something...)*/
    pStru_MB->UserIF.pFunc_MBUserCBFunc();

    return enum_MB_EX_NONE;
}


/********************************************************************************
*   PROTO.  :  	Enum_MBExceptionCode    eMBFuncWriteHoldingRegister(Stru_MB *pStru_MB)
*   PARAM.  :  	Stru_MB *pStru_MB)
*   RETURN  :   exception code 
*   DESP.   :	function: write signal register, function code 0x06.
********************************************************************************/
Enum_MBExceptionCode    eMBFuncWriteHoldingRegister(Stru_MB *pStru_MB)
{
    USHORT                  RegValue;
    USHORT                  RegAddress;
    USHORT                  RegCtrlAddress;
  
    RegValue = ( (USHORT)( pStru_MB->MBHandle.pMBFrame_PDU[MB_PDU_FUNC_WRITE_VALUE_OFF] ) << 8 ) \
             | ( pStru_MB->MBHandle.pMBFrame_PDU[MB_PDU_FUNC_WRITE_VALUE_OFF + 1] );

    RegAddress = ( (USHORT)( pStru_MB->MBHandle.pMBFrame_PDU[MB_PDU_FUNC_WRITE_ADDR_OFF] ) << 8 ) \
               | (USHORT)( pStru_MB->MBHandle.pMBFrame_PDU[MB_PDU_FUNC_WRITE_ADDR_OFF + 1] );

/* # judgement the count of read register */  
    if( RegValue < MB_PDU_FUNC_WRITE_VALUE_MIN || RegValue > MB_PDU_FUNC_WRITE_VALUE_MAX )
    {
        return enum_MB_EX_ILLEGAL_DATA_VALUE;
    }

/* # judgement register address */
    if( ( RegAddress < pStru_MB->UserIF.pxUserReg.usRegHoldStart )
     || ( RegAddress > ( pStru_MB->UserIF.pxUserReg.usRegHoldStart + pStru_MB->UserIF.pxUserReg.usRegHoldNum - 1 ) ) )
    {
        return enum_MB_EX_ILLEGAL_DATA_ADDRESS;
    }

/* # handle request */
    RegCtrlAddress = RegAddress - pStru_MB->UserIF.pxUserReg.usRegHoldStart;
    pStru_MB->UserIF.pxUserReg.pusRegHoldBuf[RegCtrlAddress] = RegValue;

/* # generate PDU */
    memcpy(&(pStru_MB->MBHandle.SndBuff[MB_PDU_DATA_OFF]), &(pStru_MB->MBHandle.pMBFrame_PDU[0]), 5);
    pStru_MB->MBHandle.SndBuffCount = 5;

/* # callback function(Data has been updated, user can do something...)*/
    pStru_MB->UserIF.pFunc_MBUserCBFunc();


    return enum_MB_EX_NONE;
}



/********************************************************************************
*   PROTO.  :  	Enum_MBExceptionCode    eMBFuncWriteHoldingRegister(Stru_MB *pStru_MB)
*   PARAM.  :  	Stru_MB *pStru_MB)
*   RETURN  :   exception code 
*   DESP.   :	function: write multiple register, function code 0x10.
********************************************************************************/
Enum_MBExceptionCode    eMBFuncWriteMultipleHoldingRegister(Stru_MB *pStru_MB)
{
    USHORT                  RegAddress;
    USHORT                  RegCtrlAddress;
    USHORT                  RegCount;
    SHORT 					i;
  
    RegCount = ( (USHORT)( pStru_MB->MBHandle.pMBFrame_PDU[MB_PDU_FUNC_WRITE_MUL_REGCNT_OFF] ) << 8 ) \
                   | (USHORT)( pStru_MB->MBHandle.pMBFrame_PDU[MB_PDU_FUNC_WRITE_MUL_REGCNT_OFF + 1] );

    RegAddress = ( (USHORT)( pStru_MB->MBHandle.pMBFrame_PDU[MB_PDU_FUNC_WRITE_MUL_ADDR_OFF]) << 8 ) \
                     | (USHORT)( pStru_MB->MBHandle.pMBFrame_PDU[MB_PDU_FUNC_WRITE_MUL_ADDR_OFF + 1] );

/* # judgement the count of read register */  
    if( ( RegCount < MB_PDU_FUNC_WRITE_MUL_REGCNT_MIN || RegCount > MB_PDU_FUNC_WRITE_MUL_REGCNT_MAX ) \
     || ( ( RegCount*2 ) != pStru_MB->MBHandle.pMBFrame_PDU[MB_PDU_FUNC_WRITE_MUL_BYTECNT_OFF] ) )
    {
        return enum_MB_EX_ILLEGAL_DATA_VALUE;
    }

/* # judgement register address */
    if( ( RegAddress < pStru_MB->UserIF.pxUserReg.usRegHoldStart ) \
     || ( RegAddress + RegCount -1 ) > ( pStru_MB->UserIF.pxUserReg.usRegHoldStart + pStru_MB->UserIF.pxUserReg.usRegHoldNum -1  ) ) 
    {
        return enum_MB_EX_ILLEGAL_DATA_ADDRESS;
    }

/* # handle request */
    /* ## write */
    RegCtrlAddress = RegAddress - pStru_MB->UserIF.pxUserReg.usRegHoldStart;
    for(i=0; i<RegCount; i++)
    {
        pStru_MB->UserIF.pxUserReg.pusRegHoldBuf[ RegCtrlAddress++ ] = ( (USHORT)( pStru_MB->MBHandle.pMBFrame_PDU[ MB_PDU_FUNC_WRITE_MUL_VALUES_OFF + (i*2)] ) << 8 ) \
                                                                              | (USHORT)( pStru_MB->MBHandle.pMBFrame_PDU[ (MB_PDU_FUNC_WRITE_MUL_VALUES_OFF + 1) + (i*2) ] );

    }

/* # generate PDU */
    pStru_MB->MBHandle.SndBuff[MB_PDU_DATA_OFF] = 0x0a;
    pStru_MB->MBHandle.SndBuffCount += 1;

    memcpy(&(pStru_MB->MBHandle.SndBuff[ MB_PDU_DATA_OFF + pStru_MB->MBHandle.SndBuffCount ]), &(pStru_MB->MBHandle.pMBFrame_PDU[MB_PDU_FUNC_WRITE_MUL_ADDR_OFF]), 4);
    pStru_MB->MBHandle.SndBuffCount += 4;

/* # callback function(Data has been updated, user can do something...)*/
    pStru_MB->UserIF.pFunc_MBUserCBFunc();

    return enum_MB_EX_NONE;
}


/********************************************************************************
*   PROTO.  :  	Enum_MBExceptionCode    eMBFuncReadWriteMultipleHoldingRegister(Stru_MB *pStru_MB)
*   PARAM.  :  	Stru_MB *pStru_MB)
*   RETURN  :   exception code 
*   DESP.   :	function: read and write multiple register, function code 0x17.
********************************************************************************/
Enum_MBExceptionCode    eMBFuncReadWriteMultipleHoldingRegister(Stru_MB *pStru_MB)
{
    USHORT                  RegReadCount;
    USHORT                  RegWriteCount;

    USHORT                  RegReadAddress;
    USHORT                  RegWriteAddress;

    USHORT                  RegCtrlAddress;

    SHORT 					i;

/* # judgement the count of read register */    
    RegReadCount = ( (USHORT)( pStru_MB->MBHandle.pMBFrame_PDU[MB_PDU_FUNC_READWRITE_READ_REGCNT_OFF] ) << 8 ) \
                       | (USHORT)( pStru_MB->MBHandle.pMBFrame_PDU[MB_PDU_FUNC_READWRITE_READ_REGCNT_OFF + 1 ] ) ;
    
    RegWriteCount =  ( (USHORT)( pStru_MB->MBHandle.pMBFrame_PDU[MB_PDU_FUNC_READWRITE_WRITE_REGCNT_OFF] ) << 8 ) \
                         | (USHORT)( pStru_MB->MBHandle.pMBFrame_PDU[MB_PDU_FUNC_READWRITE_WRITE_REGCNT_OFF + 1] );
    
    if(  ( RegReadCount < MB_PDU_FUNC_READWRITE_READ_REGCNT_MIN || RegReadCount > MB_PDU_FUNC_READWRITE_READ_REGCNT_MAX ) \
      || ( RegWriteCount < MB_PDU_FUNC_READWRITE_WRITE_REGCNT_MIN || RegWriteCount > MB_PDU_FUNC_READWRITE_WRITE_REGCNT_MAX ) \
      || ( ( RegWriteCount*2 ) != pStru_MB->MBHandle.pMBFrame_PDU[MB_PDU_FUNC_READWRITE_BYTECNT_OFF] ) )
    {
        return enum_MB_EX_ILLEGAL_DATA_VALUE;
    }
/* # judgement register address */
    RegReadAddress = ( (USHORT)( pStru_MB->MBHandle.pMBFrame_PDU[MB_PDU_FUNC_READWRITE_READ_ADDR_OFF]) << 8 ) \
                         | (USHORT)( pStru_MB->MBHandle.pMBFrame_PDU[MB_PDU_FUNC_READWRITE_READ_ADDR_OFF + 1] );
    
    RegWriteAddress = ( (USHORT)( pStru_MB->MBHandle.pMBFrame_PDU[MB_PDU_FUNC_READWRITE_WRITE_ADDR_OFF] << 8 ) \
                          | (USHORT)( pStru_MB->MBHandle.pMBFrame_PDU[MB_PDU_FUNC_READWRITE_WRITE_ADDR_OFF + 1] ));
    
    if( ( RegReadAddress < pStru_MB->UserIF.pxUserReg.usRegHoldStart ) \
     || ( RegReadAddress + RegReadCount - 1 ) > ( pStru_MB->UserIF.pxUserReg.usRegHoldNum + pStru_MB->UserIF.pxUserReg.usRegHoldStart - 1 ) \
     || ( RegWriteAddress < pStru_MB->UserIF.pxUserReg.usRegHoldStart ) \
     || ( RegWriteAddress + RegWriteCount - 1 ) > ( pStru_MB->UserIF.pxUserReg.usRegHoldNum + pStru_MB->UserIF.pxUserReg.usRegHoldStart - 1 ) ) 
    {
        return enum_MB_EX_ILLEGAL_DATA_ADDRESS;
    }

/* # handle request */
    /* ## read */ /*and*/ /* generate PDU */
    pStru_MB->MBHandle.SndBuff[MB_PDU_DATA_OFF] = 0x17;
    pStru_MB->MBHandle.SndBuffCount += 1;

    pStru_MB->MBHandle.SndBuff[ MB_PDU_DATA_OFF + pStru_MB->MBHandle.SndBuffCount ] = RegReadCount*2;
    pStru_MB->MBHandle.SndBuffCount += 1;

    RegCtrlAddress = RegReadAddress - pStru_MB->UserIF.pxUserReg.usRegHoldStart;
    for(i=0; i<RegReadCount; i++)
    {
        pStru_MB->MBHandle.SndBuff[ ( MB_PDU_DATA_OFF + pStru_MB->MBHandle.SndBuffCount ) + ( i * 2 ) ] = (UCHAR)(pStru_MB->UserIF.pxUserReg.pusRegHoldBuf[RegCtrlAddress] >> 8 );
        pStru_MB->MBHandle.SndBuff[ ( MB_PDU_DATA_OFF + pStru_MB->MBHandle.SndBuffCount ) + ( i * 2 ) + 1] = (UCHAR)(pStru_MB->UserIF.pxUserReg.pusRegHoldBuf[RegCtrlAddress] & 0xFF );
        RegCtrlAddress++;
    }
    pStru_MB->MBHandle.SndBuffCount += RegReadCount*2; 
    
    /* ## write */
    RegCtrlAddress = RegWriteAddress - pStru_MB->UserIF.pxUserReg.usRegHoldStart;
    for(i=0; i<RegWriteCount; i++)
    {
        pStru_MB->UserIF.pxUserReg.pusRegHoldBuf[ RegCtrlAddress++ ] = ( (USHORT)( pStru_MB->MBHandle.pMBFrame_PDU[ MB_PDU_FUNC_READWRITE_WRITE_VALUES_OFF + (i*2)] ) << 8 ) \
                                                                              | (USHORT)( pStru_MB->MBHandle.pMBFrame_PDU[ (MB_PDU_FUNC_READWRITE_WRITE_VALUES_OFF + 1) + (i*2) ] );

    }

/* callback function(Data has been updated, user can do something...)*/
    pStru_MB->UserIF.pFunc_MBUserCBFunc();

    return enum_MB_EX_NONE;
}
