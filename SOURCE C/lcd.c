#include<p30f4011.h>

#include "../INCLUDE/GenericTypeDefs.h"
#include "../INCLUDE/system.h"
#include "../INCLUDE/LCD.h"

BYTE_VAL LCD_Temp;

#define LCD_RS	LCD_Temp.bits.b7
#define	LCD_LED	LCD_Temp.bits.b0
#define LCD_D7	LCD_Temp.bits.b1
#define LCD_D6	LCD_Temp.bits.b2
#define	LCD_D5	LCD_Temp.bits.b3
#define	LCD_D4	LCD_Temp.bits.b4
#define LCD_RW	LCD_Temp.bits.b6

void LCD_Delayms(unsigned int ms)
{
	#define      FCY            120000
	unsigned int i=0;
	while(ms--)
	{
	while(++i<FCY/5);
	i=0;
	}
}

void LCD_Serial_Out(unsigned char lcd_data)
{
	char i;
	for (i = 7;i >=0 ;i-- ){
		SERIAL_DATA = 0x01&(lcd_data >> i);
		SERIAL_CLK = 1;
		Nop();
		Nop();
		SERIAL_CLK = 0;		
	}
	LCD_LAT = 1;
	Nop();
	Nop();
	LCD_LAT = 0;
}

void LCD_Export (unsigned char Data)
{
/*	LCD_D4 = (Data>>4)&0x01;
	LCD_D5 = (Data>>5)&0x01;
	LCD_D6 = (Data>>6)&0x01;
	LCD_D7 = (Data>>7)&0x01;
	LCD_EN = 1;   ShortDelay();   LCD_EN = 0;   //Xung Enable

	LCD_D4 = (Data>>0)&0x01;
	LCD_D5 = (Data>>1)&0x01;
	LCD_D6 = (Data>>2)&0x01;
	LCD_D7 = (Data>>3)&0x01;
	LCD_EN = 1;   ShortDelay();   LCD_EN = 0;   //Xung Enable
*/
	

	LCD_D7 = (Data >> 7) & 0x01;
	LCD_D6 = (Data >> 6) & 0x01;
	LCD_D5 = (Data >> 5) & 0x01;
	LCD_D4 = (Data >> 4) & 0x01;
	LCD_Serial_Out(LCD_Temp.Val);

	
	LCD_EN = 1;			/* LCD Enable Command*/
//	LCD_Serial_Out(LCD_Temp.Val);
	ShortDelay();	
	LCD_EN = 0;
//	LCD_Serial_Out(LCD_Temp.Val);

	LCD_D7 = (Data >> 3) & 0x01;
	LCD_D6 = (Data >> 2) & 0x01;
	LCD_D5 = (Data >> 1) & 0x01;
	LCD_D4 = (Data >> 0) & 0x01;
	LCD_Serial_Out(LCD_Temp.Val);


	LCD_EN = 1;	/* LCD Enable Command*/
//	LCD_Serial_Out(LCD_Temp.Val);
	ShortDelay();
	LCD_EN = 0;
//	LCD_Serial_Out(LCD_Temp.Val);
						
}

void LCD_LED_CMD(unsigned char CMD)
{
	if(CMD == 1)
		LCD_LED = 1;
	else
		LCD_LED = 0;
	LCD_Serial_Out(LCD_Temp.Val);
}

void LCD_CMD(unsigned char CMD)
{
	LCD_RS = 0; 
	//LCD_Serial_Out(LCD_Temp.Val);                       //Dat che do xuat lenh
	LCD_Export(CMD);
}

void LCD_DAT(unsigned char DATA)
{
	LCD_RS = 1;  
	//LCD_Serial_Out(LCD_Temp.Val);                      //Dat che do xuat du lieu
	LCD_Export(DATA);
}

void LCD_Init(void)
{
	LCD_EN = 0;
	LCD_Temp.Val = 0;
	LCD_Serial_Out(LCD_Temp.Val);
	LCD_Delayms(500);
	LCD_CMD(LCD_4B2L);         //Dat che do giao tiep 4-bit, man hinh 2 dong
	LCD_Delayms(50);
	LCD_CMD(LCD_4B2L);         //Dat che do giao tiep 4-bit, man hinh 2 dong
	LCD_Delayms(50);
	LCD_CMD(LCD_4B2L);         //Dat che do giao tiep 4-bit, man hinh 2 dong
	LCD_Delayms(50);
	LCD_CMD(LCD_OFF);         //Tat man hinh
	LCD_Delayms(50);
	LCD_CMD(LCD_CLEAR);         //Xoa man hinh
	LCD_Delayms(50);
	LCD_CMD(LCD_ON);         //Bat man hinh
	LCD_Delayms(50);
	LCD_CMD(LCD_NORMAL);      //Che do nhap lieu binh thuong
	                     //Cursor move Increment, Not to shift the display
	LCD_Delayms(50);
	LCD_CMD(LCD_CLEAR);         //Xoa man hinh
	LCD_Delayms(50);
}

void LCD_PutChar(unsigned char character)
{
   LCD_Delayms(1);
   LCD_DAT(character);
   LCD_Delayms(1);
}

void LCD_PutString(const char *str)
{
//   LCDdelayms(1);
   char ps;
   ps = *str;      
   while(ps>0)      
   {
      str++;         
      if (ps==0) break;
      LCD_Delayms(1);
      LCD_DAT(ps);      
       ps = *str;      
   }   
}

void LCD_Gotoxy(char x, char y)// start from (1,1) 
{
   char tg;
   LCD_Delayms(5);
    switch (y)
   {
      case 1:tg = 0x80+x-1;
         break;
      case 2:tg = 0xC0+x-1;
         break;
	  case 3:tg = 0x94+x-1;
		 break;	
	  case 4:tg = 0xD4+x-1;
		 break;
	  default:
		 break;
    }
   LCD_CMD(tg);
}

void LCD_Clear(void)
{
   LCD_CMD(LCD_CLEAR);
}


void LCD_PutNum(int var)
{
	unsigned char i,j=0;
	unsigned char ascii[10];
	
	i=0;
	if (var==0) 
		{
		LCD_PutChar(0x30);
		goto kt;
		}
	else if (var>0)
		{	
		while(var>0)
			{
				ascii[i++]=(unsigned char)(var%10 + 0x30);
				var=var/10;
			}
		}
	else if (var<0)
		{
		LCD_PutChar(0x2D);
		var=var*(-1);
		while(var>0)
			{
			ascii[i++]=(unsigned char)(var%10 + 0x30);
			var=var/10;
			}
		}		
	for(j=i;j>0;j--) 
		{
		LCD_PutChar(ascii[j-1]);
		}
	kt:
	Nop();
}


