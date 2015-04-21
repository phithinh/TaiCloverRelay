#ifndef __DS1302_H
#define __DS1302_H
#include "../INCLUDE/GenericTypeDefs.h"

#define WR_SEC				0x80
#define WR_MIN				0x82
#define WR_HR				0x84
#define WR_DATE				0x86
#define WR_MONTH			0x88
#define WR_DAY				0x8a
#define WR_YEAR				0x8c
#define WR_CONTROL			0x8e
#define WR_CHARGER			0x90	
#define WR_CLOCKBURST		0xbe
#define WR_RAM0				0xc0
#define WR_RAM30			0xfc
#define WR_RAMBURST			0xfe

#define RD_SEC				0x81
#define RD_MIN				0x83
#define RD_HR				0x85
#define RD_DATE				0x87
#define RD_MONTH			0x89
#define RD_DAY				0x8B
#define RD_YEAR				0x8D
#define RD_CONTROL			0x91
#define RD_CHARGER			0x81
#define RD_CLOCKBURST		0xBF
#define RD_RAM0				0xC1
#define RD_RAM30			0xFD
#define RD_RAMBURST			0xFF

#define Am		0
#define Pm 		1



void DS1302_Init(void);
void WriteDS1302( BYTE ds_addr, BYTE ds_data );
BYTE ReadDS1302( BYTE ds_addr );
void DS1302_Read_RTC(void);
void DS_Write_RTC(BYTE YY, BYTE MM, BYTE DD, BYTE day,
					 BYTE hr, BYTE mm, BYTE sec, BYTE am);
void LCD_Show_RTC_task(void);
void LCD_Show_RTC_Option_task(void);

void Relay_Main(void);

void LCD_Show_RTC_Option_ResetDisplay(void);
#endif	// DS1302_H
