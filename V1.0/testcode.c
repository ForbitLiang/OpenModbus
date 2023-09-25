/***************************Copyright (c)**************************************
*                      ***************************
*                      ***************************
***************************FILEINFO.*******************************************
*	NAME    :	testcode.c
* 	VERSION :	V1.0
* 	DATE    :	2023.09.23
* 	AUTHOR  :	forbit
*	DESP.   :
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/mb.h"

unsigned char reg[20] = {0};
unsigned short holding_register[20] = {0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,0x10,0x20,0x30,0x40,0x50};



/* reserve two byte CRC  */
unsigned char func03_test1_input_length = 8;
unsigned char func03_test1_input[8] = {0x01,0x03,0x00,0x01,0x00,0x04,0x0,0x0}; // test1
// unsigned char func03_test1_input[8] = {00,03,00,01,00,04,0,0};  // test2
// unsigned char func03_test1_input[8] = {02,03,00,01,00,04,0,0};  // test3
// unsigned char func03_test1_input[8] = {01,03,00,00,00,00,0,0}; // test4
// unsigned char func03_test1_input[8] = {0x01,0x03,00,0x12,0x00,0x03,0x0,0x0};  // test5
// unsigned char func03_test1_input[8] = {0x01,0x03,00,0x12,0x00,0x04,0x0,0x0};  // test6
// unsigned char func03_test1_input[8] = {0x01,0x03,0x00,0x07,0x00,0x04,0x0,0x0}; // test7

unsigned char func06_test1_input_length = 8;
unsigned char func06_test1_input[8] = {0x01,0x06,0x00,0x01,0x00,0x02,0x00,0x00};  // test1
// unsigned char func06_test1_input[8] = {0x01,0x06,0x00,0x03,0x01,0x12,0x00,0x00};  // test2
// unsigned char func06_test1_input[8] = {0x01,0x06,0x00,0x15,0x00,0x02,0x00,0x00};  // test3
// unsigned char func06_test1_input[8] = {0x01,0x06,0x00,0x00,0x00,0x02,0x00,0x00};  // test4

unsigned char func10_test1_input_length = 15;   // test1
unsigned char func10_test1_input[15] = { 0x01, 0x0a, 0x00, 0x01, 0x00, 0x03, 0x06, 0x00, 0x02, 0x00, 0x03, 0x00, 0x04, 0x00, 0x00};  // test1
// unsigned char func10_test1_input_length = 13;   // test2
// unsigned char func10_test1_input[13] = { 0x01, 0x0a, 0x00, 0x05, 0x00, 0x02, 0x04, 0x00, 0x02, 0x00, 0x03, 0x00, 0x00};   // test2
// unsigned char func10_test1_input_length = 9;   // test3
// unsigned char func10_test1_input[9] = { 0x01, 0x0a, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00};   // test3
// unsigned char func10_test1_input_length = 15;   // test4
// unsigned char func10_test1_input[15] = { 0x01, 0x0a, 0x00, 0x13, 0x00, 0x03, 0x06, 0x00, 0x01, 0x00, 0x02, 0x00, 0x03, 0x00, 0x00};   // test4
// unsigned char func10_test1_input_length = 13;   // test5
// unsigned char func10_test1_input[15] = { 0x01, 0x0a, 0x00, 0x13, 0x00, 0x02, 0x04, 0x00, 0x01, 0x01, 0x02, 0x00, 0x00};   // test5
// unsigned char func10_test1_input_length = 15;   // test6
// unsigned char func10_test1_input[15] = { 0x01, 0x0a, 0x00, 0x00, 0x00, 0x03, 0x06, 0x00, 0x01, 0x00, 0x02, 0x00, 0x03, 0x00, 0x00};   // test6
// unsigned char func10_test1_input_length = 15;   // test6
// unsigned char func10_test1_input[15] = { 0x01, 0x0a, 0x00, 0x15, 0x00, 0x03, 0x06, 0x00, 0x01, 0x00, 0x02, 0x00, 0x03, 0x00, 0x00};   // test6

