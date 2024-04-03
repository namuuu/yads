all: TIM.o LET.o
PATH_CC=/home/kali/Documents/ObjetConnecté/tools-master/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin
CCC=$(PATH_CC)/arm-linux-gnueabihf-gcc
CFLAGS = -Wall -Wextra -std=c99 -D_XOPEN_SOURCE=500

INC = -I. -I$(TARGET_PI)/include/ncurses -I$(TARGET_PI)/incude -I$(TARGET_WPI)/include
LIB = -L$(TARGET_PI)/lib -L$(TARGET_WPI)/lib

DEP = ../libs/buttons.o

moduleTestPC.o: moduleTest.c
	@gcc -c moduleTest.c -o moduleTestPC.o -lncurses -lmenu

moduleTestPI.o:
	@$(CCC) -c moduleTest.c -o moduleTestPI.o -lwiringPi

TIM.o: TIM.c
	@$(CCC) $(CFLAGS) -c TIM.c -o TIM.o -lwiringPi

LET.o: LET.c
	@$(CCC) $(CFLAGS) -c LET.c -o LET.o -lwiringPi

clean :
	rm -f *.o