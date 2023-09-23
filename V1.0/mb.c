/***************************Copyright (c)**************************************
*                      ***************************
*                      ***************************
***************************FILEINFO.*******************************************
*	NAME    :	mb.h
* 	VERSION :	V1.0
* 	DATE    :	2023.09.23
* 	AUTHOR  :	forbit Liang
*	DESP.   :	This module has TCP and RTU functions, and the function code only supports register operations· 
                This module has the following features in terms of functionality
                    - Build only for the application layer
                    - Lower coupling between sub modules
                    - Stronger availability
                Refer-Thank you!
                - freemodbus
                - 《Modbus协议中文版【完整版】.pdf》
******************************************************************************/

/* ----------------------- System includes ----------------------------------*/
#include "stdlib.h"
#include "string.h"

/* ----------------------- Platform includes --------------------------------*/

/* ----------------------- Modbus includes ----------------------------------*/
#include "include/mb.h"

#if enum_MB_RTU_ENABLED == 1
#include "rtu/mbrtu.h"
#endif
#if enum_MB_TCP_ENABLED == 1
#include "tcp/mbtcp.h"
#endif


static xMBFunctionHandler FuncHandlers[MB_FUNC_HANDLERS_MAX] = {
#if MB_FUNC_OTHER_REP_SLAVEID_ENABLED > 0
    {MB_FUNC_OTHER_REPORT_SLAVEID, eMBFuncReportSlaveID},
#endif
#if MB_FUNC_READ_INPUT_ENABLED > 0
    {MB_FUNC_READ_INPUT_REGISTER, eMBFuncReadInputRegister},
#endif
#if MB_FUNC_READ_HOLDING_ENABLED > 0
    {MB_FUNC_READ_HOLDING_REGISTER, eMBFuncReadHoldingRegister},
#endif
#if MB_FUNC_WRITE_MULTIPLE_HOLDING_ENABLED > 0
    {MB_FUNC_WRITE_MULTIPLE_REGISTERS, eMBFuncWriteMultipleHoldingRegister},
#endif
#if MB_FUNC_WRITE_HOLDING_ENABLED > 0
    {MB_FUNC_WRITE_REGISTER, eMBFuncWriteHoldingRegister},
#endif
#if MB_FUNC_READWRITE_HOLDING_ENABLED > 0
    {MB_FUNC_READWRITE_MULTIPLE_REGISTERS, eMBFuncReadWriteMultipleHoldingRegister},
#endif
#if MB_FUNC_READ_COILS_ENABLED > 0
    {MB_FUNC_READ_COILS, eMBFuncReadCoils},
#endif
#if MB_FUNC_WRITE_COIL_ENABLED > 0
    {MB_FUNC_WRITE_SINGLE_COIL, eMBFuncWriteCoil},
#endif
#if MB_FUNC_WRITE_MULTIPLE_COILS_ENABLED > 0
    {MB_FUNC_WRITE_MULTIPLE_COILS, eMBFuncWriteMultipleCoils},
#endif
#if MB_FUNC_READ_DISCRETE_INPUTS_ENABLED > 0
    {MB_FUNC_READ_DISCRETE_INPUTS, eMBFuncReadDiscreteInputs},
#endif
};


/****************************************************************************
*   PROTO.  :  	Enum_MBErrorCode    MBInit(Stru_MB *pStru_MB, Enum_MBMode Enum_Mode, UCHAR SlaveAddress)
*   PARAM.  :  	Stru_MB *pStru_MB       
*               Enum_MBMode Enum_Mode   working mode    
*               UCHAR SlaveAddress      as a slave,self address        
*   RETURN  :   error code 
*   DESP.   :	initial
****************************************************************************/
Enum_MBErrorCode    MBInit(Stru_MB *pStru_MB, Enum_MBMode Enum_Mode, UCHAR SlaveAddress)
{
    Enum_MBErrorCode    Enum_ErrCode = enum_MB_ENOERR;    
    Stru_MBHandle       *pStru_MBHandle = &(pStru_MB->MBHandle);

    assert_param(NULL != ppStru_MBHandle);

    clear_entire_struct(pStru_MB);

    if( ( SlaveAddress == MB_ADDRESS_BROADCAST ) \
     || ( SlaveAddress < MB_ADDRESS_MIN ) \
     || ( SlaveAddress > MB_ADDRESS_MAX ) )
    {
        return enum_MB_EINVAL;                                           
    }

    pStru_MBHandle->MBCurrMode = Enum_Mode;
    pStru_MBHandle->MBAddressSelf = SlaveAddress;

    switch(Enum_Mode)                                                  
    {
        
#if enum_MB_RTU_ENABLED == 1
        case enum_MB_RTU:
            Enum_ErrCode = MBRTUInit(pStru_MB);
            break;
#endif /* enum_MB_RTU_ENABLED == 1 */

#if enum_MB_TCP_ENABLED == 1
        case enum_MB_TCP:
            Enum_ErrCode = MBTCPInit(pStru_MB);
            break;
#endif /* enum_MB_TCP_ENABLED == 1 */

        default:
            Enum_ErrCode = enum_MB_EINVAL;                               
            break;
    }

    if( Enum_ErrCode == enum_MB_ENOERR )
    {
        if( !MBPortEventInit(pStru_MBHandle) )
        {
            Enum_ErrCode = enum_MB_EPORTERR;                          
        }
    }

    return Enum_ErrCode;
}


