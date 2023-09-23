/***************************Copyright (c)**************************************
*                      ***************************
*                      ***************************
***************************FILEINFO.*******************************************
*	NAME    :	mbrtu.c
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
#include "mbrtu.h"  


/* ----------------------- Defines ------------------------------------------*/
#define MB_RTU_SIZE_MIN                 8       /* Minimum size of a Modbus RTU frame. */
#define MB_RTU_PDU_SIZE_MIN             4       /* Minimum size of a Modbus RTU frame. */
#define MB_RTU_PDU_SIZE_MAX             256     /* Maximum size of a Modbus RTU frame. */
#define MB_RTU_PDU_SIZE_CRC             2       /* Size of CRC field in PDU. */
#define MB_RTU_PDU_ADDR_OFF             0       /* Offset of slave address in Ser-PDU. */
#define MB_RTU_PDU_PDU_OFF              1       /* Offset of Modbus-PDU in Ser-PDU. */ 

#define MB_RTU_ADU_ADDRESS_OFF          6       /* the location of adu off */
#define MB_RTU_ADU_ERROR_CODE_OFF       7       /* the location of error code */
#define MB_RTU_ADU_EXCEPTION_CODE_OFF   8       /* the location of exception code */

#define MB_RTU_ADU_PREFIX_LENGTH        1       /* the length of adu's prefix */


static Enum_MBErrorCode     MBRTUReceive(Stru_MBHandle *pStru_MBHandle);
static Enum_MBErrorCode     MBRTUSend(Stru_MBHandle *pStru_MBHandle);


/* ----------------------- Start implementation -----------------------------*/
Enum_MBErrorCode MBRTUInit(Stru_MB *pStru_MB)
{

    Enum_MBErrorCode    Enum_ErrCode = enum_MB_ENOERR;
    Stru_MBFrameFunc 	*pFrameFunc = &(pStru_MB->FrameFunc);

    pFrameFunc->PFuncType_MBFrameReceiveCur = MBRTUReceive;
    pFrameFunc->PFuncType_MBFrameSendCur = MBRTUSend;

    return Enum_ErrCode;
}

    
static Enum_MBErrorCode MBRTUReceive(Stru_MBHandle *pStru_MBHandle)
{
    Enum_MBErrorCode    Enum_ErrCode = enum_MB_ENOERR;

    assert_param( pStru_MBHandle->usBuffPos < MB_RTU_PDU_SIZE_MAX ); 
    
    if( ( pStru_MBHandle->RcvBuffPos >= MB_RTU_SIZE_MIN ) \
     && ( usMBCRC16( ( UCHAR * ) pStru_MBHandle->RcvBuff, pStru_MBHandle->RcvBuffPos ) == 0 ) )
    {
        pStru_MBHandle->RcvAddress = pStru_MBHandle->RcvBuff[MB_RTU_PDU_ADDR_OFF];
        pStru_MBHandle->FrameLength_PDU = ( USHORT )( pStru_MBHandle->RcvBuffPos - MB_RTU_PDU_PDU_OFF - MB_RTU_PDU_SIZE_CRC );
        pStru_MBHandle->pMBFrame_PDU = ( UCHAR * ) & pStru_MBHandle->RcvBuff[MB_RTU_PDU_PDU_OFF];
    }
    else
    {
        Enum_ErrCode = enum_MB_EIO;
    }
    
    return Enum_ErrCode;
}



static Enum_MBErrorCode MBRTUSend(Stru_MBHandle *pStru_MBHandle)
{
    Enum_MBErrorCode    Enum_ErrCode = enum_MB_ENOERR;
    USHORT              CRC16;
    
/* # generate ADU */
    pStru_MBHandle->SndBuff[MB_RTU_ADU_ADDRESS_OFF] = pStru_MBHandle->RcvAddress;
    pStru_MBHandle->SndBuffCount += 1;

    /* if happen exception generate exception PDU */
    if( pStru_MBHandle->MBExceptionCode != enum_MB_EX_NONE )
    {
        switch( pStru_MBHandle->RcvFunctionCode )
        {
            case MB_FUNC_READ_HOLDING_REGISTER:
                pStru_MBHandle->SndBuff[MB_RTU_ADU_ERROR_CODE_OFF] = 0x83;
                break;
            case MB_FUNC_WRITE_REGISTER:
                pStru_MBHandle->SndBuff[MB_RTU_ADU_ERROR_CODE_OFF] = 0x86;
                break;
            case MB_FUNC_WRITE_MULTIPLE_REGISTERS:
                pStru_MBHandle->SndBuff[MB_RTU_ADU_ERROR_CODE_OFF] = 0x90;
                break;
            case MB_FUNC_READWRITE_MULTIPLE_REGISTERS:
                pStru_MBHandle->SndBuff[MB_RTU_ADU_ERROR_CODE_OFF] = 0x97;
                break;
            
            default:
                break;
        }
        pStru_MBHandle->SndBuffCount += 1;
			
        pStru_MBHandle->SndBuff[MB_RTU_ADU_EXCEPTION_CODE_OFF] = pStru_MBHandle->MBExceptionCode;
        pStru_MBHandle->SndBuffCount += 1;
    }
    
    /* Calculate CRC16 checksum for Modbus-Serial-Line-PDU. */
    CRC16 = usMBCRC16( ( UCHAR * ) &( pStru_MBHandle->SndBuff[MB_PDU_DATA_OFF - MB_RTU_ADU_PREFIX_LENGTH]) , pStru_MBHandle->SndBuffCount );
    pStru_MBHandle->SndBuff[ ( MB_PDU_DATA_OFF - MB_RTU_ADU_PREFIX_LENGTH ) + pStru_MBHandle->SndBuffCount++] = (UCHAR)( CRC16 & 0xFF );
    pStru_MBHandle->SndBuff[ ( MB_PDU_DATA_OFF - MB_RTU_ADU_PREFIX_LENGTH ) + pStru_MBHandle->SndBuffCount++] = (UCHAR)( CRC16 >> 8 );

    pStru_MBHandle->pMBSendFrame = &(pStru_MBHandle->SndBuff[MB_PDU_DATA_OFF - MB_RTU_ADU_PREFIX_LENGTH]);

    return Enum_ErrCode;
}