unsigned char func17_test1_input_length = 19;   // test1
unsigned char func17_test1_input[19] = {0x01, 0x17,	0x00, 0x01,	0x00, 0x02,	0x00, 0x01,	0x00, 0x03,	0x06, 0x00,	0x02, 0x00,	0x03, 0x00,	0x04, 0x00, 0x00};  // test1
// unsigned char func17_test1_input_length = 19;   // test2
// unsigned char func17_test1_input[19] = {0x01, 0x17,	0x00, 0x01,	0x00, 0x00,	0x00, 0x01,	0x00, 0x03,	0x06, 0x00,	0x02, 0x00,	0x03, 0x00,	0x04, 0x00, 0x00};  // test2
// unsigned char func17_test1_input_length = 19;   // test3
// unsigned char func17_test1_input[19] = {0x01, 0x17,	0x00, 0x01,	0x00, 0x7F,	0x00, 0x01,	0x00, 0x03,	0x06, 0x00,	0x02, 0x00,	0x03, 0x00,	0x04, 0x00, 0x00};  // test3
// unsigned char func17_test1_input_length = 19;   // test4
// unsigned char func17_test1_input[19] = {0x01, 0x17,	0x00, 0x01,	0x00, 0x02,	0x00, 0x00,	0x00, 0x03,	0x06, 0x00,	0x02, 0x00,	0x03, 0x00,	0x04, 0x00, 0x00};  // test4
// unsigned char func17_test1_input_length = 19;   // test5
// unsigned char func17_test1_input[19] = {0x01, 0x17,	0x00, 0x01,	0x00, 0x02,	0x00, 0x7a,	0x00, 0x03,	0x06, 0x00,	0x02, 0x00,	0x03, 0x00,	0x04, 0x00, 0x00};  // test5
// unsigned char func17_test1_input_length = 19;   // test6
// unsigned char func17_test1_input[19] = {0x01, 0x17,	0x00, 0x01,	0x00, 0x02,	0x00, 0x01,	0x00, 0x03,	0x07, 0x00,	0x02, 0x00,	0x03, 0x00,	0x04, 0x00, 0x00};  // test6
// unsigned char func17_test1_input_length = 19;   // test7
// unsigned char func17_test1_input[19] = {0x01, 0x17,	0x00, 0x13,	0x00, 0x02,	0x00, 0x01,	0x00, 0x03,	0x06, 0x00,	0x02, 0x00,	0x03, 0x00,	0x04, 0x00, 0x00};  // test7
// unsigned char func17_test1_input_length = 19;   // test8
// unsigned char func17_test1_input[19] = {0x01, 0x17,	0x00, 0x13,	0x00, 0x03,	0x00, 0x01,	0x00, 0x03,	0x06, 0x00,	0x02, 0x00,	0x03, 0x00,	0x04, 0x00, 0x00};  // test8
// unsigned char func17_test1_input_length = 19;   // test10
// unsigned char func17_test1_input[19] = {0x01, 0x17,	0x00, 0x01,	0x00, 0x02,	0x00, 0x12,	0x00, 0x03,	0x06, 0x00,	0x02, 0x00,	0x03, 0x00,	0x04, 0x00, 0x00};  // test10
// unsigned char func17_test1_input_length = 19;   // test11
// unsigned char func17_test1_input[19] = {0x01, 0x17,	0x00, 0x01,	0x00, 0x02,	0x00, 0x13,	0x00, 0x03,	0x06, 0x00,	0x02, 0x00,	0x03, 0x00,	0x04, 0x00, 0x00};  // test11

unsigned char func03tcp_test1_input_length = 12;
unsigned char func03tcp_test1_input[12] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0xFF, 0x03,0x00,0x01,0x00,0x04}; // test1


unsigned char func06tcp_test1_input_length = 12;
unsigned char func06tcp_test1_input[12] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0xFF, 0x06,0x00,0x01,0x00,0x02};  // test1


unsigned char func10tcp_test1_input_length = 19;   // test1
unsigned char func10tcp_test1_input[19] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0xFF, 0x0a, 0x00, 0x01, 0x00, 0x03, 0x06, 0x00, 0x02, 0x00, 0x03, 0x00, 0x04};  // test1


