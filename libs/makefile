# Compile menuLib.c with a custom compiler
PATH_CC=/home/kali/Documents/ObjetConnecté/tools-master/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin
CCC=$(PATH_CC)/arm-linux-gnueabihf-gcc
all: menuLibPI.o

menuLibPI.o: menuLib.c
	@$(CCC) -c menuLib.c -o menuLibPI.o -lwiringPi -lpthread -lrt

clean:
	rm -f menuLibPI.o