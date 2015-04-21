/*
 * button.c
 *
 *  Created on: Nov 1, 2014
 *      Author: Phi Thinh
 */
#include "../INCLUDE/GenericTypeDefs.h"
#include "../INCLUDE/system.h" 
#include "../INCLUDE/DS1302.h"
#include "key.h"
#include "button.h"

#define CLEAR_SEC_BUTTON_EN

BUTTON_OPTION_MODE_DEF Button_Option_Mode;
BUTTON_OPTION_MODE_DEF Button_Option_LastMode = BUTTON_OP_Day;
extern BYTE Year;
extern BYTE Month;
extern BYTE Date;
extern BYTE Day;
extern BYTE Hour;
extern BYTE Min;
extern BYTE Sec;
extern BYTE AM;
#define BO_Year    Year
#define BO_Month   Month
#define BO_Date    Date
#define BO_Day     Day
#define BO_Hour    Hour
#define BO_Min     Min
#define BO_Sec     Sec
#define BO_AM      AM
void Button_Option_Task(void){
	char t_button_char;
	t_button_char = Key_Get();
	if (t_button_char){
		LCD_Show_RTC_Option_ResetDisplay();
	}		
	switch(Button_Option_Mode){
	case BUTTON_OP_Year:
		if(t_button_char == BUTTON_MODE){
			Button_Option_LastMode = Button_Option_Mode;
			Button_Option_Mode = BUTTON_OP_IDEL;
		}else if(t_button_char == BUTTON_UP){
			BO_Year = (BO_Year+1)%100;
			DS_Write_RTC(Year ,Month ,Date ,Day ,Hour ,Min ,Sec ,AM);
		}else if(t_button_char == BUTTON_DOWN){
			if(BO_Year <= 0){
				BO_Year = 99;
			}else {
				BO_Year--;
			}
			DS_Write_RTC(Year ,Month ,Date ,Day ,Hour ,Min ,Sec ,AM);
		}else if(t_button_char == BUTTON_NEXT){
			Button_Option_LastMode = Button_Option_Mode;
			Button_Option_Mode = BUTTON_OP_Hour;
		}
	break;
	case BUTTON_OP_Month:
		if(t_button_char == BUTTON_MODE){
			Button_Option_LastMode = Button_Option_Mode;
			Button_Option_Mode = BUTTON_OP_IDEL;
		}else if(t_button_char == BUTTON_UP){
			BO_Month = (BO_Month%12)+1;
			DS_Write_RTC(Year ,Month ,Date ,Day ,Hour ,Min ,Sec ,AM);
		}else if(t_button_char == BUTTON_DOWN){
			if(BO_Month <= 1){
				BO_Month = 12;
			}else {
				BO_Month--;
			}
			DS_Write_RTC(Year ,Month ,Date ,Day ,Hour ,Min ,Sec ,AM);
		}else if(t_button_char == BUTTON_NEXT){
			Button_Option_LastMode = Button_Option_Mode;
			Button_Option_Mode = BUTTON_OP_Year;
		}
	break;
	case BUTTON_OP_Date:
		if(t_button_char == BUTTON_MODE){
			Button_Option_LastMode = Button_Option_Mode;
			Button_Option_Mode = BUTTON_OP_IDEL;
		}else if(t_button_char == BUTTON_UP){
			BO_Date = (BO_Date%31)+1;
			DS_Write_RTC(Year ,Month ,Date ,Day ,Hour ,Min ,Sec ,AM);
		}else if(t_button_char == BUTTON_DOWN){
			if(BO_Date <= 1){
				BO_Date = 31;
			}else {
				BO_Date--;
			}
			DS_Write_RTC(Year ,Month ,Date ,Day ,Hour ,Min ,Sec ,AM);
		}else if(t_button_char == BUTTON_NEXT){
			Button_Option_LastMode = Button_Option_Mode;
			Button_Option_Mode = BUTTON_OP_Month;
		}
	break;
	case BUTTON_OP_Day:
		if(t_button_char == BUTTON_MODE){
			Button_Option_LastMode = Button_Option_Mode;
			Button_Option_Mode = BUTTON_OP_IDEL;
		}else if(t_button_char == BUTTON_UP){
			BO_Day = (BO_Day%7)+1;
			DS_Write_RTC(Year ,Month ,Date ,Day ,Hour ,Min ,Sec ,AM);
		}else if(t_button_char == BUTTON_DOWN){
			if(BO_Day <= 1){
				BO_Day = 7;
			}else {
				BO_Day--;
			}
			DS_Write_RTC(Year ,Month ,Date ,Day ,Hour ,Min ,Sec ,AM);
		}else if(t_button_char == BUTTON_NEXT){
			Button_Option_LastMode = Button_Option_Mode;
			Button_Option_Mode = BUTTON_OP_Date;
		}
	break;
	case BUTTON_OP_Hour:
		if(t_button_char == BUTTON_MODE){
			Button_Option_LastMode = Button_Option_Mode;
			Button_Option_Mode = BUTTON_OP_IDEL;
		}else if(t_button_char == BUTTON_UP){
			BO_Hour = (BO_Hour%12)+1;
			DS_Write_RTC(Year ,Month ,Date ,Day ,Hour ,Min ,Sec ,AM);
		}else if(t_button_char == BUTTON_DOWN){
			if(BO_Hour <= 1){
				BO_Hour = 12;
			}else {
				BO_Hour--;
			}
			DS_Write_RTC(Year ,Month ,Date ,Day ,Hour ,Min ,Sec ,AM);
		}else if(t_button_char == BUTTON_NEXT){
			Button_Option_LastMode = Button_Option_Mode;
			Button_Option_Mode = BUTTON_OP_Min;
		}
	break;
	case BUTTON_OP_Min:
		if(t_button_char == BUTTON_MODE){
			Button_Option_LastMode = Button_Option_Mode;
			Button_Option_Mode = BUTTON_OP_IDEL;
		}else if(t_button_char == BUTTON_UP){
			BO_Min = (BO_Min+1)%60;
			DS_Write_RTC(Year ,Month ,Date ,Day ,Hour ,Min ,Sec ,AM);
		}else if(t_button_char == BUTTON_DOWN){
			if(BO_Min <= 0){
				BO_Min = 59;
			}else {
				BO_Min--;
			}
			DS_Write_RTC(Year ,Month ,Date ,Day ,Hour ,Min ,Sec ,AM);
		}else if(t_button_char == BUTTON_NEXT){
			Button_Option_LastMode = Button_Option_Mode;
			Button_Option_Mode = BUTTON_OP_Sec;
		}
	break;
	case BUTTON_OP_Sec:
		if(t_button_char == BUTTON_MODE){
			Button_Option_LastMode = Button_Option_Mode;
			Button_Option_Mode = BUTTON_OP_IDEL;
		}else if(t_button_char == BUTTON_UP){
			BO_Sec = (BO_Sec+1)%60;
			DS_Write_RTC(Year ,Month ,Date ,Day ,Hour ,Min ,Sec ,AM);
		}else if(t_button_char == BUTTON_DOWN){
			//if(BO_Sec <= 0){
			//	BO_Sec = 59;
			//}else {
			//	BO_Sec--;
			//}
			BO_Sec =0;
			DS_Write_RTC(Year ,Month ,Date ,Day ,Hour ,Min ,Sec ,AM);
		}else if(t_button_char == BUTTON_NEXT){
			Button_Option_LastMode = Button_Option_Mode;
			Button_Option_Mode = BUTTON_OP_AM;
		}
	break;
	case BUTTON_OP_AM:
		if(t_button_char == BUTTON_MODE){
			Button_Option_LastMode = Button_Option_Mode;
			Button_Option_Mode = BUTTON_OP_IDEL;
		}else if(t_button_char == BUTTON_UP){
			BO_AM = !BO_AM;
			DS_Write_RTC(Year ,Month ,Date ,Day ,Hour ,Min ,Sec ,AM);
		}else if(t_button_char == BUTTON_DOWN){
			BO_AM = !BO_AM;
			DS_Write_RTC(Year ,Month ,Date ,Day ,Hour ,Min ,Sec ,AM);
		}else if(t_button_char == BUTTON_NEXT){
			Button_Option_LastMode = Button_Option_Mode;
			Button_Option_Mode = BUTTON_OP_Day;
		}
	break;
	case BUTTON_OP_IDEL:
		if(t_button_char == BUTTON_MODE){
			if(Button_Option_LastMode == BUTTON_OP_IDEL){
				Button_Option_LastMode = BUTTON_OP_Day;
				Button_Option_Mode = Button_Option_LastMode;
			}
			Button_Option_Mode = Button_Option_LastMode;
		}
		#ifdef CLEAR_SEC_BUTTON_EN
		else if (t_button_char == BUTTON_NEXT){
			BO_Sec =0;
			DS_Write_RTC(Year ,Month ,Date ,Day ,Hour ,Min ,Sec ,AM);
		}
		#endif
	break;
	case BUTTON_OP_INIT:
	default:
		Button_Option_Mode = BUTTON_OP_IDEL;
		Button_Option_LastMode = BUTTON_OP_Day;
	break;
	}
}
BUTTON_OPTION_MODE_DEF Button_getSta(void){
	return Button_Option_Mode;
}
