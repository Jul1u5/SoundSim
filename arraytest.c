/*

 * test1.c
 *
 *  Created on: 04.09.2015
 *      Author: juliusplehn
 */
#include <stdio.h>
#include <stdlib.h>
int index_array(int *arr, size_t rows, int x, int y)
{
    return arr[x * rows + y];
}

int main(int argc, char **argv) {

	size_t rows = 0;
	size_t cols = 4;
	int realcount = 0;
	int *sendarray = 0;
	if(realcount==rows){
		size_t newnum = (rows + 2) * 2;
		int *newptr = realloc(sendarray, newnum * cols * sizeof(*sendarray));
		rows = newnum;
		sendarray = newptr;
	}
	//int *arr = malloc(rows * cols * sizeof(*arr));
	//ausgewählte Zeile mal Anzahl der Zeilen + Spalte
	sendarray[realcount * rows + 1] = 5;
	++realcount;
	sendarray[realcount * rows + 10] = 30;
	++realcount;
	int arr_1_1 = index_array(sendarray, rows, 0, 1);
	int arr_4_1 = index_array(sendarray, rows, 1, 10);
	int arr2 = index_array(sendarray, rows, 1, 1);
	int arr3 = index_array(sendarray, rows, 100, 0);
	printf("1,1: %d\n",arr_1_1);
	printf("4,1: %d\n",arr_4_1);
	printf("arr2: %d\n",arr2);
	printf("arr3: %d\n",arr3);
}

