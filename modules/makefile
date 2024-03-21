all: TIM.o
INC = -I. -I$(TARGET_PI)/include/ncurses -I$(TARGET_PI)/incude -I$(TARGET_WPI)/include
LIB = -L$(TARGET_PI)/lib -L$(TARGET_WPI)/lib

moduleTestPC.o: moduleTest.c
	@gcc -c moduleTest.c -o moduleTestPC.o -lncurses -lmenu

moduleTestPI.o:
	@$(CCC) -c moduleTest.c -o moduleTestPI.o -lwiringPi

TIM.o: TIM.c
	@$(CCC) -c TIM.c -o TIM.o -lwiringPi

LET.o: LET.c
	@$(CCC) -c LET.c -o LET.o -lwiringPi

clean :
	rm -f *.o