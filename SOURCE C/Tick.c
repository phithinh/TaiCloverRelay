#include <p30f4011.h>

#include "../INCLUDE/system.h"
#include <timer.h>

signed long tick_count;	// !new update (changed data type)

void System_tick_initial(void)
{
	//_TRISE2=0;
	CloseTimer2();
	ConfigIntTimer2(T2_INT_PRIOR_7 & T2_INT_ON);
	OpenTimer2(T2_ON & T2_GATE_OFF &
           T2_PS_1_1 & T2_SOURCE_INT,1475); //100us
}
signed long Tick_read_sw(void)	// ! new update (changed data type and funct name)
{
	return(tick_count);
}	
char Key_Task(void);
void Button_Option_Task(void);
void _ISR _T2Interrupt(void) //10hz
{
	_T2IF=0;
	tick_count++;
	Key_Task();
	Button_Option_Task();
}
