/***************************Copyright (c)**************************************
*                      ***************************
*                      ***************************
***************************FILEINFO.*******************************************
*	NAME    :	event.c
* 	VERSION :	V1.0
* 	DATE    :	2023.09.23
* 	AUTHOR  :	forbit
*	DESP.   :
******************************************************************************/

/* ----------------------- System includes ----------------------------------*/


/* ----------------------- Platform includes --------------------------------*/


/* ----------------------- Modbus includes ----------------------------------*/
#include "../include/mb.h"


/* ----------------------- Start implementation -----------------------------*/
BOOL    MBPortEventInit(Stru_MBHandle *pStru_MBHandle)
{
    pStru_MBHandle->MBCurrEvent = enum_EV_READY;

    return TRUE;
}

BOOL    MBPortEventPost(Stru_MBHandle *pStru_MBHandle, Enum_StateMachine_MBEvent Enum_Event )
{

    pStru_MBHandle->MBCurrEvent = Enum_Event;

    return TRUE;
}

Enum_StateMachine_MBEvent    MBPortEventGet(Stru_MBHandle *pStru_MBHandle)
{
    return pStru_MBHandle->MBCurrEvent;
}


