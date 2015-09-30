#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "main.h"
#include "soundwavefunction.h"
#include "collision.h"
#include "minunit.h"

int tests_run = 0;
int x_format = 100;
int y_format = 100;
int z_format = 100;
item_node ***room;
item_node ***room_new;
item_node *test1;
item_node *test2;
item_node *test3;


static char * testGetItemID() {
	mu_assert("error,getItemID(test1) != 0", getItemID(test1) == 0);
	mu_assert("error,getItemID(test2) != 2", getItemID(test2) == 2);
}


static char * all_tests() {
	mu_run_test(testGetItemID);
	
	return 0;
}

int main(int argc, char **argv) {

	createRoom(x_format,y_format);

	test1 = createItem(25, 25,25, 0);
	test2 = createItem(101,10,10,2);
	test3 = createItem(60,60,60,0);

	setFreq20b40(test1, 70);
	setFreq40b100(test1, 70);
	setFreq100b150(test1, 70);
	setFreq150b400(test1, 70);
	setFreq400b1000(test1, 70);
	setFreq1000b2000(test1, 70);
	setFreq2000b3500(test1, 70);
	setFreq3500b6000(test1, 70);
	setFreq6000b10000(test1, 70);
	setFreq10000b20000(test1, 70);

	setFreq20b40(test3, 70);
	setFreq40b100(test3, 70);
	setFreq100b150(test3, 70);
	setFreq150b400(test3, 70);
	setFreq400b1000(test3, 70);
	setFreq1000b2000(test3, 70);
	setFreq2000b3500(test3, 70);
	setFreq3500b6000(test3, 70);
	setFreq6000b10000(test3, 70);
	setFreq10000b20000(test3, 70);

	setDirectionID(test1, 4);
	setSideOfWave(test1, 0);
	setDirectionID(test3, 2);
	setSideOfWave(test3, 1);

	char *result = all_tests();
	if (result != 0) {
		printf("%s\n", result);
	}
	else {
		printf("ALL TESTS PASSED\n");
	}
	printf("Tests run: %d\n", tests_run);

	return result != 0;
}