unsigned char func17tcp_test1_input_length = 23;   // test1
unsigned char func17tcp_test1_input[23] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0xFF, 0x17,	0x00, 0x01,	0x00, 0x02,	0x00, 0x01,	0x00, 0x03,	0x06, 0x00,	0x02, 0x00,	0x03, 0x00,	0x04};  // test1



void printshortArray(unsigned short * array, int size);
void printcharArray(unsigned char * array, int size);
/* test RTU */
void test_0x03(void);
void test_0x06(void);
void test_0x10(void);
void test_0x17(void);
void test_0x03_TCP(void);
void test_0x06_TCP(void);
void test_0x10_TCP(void);
void test_0x17_TCP(void);
void callback_funciton(void);


int main(void)
{
	// test_0x03();
	// test_0x06();
	// test_0x10();
	// test_0x17();
	// test_0x03_TCP();
	// test_0x06_TCP();
	// test_0x10_TCP();
	test_0x17_TCP();
	return 0;
}

void printcharArray(unsigned char * array, int size)
{
	int i = 0;

	printf("printArray:");

    for (i; i < size; i++) {
        printf("%x ", array[i]);
    }
    printf("\n");
}

void printshortArray(unsigned short * array, int size)
{
	int i = 0;

	printf("printArray:");

    for (i; i < size; i++) {
        printf("%x ", array[i]);
    }
    printf("\n");
}

void test_0x03(void)
{
	Stru_MB *pStru_MB 					= (Stru_MB*)malloc(sizeof(Stru_MB));
	USHORT              			 	CRC16;
	int										    i;

	printf("---- Test 0x03 function ----\n");
	printf("user Register date: ");
	printshortArray(holding_register, 20);

	/* modbus user initial */

	pStru_MB->MBHandle.MBErrorCode = MBInit(pStru_MB, enum_MB_RTU, 0x01);

	pStru_MB->UserIF.pxUserReg.pusRegHoldBuf = holding_register;
	pStru_MB->UserIF.pxUserReg.usRegHoldStart = 0x01;
	pStru_MB->UserIF.pxUserReg.usRegHoldNum = 0x14;
	pStru_MB->UserIF.pFunc_MBUserCBFunc = callback_funciton;

	pStru_MB->MBHandle.MBErrorCode = MBPoll(pStru_MB);

    printf("\nrun this? Enum_ErrCode: %d.\nEnum_StateMachine_MBEvent:%d \n", pStru_MB->MBHandle.MBErrorCode, MBPortEventGet(&(pStru_MB->MBHandle)));

// 1. generate data
//	printArray(func03_test1_input, func03_test1_input_length);
	CRC16 = usMBCRC16(func03_test1_input, func03_test1_input_length-2);
	func03_test1_input[func03_test1_input_length-2] = ( UCHAR )( CRC16 & 0xFF );  // Li Ho
    func03_test1_input[func03_test1_input_length-1] = ( UCHAR )( CRC16 >> 8 );
//	printcharArray(func03_test1_input, func03_test1_input_length);

// 2. input data
	memcpy(pStru_MB->MBHandle.RcvBuff, func03_test1_input, sizeof(func03_test1_input));
	pStru_MB->MBHandle.RcvBuffPos = func03_test1_input_length;
	printf("\ninput date: ");
	printcharArray(pStru_MB->MBHandle.RcvBuff, func03_test1_input_length);

// 3. update event
	MBPortEventPost(&(pStru_MB->MBHandle), enum_EV_FRAME_RECEIVED);

// 4. loop handle
	for(i=0; i<3; i++)
	{
		printf("\nrun this? Enum_ErrCode: %d.\nEnum_StateMachine_MBEvent:%d.\nMBExceptionCode:%d.\n", pStru_MB->MBHandle.MBErrorCode, MBPortEventGet(&(pStru_MB->MBHandle)), pStru_MB->MBHandle.MBExceptionCode);
		pStru_MB->MBHandle.MBErrorCode = MBPoll(pStru_MB);
	}

// 5. extract result
	if( MBPortEventGet(&(pStru_MB->MBHandle)) == enum_EV_FRAME_SENT)
	{
		MBPortEventPost(&(pStru_MB->MBHandle), enum_EV_READY);
		printf("\nOutput date: ");
		printcharArray(pStru_MB->MBHandle.pMBSendFrame, pStru_MB->MBHandle.SndBuffCount);
	}

// handle error

}



