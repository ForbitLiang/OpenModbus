/***************************Copyright (c)**************************************
*                      ***************************
*                      ***************************
***************************FILEINFO.*******************************************
*	NAME    :	mb.h
* 	VERSION :	V1.0
* 	DATE    :	2023.09.23
* 	AUTHOR  :	forbit
*	DESP.   :
******************************************************************************/

#ifndef _MB_H
#define _MB_H

/*
************************************************************************************************************************
*                                                 INCLUDE HEADER FILES
************************************************************************************************************************
*/
#include "../mbport_user/port.h"
#include "../mbport_user/mbconfig.h"

/*
************************************************************************************************************************
************************************************************************************************************************
*                                                      catalog
************************************************************************************************************************
************************************************************************************************************************
*/
/*
- define
    - proto
        - Frame
        - MB_FUNC
        - Modbus Slave Defines
        - func
- data types
- enumerations
    - frame
    - State machine and error code of process
- data structures
- function

/*
************************************************************************************************************************
************************************************************************************************************************
*                                                   # D E F I N E S
************************************************************************************************************************
************************************************************************************************************************
*/


/*
========================================================================================================================
*                                                      proto
========================================================================================================================
*/


/*
------------------------------------------------------------------------------------------------------------------------
*                                                   Frame
------------------------------------------------------------------------------------------------------------------------
*/
/*!
 *            <--------------- MODBUS PDU  ---------------->
 *            +---------------+----------------------------+
 *            | Function Code | Data                       |
 *            +---------------+----------------------------+
 *            |               |                            |
 *  byte:    (0)             (1)
 */

#define     MB_PDU_FUNC_OFF                                 ( 0 )          /*!< Offset of function code in PDU. */
#define     MB_PDU_DATA_OFF                                 ( 7 )          /*!< Offset for send data in PDU. */

#define     MB_RTU_PDU_INDEX_OFF                            ( 1 )

#define     MB_BUFF_SIZE                                    ( 256 )

#define     MB_ADDRESS_BROADCAST                            ( 0 )       /* Modbus broadcast address. */
#define     MB_ADDRESS_MIN                                  ( 1 )       /* Smallest possible slave address. */
#define     MB_ADDRESS_MAX                                  ( 247 )     /* Biggest possible slave address. */
#define     MB_TCP_FAKE_ADDRESS                             ( 1 )     /* tcp address. */


/*
------------------------------------------------------------------------------------------------------------------------
*                                                   MB_FUNC
------------------------------------------------------------------------------------------------------------------------
*/
#define     MB_FUNC_NONE                                    (  0 )
#define     MB_FUNC_READ_COILS                              (  1 )
#define     MB_FUNC_READ_DISCRETE_INPUTS                    (  2 )
#define     MB_FUNC_READ_HOLDING_REGISTER                   (  3 )
#define     MB_FUNC_READ_INPUT_REGISTER                     (  4 )
#define     MB_FUNC_WRITE_SINGLE_COIL                       (  5 )
#define     MB_FUNC_WRITE_REGISTER                          (  6 )
#define     MB_FUNC_DIAG_READ_EXCEPTION                     (  7 )
#define     MB_FUNC_DIAG_DIAGNOSTIC                         (  8 )
#define     MB_FUNC_WRITE_MULTIPLE_REGISTERS                ( 10 )
#define     MB_FUNC_DIAG_GET_COM_EVENT_CNT                  ( 11 )
#define     MB_FUNC_DIAG_GET_COM_EVENT_LOG                  ( 12 )
#define     MB_FUNC_WRITE_MULTIPLE_COILS                    ( 15 )
#define     MB_FUNC_OTHER_REPORT_SLAVEID                    ( 17 )
#define     MB_FUNC_READWRITE_MULTIPLE_REGISTERS            ( 23 )
#define     MB_FUNC_ERROR                                   ( 128 )



/*
------------------------------------------------------------------------------------------------------------------------
*                                                   func
------------------------------------------------------------------------------------------------------------------------
*/



/*
************************************************************************************************************************
************************************************************************************************************************
*                                                  D A T A   T Y P E S
************************************************************************************************************************
************************************************************************************************************************
*/
typedef  struct     stru_mbuserregister            Stru_MBUserRegister;
typedef  struct     stru_mbuserfunc                Stru_MBUserFunc;
typedef  struct     stru_mbuserif                  Stru_MBUserIF;
typedef  struct     xmbfunctionhandler             xMBFunctionHandler;
typedef  struct     stru_mbframefunc               Stru_MBFrameFunc;

typedef  struct     stru_mbhandle                  Stru_MBHandle;
typedef  struct     stru_mb                        Stru_MB;

typedef  enum       enum_mbmode                    Enum_MBMode;

typedef  enum       enum_mberrorcode               Enum_MBErrorCode;
typedef  enum       enum_mbexceptioncode           Enum_MBExceptionCode;

typedef  enum       enum_statemachine_mbevent      Enum_StateMachine_MBEvent;


