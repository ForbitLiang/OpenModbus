/***************************Copyright (c)**************************************
*                      ***************************
*                      ***************************
***************************FILEINFO.*******************************************
*	NAME    :	mbconfig.h
* 	VERSION :	V1.0
* 	DATE    :	2023.09.23
* 	AUTHOR  :	forbit Liang
*	DESP.   :	
******************************************************************************/

#ifndef _MB_CONFIG_H
#define _MB_CONFIG_H


#define enum_MB_ASCII_ENABLED                        (  0 )      /*If Modbus ASCII support is enabled. */
#define enum_MB_RTU_ENABLED                          (  1 )      /*If Modbus RTU support is enabled. */
#define enum_MB_TCP_ENABLED                          (  1 )      /*If Modbus TCP support is enabled. */


#define MB_FUNC_HANDLERS_MAX                        ( 16 )
#define MB_FUNC_OTHER_REP_SLAVEID_BUF               ( 32 )


#define MB_FUNC_OTHER_REP_SLAVEID_ENABLED           (  0 )      /*If the <em>Report Slave ID</em> function should be enabled. */
#define MB_FUNC_READ_INPUT_ENABLED                  (  0 )      /*If the <em>Read Input Registers</em> function should be enabled. */
#define MB_FUNC_READ_HOLDING_ENABLED                (  1 )      /*If the <em>Read Holding Registers</em> function should be enabled. */
#define MB_FUNC_WRITE_HOLDING_ENABLED               (  1 )      /*If the <em>Write Single Register</em> function should be enabled. */
#define MB_FUNC_WRITE_MULTIPLE_HOLDING_ENABLED      (  1 )      /*If the <em>Write Multiple registers</em> function should be enabled. */
#define MB_FUNC_READ_COILS_ENABLED                  (  0 )      /*If the <em>Read Coils</em> function should be enabled. */
#define MB_FUNC_WRITE_COIL_ENABLED                  (  0 )      /*If the <em>Write Coils</em> function should be enabled. */
#define MB_FUNC_WRITE_MULTIPLE_COILS_ENABLED        (  0 )      /*If the <em>Write Multiple Coils</em> function should be enabled. */
#define MB_FUNC_READ_DISCRETE_INPUTS_ENABLED        (  0 )      /*If the <em>Read Discrete Inputs</em> function should be enabled. */
#define MB_FUNC_READWRITE_HOLDING_ENABLED           (  1 )      /*If the <em>Read/Write Multiple Registers</em> function should be enabled. */


#endif  /* _MB_CONFIG_H */

