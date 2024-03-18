all: moduleTestPC.o moduleTestPI.o

INC = -I. -I$(TARGET_PI)/include/ncurses -I$(TARGET_PI)/incude -I$(TARGET_WPI)/include
LIB = -L$(TARGET_PI)/lib -L$(TARGET_WPI)/lib

moduleTestPC.o:
	@gcc $(CFLAGS) $(LIBS) $(LIB) $(CFLAGS) -c moduleTest.c -o moduleTestPC.o

moduleTestPI.o:
	@$(CCC) $(CFLAGS) $(LIBS) $(LIB) $(CFLAGS) -c moduleTest.c -o moduleTestPI.o

clean :
	rm -f moduleTestPC.o moduleTestPI.o