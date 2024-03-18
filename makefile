.PHONY: all modules pi pc clean

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -D_XOPEN_SOURCE=500

TARGET_PI=/mnt/c/Users/Namu/Documents/IG2I/ObjetConnecté/target-pi
TARGET_WPI=/mnt/c/Users/Namu/Documents/IG2I/ObjetConnecté/target_wpi

INC = -I. -I $(TARGET_PI)/include/ncurses -I $(TARGET_PI)/incude -I $(TARGET_WPI)/include
LIB = -L$(TARGET_PI)/lib -L$(TARGET_WPI)/lib
LIBS = -lncurses -lmenu

all: modules pi pc 

modules:
	@echo "Building modules..."
	@cd modules && make --always-make

pi: yads.c
	@echo "Building for PI..."
	@$(CCC) $(CFLAGS) $(INC) $(LIBS) $(LIB) -o pi_yads yads.c modules/moduleTestPI.o

pc: yads.c
	@echo "Building for PC..."
	@$(CC) $(CFLAGS) $(INC) $(LIBS) $(LIB) -o pc_yads yads.c modules/moduleTestPC.o

clean:
	rm -f pc_yads pi_yads
	@cd modules && make clean
