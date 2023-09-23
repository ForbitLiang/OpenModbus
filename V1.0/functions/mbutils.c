/***************************Copyright (c)**************************************
*                      ***************************
*                      ***************************
***************************FILEINFO.*******************************************
*	NAME    :	mbutils.c
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


UCHAR clear_entire_struct(Stru_MB *pStru_MB)
{
    memset(pStru_MB, 0, sizeof(*pStru_MB));
}


UCHAR clear_part_struct(Stru_MB *pStru_MB)
{   
    pStru_MB->MBHandle.MBErrorCode = enum_MB_ENOERR;
    pStru_MB->MBHandle.MBExceptionCode = enum_MB_EX_NONE;

    pStru_MB->MBHandle.RcvAddress = 0x00;
    pStru_MB->MBHandle.RcvFunctionCode = 0x00;
    pStru_MB->MBHandle.RcvBuffPos = 0x00; 
    memset(pStru_MB->MBHandle.RcvBuff, 0, sizeof(pStru_MB->MBHandle.RcvBuff));
    pStru_MB->pMBFrame_PDU = 0x00;
    memset(pStru_MB->MBHandle.SndBuff, 0, sizeof(pStru_MB->MBHandle.SndBuff));
    pStru_MB->MBHandle.SndBuffCount = 0x00;
    pStru_MB->pMBSendFrame = 0x00;
    pStru_MB->FrameLength_PDU = 0x00;
}