/********************************************************************
* FileName:		Console.h
* Dependencies: none
* Processor:	PIC18, PIC24F, PIC24H, dsPIC30, dsPIC33
*               tested with 18F4620, dsPIC33FJ256GP710	
* Hardware:		PICDEM Z, Explorer 16, PIC18 Explorer
* Complier:     Microchip C18 v3.04 or higher
*				Microchip C30 v2.03 or higher
*               Microchip C32 v1.02 or higher
* Company:		Microchip Technology, Inc.
*
* Copyright � 2007-2009 Microchip Technology Inc.  All rights reserved.
*
* Microchip licenses to you the right to use, modify, copy and distribute 
* Software only when embedded on a Microchip microcontroller or digital 
* signal controller and used with a Microchip radio frequency transceiver, 
* which are integrated into your product or third party product (pursuant 
* to the terms in the accompanying license agreement). 
*
* You should refer to the license agreement accompanying this Software for 
* additional information regarding your rights and obligations.
*
* SOFTWARE AND DOCUMENTATION ARE PROVIDED �AS IS� WITHOUT WARRANTY OF ANY 
* KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY 
* WARRANTY OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A 
* PARTICULAR PURPOSE. IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE 
* LIABLE OR OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT LIABILITY, 
* CONTRIBUTION, BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE THEORY ANY 
* DIRECT OR INDIRECT DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO 
* ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR CONSEQUENTIAL DAMAGES, 
* LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF SUBSTITUTE GOODS, 
* TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES (INCLUDING BUT 
* NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
*
*********************************************************************
* File Description:
*
*  This header file allows usage of the console functions located
*   in Console.c
*
* Change History:
*  Rev   Date         Description
*  0.1   11/09/2006   Initial revision
*  1.0   01/09/2007   Initial release
*  2.0   4/15/2009    MiMAC and MiApp revision
*  2.1   06/20/2009   Add LCD support
********************************************************************/
#ifndef  _CONSOLE_H
#define  _CONSOLE_H

//#include "config.h"
//#include "SystemProfile.h"

#define BAUD_RATE 19200
#define ENABLE_CONSOLE

#ifndef BYTE
#define BYTE char
#endif

/************************ DEFINITIONS ******************************/
/************************ FUNCTION PROTOTYPES **********************/
//#if defined(__dsPIC30F__) || defined(__dsPIC33F__) || defined(__PIC24F__) || defined(__PIC24H__) || defined(__PIC32MX__)
	void ConsoleInit(void);
	#define ConsoleIsPutReady()     (U1STAbits.TRMT)
	void ConsolePut(BYTE c);
	void ConsolePutROMString(char* str);
	BYTE ConsoleGet(void);
	//BYTE ConsoleGetString(char *buffer, BYTE bufferLen);
	void PrintChar(BYTE);
	void PrintDec(BYTE);

//#error Unknown processor.  See Compiler.h
//#endif

//#define Printf(x) ConsolePutROMString( (char*)x)
//#define printf(x) ConsolePutROMString( (char*)x)

extern void serial_com_isrq_hanlder(unsigned char p_data_ub);
#endif

