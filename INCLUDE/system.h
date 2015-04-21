#ifndef __SYSTEM_H
#define __SYSTEM_H

#include<p30f4011.h>

//#include"GenericTypeDefs.h"


#define Fcy		14745600
#define IN_ON	0
#define IN_OFF	1


#define X1				_RD2
#define X2				_RD0
#define X3				_RF6
#define X4				_RF5
#define X5				_RF4
#define X6				_RF1
#define X7				_RF0
#define X8				_RE5


#define SERIAL_DATA		_LATB0
#define SERIAL_CLK		_LATB1

#define RELAY_OE		_LATB2
#define RELAY_LAT		_LATE1
#define LCD_EN			_LATD3
#define LCD_LAT			_LATB6

#define System_LED		_LATB7

#define Button1			_RE4
#define Button2			_RE3
#define Button3			_RE2
#define Button4			_RE0

#define DS1302_CLK		_LATB3
#define DS1302_IN		_RB4
#define DS1302_OUT		_LATB4
#define DS1302_RST		_LATB5
#define DS1302_IO_TRIS	_TRISB4

#define RL_CLR 0x0000

#define Y1 	0x0010
#define Y2 	0x0008
#define Y3 	0x0004
#define Y4 	0x0002
#define Y5 	0x0020
#define Y6 	0x0040
#define Y7 	0x0080
#define Y8 	0x0001

#define Y9 	0x0100
#define Y10 0x4000
#define Y11 0x8000
#define Y12 0x2000
#define Y13 0x1000
#define Y14 0x0800
#define Y15 0x0400
#define Y16 0x0200


/*DAC driver define*/




/*Encoder driver define*/



void IO_port_Initial(void);
void RELAY_Init(void);
void RELAY_Control(unsigned int relay_data);



//unsigned int Tick_read(void);
signed long Tick_read_sw();
void System_tick_initial(void);

#endif

