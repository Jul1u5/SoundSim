all: soundsim
CC = gcc
OBJ = main.o soundwavefunction.o collision.o
OPTIONS = -std=c99 -Wformat -g
soundsim: $(OBJ)
	$(CC) $(OPTIONS) $(OBJ) -o soundsim

main.o: soundwavefunction.h collision.h

%.o: %.c
	$(CC) $(OPTIONS) -c $<

.PHONY: clean
clean:
	rm *.o soundsim
