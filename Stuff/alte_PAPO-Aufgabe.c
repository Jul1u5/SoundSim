#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
int main(int argumentCount, char ** argumente){
	int rank, size;
	int tag = 1;
	MPI_Status Stat;
	MPI_Init(&argumentCount, &argumente);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	if(rank==0){
		//master, Verteilung und Verarbeitung am Ende
		//für jeden Slave Process wird festgehalten wie viele Zahlen er am Ende zugewiesen bekommt
		int * paraarray = malloc(size*sizeof(int));
		//array nullen
		for(int j = 0; j<size; j++){
			paraarray[j] = 0;
		}
		//um die Zahlen gleichmäßig zu verteilen werden alle Summanden durchlaufen und nacheinander auf die Prozesse 1 bis size-1 aufgeteilt
		int new_process_rank = 1;
		for(int i = 1;i<argumentCount;i++)
		{
			//die eigene Summanende anzahl wird erhöht
			paraarray[new_process_rank]=paraarray[new_process_rank]+1;
			//wenn alle Ranks durchlaufen wurden wird wieder auf den 1. gesprungen (der 0. ist der Master und nur zum verteilen und einsammeln gedacht)
			if(new_process_rank+1>=size){
				new_process_rank = 1;
			}else
			{
				++new_process_rank;
			}
		}
		//Anzahl der Werte pro Prozess stehen fest
		//nun entsprechende Anzahl von Zahlen an jeweilige Processe senden
		int part = 1;
		for(int p = 1;p<size;p++)
		{
			//für jeden Slave wird ein array mit seinen Zahlen erstellt, deren Anzahl wurde eben ermittelt
			int message[paraarray[p]];
			for (int m = 0; m < paraarray[p]; ++m)
			{
				//die Eingabe wird mittels atoi() zu einer Zahl umgewandelt
				message[m] = atoi(argumente[part]);
				++part;
			}
			//1. Senden der Array Größe, da diese dem Empfänger bekannt sein muss
			MPI_Send(&paraarray[p], 1, MPI_INT, p, tag, MPI_COMM_WORLD);
			//2. Array schicken
			MPI_Send(message, paraarray[p], MPI_INT, p, tag, MPI_COMM_WORLD);
		}
		free(paraarray);
		//einsammeln
		int sum = 0;
		for(int i = 1;i<size; ++i)
		{
			int add = 0;
			MPI_Recv(&add, 1, MPI_INT, i, tag, MPI_COMM_WORLD, &Stat);
			sum = sum+add;
		}
		printf("%d\n", sum );
	}else{
		//alle anderen ranks
		int count;
		//siehe 1.
		MPI_Recv(&count, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &Stat);
		int inmsg [count];
		//siehe 2.
		MPI_Recv(&inmsg, count, MPI_INT, 0, tag, MPI_COMM_WORLD, &Stat);
		//jeder Process kann sich jetzt mit seinen eigenen Werten beschäftigen
		//jetzt addieren
		int sum = 0;
		for(int i = 0;i<count;++i)
		{
			sum = sum + inmsg[i];
		}
		//zurücksenden
		MPI_Send(&sum, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);

	}
	MPI_Finalize();
	return 0;
}