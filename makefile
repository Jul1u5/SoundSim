all: soundsim
vampir: soundsimvampir
MPICC?=mpicc
OBJ = main.o soundwavefunction.o collision.o extras.o
OPTIONS = -std=c99 -Wformat -g
soundsim: $(OBJ)
	$(MPICC) $(OPTIONS) $(OBJ) -o soundsim
soundsimvampir: $(OBJ)
	vtcc -vt:cc $(MPICC) $(OPTIONS) $(OBJ) -fopenmp -o soundsimvampir
main.o: soundwavefunction.h collision.h extras.h

%.o: %.c
	$(MPICC) $(OPTIONS) -c $<

.PHONY: clean
clean:
	rm *.o soundsim soundsimvampir