void test_0x06(void)
{
	Enum_MBErrorCode Enum_ErrCode = enum_MB_ENOERR;

	Stru_MB *pStru_MB 					= (Stru_MB*)malloc(sizeof(Stru_MB));
	USHORT              			 	CRC16;
	int										    i;

	printf("---- Test 0x06 function ----\n");
	printf("user Register date: ");
	printshortArray(holding_register, 20);

	/* modbus user initial */

	Enum_ErrCode = MBInit(pStru_MB, enum_MB_RTU, 0x01);

	pStru_MB->UserIF.pxUserReg.pusRegHoldBuf = holding_register;
	pStru_MB->UserIF.pxUserReg.usRegHoldStart = 0x01;
	pStru_MB->UserIF.pxUserReg.usRegHoldNum = 0x14;
	pStru_MB->UserIF.pFunc_MBUserCBFunc = callback_funciton;

	Enum_ErrCode = MBPoll(pStru_MB);

    printf("\nrun this? Enum_ErrCode: %d.\nEnum_StateMachine_MBEvent:%d \n", Enum_ErrCode, MBPortEventGet(&(pStru_MB->MBHandle)));

// 1. generate data
	CRC16 = usMBCRC16(func06_test1_input, func06_test1_input_length-2);
	func06_test1_input[func06_test1_input_length-2] = ( UCHAR )( CRC16 & 0xFF );  // Li Ho
    func06_test1_input[func06_test1_input_length-1] = ( UCHAR )( CRC16 >> 8 );
	// printcharArray(func06_test1_input, func06_test1_input_length);

// 2. input data
	memcpy(pStru_MB->MBHandle.RcvBuff, func06_test1_input, sizeof(func06_test1_input));
	pStru_MB->MBHandle.RcvBuffPos = func06_test1_input_length;
	printf("\ninput date: ");
	printcharArray(pStru_MB->MBHandle.RcvBuff, func06_test1_input_length);

// 3. update event
	MBPortEventPost(&(pStru_MB->MBHandle), enum_EV_FRAME_RECEIVED);

// 4. loop handle
	for(i=0; i<3; i++)
	{
		Enum_ErrCode = MBPoll(pStru_MB);
		printf("\nrun this? Enum_ErrCode: %d.\nEnum_StateMachine_MBEvent:%d.\nMBExceptionCode:%d.\n", Enum_ErrCode, MBPortEventGet(&(pStru_MB->MBHandle)), pStru_MB->MBHandle.MBExceptionCode);
	}

// 5. extract result
	if( MBPortEventGet(&(pStru_MB->MBHandle)) == enum_EV_FRAME_SENT)
	{
		MBPortEventPost(&(pStru_MB->MBHandle), enum_EV_READY);
		printf("\nOutput date: ");
		printcharArray(pStru_MB->MBHandle.pMBSendFrame, pStru_MB->MBHandle.SndBuffCount);
	}

	printf("user Register date: ");
	printshortArray(holding_register, 20);


}


