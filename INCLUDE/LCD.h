#ifndef _LCD_H
#define _LCD_H
 /*LCD data command define*/
#define      LCD_CLEAR		0x01      //Xoa man hinh LCD
#define      LCD_HOME		0x02      //Tro ve dau dong
#define      LCD_NORMAL		0x06      //Che do nhap du lieu binh thuong
#define      LCD_NORMAL_S	0x07      //Che do nhap du lieu binh thuong, dich man hinh
#define      LCD_OFF		0x08      //Tat man hinh
#define      LCD_ON			0x0C      //Bat man hinh
#define      LCD_ON_CRSR	0x0E      //Bat man hinh va con tro
#define      LCD_ON_BLINK	0x0F      //Bat man hinh va con tro (nhap nhay)
#define      LCD_4B2L		0x28      //Che do 2 dong, giao tiep 4 bit du lieu
#define      LCD_HOMEL1		0x80      //Ve dau dong 1
#define      LCD_HOMEL2		0xC0      //Ve dau dong 2


#define      ShortDelay()   {Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop();}

void LCD_Delayms(unsigned int ms);
void LCD_Export (unsigned char Data);
void LCD_LED_CMD(unsigned char CMD);
void LCD_CMD(unsigned char CMD);
void LCD_DAT(unsigned char DATA);
void LCD_Init(void);
void LCD_PutChar(unsigned char character);
void LCD_PutString(const char *str);
void LCD_Gotoxy(char x, char y);// start from (1,1) 
void LCD_Clear(void);
void LCD_PutNum(int var);

#endif
