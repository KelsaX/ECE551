CFLAGS=-std=gnu99 -pedantic -Wall
myPower: test-power.o power.o
	gcc -o myPower test-power.o power.o
test-power.o: test-power.c
	gcc $(CFLAGS) -c test-power.c
power.o: power.c
	gcc $(CFLAGS) -c power.c
