#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "soundwavefunction.h"
/**
 * Erzeugt eine Wand komplett um den Raum
 */
void createWall() {
	for (int i = 0; i < x_format; i++) {
		for (int j = 0; j < y_format; j++) {
			for (int k = 0; k < z_format; k++) {
				item_node *wallA = createItem(x_format - 1, j, k, 1); 	//rechte Wand
				//item_node *wallB = createItem(i, j, 1, 1);				// vordere Wand
				item_node *wallC = createItem(i, 1, k, 1);				//Boden
				item_node *wallD = createItem(i, j, z_format - 1, 1);	//hintere Wand
				item_node * wallE = createItem(1, j, k, 1);				// linke Wand
				//item_node * wallF = createItem(j, y_format - 1, k, 1);	// Decke
				//printf("test\n");
			}
		}
	}
}

void door() {
	for (int i =0; i < x_format; i++) {
		for (int j = 0; j < y_format; j++) {
			for (int k = 0; k < z_format; k++) {
				item_node *doorA = createItem(15, j, k, 1); // x = 10 eig.
			}
		}
	}
	}/*
	for (int i = 0; i < x_format; i++) {
		for (int j = y_format / 3; j < y_format / 2; j++) {
			for (int k = z_format * 0.7; k < z_format; k++) {
				item_node *doorB = createItem(10, j, k, 1);
			}
		}
	}
	for (int i = 0; i < x_format; i++) {
		for (int j = y_format / 2; j < y_format; j++) {
			for (int k = 0; k < z_format; k++) {
				item_node *doorC = createItem(10, j, k, 1);
			}
		}
	}
}*/

void box() {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			for (int k = 0; k < 20; k++ ) {
				item_node *boxpart = createItem(i, j, k, 1);
			}
		}
	}
}
/**
 * Funktion eines Lautsprechers wird simuliert
 */