typedef  void                                      (*PFuncType_MBUserCBFunc)(void);

typedef             Enum_MBExceptionCode           (*PFuncType_MBFunctionHandler)(Stru_MB *pStru_MB);

typedef             Enum_MBErrorCode	           (*PFuncType_MBFrameReceive)(Stru_MBHandle *);
typedef             Enum_MBErrorCode	           (*PFuncType_MBFrameSend)(Stru_MBHandle *);



/*
************************************************************************************************************************
************************************************************************************************************************
*                                                E N U M E R A T I O N S
************************************************************************************************************************
************************************************************************************************************************
*/


/*
------------------------------------------------------------------------------------------------------------------------
*                                                    frame
------------------------------------------------------------------------------------------------------------------------
*/

enum enum_mbmode
{
    enum_MB_RTU                         = 0x00,                 /* RTU transmission mode. */
    enum_MB_ASCII                       = 0x01,                 /* ASCII transmission mode. */
    enum_MB_TCP                         = 0x02                  /* TCP mode. */
};

enum enum_mbexceptioncode
{
    enum_MB_EX_NONE                     = 0x00,
    enum_MB_EX_ILLEGAL_FUNCTION         = 0x01,
    enum_MB_EX_ILLEGAL_DATA_ADDRESS     = 0x02,
    enum_MB_EX_ILLEGAL_DATA_VALUE       = 0x03,
    enum_MB_EX_SLAVE_DEVICE_FAILURE     = 0x04,
    enum_MB_EX_ACKNOWLEDGE              = 0x05,
    enum_MB_EX_SLAVE_BUSY               = 0x06,
    enum_MB_EX_MEMORY_PARITY_ERROR      = 0x08,
    enum_MB_EX_GATEWAY_PATH_FAILED      = 0x0A,
    enum_MB_EX_GATEWAY_TGT_FAILED       = 0x0B
};                                                              /* Exception codes specified in the modbus protocol */

/*
------------------------------------------------------------------------------------------------------------------------
*                                         State machine and error code of process
------------------------------------------------------------------------------------------------------------------------
*/

enum enum_statemachine_mbevent
{
    enum_EV_INITIAL                     = 0x00,                 /* initial state. */
    enum_EV_READY                       = 0x01,                 /* Startup finished. */
    enum_EV_FRAME_RECEIVED              = 0x02,                 /* Frame received. */
    enum_EV_EXECUTE                     = 0x03,                 /* Execute function. */
    enum_EV_FRAME_SENT                  = 0x04,                 /* Frame sent. */
    enum_EV_FINISH                      = 0x05                  /* clear information */
};


enum enum_mberrorcode
{
    enum_MB_ENOERR                      = 0x00,                 /* no error. */
    enum_MB_ENOREG                      = 0x01,                 /* illegal register address. */
    enum_MB_EINVAL                      = 0x02,                 /* illegal argument. */
    enum_MB_EPORTERR                    = 0x03,                 /* porting layer error. */
    enum_MB_ENORES                      = 0x04,                 /* insufficient resources. */
    enum_MB_EIO                         = 0x05,                 /* I/O error. */
    enum_MB_EILLSTATE                   = 0x06,                 /* protocol stack in illegal state. */
    enum_MB_ETIMEDOUT                   = 0x07                  /* timeout error occurred. */
};                                                              /* Individual defined error codes. */



/*
************************************************************************************************************************
************************************************************************************************************************
*                                          D A T A   S T R U C T U R E S
************************************************************************************************************************
************************************************************************************************************************
*/

/*
------------------------------------------------------------------------------------------------------------------------
*                                                   register description
------------------------------------------------------------------------------------------------------------------------
*/
struct stru_mbuserregister
{
    /* DiscreteInputs iables */
    USHORT                              usDiscInStart;
    USHORT                              usDiscInNum;
    UCHAR                               *pucDiscInBuf;

    /* Coils iables */
    USHORT                              usCoilStart;
    USHORT                              usCoilNum;
    UCHAR                               *pucCoilBuf;

    /* InputRegister iables */
    USHORT                              usRegInStart;
    USHORT                              usRegInNum;
    USHORT                              *pusRegInBuf;

    /* HoldingRegister iables */
    USHORT                              usRegHoldStart;
    USHORT                              usRegHoldNum;
    USHORT                              *pusRegHoldBuf;
};


/*
------------------------------------------------------------------------------------------------------------------------
*                                                   register function
------------------------------------------------------------------------------------------------------------------------
*/


struct stru_mbuserif
{
    Stru_MBUserRegister                 pxUserReg;
    PFuncType_MBUserCBFunc              pFunc_MBUserCBFunc;
};


struct xmbfunctionhandler
{
    UCHAR                               FunctionCode;
    PFuncType_MBFunctionHandler         pxHandler;
};


/*
------------------------------------------------------------------------------------------------------------------------
*                                                   process
------------------------------------------------------------------------------------------------------------------------
*/
struct stru_mbframefunc
{
    PFuncType_MBFrameReceive            PFuncType_MBFrameReceiveCur;
    PFuncType_MBFrameSend               PFuncType_MBFrameSendCur;
};