void test_0x10(void)
{
	Enum_MBErrorCode Enum_ErrCode = enum_MB_ENOERR;

	Stru_MB *pStru_MB 					= (Stru_MB*)malloc(sizeof(Stru_MB));
	USHORT              			 	CRC16;
	int										    i;

	printf("---- Test 0x10 function ----\n");
	printf("user Register date: ");
	printshortArray(holding_register, 20);

	/* modbus user initial */
	Enum_ErrCode = MBInit(pStru_MB, enum_MB_RTU, 0x01);

	pStru_MB->UserIF.pxUserReg.pusRegHoldBuf = holding_register;
	pStru_MB->UserIF.pxUserReg.usRegHoldStart = 0x01;
	pStru_MB->UserIF.pxUserReg.usRegHoldNum = 0x14;
	pStru_MB->UserIF.pFunc_MBUserCBFunc = callback_funciton;

	Enum_ErrCode = MBPoll(pStru_MB);

    printf("\nrun this? Enum_ErrCode: %d.\nEnum_StateMachine_MBEvent:%d \n", Enum_ErrCode, MBPortEventGet(&(pStru_MB->MBHandle)));

// 1. generate data
	CRC16 = usMBCRC16(func10_test1_input, func10_test1_input_length-2);
	func10_test1_input[func10_test1_input_length-2] = ( UCHAR )( CRC16 & 0xFF );  // Li Ho
    func10_test1_input[func10_test1_input_length-1] = ( UCHAR )( CRC16 >> 8 );
	// printcharArray(func06_test1_input, func06_test1_input_length);

// 2. input data
	memcpy(pStru_MB->MBHandle.RcvBuff, func10_test1_input, sizeof(func10_test1_input));
	pStru_MB->MBHandle.RcvBuffPos = func10_test1_input_length;
	printf("\ninput date: ");
	printcharArray(pStru_MB->MBHandle.RcvBuff, func10_test1_input_length);

// 3. update event
	MBPortEventPost(&(pStru_MB->MBHandle), enum_EV_FRAME_RECEIVED);

// 4. loop handle
	for(i=0; i<3; i++)
	{
		Enum_ErrCode = MBPoll(pStru_MB);
		printf("\nrun this? Enum_ErrCode: %d.\nEnum_StateMachine_MBEvent:%d.\nMBExceptionCode:%d.\n", Enum_ErrCode, MBPortEventGet(&(pStru_MB->MBHandle)), pStru_MB->MBHandle.MBExceptionCode);
	}

// 5. extract result
	if( MBPortEventGet(&(pStru_MB->MBHandle)) == enum_EV_FRAME_SENT)
	{
		MBPortEventPost(&(pStru_MB->MBHandle), enum_EV_READY);
		printf("\nOutput date: ");
		printcharArray(pStru_MB->MBHandle.pMBSendFrame, pStru_MB->MBHandle.SndBuffCount);
	}
	printf("user Register date: ");
	printshortArray(holding_register, 20);

	printf("\nrun this? Enum_ErrCode: %d.\nEnum_StateMachine_MBEvent:%d.\nMBExceptionCode:%d.", Enum_ErrCode, MBPortEventGet(&(pStru_MB->MBHandle)), pStru_MB->MBHandle.MBExceptionCode);

}


void test_0x17(void)
{

	Enum_MBErrorCode Enum_ErrCode = enum_MB_ENOERR;

	Stru_MB *pStru_MB 					= (Stru_MB*)malloc(sizeof(Stru_MB));
	USHORT              			 	CRC16;
	int										    i;

	printf("---- Test 0x17 function ----\n");
	printf("user Register date: ");
	printshortArray(holding_register, 20);

	/* modbus user initial */


	Enum_ErrCode = MBInit(pStru_MB, enum_MB_RTU, 0x01);

	pStru_MB->UserIF.pxUserReg.pusRegHoldBuf = holding_register;
	pStru_MB->UserIF.pxUserReg.usRegHoldStart = 0x01;
	pStru_MB->UserIF.pxUserReg.usRegHoldNum = 0x14;
	pStru_MB->UserIF.pFunc_MBUserCBFunc = callback_funciton;


	Enum_ErrCode = MBPoll(pStru_MB);

    printf("\nrun this? Enum_ErrCode: %d.\nEnum_StateMachine_MBEvent:%d \n", Enum_ErrCode, MBPortEventGet(&(pStru_MB->MBHandle)));

// 1. generate data
	CRC16 = usMBCRC16(func17_test1_input, func17_test1_input_length-2);
	func17_test1_input[func17_test1_input_length-2] = ( UCHAR )( CRC16 & 0xFF );  // Li Ho
    func17_test1_input[func17_test1_input_length-1] = ( UCHAR )( CRC16 >> 8 );
	printcharArray(func17_test1_input, func17_test1_input_length);

// 2. input data
	memcpy(pStru_MB->MBHandle.RcvBuff, func17_test1_input, sizeof(func17_test1_input));
	pStru_MB->MBHandle.RcvBuffPos = func17_test1_input_length;
	printf("\ninput date: ");
	printcharArray(pStru_MB->MBHandle.RcvBuff, func17_test1_input_length);

// 3. update event
	MBPortEventPost(&(pStru_MB->MBHandle), enum_EV_FRAME_RECEIVED);

// 4. loop handle
	for(i=0; i<3; i++)
	{
		Enum_ErrCode = MBPoll(pStru_MB);
			printf("\nrun this? Enum_ErrCode: %d.\nEnum_StateMachine_MBEvent:%d.\nMBExceptionCode:%d.", Enum_ErrCode, MBPortEventGet(&(pStru_MB->MBHandle)), pStru_MB->MBHandle.MBExceptionCode);
	}

// 5. extract result
	if( MBPortEventGet(&(pStru_MB->MBHandle)) == enum_EV_FRAME_SENT)
	{
		MBPortEventPost(&(pStru_MB->MBHandle), enum_EV_READY);
		printf("\nOutput date: ");
		printcharArray(pStru_MB->MBHandle.pMBSendFrame, pStru_MB->MBHandle.SndBuffCount);
	}

	printf("user Register date: ");
	printshortArray(holding_register, 20);

}

