# MPLAB IDE generated this makefile for use with GNU make.
# Project: RTC_8in_16out.mcp
# Date: Mon Oct 27 15:23:11 2014

AS = pic30-as.exe
CC = pic30-gcc.exe
LD = pic30-ld.exe
AR = pic30-ar.exe
HX = pic30-bin2hex.exe
RM = rm

RTC_8in_16out.hex : RTC_8in_16out.cof
	$(HX) "RTC_8in_16out.cof"

RTC_8in_16out.cof : main.o IO.o lcd.o Tick.o tips.o
	$(CC) -mcpu=30F4011 "main.o" "IO.o" "lcd.o" "Tick.o" "tips.o" -o"RTC_8in_16out.cof" -Wl,--script="..\..\..\..\..\Program Files\Microchip\mplabc30\v3.25\support\dsPIC30F\gld\p30F4011.gld",--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,--defsym=__ICD2RAM=1,-Map="RTC_8in_16out.map",--report-mem

main.o : INCLUDE/LCD.h INCLUDE/GenericTypeDefs.h ../../../../../program\ files/microchip/mplabc30/v3.25/support/dsPIC30F/h/p30f4011.h INCLUDE/system.h ../../../../../program\ files/microchip/mplabc30/v3.25/support/dsPIC30F/h/p30f4011.h SOURCE\ C/main.c
	$(CC) -mcpu=30F4011 -x c -c "SOURCE C\main.c" -o"main.o" -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -g -Wall

IO.o : INCLUDE/GenericTypeDefs.h ../../../../../program\ files/microchip/mplabc30/v3.25/support/dsPIC30F/h/p30f4011.h INCLUDE/system.h ../../../../../program\ files/microchip/mplabc30/v3.25/support/dsPIC30F/h/p30f4011.h SOURCE\ C/IO.c
	$(CC) -mcpu=30F4011 -x c -c "SOURCE C\IO.c" -o"IO.o" -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -g -Wall

lcd.o : INCLUDE/LCD.h INCLUDE/GenericTypeDefs.h ../../../../../program\ files/microchip/mplabc30/v3.25/support/dsPIC30F/h/p30f4011.h INCLUDE/system.h INCLUDE/GenericTypeDefs.h ../../../../../program\ files/microchip/mplabc30/v3.25/support/dsPIC30F/h/p30f4011.h SOURCE\ C/lcd.c
	$(CC) -mcpu=30F4011 -x c -c "SOURCE C\lcd.c" -o"lcd.o" -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -g -Wall

Tick.o : ../../../../../program\ files/microchip/mplabc30/v3.25/support/dsPIC30F/h/p30F4011.h ../../../../../program\ files/microchip/mplabc30/v3.25/support/dsPIC30F/h/p30fxxxx.h ../../../../../program\ files/microchip/mplabc30/v3.25/support/peripheral_30F_24H_33F/timer.h INCLUDE/GenericTypeDefs.h ../../../../../program\ files/microchip/mplabc30/v3.25/support/dsPIC30F/h/p30f4011.h INCLUDE/system.h ../../../../../program\ files/microchip/mplabc30/v3.25/support/dsPIC30F/h/p30f4011.h SOURCE\ C/Tick.c
	$(CC) -mcpu=30F4011 -x c -c "SOURCE C\Tick.c" -o"Tick.o" -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -g -Wall

tips.o : INCLUDE/GenericTypeDefs.h ../../../../../program\ files/microchip/mplabc30/v3.25/support/dsPIC30F/h/p30f4011.h INCLUDE/system.h ../../../../../program\ files/microchip/mplabc30/v3.25/support/dsPIC30F/h/p30f4011.h SOURCE\ C/tips.c
	$(CC) -mcpu=30F4011 -x c -c "SOURCE C\tips.c" -o"tips.o" -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -g -Wall

clean : 
	$(RM) "main.o" "IO.o" "lcd.o" "Tick.o" "tips.o" "RTC_8in_16out.cof" "RTC_8in_16out.hex"

