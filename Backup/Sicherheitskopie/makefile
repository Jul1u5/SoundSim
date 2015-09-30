all: soundsim
CC = gcc
OBJ = main.o soundwavefunction.o
OPTIONS = -std=c99
soundsim: $(OBJ)
	$(CC) $(OPTIONS) $(OBJ) -o soundsim

main.o: soundwavefunction.h

%.o: %.c
	$(CC) $(OPTIONS) -c $<

.PHONY: clean
clean:
	rm *.o soundsim