/****************************************************************************
*   PROTO.  :  	MBPoll(Stru_MB *pStru_MB)
*   PARAM.  :  	Stru_MB *pStru_MB)
*   RETURN  :   error code 
*   DESP.   :	poll
****************************************************************************/
Enum_MBErrorCode    MBPoll(Stru_MB *pStru_MB)
{

    Stru_MBHandle                       *pStru_MBHandle = &(pStru_MB->MBHandle);
    Stru_MBFrameFunc 	                *pStru_FrameFunc = &(pStru_MB->FrameFunc);

    Enum_MBErrorCode                    Enum_ErrCode = enum_MB_ENOERR;
    
    SHORT                                i;   

    switch ( MBPortEventGet(pStru_MBHandle) )
    {
        case enum_EV_INITIAL:
            Enum_ErrCode = enum_MB_EILLSTATE;
            break;

        case enum_EV_READY:
            /* user self pick up */
            break;

        case enum_EV_FRAME_RECEIVED:        /* extract PDU */
            
            Enum_ErrCode = pStru_FrameFunc->PFuncType_MBFrameReceiveCur(pStru_MBHandle);
            
            if( Enum_ErrCode != enum_MB_ENOERR )
            {
                MBPortEventPost(pStru_MBHandle, enum_EV_FINISH);
                return Enum_ErrCode;
            }

            if( (pStru_MBHandle->RcvAddress == pStru_MBHandle->MBAddressSelf) \
                 || (pStru_MBHandle->RcvAddress == MB_ADDRESS_BROADCAST))
            {
                MBPortEventPost(pStru_MBHandle, enum_EV_EXECUTE);
            }
            else
            {
                MBPortEventPost(pStru_MBHandle, enum_EV_FINISH);
                return enum_MB_EILLSTATE;
            }
            
            break;

        case enum_EV_EXECUTE:       /* handle PDU and generate send PDU */

            pStru_MBHandle->RcvFunctionCode = pStru_MBHandle->pMBFrame_PDU[MB_PDU_FUNC_OFF];
     
            for( i = 0; i < MB_FUNC_HANDLERS_MAX; i++ )
            {

                if( FuncHandlers[i].FunctionCode == pStru_MBHandle->RcvFunctionCode )
                {
                    pStru_MBHandle->MBExceptionCode = FuncHandlers[i].pxHandler(pStru_MB);
                    break;
                }
                else if( FuncHandlers[i].FunctionCode == 0 )
                {
                    pStru_MBHandle->MBExceptionCode = enum_MB_EX_ILLEGAL_FUNCTION;
                    break;
                }
            }   

            if( pStru_MBHandle->RcvAddress == MB_ADDRESS_BROADCAST )
            {      
                MBPortEventPost(pStru_MBHandle, enum_EV_FINISH);
                break;
            }

            Enum_ErrCode = pStru_FrameFunc->PFuncType_MBFrameSendCur(pStru_MBHandle);
            MBPortEventPost(pStru_MBHandle, enum_EV_FRAME_SENT);

            break;

        case enum_EV_FRAME_SENT:
            /* user self pick up */
            break;

        case enum_EV_FINISH:
            clear_part_struct(pStru_MB);
            MBPortEventPost(pStru_MBHandle, enum_EV_READY);
            break;
            
        default:
            break;
    }

    return enum_MB_ENOERR;
}

