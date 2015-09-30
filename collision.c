#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "collision.h"
#include "soundwavefunction.h"
#include <stdbool.h>
/**
 * Absorption der Frequenzen um einen Koeffizienten

 * @param temp Item das reduziert wird
 * @param x
 * @param y
 * @param z
 * @param coeff Reduzierungsfaktor
 */
void absorption(item_node *temp, float coeff) {
	// der Absoprtionsfaktor ist für Hindernisse und wird auf alle dB Zahlen angewandt.
	setFreq20b40(temp, getFreq20b40(temp) * coeff);
	setFreq40b100(temp, getFreq40b100(temp) * coeff);
	setFreq100b150(temp, getFreq100b150(temp) * coeff);
	setFreq150b400(temp, getFreq150b400(temp) * coeff);
	setFreq400b1000(temp, getFreq400b1000(temp) * coeff);
	setFreq1000b2000(temp, getFreq1000b2000(temp) * coeff);
	setFreq2000b3500(temp, getFreq2000b3500(temp) * coeff);
	setFreq3500b6000(temp, getFreq3500b6000(temp) * coeff);
	setFreq6000b10000(temp, getFreq6000b10000(temp) * coeff);
	setFreq10000b20000(temp, getFreq10000b20000(temp) * coeff);
}
/**
 * Allgemeine Interferenzen
 * @param x
 * @param y
 * @param z
 */
