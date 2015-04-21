#include <p30f4011.h>
#include "../INCLUDE/system.h" 
#include "../INCLUDE/LCD.h" 
#include "../INCLUDE/GenericTypeDefs.h" 
#include "../INCLUDE/DS1302.h"

#include "../button/button.h"

#include "../serial_com/serial_com_appl.h"

_FOSC(CSW_FSCM_OFF & XT_PLL8);//XT_PLL8            //Fail-Safe Clock Monitor Off, HS OSC
_FWDT(WDT_ON & WDTPSA_512 & WDTPSB_16);   //WatchDog On freq =125k/64/16
_FBORPOR(MCLR_EN & PBOR_ON & BORV_27 & RST_IOPIN);   //MCLR Enable, Power on Reset On, Brown-out Reset On = 2.7V.
_FGS(CODE_PROT_OFF);               //Code Protection OFF



int main(void)
{
	ClrWdt();
	IO_port_Initial();
	RELAY_Init();
	LCD_Init();
	LCD_LED_CMD(1);	

//	RELAY_Control(Y1|Y3|Y8|Y16);

	DS1302_Init();
/*	void DS_Write_RTC(BYTE YY, BYTE MM, BYTE DD, BYTE day,
					 BYTE hr, BYTE mm, BYTE sec, BYTE am);*/
//	DS_Write_RTC(15, 04, 13, 2,
//					11,59,50,Pm);
	serial_com_init_v();
	System_tick_initial();
	while(1){
		ClrWdt();
		DS1302_Read_RTC();
		LCD_Show_RTC_Option_task();
		//LCD_Show_RTC_task();
		Relay_Main();
		//Button_Option_Task();
		//Key_Task();
		serial_com_main();
	}
}
