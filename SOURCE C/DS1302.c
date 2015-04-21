#include <p30f4011.h>
#include "../INCLUDE/system.h" 
#include "../INCLUDE/LCD.h" 
#include "../INCLUDE/DS1302.h" 
#include "../INCLUDE/GenericTypeDefs.h"

#include "../button/button.h"

#include "../interfaces/interfaces.h"


const char Day_String[7][3]={"CN","T2","T3","T4","T5","T6","T7"};
const char Am_Pm_String[2][3]={"Am","Pm"};



BYTE Year;
BYTE Month;
BYTE Date;
BYTE Day;
BYTE Hour;
BYTE Min;
BYTE Sec;
BYTE AM;

char monday_idx;
char Tuesday_idx;
char Wed_idx;
char Thurs_idx;
void Relay_sms_handler(void);

void WriteDS1302( BYTE ds_addr, BYTE ds_data )
{
	BYTE i;
	DS1302_CLK = 0;
	DS1302_RST = 1;
	DS1302_IO_TRIS = 0;
	Nop();
	Nop();
	Nop();
	Nop();
	for(i = 0; i < 8; i++)
	{
		DS1302_CLK = 0;
		DS1302_OUT = ds_addr & 0x01;
		Nop();
		Nop();
		DS1302_CLK = 1;
		ds_addr = ds_addr >> 1;
		Nop();
		Nop();
	}
	for(i = 0; i < 8; i++)
	{
		DS1302_CLK = 0;
		DS1302_OUT = ds_data & 0x01;
		Nop();
		Nop();	
		DS1302_CLK = 1;
		ds_data = ds_data >> 1;
		Nop();
		Nop();
	}
	DS1302_OUT = 0;
	Nop();
	Nop();
	DS1302_RST  = 0;
	DS1302_IO_TRIS = 1;
}

/*******************Read_DS1302***********************************/
BYTE ReadDS1302( BYTE ds_addr )
{
	BYTE i;
	BYTE_VAL DS1302DATA;
	DS1302_CLK = 0;
	DS1302_RST = 1;
	DS1302_IO_TRIS = 0;
	Nop();
	Nop();
	Nop();
	Nop();
	for(i = 0; i < 8; i++)
	{
		DS1302_CLK = 0;
		DS1302_OUT = ds_addr & 0x01;
		Nop();
		Nop();
		DS1302_CLK = 1;
		ds_addr = ds_addr >> 1;
		Nop();
		Nop();
	}
	DS1302_IO_TRIS = 1;
	Nop();
	Nop();
	Nop();
	Nop();
	for(i = 0; i < 7; i++)
	{
		DS1302_CLK = 0;
		Nop();
		Nop();
		DS1302DATA.bits.b7 = DS1302_IN;
		DS1302DATA.Val = DS1302DATA.Val >> 1;
		DS1302_CLK = 1;
	}
	DS1302_CLK = 0;
	Nop();
	Nop();
	DS1302_RST = 0;
	return DS1302DATA.Val;
}

/************************Initial_DS1302*****************************/
void DS1302_Init(void)
{
	BYTE_VAL init_read;
	WriteDS1302( WR_CONTROL,0x00 );
	WriteDS1302( WR_CHARGER,0x00 );
	init_read.Val = ReadDS1302(RD_SEC);
	if(init_read.bits.b7 == 1)    // check is clock halt bit (CH)
	{
		init_read.bits.b7 = 0;
		WriteDS1302( WR_SEC,init_read.Val );	
	}
	init_read.Val = ReadDS1302(RD_HR);
	if(init_read.bits.b7 == 0)	// check isnot 12 hr format
	{
		init_read.bits.b7 = 1;
		WriteDS1302( WR_HR,init_read.Val );
	}

	
}

void DS1302_Read_RTC(void)
{
	BYTE_VAL DS_Year;
	BYTE_VAL DS_Month;
	BYTE_VAL DS_Date;
	BYTE_VAL DS_Day;
	BYTE_VAL DS_Hour;
	BYTE_VAL DS_Min;
	BYTE_VAL DS_Sec;
	DS_Year.Val = ReadDS1302(RD_YEAR);
	DS_Month.Val = ReadDS1302(RD_MONTH);
	DS_Date.Val = ReadDS1302(RD_DATE);
	DS_Day.Val = ReadDS1302(RD_DAY);
	DS_Hour.Val = ReadDS1302(RD_HR);
	DS_Min.Val = ReadDS1302(RD_MIN);
	DS_Sec.Val = ReadDS1302(RD_SEC);
	Year =  DS_Year.BCD.H*10 + DS_Year.BCD.L;
	Month = (DS_Month.BCD.H & 0x01)*10 + DS_Month.BCD.L;
	Date = (DS_Date.BCD.H & 0x03)*10 + DS_Date.BCD.L;
	Day = 	(DS_Day.Val & 0x07);
	Hour = (DS_Hour.BCD.H & 0x01)*10 + DS_Hour.BCD.L;
	AM = DS_Hour.bits.b5;
	Min = (DS_Min.BCD.H & 0x07)*10 +DS_Min.BCD.L;
	Sec = (DS_Sec.BCD.H & 0x07)*10 +DS_Sec.BCD.L;
}