void test_0x03_TCP(void)
{
	Stru_MB *pStru_MB 					= (Stru_MB*)malloc(sizeof(Stru_MB));
	USHORT              			 	CRC16;
	int										    i;

	printf("---- Test 0x03 function ----\n");
	printf("user Register date: ");
	printshortArray(holding_register, 20);

	/* modbus user initial */

	pStru_MB->MBHandle.MBErrorCode = MBInit(pStru_MB, enum_MB_TCP, MB_TCP_FAKE_ADDRESS);

	pStru_MB->UserIF.pxUserReg.pusRegHoldBuf = holding_register;
	pStru_MB->UserIF.pxUserReg.usRegHoldStart = 0x01;
	pStru_MB->UserIF.pxUserReg.usRegHoldNum = 0x14;
	pStru_MB->UserIF.pFunc_MBUserCBFunc = callback_funciton;

	pStru_MB->MBHandle.MBErrorCode = MBPoll(pStru_MB);

    printf("\nrun this? Enum_ErrCode: %d.\nEnum_StateMachine_MBEvent:%d \n", pStru_MB->MBHandle.MBErrorCode, MBPortEventGet(&(pStru_MB->MBHandle)));


// 1. input data
	memcpy(pStru_MB->MBHandle.RcvBuff, func03tcp_test1_input, sizeof(func03tcp_test1_input));
	pStru_MB->MBHandle.RcvBuffPos = func03tcp_test1_input_length;
	printf("\ninput date: ");
	printcharArray(pStru_MB->MBHandle.RcvBuff, func03tcp_test1_input_length);

// 3. update event
	MBPortEventPost(&(pStru_MB->MBHandle), enum_EV_FRAME_RECEIVED);

// 4. loop handle
	for(i=0; i<3; i++)
	{
		printf("\nrun this? Enum_ErrCode: %d.\nEnum_StateMachine_MBEvent:%d.\nMBExceptionCode:%d.\n", pStru_MB->MBHandle.MBErrorCode, MBPortEventGet(&(pStru_MB->MBHandle)), pStru_MB->MBHandle.MBExceptionCode);
		pStru_MB->MBHandle.MBErrorCode = MBPoll(pStru_MB);
	}

// 5. extract result
	if( MBPortEventGet(&(pStru_MB->MBHandle)) == enum_EV_FRAME_SENT)
	{
		MBPortEventPost(&(pStru_MB->MBHandle), enum_EV_READY);
		printf("\nOutput date: ");
		printcharArray(pStru_MB->MBHandle.pMBSendFrame, pStru_MB->MBHandle.SndBuffCount);
	}

// handle error

}