/*
------------------------------------------------------------------------------------------------------------------------
*                                                   all
------------------------------------------------------------------------------------------------------------------------
*/
struct stru_mbhandle
{

    UCHAR                               MBAddressSelf;
    Enum_MBMode                         MBCurrMode;                 /* working mode */

    Enum_MBErrorCode                    MBErrorCode;
    Enum_MBExceptionCode                MBExceptionCode;            /* parse parpackage error */

    Enum_StateMachine_MBEvent 	        MBCurrEvent;                /* current handle process's event, it is detail of "current handle process's state" */

    UCHAR                               RcvAddress;
    UCHAR                               RcvFunctionCode;
	USHORT 			                    RcvBuffPos;
	UCHAR                               RcvBuff[MB_BUFF_SIZE];
    UCHAR                               *pMBFrame_PDU;

	UCHAR 	                            SndBuff[MB_BUFF_SIZE];
    USHORT 			                    SndBuffCount;
    UCHAR                               *pMBSendFrame;

    USHORT                              FrameLength_PDU;
};


struct stru_mb
{
    Stru_MBHandle                       MBHandle;
	Stru_MBFrameFunc  	                FrameFunc;
    Stru_MBUserIF                       UserIF;
};


/*
************************************************************************************************************************
************************************************************************************************************************
*                                        F U N C T I O N   P R O T O T Y P E S
************************************************************************************************************************
************************************************************************************************************************
*/


/*
------------------------------------------------------------------------------------------------------------------------
*                                                   Utils
------------------------------------------------------------------------------------------------------------------------
*/
UCHAR                       clear_entire_struct(Stru_MB *pStru_MB);
UCHAR                       clear_part_struct(Stru_MB *pStru_MB);


/* ================================================================================================================== */
/*                                             Interface that users  implement                                        */
/* ================================================================================================================== */

/*
------------------------------------------------------------------------------------------------------------------------
*                                                   port
------------------------------------------------------------------------------------------------------------------------
*/
/* ----------------------- Supporting functions -----------------------------*/
BOOL                        MBPortEventInit(Stru_MBHandle *pxHandle);
BOOL                        MBPortEventPost(Stru_MBHandle *pxHandle, Enum_StateMachine_MBEvent eEvent );
Enum_StateMachine_MBEvent   MBPortEventGet(Stru_MBHandle *pxHandle);



/* ================================================================================================================== */
/*                                               register function                                                    */
/* ================================================================================================================== */

#if MB_FUNC_OTHER_REP_SLAVEID_BUF > 0
Enum_MBExceptionCode        eMBFuncReportSlaveID(Stru_MB *pStru_MB);
#endif

#if MB_FUNC_READ_INPUT_ENABLED > 0
Enum_MBExceptionCode        eMBFuncReadInputRegister(Stru_MB *pStru_MB);
#endif

#if MB_FUNC_READ_HOLDING_ENABLED > 0
Enum_MBExceptionCode        eMBFuncReadHoldingRegister(Stru_MB *pStru_MB);
#endif

#if MB_FUNC_WRITE_HOLDING_ENABLED > 0
Enum_MBExceptionCode        eMBFuncWriteHoldingRegister(Stru_MB *pStru_MB);
#endif

#if MB_FUNC_WRITE_MULTIPLE_HOLDING_ENABLED > 0
Enum_MBExceptionCode        eMBFuncWriteMultipleHoldingRegister(Stru_MB *pStru_MB);
#endif

#if MB_FUNC_READ_COILS_ENABLED > 0
Enum_MBExceptionCode        eMBFuncReadCoils(Stru_MB *pStru_MB);
#endif

#if MB_FUNC_WRITE_COIL_ENABLED > 0
Enum_MBExceptionCode        eMBFuncWriteCoil(Stru_MB *pStru_MB);
#endif

#if MB_FUNC_WRITE_MULTIPLE_COILS_ENABLED > 0
Enum_MBExceptionCode        eMBFuncWriteMultipleCoils(Stru_MB *pStru_MB);
#endif

#if MB_FUNC_READ_DISCRETE_INPUTS_ENABLED > 0
Enum_MBExceptionCode        eMBFuncReadDiscreteInputs(Stru_MB *pStru_MB);
#endif

#if MB_FUNC_READWRITE_HOLDING_ENABLED > 0
Enum_MBExceptionCode        eMBFuncReadWriteMultipleHoldingRegister(Stru_MB *pStru_MB);
#endif



/* ================================================================================================================== */
/*                                                      RROCESS                                                       */
/* ================================================================================================================== */
Enum_MBErrorCode            MBInit( Stru_MB     *pStru_MB,
                                    Enum_MBMode Enum_Mode,
                                    UCHAR       SlaveAddress );
Enum_MBErrorCode            MBPoll( Stru_MB     *pStru_MB );



#endif /* _MB_H */


