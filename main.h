#ifndef MAIN_H
#define MAIN_H
#include <stdbool.h>
extern int x_format;
extern int y_format;
extern int z_format;
/**
 * Alle Elemente werden in Form dieses Structs repräsentiert
 */
typedef struct item_node{
	//id = 0 -> Sound Item, 1 = Hinderniss, 2 = out of bounds, 3 = Linked List Head
	int id;
	struct item_node *next;
	struct item_node *prev;
	union{
		struct{
			int freq_20_40; // Angabe hier 20 bis 40 hz
			int freq_40_100;
		   	int freq_100_150;
            int freq_150_400;
            int freq_400_1000;
            int freq_1000_2000;
            int freq_2000_3500;
            int freq_3500_6000;
            int freq_6000_10000; //Frequenzbereich hat einen dB Wert
            int freq_10000_20000;
		   	bool touched;
		   	int direction_id; //direction_id: 1 = 0oben, 2 = 45obenrechts, 3 = 90rechts, 4 = 135untenrechts,
		   						// 5 = 180(unten), 6 = 225(unten)links, 7 = 270links, 8 = 315links oben, 0 = nichts
		   						// 9 = 0unten, 10 = 45unten, 11 = 90unten, 12 = 135unten, 13 = 180unten, 14 = 225 unten
		   						// 15 = 270unten, 16 = 315unten, 17 = 0oben, 18= 45oben, 19 = 90oben, 20 = 135oben, 21= 180 oben
		   						// 22 = 225oben, 23 = 270oben, 24 = 315oben, 25 = von der Decke zum Boden, 26 = vom Boden zu decke. Undenkbar =D
								//Ausfallwinkel: 1 -> 5, 2 -> 4, 3 -> 7, 4 -> 2, 5 -> 1, 6 -> 8, 7 -> 3, 8 -> 6
            int movement; // Anzahl an Verschiebungen, welche die dB Zahl reduziert TODO Methoden.
            int sideofwave;
            struct item_node *waveroot;
		} Sound;
		struct{
			float reduce; // muss ein Absoprtionsfaktor sein ≥ 1 und für die Frequenz angepasst werden
		} Obstacle;
	} data;
}item_node;
int getItemID(item_node *node );
void setItemID(item_node *node, int id);
int getFieldID(int x, int y, int z);


void setFreq20b40(item_node *node, int value);
void setFreq40b100(item_node *node, int value);
void setFreq100b150(item_node *node, int value);
void setFreq150b400(item_node *node, int value);
void setFreq400b1000(item_node *node, int value);
void setFreq1000b2000(item_node *node, int value);
void setFreq2000b3500(item_node *node, int value);
void setFreq3500b6000(item_node *node, int value);
void setFreq6000b10000(item_node *node, int value);
void setFreq10000b20000(item_node *node, int value);

int getFreq20b40(item_node *node);
int getFreq40b100(item_node *node);
int getFreq100b150(item_node *node);
int getFreq150b400(item_node *node);
int getFreq400b1000(item_node *node);
int getFreq1000b2000(item_node *node);
int getFreq2000b3500(item_node *node);
int getFreq3500b6000(item_node *node);
int getFreq6000b10000(item_node *node);
int getFreq10000b20000(item_node *node);

void setDirectionID(item_node *node, int value);
int getDirectionID(item_node *node);
item_node *getItem_Root(int x, int y, int z);
item_node* createItem (int x, int y, int z, int id);
item_node* addItem (item_node *node, int x, int y, int z);
void addItemNewRoom (item_node * node, int x, int y, int z);
int isSoundField(int x, int y, int z);
void removeItem(item_node *node);

#endif