void DS_Write_RTC(BYTE YY, BYTE MM, BYTE DD, BYTE day,
					 BYTE hr, BYTE mm, BYTE sec, BYTE am)
{
	BYTE_VAL DS_Year;
	BYTE_VAL DS_Month;
	BYTE_VAL DS_Date;
	BYTE_VAL DS_Day;
	BYTE_VAL DS_Hour;
	BYTE_VAL DS_Min;
	BYTE_VAL DS_Sec;
	
	DS_Year.BCD.H = YY/10;
	DS_Year.BCD.L = YY%10;
	DS_Month.BCD.H = MM/10;
	DS_Month.BCD.L = MM%10;
	DS_Date.BCD.H = DD/10;
	DS_Date.BCD.L = DD%10;
	DS_Day.Val = day;
	DS_Hour.bits.b7 = 1;
	DS_Hour.bits.b5 = am;
	DS_Hour.bits.b4 = hr/10;
	DS_Hour.BCD.L = hr%10;
	DS_Min.BCD.H = mm/10;
	DS_Min.BCD.L = mm%10;
	DS_Sec.BCD.H = sec/10;
	DS_Sec.BCD.L = sec%10;
	
	WriteDS1302( WR_YEAR, DS_Year.Val);
	WriteDS1302( WR_MONTH, DS_Month.Val);
	WriteDS1302( WR_DATE, DS_Date.Val);
	WriteDS1302( WR_DAY, DS_Day.Val);
	WriteDS1302( WR_HR, DS_Hour.Val);
	WriteDS1302( WR_MIN, DS_Min.Val);
	WriteDS1302( WR_SEC, DS_Sec.Val);
	
}


void LCD_Show_RTC_task(void)
{
	
	LCD_Gotoxy(1,1);
	LCD_PutString(Day_String[Day-1]);
	LCD_PutString(" ");
	if(Date < 10)
		LCD_PutNum(0);
	LCD_PutNum(Date);
	LCD_PutString("/");
	if(Month < 10)
		LCD_PutNum(0);
	LCD_PutNum(Month);
	LCD_PutString("/");
	LCD_PutNum(Year+2000);	
	LCD_Gotoxy(1,2);
	if(Hour < 10)
		LCD_PutNum(0);
	LCD_PutNum(Hour);
	LCD_PutString(":");
	if(Min < 10)
		LCD_PutNum(0);
	LCD_PutNum(Min);
	LCD_PutString(":");
	if(Sec < 10)
		LCD_PutNum(0);
	LCD_PutNum(Sec);
	LCD_PutString(" ");
	LCD_PutString(Am_Pm_String[AM]);
}
extern signed long tick_count;
signed long LCD_Show_RTC_Option_tick = 0;
char LCD_Show_RTC_cursor_b = 0;
char LCD_Show_RTC_trigger = 1;
BYTE LCD_PreDay;
void LCD_Show_RTC_Option_task(void)
{
	char t_option_mode;
	if(((tick_count-LCD_Show_RTC_Option_tick)>2000)
		||LCD_Show_RTC_trigger){

		/*
		 * the refresh lcd
		 * */
		if (LCD_PreDay != Day){
			LCD_CMD(LCD_CLEAR);         //Xoa man hinh
			LCD_PreDay = Day;
		}
		if (!LCD_Show_RTC_trigger)
			LCD_Show_RTC_cursor_b = !LCD_Show_RTC_cursor_b;
		LCD_Show_RTC_trigger = 0;
		LCD_Show_RTC_Option_tick = tick_count;
		//
		t_option_mode = Button_getSta();
		LCD_Gotoxy(1,1);
		
		if((t_option_mode == BUTTON_OP_Day)&&LCD_Show_RTC_cursor_b){
			LCD_PutString("  ");
		}else{
			LCD_PutString(Day_String[Day-1]);
		}
		LCD_PutString(" ");
		
		if((t_option_mode == BUTTON_OP_Date)&&LCD_Show_RTC_cursor_b){
			LCD_PutString("  ");
		}else{
			if(Date < 10)
				LCD_PutNum(0);
			LCD_PutNum(Date);
		}
		LCD_PutString("/");
		
		if((t_option_mode == BUTTON_OP_Month)&&LCD_Show_RTC_cursor_b){
			LCD_PutString("  ");
		}else{
			if(Month < 10)
				LCD_PutNum(0);
			LCD_PutNum(Month);
		}
		LCD_PutString("/");
		if((t_option_mode == BUTTON_OP_Year)&&LCD_Show_RTC_cursor_b){
			LCD_PutString("    ");
			}else{
			LCD_PutNum(Year+2000);	
		}
		
		LCD_Gotoxy(1,2);
		if((t_option_mode == BUTTON_OP_Hour)&&LCD_Show_RTC_cursor_b){
			LCD_PutString("  ");
		}else{
			if(Hour < 10)
				LCD_PutNum(0);
			LCD_PutNum(Hour);
		}
		LCD_PutString(":");
		
		if((t_option_mode == BUTTON_OP_Min)&&LCD_Show_RTC_cursor_b){
			LCD_PutString("  ");
		}else{
			if(Min < 10)
				LCD_PutNum(0);
			LCD_PutNum(Min);
		}
		LCD_PutString(":");
		
		if((t_option_mode == BUTTON_OP_Sec)&&LCD_Show_RTC_cursor_b){
			LCD_PutString("  ");
		}else{
			if(Sec < 10)
				LCD_PutNum(0);
			LCD_PutNum(Sec);
		}
		LCD_PutString(" ");
		if((t_option_mode == BUTTON_OP_AM)&&LCD_Show_RTC_cursor_b){
			LCD_PutString("  ");
		}else{
			LCD_PutString(Am_Pm_String[AM]);
		}
	}
}

