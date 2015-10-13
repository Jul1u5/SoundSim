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
	for (int i = 0; i < x_format; i++) {
		for (int j = 0; j < y_format; j++) {
			for (int k = 0; k < z_format; k++) {
				if ((j < (y_format / 2 - y_format / 10) || j > (y_format / 2 + y_format / 10)) || k > z_format / 1.4)
				{
					item_node *doorA = createItem(15, j, k, 1); // x = 10 eig.
				}
			}
		}
	}
}

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
		item_node *soundA = createItem(5, 85, 18, 0);
		item_node *soundB = createItem(5, 90, 16, 0);
		item_node *soundC = createItem(5, 100, 14, 0);
		item_node *soundD = createItem(5, 105, 12, 0);
		item_node *soundE = createItem(5, 110, 10, 0);
		item_node *soundF = createItem(5, 115, 8, 0);
		item_node *soundG = createItem(5, 120, 10, 0);
		item_node *soundH = createItem(5, 125, 12, 0);
		item_node *soundI = createItem(5, 130, 14, 0);
		item_node *soundJ = createItem(5, 135, 16, 0);
		item_node *soundK = createItem(5, 140, 18, 0);
		item_node *soundL = createItem(5, 80, 20, 0);
		item_node *soundM = createItem(5, 145, 20, 0);
		item_node *soundAA = createItem(5, 85, 24, 0);
		item_node *soundBB = createItem(5, 90, 26, 0);
		item_node *soundCC = createItem(5, 100, 28, 0);
		item_node *soundDD = createItem(5, 105, 30, 0);
		item_node *soundEE = createItem(5, 110, 32, 0);
		item_node *soundFF = createItem(5, 115, 34, 0);
		item_node *soundGG = createItem(5, 120, 32, 0);
		item_node *soundHH = createItem(5, 125, 30, 0);
		item_node *soundII = createItem(5, 130, 28, 0);
		item_node *soundJJ = createItem(5, 135, 26, 0);
		item_node *soundKK = createItem(5, 140, 24, 0);
		item_node *soundLL = createItem(5, 80, 22, 0);
		item_node *soundMM = createItem(5, 145, 22, 0);
		//item_node *soundWAND = createItem(21, 199, 20, 1);

		setDirectionID(soundA, 3);
		setDirectionID(soundB, 3);
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
		setDirectionID(soundM, 3);
		setDirectionID(soundAA, 3);
		setDirectionID(soundBB, 3);
		setDirectionID(soundCC, 3);
		setDirectionID(soundDD, 3);
		setDirectionID(soundEE, 3);
		setDirectionID(soundFF, 3);
		setDirectionID(soundGG, 3);
		setDirectionID(soundHH, 3);
		setDirectionID(soundII, 3);
		setDirectionID(soundJJ, 3);
		setDirectionID(soundKK, 3);
		setDirectionID(soundLL, 3);
		setDirectionID(soundMM, 3);

		setFreq20b40(soundA, 110);
		setFreq40b100(soundA, 110);
		setFreq100b150(soundA, 110);
		setFreq150b400(soundA, 110);
		setFreq400b1000(soundA, 110);
		setFreq1000b2000(soundA, 110);
		setFreq2000b3500(soundA, 110);
		setFreq3500b6000(soundA, 110);
		setFreq6000b10000(soundA, 110);
		setFreq10000b20000(soundA, 110);
		setFreq20b40(soundB, 110);
		setFreq40b100(soundB, 110);
		setFreq100b150(soundB, 110);
		setFreq150b400(soundB, 110);
		setFreq400b1000(soundB, 110);
		setFreq1000b2000(soundB, 110);
		setFreq2000b3500(soundB, 110);
		setFreq3500b6000(soundB, 110);
		setFreq6000b10000(soundB, 110);
		setFreq10000b20000(soundB, 110);
		setFreq20b40(soundC, 110);
		setFreq40b100(soundC, 110);
		setFreq100b150(soundC, 110);
		setFreq150b400(soundC, 110);
		setFreq400b1000(soundC, 110);
		setFreq1000b2000(soundC, 110);
		setFreq2000b3500(soundC, 110);
		setFreq3500b6000(soundC, 110);
		setFreq6000b10000(soundC, 110);
		setFreq10000b20000(soundC, 110);
		setFreq20b40(soundD, 110);
		setFreq40b100(soundD, 110);
		setFreq100b150(soundD, 110);
		setFreq150b400(soundD, 110);
		setFreq400b1000(soundD, 110);
		setFreq1000b2000(soundD, 110);
		setFreq2000b3500(soundD, 110);
		setFreq3500b6000(soundD, 110);
		setFreq6000b10000(soundD, 110);
		setFreq10000b20000(soundD, 110);
		setFreq20b40(soundE, 110);
		setFreq40b100(soundE, 110);
		setFreq100b150(soundE, 110);
		setFreq150b400(soundE, 110);
		setFreq400b1000(soundE, 110);
		setFreq1000b2000(soundE, 110);
		setFreq2000b3500(soundE, 110);
		setFreq3500b6000(soundE, 110);
		setFreq6000b10000(soundE, 110);
		setFreq10000b20000(soundE, 110);
		setFreq20b40(soundF, 110);
		setFreq40b100(soundF, 110);
		setFreq100b150(soundF, 110);
		setFreq150b400(soundF, 110);
		setFreq400b1000(soundF, 110);
		setFreq1000b2000(soundF, 110);
		setFreq2000b3500(soundF, 110);
		setFreq3500b6000(soundF, 110);
		setFreq6000b10000(soundF, 110);
		setFreq10000b20000(soundF, 110);
		setFreq20b40(soundG, 110);
		setFreq40b100(soundG, 110);
		setFreq100b150(soundG, 110);
		setFreq150b400(soundG, 108);
		setFreq400b1000(soundG, 110);
		setFreq1000b2000(soundG, 120);
		setFreq2000b3500(soundG, 110);
		setFreq3500b6000(soundG, 110);
		setFreq6000b10000(soundG, 110);
		setFreq10000b20000(soundG, 110);
		setFreq20b40(soundH, 110);
		setFreq40b100(soundH, 110);
		setFreq100b150(soundH, 110);
		setFreq150b400(soundH, 110);
		setFreq400b1000(soundH, 110);
		setFreq1000b2000(soundH, 110);
		setFreq2000b3500(soundH, 110);
		setFreq3500b6000(soundH, 110);
		setFreq6000b10000(soundH, 110);
		setFreq10000b20000(soundH, 110);
		setFreq20b40(soundI, 110);
		setFreq40b100(soundI, 110);
		setFreq100b150(soundI, 110);
		setFreq150b400(soundI, 110);
		setFreq400b1000(soundI, 110);
		setFreq1000b2000(soundI, 110);
		setFreq2000b3500(soundI, 110);
		setFreq3500b6000(soundI, 110);
		setFreq6000b10000(soundI, 110);
		setFreq10000b20000(soundI, 110);
		setFreq20b40(soundJ, 110);
		setFreq40b100(soundJ, 110);
		setFreq100b150(soundJ, 110);
		setFreq150b400(soundJ, 110);
		setFreq400b1000(soundJ, 110);
		setFreq1000b2000(soundJ, 110);
		setFreq2000b3500(soundJ, 110);
		setFreq3500b6000(soundJ, 110);
		setFreq6000b10000(soundJ, 110);
		setFreq10000b20000(soundJ, 110);
		setFreq20b40(soundK, 110);
		setFreq40b100(soundK, 110);
		setFreq100b150(soundK, 110);
		setFreq150b400(soundK, 110);
		setFreq400b1000(soundK, 110);
		setFreq1000b2000(soundK, 110);
		setFreq2000b3500(soundK, 110);
		setFreq3500b6000(soundK, 110);
		setFreq6000b10000(soundK, 110);
		setFreq10000b20000(soundK, 110);
		setFreq20b40(soundL, 110);
		setFreq40b100(soundL, 110);
		setFreq100b150(soundL, 110);
		setFreq150b400(soundL, 110);
		setFreq400b1000(soundL, 110);
		setFreq1000b2000(soundL, 110);
		setFreq2000b3500(soundL, 110);
		setFreq3500b6000(soundL, 110);
		setFreq6000b10000(soundL, 110);
		setFreq10000b20000(soundL, 110);
		setFreq20b40(soundM, 110);
		setFreq40b100(soundM, 35);
		setFreq100b150(soundM, 110);
		setFreq150b400(soundM, 100);
		setFreq400b1000(soundM, 110);
		setFreq1000b2000(soundM, 110);
		setFreq2000b3500(soundM, 20);
		setFreq3500b6000(soundM, 120);
		setFreq6000b10000(soundM, 110);
		setFreq10000b20000(soundM, 110);
		setFreq20b40(soundAA, 110);
		setFreq40b100(soundAA, 110);
		setFreq100b150(soundAA, 110);
		setFreq150b400(soundAA, 110);
		setFreq400b1000(soundAA, 110);
		setFreq1000b2000(soundAA, 110);
		setFreq2000b3500(soundAA, 110);
		setFreq3500b6000(soundAA, 110);
		setFreq6000b10000(soundAA, 110);
		setFreq10000b20000(soundAA, 110);
		setFreq20b40(soundBB, 110);
		setFreq40b100(soundBB, 110);
		setFreq100b150(soundBB, 110);
		setFreq150b400(soundBB, 110);
		setFreq400b1000(soundBB, 110);
		setFreq1000b2000(soundBB, 110);
		setFreq2000b3500(soundBB, 110);
		setFreq3500b6000(soundBB, 110);
		setFreq6000b10000(soundBB, 110);
		setFreq10000b20000(soundBB, 110);
		setFreq20b40(soundCC, 110);
		setFreq40b100(soundCC, 110);
		setFreq100b150(soundCC, 110);
		setFreq150b400(soundCC, 110);
		setFreq400b1000(soundCC, 110);
		setFreq1000b2000(soundCC, 110);
		setFreq2000b3500(soundCC, 110);
		setFreq3500b6000(soundCC, 110);
		setFreq6000b10000(soundCC, 110);
		setFreq10000b20000(soundCC, 110);
		setFreq20b40(soundDD, 110);
		setFreq40b100(soundDD, 110);
		setFreq100b150(soundDD, 110);
		setFreq150b400(soundDD, 110);
		setFreq400b1000(soundDD, 110);
		setFreq1000b2000(soundDD, 110);
		setFreq2000b3500(soundDD, 110);
		setFreq3500b6000(soundDD, 110);
		setFreq6000b10000(soundDD, 110);
		setFreq10000b20000(soundDD, 110);
		setFreq20b40(soundEE, 110);
		setFreq40b100(soundEE, 110);
		setFreq100b150(soundEE, 110);
		setFreq150b400(soundEE, 110);
		setFreq400b1000(soundEE, 110);
		setFreq1000b2000(soundEE, 110);
		setFreq2000b3500(soundEE, 110);
		setFreq3500b6000(soundEE, 110);
		setFreq6000b10000(soundEE, 110);
		setFreq10000b20000(soundEE, 110);
		setFreq20b40(soundFF, 110);
		setFreq40b100(soundFF, 110);
		setFreq100b150(soundFF, 110);
		setFreq150b400(soundFF, 110);
		setFreq400b1000(soundFF, 110);
		setFreq1000b2000(soundFF, 110);
		setFreq2000b3500(soundFF, 110);
		setFreq3500b6000(soundFF, 110);
		setFreq6000b10000(soundFF, 110);
		setFreq10000b20000(soundFF, 110);
		setFreq20b40(soundGG, 110);
		setFreq40b100(soundGG, 110);
		setFreq100b150(soundGG, 110);
		setFreq150b400(soundGG, 110);
		setFreq400b1000(soundGG, 110);
		setFreq1000b2000(soundGG, 110);
		setFreq2000b3500(soundGG, 110);
		setFreq3500b6000(soundGG, 110);
		setFreq6000b10000(soundGG, 110);
		setFreq10000b20000(soundGG, 110);
		setFreq20b40(soundHH, 110);
		setFreq40b100(soundHH, 110);
		setFreq100b150(soundHH, 110);
		setFreq150b400(soundHH, 110);
		setFreq400b1000(soundHH, 110);
		setFreq1000b2000(soundHH, 110);
		setFreq2000b3500(soundHH, 110);
		setFreq3500b6000(soundHH, 110);
		setFreq6000b10000(soundHH, 110);
		setFreq10000b20000(soundHH, 110);
		setFreq20b40(soundII, 110);
		setFreq40b100(soundII, 110);
		setFreq100b150(soundII, 110);
		setFreq150b400(soundII, 110);
		setFreq400b1000(soundII, 110);
		setFreq1000b2000(soundII, 110);
		setFreq2000b3500(soundII, 110);
		setFreq3500b6000(soundII, 110);
		setFreq6000b10000(soundII, 110);
		setFreq10000b20000(soundII, 110);
		setFreq20b40(soundJJ, 110);
		setFreq40b100(soundJJ, 110);
		setFreq100b150(soundJJ, 110);
		setFreq150b400(soundJJ, 110);
		setFreq400b1000(soundJJ, 110);
		setFreq1000b2000(soundJJ, 110);
		setFreq2000b3500(soundJJ, 110);
		setFreq3500b6000(soundJJ, 110);
		setFreq6000b10000(soundJJ, 110);
		setFreq10000b20000(soundJJ, 110);
		setFreq20b40(soundKK, 110);
		setFreq40b100(soundKK, 110);
		setFreq100b150(soundKK, 110);
		setFreq150b400(soundKK, 110);
		setFreq400b1000(soundKK, 110);
		setFreq1000b2000(soundKK, 110);
		setFreq2000b3500(soundKK, 110);
		setFreq3500b6000(soundKK, 110);
		setFreq6000b10000(soundKK, 110);
		setFreq10000b20000(soundKK, 110);
		setFreq20b40(soundLL, 110);
		setFreq40b100(soundLL, 110);
		setFreq100b150(soundLL, 110);
		setFreq150b400(soundLL, 110);
		setFreq400b1000(soundLL, 110);
		setFreq1000b2000(soundLL, 110);
		setFreq2000b3500(soundLL, 110);
		setFreq3500b6000(soundLL, 110);
		setFreq6000b10000(soundLL, 110);
		setFreq10000b20000(soundLL, 110);
		setFreq20b40(soundMM, 110);
		setFreq40b100(soundMM, 35);
		setFreq100b150(soundMM, 110);
		setFreq150b400(soundMM, 100);
		setFreq400b1000(soundMM, 110);
		setFreq1000b2000(soundMM, 110);
		setFreq2000b3500(soundMM, 20);
		setFreq3500b6000(soundMM, 120);
		setFreq6000b10000(soundMM, 110);
		setFreq10000b20000(soundMM, 110);

		setSideOfWave(soundA, 0);
		setSideOfWave(soundB, 0);
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
		setSideOfWave(soundM, 0);
		setSideOfWave(soundAA, 0);
		setSideOfWave(soundBB, 0);
		setSideOfWave(soundCC, 0);
		setSideOfWave(soundDD, 0);
		setSideOfWave(soundEE, 0);
		setSideOfWave(soundFF, 0);
		setSideOfWave(soundGG, 0);
		setSideOfWave(soundHH, 0);
		setSideOfWave(soundII, 0);
		setSideOfWave(soundJJ, 0);
		setSideOfWave(soundKK, 0);
		setSideOfWave(soundLL, 0);
		setSideOfWave(soundMM, 0);
	}
}
