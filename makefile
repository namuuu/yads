.PHONY: all modules pi pc clean

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -D_XOPEN_SOURCE=500

PATH_CC=/home/tomas/Documents/Ecole/LE3/Objet_Connecté/tools-master/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin
CCC=$(PATH_CC)/arm-linux-gnueabihf-gcc

INC = -I. -I $(TARGET_PI)/include/ncurses -I $(TARGET_PI)/incude -I $(TARGET_WPI)/include
LIB = -L$(TARGET_PI)/lib -L$(TARGET_WPI)/lib
LIBS = -lncurses -lmenu -lwiringPi -lpthread -lrt

all: modules pi pc 

modules:
	@echo "Building modules..."
	@cd modules && make --always-make

libs:
	@echo "Building libs..."
	@cd libs && make --always-make

pi: yads.c
	@echo "Building for PI..."
	@$(CCC) $(CFLAGS) $(INC) $(LIB) -o pi_yads yads.c libs/menuLibPI.o libs/session.o libs/data.o $(LIBS) 

pc: yads.c
	@echo "Building for PC..."
	@$(CC) $(CFLAGS) $(INC) $(LIB) -o pc_yads yads.c modules/moduleTestPC.o libs/menuLibPC.o $(LIBS) 

clean:
	rm -f pc_yads pi_yads
	@cd modules && make clean

send :
	sshpass -p pi scp pi_yads pi@192.168.95.114:/home/pi/Desktop