void LCD_Show_RTC_Option_ResetDisplay(void){
	LCD_Show_RTC_Option_tick = tick_count;
	LCD_Show_RTC_cursor_b = 0; //no need hidden effective 
	LCD_Show_RTC_trigger = 1;

}
short int OvTime_type1(){
	//return
	return (!X1);
}
short int OvTime_type2(){
	//return
	return (!X2);
}
#define CalSum_Min(hour,min)	(short int)(((short int)hour*60)+(short int)min)

unsigned int l_relay_requested_sta_uw = 0;
unsigned char l_relay_manual_in_day_flag_ub = 0;
BYTE PreDay;
#define g_com_requested_by_sms_flag_ub serial_com_st.requested_flag_b
#define g_com_requested_sta_uw	serial_com_st.Requested_relay_st.Val_uw
#define l_relay_sta_uw relay_control_st.Relay_status_st.Val_uw
#define l_relay_OT1_b relay_control_st.Overtime_status_st.Overtime_1
#define l_relay_OT2_b relay_control_st.Overtime_status_st.Overtime_2

void Relay_sms_handler(void){
	if(g_com_requested_by_sms_flag_ub){
		g_com_requested_by_sms_flag_ub = 0;
		l_relay_manual_in_day_flag_ub = 1;
		l_relay_requested_sta_uw = g_com_requested_sta_uw;
	}

	/*
	 * the sms request is available in 1 day only
	 * */
	if (PreDay != Day){
		l_relay_manual_in_day_flag_ub = 0;

	}
	PreDay = Day;
}

