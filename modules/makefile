all: TIM.o
INC = -I. -I$(TARGET_PI)/include/ncurses -I$(TARGET_PI)/incude -I$(TARGET_WPI)/include
LIB = -L$(TARGET_PI)/lib -L$(TARGET_WPI)/lib

moduleTestPC.o: moduleTest.c
	@gcc -c moduleTest.c -o moduleTestPC.o -lncurses -lmenu

moduleTestPI.o:
	@$(CCC) $(INC) $(LIB) -c moduleTest.c -o moduleTestPI.o -lncurses

TIM.o: TIM.c
	@$(CCC) $(INC) $(LIB) -c TIM.c -o TIM.o -lncurses

clean :
	rm -f *.o