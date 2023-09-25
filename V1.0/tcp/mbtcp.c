/***************************Copyright (c)**************************************
*                      ***************************
*                      ***************************
***************************FILEINFO.*******************************************
*	NAME    :	mbtcp.c
* 	VERSION :	V1.0
* 	DATE    :	2023.09.23
* 	AUTHOR  :	forbit
*	DESP.   :
******************************************************************************/

/* ----------------------- System includes ----------------------------------*/
#include "stdlib.h"
#include "string.h"

/* ----------------------- Platform includes --------------------------------*/


/* ----------------------- Modbus includes ----------------------------------*/
#include "mbtcp.h"

/* ----------------------- Defines ------------------------------------------*/
#define MB_TCP_SIZE_MIN                 8       /* Minimum size of a Modbus TCP frame. */
#define MB_TCP_PDU_SIZE_MIN             4       /* Minimum size of a Modbus TCP frame. */
#define MB_TCP_PDU_SIZE_MAX             256     /* Maximum size of a Modbus TCP frame. */
#define MB_TCP_PDU_PDU_OFF              7       /* Offset of Modbus-PDU in Ser-PDU. */

#define MB_TCP_ADU_OFF                  0       /* the location of adu off */
#define MB_TCP_ADU_TRANSACTION_ID_OFF   0       /* the location of transaction identifier */
#define MB_TCP_ADU_PROTOCOL_ID_OFF      2       /* the location of protocol Identifier */
#define MB_TCP_ADU_LENGTH_ID_OFF        4       /* the location of length Identifier */
#define MB_TCP_ADU_UNIT_ID_OFF          6       /* the location of unit Identifier */
#define MB_TCP_ADU_ERROR_CODE_OFF       7       /* the location of error code */
#define MB_TCP_ADU_EXCEPTION_CODE_OFF   8       /* the location of exception code */

#define MB_TCP_ADU_PREFIX_LENGTH        7       /* the length of adu's prefix */


static Enum_MBErrorCode     MBTCPReceive(Stru_MBHandle *pStru_MBHandle);
static Enum_MBErrorCode     MBTCPSend(Stru_MBHandle *pStru_MBHandle);

Enum_MBErrorCode    MBTCPInit(Stru_MB *pStru_MB)
{
    Enum_MBErrorCode    Enum_ErrCode = enum_MB_ENOERR;
    Stru_MBFrameFunc 	*pFrameFunc = &(pStru_MB->FrameFunc);

    pFrameFunc->PFuncType_MBFrameReceiveCur = MBTCPReceive;
    pFrameFunc->PFuncType_MBFrameSendCur = MBTCPSend;

    return Enum_ErrCode;
}

static Enum_MBErrorCode     MBTCPReceive(Stru_MBHandle *pStru_MBHandle)
{
    Enum_MBErrorCode    Enum_ErrCode = enum_MB_ENOERR;

    assert_param( pStru_MBHandle->usBuffPos < MB_TCP_PDU_SIZE_MAX );

    if( pStru_MBHandle->RcvBuffPos >= MB_TCP_SIZE_MIN )
    {
        pStru_MBHandle->RcvAddress = MB_TCP_FAKE_ADDRESS;
        pStru_MBHandle->FrameLength_PDU = ( USHORT )( pStru_MBHandle->RcvBuffPos - MB_TCP_PDU_PDU_OFF );
        pStru_MBHandle->pMBFrame_PDU = ( UCHAR * ) & pStru_MBHandle->RcvBuff[MB_TCP_PDU_PDU_OFF];
        printf("\n test \n");
        printcharArray(pStru_MBHandle->pMBFrame_PDU, pStru_MBHandle->FrameLength_PDU);
    }
    else
    {
        Enum_ErrCode = enum_MB_EIO;
    }

    return Enum_ErrCode;
}

static Enum_MBErrorCode     MBTCPSend(Stru_MBHandle *pStru_MBHandle)
{
    Enum_MBErrorCode    Enum_ErrCode = enum_MB_ENOERR;
    USHORT              CRC16;

/* # generate ADU */

    pStru_MBHandle->SndBuff[MB_TCP_ADU_TRANSACTION_ID_OFF] = pStru_MBHandle->RcvBuff[MB_TCP_ADU_TRANSACTION_ID_OFF];
    pStru_MBHandle->SndBuff[MB_TCP_ADU_TRANSACTION_ID_OFF+1] = pStru_MBHandle->RcvBuff[MB_TCP_ADU_TRANSACTION_ID_OFF+1];
    pStru_MBHandle->SndBuff[MB_TCP_ADU_PROTOCOL_ID_OFF] = pStru_MBHandle->RcvBuff[MB_TCP_ADU_PROTOCOL_ID_OFF];
    pStru_MBHandle->SndBuff[MB_TCP_ADU_PROTOCOL_ID_OFF+1] = pStru_MBHandle->RcvBuff[MB_TCP_ADU_PROTOCOL_ID_OFF+1];
    /* adu length */
    pStru_MBHandle->SndBuff[MB_TCP_ADU_UNIT_ID_OFF] = pStru_MBHandle->RcvBuff[MB_TCP_ADU_UNIT_ID_OFF];

    pStru_MBHandle->SndBuffCount += 7;

    /* if happen exception generate exception PDU */
    if( pStru_MBHandle->MBExceptionCode != enum_MB_EX_NONE )
    {
        switch( pStru_MBHandle->RcvFunctionCode )
        {
            case MB_FUNC_READ_HOLDING_REGISTER:
                pStru_MBHandle->SndBuff[MB_TCP_ADU_ERROR_CODE_OFF] = 0x83;
                break;

            case MB_FUNC_WRITE_REGISTER:
                pStru_MBHandle->SndBuff[MB_TCP_ADU_ERROR_CODE_OFF] = 0x86;
                break;
            case MB_FUNC_WRITE_MULTIPLE_REGISTERS:
                pStru_MBHandle->SndBuff[MB_TCP_ADU_ERROR_CODE_OFF] = 0x90;
                break;
            case MB_FUNC_READWRITE_MULTIPLE_REGISTERS:
                pStru_MBHandle->SndBuff[MB_TCP_ADU_ERROR_CODE_OFF] = 0x97;
                break;

            default:
                break;
        }
        pStru_MBHandle->SndBuffCount += 1;

        pStru_MBHandle->SndBuff[MB_TCP_ADU_EXCEPTION_CODE_OFF] = pStru_MBHandle->MBExceptionCode;
        pStru_MBHandle->SndBuffCount += 1;
    }
    pStru_MBHandle->SndBuff[MB_TCP_ADU_LENGTH_ID_OFF] = pStru_MBHandle->SndBuffCount - 5;
    pStru_MBHandle->pMBSendFrame = &(pStru_MBHandle->SndBuff[MB_PDU_DATA_OFF - MB_TCP_ADU_PREFIX_LENGTH]);

    return Enum_ErrCode;
}