void interference(int x, int y, int z) {
	item_node *temp;
	item_node *hold;
	temp = getItem_Root(x, y, z);
	int count = 0;
	int max20b40, max40b100, max100b150, max150b400, max400b1000,
	    max1000b2000, max2000b3500, max3500b6000, max6000b10000, max10000b20000 = 0;
	while (temp != NULL) {
		if (getItemID(temp) == 0 && getDirectionID(temp) != 0) {
			if (max20b40 < getFreq20b40(temp) && getFreq20b40 > 0) {
				max20b40 = getFreq20b40(temp);
			}else max20b40 = 0;
			if (max40b100 < getFreq40b100(temp) && getFreq40b100 > 0) {
				max40b100 = getFreq40b100(temp);
				hold = temp;
			}else max40b100 = 0;
			if (max100b150 < getFreq100b150(temp) && getFreq100b150 > 0) {
				max100b150 = getFreq100b150(temp);
			}else max150b400 = 0;
			if (max150b400 < getFreq150b400(temp) && getFreq150b400 > 0) {
				max150b400 = getFreq150b400(temp);
			}else max150b400 = 0;
			if (max400b1000 < getFreq400b1000(temp) && getFreq400b1000 > 0) {
				max400b1000 = getFreq400b1000(temp);
			}else max400b1000 = 0;
			if (max1000b2000 < getFreq1000b2000(temp) && getFreq1000b2000 > 0) {
				max1000b2000 = getFreq1000b2000(temp);
			}else max1000b2000 = 0;
			if (max2000b3500 < getFreq2000b3500(temp) && getFreq2000b3500 > 0) {
				max2000b3500 = getFreq2000b3500(temp);
			} else max2000b3500 = 0;
			if (max3500b6000 < getFreq3500b6000(temp) && getFreq3500b6000 > 0) {
				max3500b6000 = getFreq3500b6000(temp);
			} else max3500b6000 = 0;
			if (max6000b10000 < getFreq6000b10000(temp) && getFreq6000b10000 > 0) {
				max6000b10000 = getFreq6000b10000(temp);
			}else max6000b10000 = 0;
			if (max10000b20000 < getFreq10000b20000(temp) && getFreq10000b20000 > 0) {
				max10000b20000 = getFreq10000b20000(temp);
			}else max10000b20000 = 0;
			count++;
		}
		temp = temp->next;
	}
	temp = getItem_Root(x, y, z);
	while (temp != NULL) {
		if (getItemID(temp) == 0) {
			//removeItem(temp);
		}
		temp = temp->next;
	}

	item_node *tempNEW;
	tempNEW = createItem(x, y, z, 0);
	setWaveRoot(tempNEW,hold);
	setDirectionID(tempNEW,getDirectionID(getWaveRoot(tempNEW)));
	setSideOfWave(tempNEW,getSideOfWave(getWaveRoot(tempNEW)));
	if (count > 1) {
		if (getItemID(tempNEW) == 0 && getDirectionID(temp) != 0) {
			switch (count) {
			case 2: setFreq20b40(tempNEW, max20b40 + 3);
				setFreq40b100(tempNEW, max40b100 + 3);
				setFreq100b150(tempNEW, max100b150 + 3);
				setFreq150b400(tempNEW, max150b400 + 3);
				setFreq400b1000(tempNEW, max400b1000 + 3);
				setFreq1000b2000(tempNEW, max1000b2000 + 3);
				setFreq2000b3500(tempNEW, max2000b3500 + 3);
				setFreq3500b6000(tempNEW, max3500b6000 + 3);
				setFreq6000b10000(tempNEW, max6000b10000 + 3);
				setFreq10000b20000(tempNEW, max10000b20000 + 3); break;
			case 3:	setFreq20b40(tempNEW, max20b40 + 5);
				setFreq40b100(tempNEW, max40b100 + 5);
				setFreq100b150(tempNEW, max100b150 + 5);
				setFreq150b400(tempNEW, max150b400 + 5);
				setFreq400b1000(tempNEW, max400b1000 + 5);
				setFreq1000b2000(tempNEW, max1000b2000 + 5);
				setFreq2000b3500(tempNEW, max2000b3500 + 5);
				setFreq3500b6000(tempNEW, max3500b6000 + 5);
				setFreq6000b10000(tempNEW, max6000b10000 + 5);
				setFreq10000b20000(tempNEW, max10000b20000 + 5); break;
			case 4:	setFreq20b40(tempNEW, max20b40 + 6);
				setFreq40b100(tempNEW, max40b100 + 6);
				setFreq100b150(tempNEW, max100b150 + 6);
				setFreq150b400(tempNEW, max150b400 + 6);
				setFreq400b1000(tempNEW, max400b1000 + 6);
				setFreq1000b2000(tempNEW, max1000b2000 + 6);
				setFreq2000b3500(tempNEW, max2000b3500 + 6);
				setFreq3500b6000(tempNEW, max3500b6000 + 6);
				setFreq6000b10000(tempNEW, max6000b10000 + 6);
				setFreq10000b20000(tempNEW, max10000b20000 + 6); break;
			case 5:	setFreq20b40(tempNEW, max20b40 + 7);
				setFreq40b100(tempNEW, max40b100 + 7);
				setFreq100b150(tempNEW, max100b150 + 7);
				setFreq150b400(tempNEW, max150b400 + 7);
				setFreq400b1000(tempNEW, max400b1000 + 7);
				setFreq1000b2000(tempNEW, max1000b2000 + 7);
				setFreq2000b3500(tempNEW, max2000b3500 + 7);
				setFreq3500b6000(tempNEW, max3500b6000 + 7);
				setFreq6000b10000(tempNEW, max6000b10000 + 7);
				setFreq10000b20000(tempNEW, max10000b20000 + 7); break;
			case 6:	setFreq20b40(tempNEW, max20b40 + 8);
				setFreq40b100(tempNEW, max40b100 + 8);
				setFreq100b150(tempNEW, max100b150 + 8);
				setFreq150b400(tempNEW, max150b400 + 8);
				setFreq400b1000(tempNEW, max400b1000 + 8);
				setFreq1000b2000(tempNEW, max1000b2000 + 8);
				setFreq2000b3500(tempNEW, max2000b3500 + 8);
				setFreq3500b6000(tempNEW, max3500b6000 + 8);
				setFreq6000b10000(tempNEW, max6000b10000 + 8);
				setFreq10000b20000(tempNEW, max10000b20000 + 8); break;
			default: setFreq20b40(tempNEW, max20b40 + 2);
				setFreq40b100(tempNEW, max40b100 + 2);
				setFreq100b150(tempNEW, max100b150 + 2);
				setFreq150b400(tempNEW, max150b400 + 2);
				setFreq400b1000(tempNEW, max400b1000 + 2);
				setFreq1000b2000(tempNEW, max1000b2000 + 2);
				setFreq2000b3500(tempNEW, max2000b3500 + 2);
				setFreq3500b6000(tempNEW, max3500b6000 + 2);
				setFreq6000b10000(tempNEW, max6000b10000 + 2);
				setFreq10000b20000(tempNEW, max10000b20000 + 2); break;
			}
		}
	}
}
/**
 * Ungültige SoundItems werden entfernt
 * @param temp
 * @param x
 * @param y
 * @param z
 * @return Gültigkeit des Wertes
 */
bool checkSoundValid(item_node * temp, int x, int y, int z) {
	//TODO: x,y,z unnötig oder?
	bool status = false;

	if (getItemID(temp) == 0)
	{	// Die Summe aller Freq kleiner oder gleich 0
		int sum = getFreq20b40(temp) + getFreq40b100(temp) + getFreq100b150(temp) + getFreq150b400(temp) + getFreq400b1000(temp) + getFreq1000b2000(temp) + getFreq2000b3500(temp) + getFreq3500b6000(temp) + getFreq6000b10000(temp) + getFreq10000b20000(temp);
		if (sum <= 0 )
		{
			removeItem(temp);
			return status;
		} else if (getDirectionID(temp) == -1)
		{	// Err 9 Richtung.
			removeItem(temp);
			return status;
		} else if (sum > 1350 )
		{	// Summe unrealistisch hoch.
			removeItem(temp);
			return status;
		} else {
			status = true;
		}
	}
	return status;
}