void test_0x06_TCP(void)
{
	Enum_MBErrorCode Enum_ErrCode = enum_MB_ENOERR;

	Stru_MB *pStru_MB 					= (Stru_MB*)malloc(sizeof(Stru_MB));
	USHORT              			 	CRC16;
	int										    i;

	printf("---- Test 0x06 function ----\n");
	printf("user Register date: ");
	printshortArray(holding_register, 20);

	/* modbus user initial */

	Enum_ErrCode = MBInit(pStru_MB,  enum_MB_TCP, MB_TCP_FAKE_ADDRESS);

	pStru_MB->UserIF.pxUserReg.pusRegHoldBuf = holding_register;
	pStru_MB->UserIF.pxUserReg.usRegHoldStart = 0x01;
	pStru_MB->UserIF.pxUserReg.usRegHoldNum = 0x14;
	pStru_MB->UserIF.pFunc_MBUserCBFunc = callback_funciton;

	Enum_ErrCode = MBPoll(pStru_MB);

    printf("\nrun this? Enum_ErrCode: %d.\nEnum_StateMachine_MBEvent:%d \n", Enum_ErrCode, MBPortEventGet(&(pStru_MB->MBHandle)));

// 1. generate data

// 2. input data
	memcpy(pStru_MB->MBHandle.RcvBuff, func06tcp_test1_input, sizeof(func06tcp_test1_input));
	pStru_MB->MBHandle.RcvBuffPos = func06tcp_test1_input_length;
	printf("\ninput date: ");
	printcharArray(pStru_MB->MBHandle.RcvBuff, func06tcp_test1_input_length);

// 3. update event
	MBPortEventPost(&(pStru_MB->MBHandle), enum_EV_FRAME_RECEIVED);

// 4. loop handle
	for(i=0; i<3; i++)
	{
		Enum_ErrCode = MBPoll(pStru_MB);
		printf("\nrun this? Enum_ErrCode: %d.\nEnum_StateMachine_MBEvent:%d.\nMBExceptionCode:%d.\n", Enum_ErrCode, MBPortEventGet(&(pStru_MB->MBHandle)), pStru_MB->MBHandle.MBExceptionCode);
	}

// 5. extract result
	if( MBPortEventGet(&(pStru_MB->MBHandle)) == enum_EV_FRAME_SENT)
	{
		MBPortEventPost(&(pStru_MB->MBHandle), enum_EV_READY);
		printf("\nOutput date: ");
		printcharArray(pStru_MB->MBHandle.pMBSendFrame, pStru_MB->MBHandle.SndBuffCount);
	}

	printf("user Register date: ");
	printshortArray(holding_register, 20);

}


void test_0x10_TCP(void)
{
	Enum_MBErrorCode Enum_ErrCode = enum_MB_ENOERR;

	Stru_MB *pStru_MB 					= (Stru_MB*)malloc(sizeof(Stru_MB));
	USHORT              			 	CRC16;
	int										    i;

	printf("---- Test 0x10 function ----\n");
	printf("user Register date: ");
	printshortArray(holding_register, 20);

	/* modbus user initial */
	Enum_ErrCode = MBInit(pStru_MB, enum_MB_TCP, MB_TCP_FAKE_ADDRESS);

	pStru_MB->UserIF.pxUserReg.pusRegHoldBuf = holding_register;
	pStru_MB->UserIF.pxUserReg.usRegHoldStart = 0x01;
	pStru_MB->UserIF.pxUserReg.usRegHoldNum = 0x14;
	pStru_MB->UserIF.pFunc_MBUserCBFunc = callback_funciton;

	Enum_ErrCode = MBPoll(pStru_MB);

    printf("\nrun this? Enum_ErrCode: %d.\nEnum_StateMachine_MBEvent:%d \n", Enum_ErrCode, MBPortEventGet(&(pStru_MB->MBHandle)));

// 1. generate data

// 2. input data
	memcpy(pStru_MB->MBHandle.RcvBuff, func10tcp_test1_input, sizeof(func10tcp_test1_input));
	pStru_MB->MBHandle.RcvBuffPos = func10tcp_test1_input_length;
	printf("\ninput date: ");
	printcharArray(pStru_MB->MBHandle.RcvBuff, func10tcp_test1_input_length);

// 3. update event
	MBPortEventPost(&(pStru_MB->MBHandle), enum_EV_FRAME_RECEIVED);

// 4. loop handle
	for(i=0; i<3; i++)
	{
		Enum_ErrCode = MBPoll(pStru_MB);
		printf("\nrun this? Enum_ErrCode: %d.\nEnum_StateMachine_MBEvent:%d.\nMBExceptionCode:%d.\n", Enum_ErrCode, MBPortEventGet(&(pStru_MB->MBHandle)), pStru_MB->MBHandle.MBExceptionCode);
	}

// 5. extract result
	if( MBPortEventGet(&(pStru_MB->MBHandle)) == enum_EV_FRAME_SENT)
	{
		MBPortEventPost(&(pStru_MB->MBHandle), enum_EV_READY);
		printf("\nOutput date: ");
		printcharArray(pStru_MB->MBHandle.pMBSendFrame, pStru_MB->MBHandle.SndBuffCount);
	}
	printf("user Register date: ");
	printshortArray(holding_register, 20);

	printf("\nrun this? Enum_ErrCode: %d.\nEnum_StateMachine_MBEvent:%d.\nMBExceptionCode:%d.", Enum_ErrCode, MBPortEventGet(&(pStru_MB->MBHandle)), pStru_MB->MBHandle.MBExceptionCode);

}


