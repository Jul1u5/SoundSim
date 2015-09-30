#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "collision.h"
#include <stdbool.h>

void absorption(item_node *temp, int x, int y, float coeff) {
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

void interference(int x, int y) {
	item_node *temp;
	temp = getItem_Root(x, y);
	int count = 0;
	int average20b40, average40b100, average100b150, average150b400, average400b1000,
	    average1000b2000, average2000b3500, average3500b6000, average6000b10000, average10000b20000 = 0;

	while (temp != NULL) {

		// Hole dir für alle Sounds auf einem Feld die dB Werte und Summiere sie. Merke wie oft mit count.
		if (getItemID(temp) == 0 && getDirectionID(temp) != 0) {
			if ( (average20b40 += getFreq20b40(temp)) > 0) {
				average20b40 += getFreq20b40(temp);
			} else { average20b40 = 0; }
			if ( (average40b100 += getFreq40b100(temp)) > 0) {
				average40b100 += getFreq40b100(temp);
			} else { average40b100 = 0; }
			if ( (average100b150 += getFreq100b150(temp)) > 0) {
				average100b150 += getFreq100b150(temp);
			} else { average100b150 = 0; }
			if ( (average150b400 += getFreq150b400(temp)) > 0) {
				average150b400 += getFreq150b400(temp);
			} else { average150b400 = 0; }
			if ( (average400b1000 += getFreq400b1000(temp)) > 0) {
				average400b1000 += getFreq400b1000(temp);
			} else { average400b1000 = 0; }
			if ( (average1000b2000 += getFreq1000b2000(temp)) > 0) {
				average1000b2000 += getFreq1000b2000(temp);
			} else {average1000b2000 = 0; }
			if ( (average2000b3500 += getFreq2000b3500(temp)) > 0) {
				average2000b3500 += getFreq2000b3500(temp);
			} else {average2000b3500 = 0; }
			if ( (average3500b6000 += getFreq3500b6000(temp)) > 0) {
				average3500b6000 += getFreq3500b6000(temp);
			} else {average3500b6000 = 0; }
			if ( (average6000b10000 += getFreq6000b10000(temp)) > 0) {
				average6000b10000 += getFreq6000b10000(temp);
			} else {average6000b10000 = 0; }
			if ( (average10000b20000 += getFreq10000b20000(temp)) > 0) {
				average10000b20000 += getFreq10000b20000(temp);
			} else {average10000b20000 = 0; }
			count++;
		}
		temp = temp->next;
	}
	if (count > 1) {
		temp = getItem_Root(x, y);
		while (temp != NULL) {
			// Bild von der Summe mit hilfe der counts den Durchschnitt(arithmetic mean).
			if (getItemID(temp) == 0 && getDirectionID(temp) != 0) {
				if (average20b40 > count) {
					setFreq20b40(temp, average20b40 / count);
				} else setFreq20b40(temp, 0);
				if (average40b100 > count) {
					setFreq40b100(temp, average40b100 / count);
				} else setFreq40b100(temp, 0);
				if (average100b150 > count) {
					setFreq100b150(temp, average100b150 / count);
				} else setFreq100b150(temp, 0);
				if (average150b400 > count) {
					setFreq150b400(temp, average150b400 / count);
				} else setFreq150b400(temp, 0);
				if (average400b1000 > count) {
					setFreq400b1000(temp, average400b1000 / count);
				} else setFreq400b1000(temp, 0);
				if (average1000b2000 > count) {
					setFreq1000b2000(temp, average1000b2000 / count);
				} else setFreq1000b2000(temp, 0);
				if (average2000b3500 > count) {
					setFreq2000b3500(temp, average2000b3500 / count);
				} else setFreq2000b3500(temp, 0);
				if (average3500b6000 > count) {
					setFreq3500b6000(temp, average3500b6000 / count);
				} else setFreq3500b6000(temp, 0);
				if (average6000b10000 > count) {
					setFreq6000b10000(temp, average6000b10000 / count);
				} else setFreq6000b10000(temp, 0);
				if (average10000b20000 > count) {
					setFreq10000b20000(temp, average10000b20000 / count);
				} else setFreq10000b20000(temp, 0);
			}
			temp = temp->next;
		}
	}
}

void checkSoundValid(item_node * temp, int x, int y) {

	if (getItemID(temp) == 0)
	{	// Die Summe aller Freq kleiner oder gleich 0
		int sum = getFreq20b40(temp) + getFreq40b100(temp) + getFreq100b150(temp) + getFreq150b400(temp) + getFreq400b1000(temp) + getFreq1000b2000(temp) + getFreq2000b3500(temp) + getFreq3500b6000(temp) + getFreq6000b10000(temp) + getFreq10000b20000(temp);
		if (sum <= 0 )
		{
			removeItem(temp);
		}else if (getDirectionID(temp) == -1)
      { // Err 9 Richtung.
        removeItem(temp);
      } else if (sum > 1350 )
      {// Summe unrealistisch hoch.
        removeItem(temp);
      }

	}
}