void loudspeaker() {
	for (int i = 0; i <= 1; i++) {
		

		item_node *soundA = createItem(20, i, 100, 0);
		/*item_node *soundB = createItem(11, i, 20, 0);
		item_node *soundC = createItem(12, i, 20, 0);
		item_node *soundD = createItem(13, i, 20, 0);
		item_node *soundE = createItem(14, i, 20, 0);
		item_node *soundF = createItem(15, i, 20, 0);
		item_node *soundG = createItem(16, i, 20, 0);
		item_node *soundH = createItem(17, i, 20, 0);
		item_node *soundI = createItem(18, i, 20, 0);
		item_node *soundJ = createItem(19, i, 20, 0);
		item_node *soundK = createItem(10, i, 20, 0);
		item_node *soundL = createItem(11, i, 20, 0);
		item_node *soundT = createItem(10, 30, 30, 0);*/
		//item_node *soundWAND = createItem(21, 199, 20, 1);

		setDirectionID(soundA, 3);
		/*setDirectionID(soundB, 3);
		setDirectionID(soundC, 3);
		setDirectionID(soundD, 3);
		setDirectionID(soundE, 3);
		setDirectionID(soundF, 3);
		setDirectionID(soundG, 3);
		setDirectionID(soundH, 3);
		setDirectionID(soundI, 3);
		setDirectionID(soundJ, 3);
		setDirectionID(soundK, 3);
		setDirectionID(soundL, 3);
		setDirectionID(soundT, 3);*/

		setFreq20b40(soundA, 70);
		setFreq40b100(soundA, 70);
		setFreq100b150(soundA, 70);
		setFreq150b400(soundA, 70);
		setFreq400b1000(soundA, 70);
		setFreq1000b2000(soundA, 70);
		setFreq2000b3500(soundA, 70);
		setFreq3500b6000(soundA, 70);
		setFreq6000b10000(soundA, 70);
		setFreq10000b20000(soundA, 70);
		/*setFreq20b40(soundB, 70);
		setFreq40b100(soundB, 70);
		setFreq100b150(soundB, 70);
		setFreq150b400(soundB, 70);
		setFreq400b1000(soundB, 70);
		setFreq1000b2000(soundB, 70);
		setFreq2000b3500(soundB, 70);
		setFreq3500b6000(soundB, 70);
		setFreq6000b10000(soundB, 70);
		setFreq10000b20000(soundB, 70);
		setFreq20b40(soundC, 70);
		setFreq40b100(soundC, 70);
		setFreq100b150(soundC, 70);
		setFreq150b400(soundC, 70);
		setFreq400b1000(soundC, 70);
		setFreq1000b2000(soundC, 70);
		setFreq2000b3500(soundC, 70);
		setFreq3500b6000(soundC, 70);
		setFreq6000b10000(soundC, 70);
		setFreq10000b20000(soundC, 70);
		setFreq20b40(soundD, 70);
		setFreq40b100(soundD, 70);
		setFreq100b150(soundD, 70);
		setFreq150b400(soundD, 70);
		setFreq400b1000(soundD, 70);
		setFreq1000b2000(soundD, 70);
		setFreq2000b3500(soundD, 70);
		setFreq3500b6000(soundD, 70);
		setFreq6000b10000(soundD, 70);
		setFreq10000b20000(soundD, 70);
		setFreq20b40(soundE, 70);
		setFreq40b100(soundE, 70);
		setFreq100b150(soundE, 70);
		setFreq150b400(soundE, 70);
		setFreq400b1000(soundE, 70);
		setFreq1000b2000(soundE, 70);
		setFreq2000b3500(soundE, 70);
		setFreq3500b6000(soundE, 70);
		setFreq6000b10000(soundE, 70);
		setFreq10000b20000(soundE, 70);
		setFreq20b40(soundF, 70);
		setFreq40b100(soundF, 70);
		setFreq100b150(soundF, 70);
		setFreq150b400(soundF, 70);
		setFreq400b1000(soundF, 70);
		setFreq1000b2000(soundF, 70);
		setFreq2000b3500(soundF, 70);
		setFreq3500b6000(soundF, 70);
		setFreq6000b10000(soundF, 70);
		setFreq10000b20000(soundF, 70);
		setFreq20b40(soundG, 70);
		setFreq40b100(soundG, 70);
		setFreq100b150(soundG, 70);
		setFreq150b400(soundG, 70);
		setFreq400b1000(soundG, 70);
		setFreq1000b2000(soundG, 70);
		setFreq2000b3500(soundG, 70);
		setFreq3500b6000(soundG, 70);
		setFreq6000b10000(soundG, 70);
		setFreq10000b20000(soundG, 70);
		setFreq20b40(soundH, 70);
		setFreq40b100(soundH, 70);
		setFreq100b150(soundH, 70);
		setFreq150b400(soundH, 70);
		setFreq400b1000(soundH, 70);
		setFreq1000b2000(soundH, 70);
		setFreq2000b3500(soundH, 70);
		setFreq3500b6000(soundH, 70);
		setFreq6000b10000(soundH, 70);
		setFreq10000b20000(soundH, 70);
		setFreq20b40(soundI, 70);
		setFreq40b100(soundI, 70);
		setFreq100b150(soundI, 70);
		setFreq150b400(soundI, 70);
		setFreq400b1000(soundI, 70);
		setFreq1000b2000(soundI, 70);
		setFreq2000b3500(soundI, 70);
		setFreq3500b6000(soundI, 70);
		setFreq6000b10000(soundI, 70);
		setFreq10000b20000(soundI, 70);
		setFreq20b40(soundJ, 70);
		setFreq40b100(soundJ, 70);
		setFreq100b150(soundJ, 70);
		setFreq150b400(soundJ, 70);
		setFreq400b1000(soundJ, 70);
		setFreq1000b2000(soundJ, 70);
		setFreq2000b3500(soundJ, 70);
		setFreq3500b6000(soundJ, 70);
		setFreq6000b10000(soundJ, 70);
		setFreq10000b20000(soundJ, 70);
		setFreq20b40(soundK, 70);
		setFreq40b100(soundK, 70);
		setFreq100b150(soundK, 70);
		setFreq150b400(soundK, 70);
		setFreq400b1000(soundK, 70);
		setFreq1000b2000(soundK, 70);
		setFreq2000b3500(soundK, 70);
		setFreq3500b6000(soundK, 70);
		setFreq6000b10000(soundK, 70);
		setFreq10000b20000(soundK, 70);
		setFreq20b40(soundL, 70);
		setFreq40b100(soundL, 70);
		setFreq100b150(soundL, 70);
		setFreq150b400(soundL, 70);
		setFreq400b1000(soundL, 70);
		setFreq1000b2000(soundL, 70);
		setFreq2000b3500(soundL, 70);
		setFreq3500b6000(soundL, 70);
		setFreq6000b10000(soundL, 70);
		setFreq10000b20000(soundL, 70);

		setFreq20b40(soundT, 70);
		setFreq40b100(soundT, 35);
		setFreq100b150(soundT, 70);
		setFreq150b400(soundT, 100);
		setFreq400b1000(soundT, 70);
		setFreq1000b2000(soundT, 70);
		setFreq2000b3500(soundT, 20);
		setFreq3500b6000(soundT, 120);
		setFreq6000b10000(soundT, 70);
		setFreq10000b20000(soundT, 70);*/

		setSideOfWave(soundA, 0);
		/*setSideOfWave(soundB, 0);
		setSideOfWave(soundC, 0);
		setSideOfWave(soundD, 0);
		setSideOfWave(soundE, 0);
		setSideOfWave(soundF, 0);
		setSideOfWave(soundG, 0);
		setSideOfWave(soundH, 0);
		setSideOfWave(soundI, 0);
		setSideOfWave(soundJ, 0);
		setSideOfWave(soundK, 0);
		setSideOfWave(soundL, 0);
		setSideOfWave(soundT, 0);*/
	}
}
