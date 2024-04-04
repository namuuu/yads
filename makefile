.PHONY: all modules pi monitor clean

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -D_XOPEN_SOURCE=500

PATH_CC=/home/kali/Documents/ObjetConnecté/tools-master/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin
CCC=$(PATH_CC)/arm-linux-gnueabihf-gcc

TARGET_PI=/home/kali/Documents/ObjetConnecté/target-pi
TARGET_WPI=/home/kali/Documents/ObjetConnecté/target_wpi

INC = -I. -I$(TARGET_PI)/include/ncurses -I$(TARGET_PI)/incude -I$(TARGET_WPI)/include
LIB = -L$(TARGET_PI)/lib -L $(TARGET_WPI)/lib
LIBS = -lncurses -lwiringPi -lpthread -lrt

all: modules pi 

modules:
	@echo "Building modules..."
	@cd modules && make --always-make

libs:
	@echo "Building libs..."
	@cd libs && make --always-make

pi: yads.c
	@echo "Building for PI..."
	@$(CCC) $(CFLAGS) $(INC) $(LIB) $(LIBS) -o pi_yads yads.c modules/TIM.o modules/LET.o libs/menuLibPI.o libs/buttons.o libs/session.o libs/data.o 

monitor: monitor.c
	@echo "Building Monitor..."
	@$(CCC) $(CFLAGS) $(INC) $(LIB) $(LIBS) -o monitor monitor.c libs/menuLibPI.o libs/buttons.o libs/session.o libs/data.o

pc: yads.c
	@echo "Building for PC..."
	@$(CC) $(CFLAGS) $(INC) $(LIB) $(LIBS) -o pc_yads yads.c modules/TIM.o modules/LET.o libs/menuLibPC.o $(LIBS) 

clean:
	rm -f pc_yads pi_yads
	@cd modules && make clean

send :
	sshpass -p pi scp pi_yads pi@192.168.12.114:/home/pi/Desktop
	sshpass -p pi scp monitor pi@192.168.12.114:/home/pi/Desktop