void test_0x17_TCP(void)
{

	Enum_MBErrorCode Enum_ErrCode = enum_MB_ENOERR;

	Stru_MB *pStru_MB 					= (Stru_MB*)malloc(sizeof(Stru_MB));
	USHORT              			 	CRC16;
	int										    i;

	printf("---- Test 0x17 function ----\n");
	printf("user Register date: ");
	printshortArray(holding_register, 20);

	/* modbus user initial */


	Enum_ErrCode = MBInit(pStru_MB, enum_MB_TCP, MB_TCP_FAKE_ADDRESS);

	pStru_MB->UserIF.pxUserReg.pusRegHoldBuf = holding_register;
	pStru_MB->UserIF.pxUserReg.usRegHoldStart = 0x01;
	pStru_MB->UserIF.pxUserReg.usRegHoldNum = 0x14;
	pStru_MB->UserIF.pFunc_MBUserCBFunc = callback_funciton;

	Enum_ErrCode = MBPoll(pStru_MB);

    printf("\nrun this? Enum_ErrCode: %d.\nEnum_StateMachine_MBEvent:%d \n", Enum_ErrCode, MBPortEventGet(&(pStru_MB->MBHandle)));

// 1. generate data

// 2. input data
	memcpy(pStru_MB->MBHandle.RcvBuff, func17tcp_test1_input, sizeof(func17tcp_test1_input));
	pStru_MB->MBHandle.RcvBuffPos = func17tcp_test1_input_length;
	printf("\ninput date: ");
	printcharArray(pStru_MB->MBHandle.RcvBuff, func17tcp_test1_input_length);

// 3. update event
	MBPortEventPost(&(pStru_MB->MBHandle), enum_EV_FRAME_RECEIVED);

// 4. loop handle
	for(i=0; i<3; i++)
	{
		Enum_ErrCode = MBPoll(pStru_MB);
			printf("\nrun this? Enum_ErrCode: %d.\nEnum_StateMachine_MBEvent:%d.\nMBExceptionCode:%d.", Enum_ErrCode, MBPortEventGet(&(pStru_MB->MBHandle)), pStru_MB->MBHandle.MBExceptionCode);
	}

// 5. extract result
	if( MBPortEventGet(&(pStru_MB->MBHandle)) == enum_EV_FRAME_SENT)
	{
		MBPortEventPost(&(pStru_MB->MBHandle), enum_EV_READY);
		printf("\nOutput date: ");
		printcharArray(pStru_MB->MBHandle.pMBSendFrame, pStru_MB->MBHandle.SndBuffCount);
	}

	printf("user Register date: ");
	printshortArray(holding_register, 20);

}


void callback_funciton(void)
{
	printf("haha");
}