void Relay_Main(void){
	unsigned char t_overtime_day_b, t_overtime_sat_sun_b;
	unsigned int t_relay_sta;
	short int t_min_Sum;
	short int t_24h_Hour;
	Relay_sms_handler();

	//overtime status
	t_overtime_day_b = OvTime_type1();
	t_overtime_sat_sun_b = OvTime_type2();

	//computing relay status
	if (0==l_relay_manual_in_day_flag_ub){
		if ((AM == Pm)&&(Hour!=12)){
			t_24h_Hour = Hour + 12;
		}else if((AM == Am)&&(Hour==12)){
			t_24h_Hour = 0;
		}else{
			t_24h_Hour = Hour;
		}
		t_min_Sum = CalSum_Min(t_24h_Hour,Min);
		t_relay_sta = 0;
		if ( t_overtime_day_b == 0 ){
			if(		((Day == 2) &&((t_min_Sum >= CalSum_Min(6,30) )&& (t_min_Sum <CalSum_Min(16,40))))
				||	((Day == 3) &&((t_min_Sum >= CalSum_Min(6,30) )&& (t_min_Sum <CalSum_Min(16,40))))
				||	((Day == 4) &&((t_min_Sum >= CalSum_Min(6,30) )&& (t_min_Sum <CalSum_Min(16,40))))
				||	((Day == 5) &&((t_min_Sum >= CalSum_Min(6,30) )&& (t_min_Sum <CalSum_Min(16,40))))
				||	((Day == 6) &&((t_min_Sum >= CalSum_Min(6,30) )&& (t_min_Sum <CalSum_Min(16,40))))
				) {
				//on relay
				t_relay_sta |= Y1  |Y2  |Y3  |Y4  |Y5  |Y6  |Y7 ;
			}else{
				//off relay
				t_relay_sta &= ~(Y1  |Y2  |Y3  |Y4  |Y5  |Y6  |Y7  );
			}
			if(		((Day == 2) &&((t_min_Sum >= CalSum_Min(6,30) )&& (t_min_Sum <CalSum_Min(16,30))))
				||	((Day == 3) &&((t_min_Sum >= CalSum_Min(6,30) )&& (t_min_Sum <CalSum_Min(16,30))))
				||	((Day == 4) &&((t_min_Sum >= CalSum_Min(6,30) )&& (t_min_Sum <CalSum_Min(16,30))))
				||	((Day == 5) &&((t_min_Sum >= CalSum_Min(6,30) )&& (t_min_Sum <CalSum_Min(16,30))))
				||	((Day == 6) &&((t_min_Sum >= CalSum_Min(6,30) )&& (t_min_Sum <CalSum_Min(16,30))))
				) {
				//on relay
				t_relay_sta |= Y8  |Y9  |Y10 |Y11 |Y12 |Y13 |Y14 |Y15 ;
			}else{
				//off relay
				t_relay_sta &= ~( Y8  |Y9  |Y10 |Y11 |Y12 |Y13 |Y14 |Y15 );
			}
		}else{
			if(		((Day == 2) &&((t_min_Sum >= CalSum_Min(6,30) )&& (t_min_Sum <CalSum_Min(19,10))))
				||	((Day == 3) &&((t_min_Sum >= CalSum_Min(6,30) )&& (t_min_Sum <CalSum_Min(19,10))))
				||	((Day == 4) &&((t_min_Sum >= CalSum_Min(6,30) )&& (t_min_Sum <CalSum_Min(19,10))))
				||	((Day == 5) &&((t_min_Sum >= CalSum_Min(6,30) )&& (t_min_Sum <CalSum_Min(19,10))))
				||	((Day == 6) &&((t_min_Sum >= CalSum_Min(6,30) )&& (t_min_Sum <CalSum_Min(19,10))))
				) {
				//on relay
				t_relay_sta |= Y1  |Y2  |Y3  |Y4  |Y5  |Y6  |Y7   ;
			}else{
				//off relay
				t_relay_sta &= ~(Y1  |Y2  |Y3  |Y4  |Y5  |Y6  |Y7  );
			}
			if(		((Day == 2) &&((t_min_Sum >= CalSum_Min(6,30) )&& (t_min_Sum <CalSum_Min(19,0 ))))
				||	((Day == 3) &&((t_min_Sum >= CalSum_Min(6,30) )&& (t_min_Sum <CalSum_Min(19,0 ))))
				||	((Day == 4) &&((t_min_Sum >= CalSum_Min(6,30) )&& (t_min_Sum <CalSum_Min(19,0 ))))
				||	((Day == 5) &&((t_min_Sum >= CalSum_Min(6,30) )&& (t_min_Sum <CalSum_Min(19,0 ))))
				||	((Day == 6) &&((t_min_Sum >= CalSum_Min(6,30) )&& (t_min_Sum <CalSum_Min(19,0 ))))
				) {
				//on relay
				t_relay_sta |=  Y8  |Y9  |Y10 |Y11 |Y12 |Y13 |Y14 |Y15 ;
			}else{
				//off relay
				t_relay_sta &= ~( Y8  |Y9  |Y10 |Y11 |Y12 |Y13 |Y14 |Y15 );
			}
		}

		// Over time with Saturday and Sunday
		if ( t_overtime_sat_sun_b == 0){
			//do no thing
		}else{
			if(	((Day == 7) &&((t_min_Sum >= CalSum_Min(6,30) )&& (t_min_Sum <CalSum_Min(16,40))))
				||	((Day == 1) &&((t_min_Sum >= CalSum_Min(6,30) )&& (t_min_Sum <CalSum_Min(16,40))))
				) {
				//on relay
				t_relay_sta |= Y1  |Y2  |Y3  |Y4  |Y5  |Y6  |Y7  |Y8  |Y9  |Y10 |Y11 |Y12 |Y13 |Y14 |Y15 ;
			}else{
				//off relay
				t_relay_sta &= ~(Y1  |Y2  |Y3  |Y4  |Y5  |Y6  |Y7  |Y8  |Y9  |Y10 |Y11 |Y12 |Y13 |Y14 |Y15 );
			}

		}

		//Y16
		if ( t_overtime_day_b == 0 ){
			if(		((Day == 2) &&(t_min_Sum >= CalSum_Min(16,40)))
				|| 	((Day == 3) &&(t_min_Sum < CalSum_Min(7 ,0 )))
				||	((Day == 3) &&(t_min_Sum >= CalSum_Min(16,40)))
				|| 	((Day == 4) &&(t_min_Sum < CalSum_Min(7 ,0 )))
				||	((Day == 4) &&(t_min_Sum >= CalSum_Min(16,40)))
				|| 	((Day == 5) &&(t_min_Sum < CalSum_Min(7 ,0 )))
				|| 	((Day == 5) &&(t_min_Sum >= CalSum_Min(16,40)))
				|| 	((Day == 6) &&(t_min_Sum < CalSum_Min(7 ,0 )))
				||	(((Day == 6)&&(t_overtime_sat_sun_b == 1)) &&(t_min_Sum >= CalSum_Min(16,40)))
				||	(((Day == 7)&&(t_overtime_sat_sun_b == 1)) &&(t_min_Sum < CalSum_Min(7 ,0 )))
				||	(((Day == 7)&&(t_overtime_sat_sun_b == 1)) &&(t_min_Sum >= CalSum_Min(16,40)))
				||	(((Day == 1)&&(t_overtime_sat_sun_b == 1)) &&(t_min_Sum < CalSum_Min(7 ,0 )))
				||	((Day == 1)&&(t_min_Sum >= CalSum_Min(16,40)))
				|| 	((Day == 2) &&(t_min_Sum < CalSum_Min(7 ,0 )))
				) {
				//on relay
				t_relay_sta |= Y16;
			} else{
				//off relay
				t_relay_sta &= ~ Y16;
			}

		}else{
			if(		((Day == 2) &&(t_min_Sum >= CalSum_Min(19,0 )))
				|| 	((Day == 3) &&(t_min_Sum < CalSum_Min(7 ,0 )))
				||	((Day == 3) &&(t_min_Sum >= CalSum_Min(19,0 )))
				|| 	((Day == 4) &&(t_min_Sum < CalSum_Min(7 ,0 )))
				||	((Day == 4) &&(t_min_Sum >= CalSum_Min(19,0 )))
				|| 	((Day == 5) &&(t_min_Sum < CalSum_Min(7 ,0 )))
				|| 	((Day == 5) &&(t_min_Sum >= CalSum_Min(19,0 )))
				|| 	((Day == 6) &&(t_min_Sum < CalSum_Min(7 ,0 )))
				||	(((Day == 6)&&(t_overtime_sat_sun_b == 1)) &&(t_min_Sum >= CalSum_Min(16,40)))
				||	(((Day == 7)&&(t_overtime_sat_sun_b == 1)) &&(t_min_Sum < CalSum_Min(7 ,0 )))
				||	(((Day == 7)&&(t_overtime_sat_sun_b == 1)) &&(t_min_Sum >= CalSum_Min(16,40)))
				||	(((Day == 1)&&(t_overtime_sat_sun_b == 1)) &&(t_min_Sum < CalSum_Min(7 ,0 )))
				||	((Day == 1)&&(t_min_Sum >= CalSum_Min(16,40)))
				|| 	((Day == 2) &&(t_min_Sum < CalSum_Min(7 ,0 )))
				) {
				//on relay
				t_relay_sta |= Y16;
			} else{
				//off relay
				t_relay_sta &= ~ Y16;
			}
		}
	} else {
		t_relay_sta = l_relay_requested_sta_uw;
	}

	//update signal
	l_relay_sta_uw = t_relay_sta;
	l_relay_OT1_b = t_overtime_day_b;
	l_relay_OT2_b = t_overtime_sat_sun_b;

	//update relay status
	RELAY_Control(t_relay_sta);
}



