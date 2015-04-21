#include "p30f4011.h"
#include "../INCLUDE/system.h"
void IO_port_Initial(void)
{
	ADPCFG 	= 0xFFFF;
//INPUT X SET TRIS
	_TRISD0 = 1;
	_TRISD2 = 1;
	_TRISF0 = 1;
	_TRISF1 = 1;
	_TRISF4 = 1;
	_TRISF5 = 1;
	_TRISF6 = 1;
	_TRISE5 = 1;

	_TRISB0 = 0;
	_TRISB1 = 0;
	_TRISB2 = 0;
	_TRISE1 = 0;
	_TRISD3 = 0;
	_TRISB6 = 0;

	_TRISB7 = 0;

	_TRISE0 = 1;
	_TRISE2 = 1;
	_TRISE3 = 1;
	_TRISE4 = 1;
	
	_TRISB3	= 0;
	_TRISB5 = 0;
	RELAY_OE = 0;
	DS1302_CLK = 0;
	DS1302_RST = 0;
	
}
void RELAY_Init(void)
{
	char i;
	for (i = 15;i >=0 ;i-- ){
		SERIAL_DATA = 0;
		SERIAL_CLK = 1;
		Nop();
		Nop();
		SERIAL_CLK = 0;		
	}
	RELAY_LAT = 1;
	Nop();
	Nop();
	RELAY_LAT = 0;	
}

void RELAY_Control(unsigned int relay_data)
{
	static unsigned int pre_relay_data;
	char i;
	if(pre_relay_data == relay_data)
		return;
	for (i = 15;i >=0 ;i-- ){
		SERIAL_DATA = 0x01&(relay_data >> i);
		SERIAL_CLK = 1;
		Nop();
		Nop();
		SERIAL_CLK = 0;		
	}
	RELAY_LAT = 1;
	Nop();
	Nop();
	RELAY_LAT = 0;	
	pre_relay_data = relay_data;
}

