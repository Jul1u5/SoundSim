#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "main.h"
#include "soundwavefunction.h"
#include "collision.h"
#include "extras.h"
#include <time.h>
#include <sys/types.h>
#include <signal.h>
#include <mpi.h>
#include <stddef.h>
//!Step Counter für Visualisierung
int visuStep = 1;
//!Raum Formate
int x_format;
int y_format;
int z_format;
int j, k, l, i;
//!OpenMPI
//!Rank 0: Verwalter V, Rank 1: Visualizer V, Rank 2-n: SoundSim S
int myrank;
int size;
const int nitems = 18;
int rows = 5;
int realcountright = 0;
int realcountleft = 0;
int cols = 18;
//!Modelierung eines Fragments !
item_node *roomtrans;
item_node ***room;
item_node ***room_new;
item_node *allElementsNew = NULL;
item_node *allElements = NULL;

/**
 * Erzeugt einen neuen Raum
 * @return
 */
item_node*** createRoom()
{
	if (room == NULL) {
		allElements = malloc(x_format * y_format * z_format * sizeof(item_node));
		room = malloc(x_format * sizeof(item_node **));
		if (room == NULL) {
			return NULL;
		}
		for (int i = 0; i < x_format; i++)
		{
			room[i] = malloc(y_format * sizeof(item_node *));
			if (room[i] == NULL) {
				return NULL;
			}
			for (int j = 0; j < y_format; j++)
			{
				room[i][j] = allElements + (i * y_format * z_format) + (j * z_format);
				if (room[i][j] == NULL) {
					return NULL;
				}
			}
		}
		for (j = 0; j < x_format; j++) {
			for (k = 0; k < y_format; k++) {
				for (l = 0; l < z_format; l++) {
					room[j][k][l].id = 3;
					room[j][k][l].next = NULL;
				}
			}
		}
	}
	return room;
}
/**
 * Allocation Test
 */
void allocRoom() {
	if (room == NULL) {
		allElements = malloc(x_format * y_format * z_format * sizeof(item_node));
		room = malloc(x_format * sizeof(item_node **));
		if (room == NULL) {
			printf("No Mem Bro!");
		}
		for (int i = 0; i < x_format; i++)
		{
			room[i] = malloc(y_format * sizeof(item_node *));
			if (room[i] == NULL) {
				printf("No Mem Bro!");
			}
			for (int j = 0; j < y_format; j++)
			{
				room[i][j] = allElements + (i * y_format * z_format) + (j * z_format);
				if (room[i][j] == NULL) {
					printf("No Mem Bro!");
				}
			}
		}

	}
}
/**
 * Erzeugt einen neuen Raum, in den die neuen Elemente gepackt werden.
 * @return
 */
item_node*** createRoomNew()
{
	/*if (room_new != NULL) {
		printf("nicht null\n");
		free(allElementsNew);
		for(int i = 0; i < x; i++)
		{
			free(room_new[i]);
			room_new[i] = NULL;
		}
		free (room_new);
		room_new = NULL;
	}*/
	room_new = NULL;
	if (room_new == NULL) {
		allElementsNew = malloc(x_format * y_format * z_format * sizeof(item_node));
		room_new = malloc(x_format * sizeof(item_node **));
		if (room_new == NULL) {
			//return NULL;
		}
		for (int i = 0; i < x_format; i++)
		{
			room_new[i] = malloc(y_format * sizeof(item_node *));
			if (room_new[i] == NULL) {
				//return NULL;
			}
			for (int j = 0; j < y_format; j++)
			{
				room_new[i][j] = allElementsNew + (i * y_format * z_format) + (j * z_format);
				if (room_new[i][j] == NULL) {
					//return NULL;
				}
			}
		}
	}
	//schöner machen!
	for (j = 0; j < x_format; j++) {
		for (k = 0; k < y_format; k++) {
			for (l = 0; l < z_format; l++) {
				//printf("x: %d, y: %d, z: %d, id: %d\n",j,k,l,getFieldID(j,k,l));

				if ((room[j][k][l].next) != NULL) {
					if ((room[j][k][l].next->id) == 1) {
						room_new[j][k][l] = room[j][k][l];
						//printf("WAND:! x: %d, y: %d, z: %d, id: %d\n",j,k,l,getFieldID(j,k,l));
					} else {
						room_new[j][k][l].id = 3;
						room_new[j][k][l].next = NULL;
						//return NULL;
					}
				}
				else {
					//printf("keine wand:! x: %d, y: %d, z: %d, id: %d\n",j,k,l,getFieldID(j,k,l));

					room_new[j][k][l].id = 3;
					room_new[j][k][l].next = NULL;
					//return NULL;

				}
			}
		}
	}
	return room_new;
}
/**
 * Raum wird gewechselt. Der Alte wird geleert.
 * @param newRoom
 */
void changeRoom(item_node *** newRoom)
{
	if (room != NULL) {
		free(allElements);
		for (int i = 0; i < x_format; i++)
		{
			free(room[i]);
		}
		free (room);
		room = NULL;
	}
	//free(room);
	//free(allElements);
	room = newRoom;
	allElements = allElementsNew;
	//memmove(room,room_new, 200 * sizeof(item_node **));
	//memmove(allElements,allElementsNew, 200 * 200 * 200 * sizeof(item_node));
}
/**
 * Gibt die ITEM ID zurück.
 * @param node
 * @return 0: Sound, 1: Hinderniss, 2: ungültiges Element
 */
int getItemID(item_node * node ) {
	if (node != NULL)
	{
		return node->id;
	} else return 2;
}
/**
 * Gibt einem ITEM die ID
 * @param node
 * @param id
 */
void setItemID(item_node * node, int id)
{
	node->id = id;
}
/**
 * Gibt die allgemeine Feld ID zurück.
 * @param x
 * @param y
 * @param z
 * @return 0: Sound, 1: Hinderniss, 2: ungültiges Element, 3: leeres Feld (Linked List Head)
 */
int getFieldID(int x, int y, int z)
{
	int returnvalue = 2;
	if (x < x_format && y < y_format && z < z_format && x >= 0 && y >= 0 && z >= 0)
	{
		if (room[x][y][z].next != NULL) {
			//0 oder 1
			returnvalue = room[x][y][z].next->id;
		}
		else returnvalue = 3;
		//ohne jeglicher Belegung
	}
	return returnvalue;
}
//den Raum zurückgeben
/**
 * Variable room als Getter.
 * @return
 */
item_node getRoom() {
	return *** room;
}
/**
 * Wahrheitswert ob es sich bei der Koordinate um ein Hinderniss handelt.
 * @param x
 * @param y
 * @param z
 * @return
 */
bool isObstacle(int x, int y, int z)
{
	bool returnvalue = false;
	if (room[x][y][z].next != NULL) {
		if (room[x][y][z].next->id == 1)
		{
			//dann Hinderniss
			returnvalue = true;
		}
	}
	return returnvalue;

}
/////////// Frequenzbereich dB ändern
void setFreq20b40(item_node * node, int value)
{
	if (getItemID(node) == 0) {
		node->data.Sound.freq_20_40 = value;
	}
}
void setFreq40b100(item_node * node, int value)
{
	if (getItemID(node) == 0) {
		node->data.Sound.freq_40_100 = value;
	}
}
void setFreq100b150(item_node * node, int value)
{
	if (getItemID(node) == 0) {
		node->data.Sound.freq_100_150 = value;
	}
}
void setFreq150b400(item_node * node, int value)
{
	if (getItemID(node) == 0) {
		node->data.Sound.freq_150_400 = value;
	}
}
void setFreq400b1000(item_node * node, int value)
{
	if (getItemID(node) == 0) {
		node->data.Sound.freq_400_1000 = value;
	}
}
void setFreq1000b2000(item_node * node, int value)
{
	if (getItemID(node) == 0) {
		node->data.Sound.freq_1000_2000 = value;
	}
}
void setFreq2000b3500(item_node * node, int value)
{
	if (getItemID(node) == 0) {
		node->data.Sound.freq_2000_3500 = value;
	}
}
void setFreq3500b6000(item_node * node, int value)
{
	if (getItemID(node) == 0) {
		node->data.Sound.freq_3500_6000 = value;
	}
}
void setFreq6000b10000(item_node * node, int value)
{
	if (getItemID(node) == 0) {
		node->data.Sound.freq_6000_10000 = value;
	}
}
void setFreq10000b20000(item_node * node, int value)
{
	if (getItemID(node) == 0) {
		node->data.Sound.freq_10000_20000 = value;
	}
}
///////// Get Methoden

int getFreq20b40(item_node * node)
{
	if (getItemID(node) == 0) {
		return node->data.Sound.freq_20_40;
	} else {
		return 99999;
	}
}
int getFreq40b100(item_node * node)
{
	if (getItemID(node) == 0) {
		return node->data.Sound.freq_40_100;
	} else {
		return 99999;
	}
}
int getFreq100b150(item_node * node)
{
	if (getItemID(node) == 0) {
		return node->data.Sound.freq_100_150;
	} else {
		return 99999;
	}
}
int getFreq150b400(item_node * node)
{
	if (getItemID(node) == 0) {
		return node->data.Sound.freq_150_400;
	} else {
		return 99999;
	}
}
int getFreq400b1000(item_node * node)
{
	if (getItemID(node) == 0) {
		return node->data.Sound.freq_400_1000;
	} else {
		return 99999;
	}
}
int getFreq1000b2000(item_node * node)
{
	if (getItemID(node) == 0) {
		return node->data.Sound.freq_1000_2000;
	} else {
		return 99999;
	}
}
int getFreq2000b3500(item_node * node)
{
	if (getItemID(node) == 0) {
		return node->data.Sound.freq_2000_3500;
	} else {
		return 99999;
	}
}
int getFreq3500b6000(item_node * node)
{
	if (getItemID(node) == 0) {
		return node->data.Sound.freq_3500_6000;
	} else {
		return 99999;
	}
}
int getFreq6000b10000(item_node * node)
{
	if (getItemID(node) == 0) {
		return node->data.Sound.freq_6000_10000;
	} else {
		return 99999;
	}
}
int getFreq10000b20000(item_node * node)
{
	if (getItemID(node) == 0) {
		return node->data.Sound.freq_10000_20000;
	} else {
		return 99999;
	}
}

////////
/**
 * Richtung eines SoundItem setzen
 * @param node
 * @param value
 */
void setDirectionID(item_node * node, int value)
{
	if (getItemID(node) == 0) {
		node->data.Sound.direction_id = value;
	}
}
/**
 * Gibt die Richtung eine SoundItem
 * @param node
 * @return Richtung
 */
int getDirectionID(item_node * node)
{
	if (getItemID(node) == 0) {
		return node->data.Sound.direction_id;
	} else return -1;
}
/**
 * Gibt die Abprallrichtung abhängig von der aktuellen Richtung
 * @param currentDirectionID
 * @return neue Richtung
 */
int getReboundID(int currentDirectionID)
{
	switch (currentDirectionID)
	{
	case 1: return 5; break;
	case 2: return 4; break;
	case 3: return 7; break;
	case 4: return 2; break;
	case 5: return 1; break;
	case 6: return 8; break;
	case 7: return 3; break;
	case 8: return 6; break;
	default: return 0; break;
	}

}
item_node getSound(item_node * node)
{
	//Absicherung fehlt
	return *node;
}
item_node getObstacle(item_node * node)
{
	//Absicherung fehlt
	return *node;
}
/**
 * Das Root Element ist das 1.Element jeder gültigen Koordinate (ID 3)
 * @param x
 * @param y
 * @param z
 * @return
 */
item_node *getItem_Root(int x, int y, int z)
{
	if (x < x_format && y < y_format && z < z_format && x >= 0 && y >= 0 && z >= 0)
	{
		return &room[x][y][z];
	} else {
		item_node* newNode = malloc(sizeof(item_node));
		newNode->id = 2;
		newNode->next = NULL;
		return newNode;
		//Element erstellen mit id 2 -> ungültig und wird dann entfernt
	}
}
//Create Item
/**
 * Erzeugt ein neues Item mit einer bestimmten ID
 * @param x
 * @param y
 * @param z
 * @param id
 * @return
 */
item_node* createItem (int x, int y, int z, int id)
{
	item_node* selected = getItem_Root(x, y, z);
	//printf("Passt?: %d\n", getItemID(selected) );
	//prüfen ob Element überhaupt Gültig ist!
	if (getItemID(selected) != 2)
	{
		while (selected->next != NULL)
			selected = selected->next;
		selected->next = malloc(sizeof(item_node));
		selected->next->prev = selected;
		selected = selected->next;
		selected->id = id;
		selected->next = NULL;
		if (selected->id == 0) {
			setMovement(selected, 0);
		}
	}
	return selected;


	// fängt für ein neues Element bei Movement 0 an.

	//item_node* selected = &room[x][y];
	/*if(selected == NULL)
	{
		printf("%s\n", "test");
	    selected = malloc(sizeof(item_node));
	}
	else{
	    while(selected->next != NULL)
	        selected = selected->next;

	    selected->next = malloc(sizeof(item_node));
	    selected = selected->next;
	}

	selected->id = id;
	selected->next = NULL;
	return selected;*/
}
/**
 * Entfernt das ausgewählte Element
 * @param node
 */
void removeItem(item_node * node) {
	if (node->next == NULL) {
		//letztes item: vorletztes next->NULL
		if (node->prev == NULL) {
			//bedeutet: er versucht den head zu löschen, dieser hat kein prev pfeil und darum geht das hier kaputt!
			//hier ist aber nicht das problem, sondern hier taucht das problem nur in erscheinung
			//irgendwo wird also der head als id = sound beschrieben, sodass z,b in collision dieser aufruf überhaupt erfolgen kann.
		}
		node->prev->next = NULL;
	}
	else {
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
	//TODO: Wahrscheinlich kann man hier noch free() machen, da node dann wieder freigegeben wird.
}
/**
 * Fügt ein Element an eine neue Stelle (Eigenschaften bleiben erhalten), Element an der alten Position wird entfernt
 * @param node
 * @param x
 * @param y
 * @param z
 * @return
 */
item_node* addItem (item_node * node, int x, int y, int z)
{
	item_node* selected = getItem_Root(x, y, z);
	//item_node* selected = &room[x][y];
	if (getItemID(selected) != 2)
	{
		removeItem(node);
		while (selected->next != NULL)
			selected = selected->next;
		selected->next = node;
		selected->next->prev = selected;
		selected = selected->next;
		selected->next = NULL;
	}
	return selected;
}
/**
 * Das Root Element von new_room ist das 1.Element jeder gültigen Koordinate (ID 3)
 * @param x
 * @param y
 * @param z
 * @return
 */
item_node *getItem_RootNewRoom(int x, int y, int z)
{
	if (x < x_format && y < y_format && z < z_format && x >= 0 && y >= 0 && z >= 0)
	{
		return &room_new[x][y][z];
	} else {
		item_node* newNode = malloc(sizeof(item_node));
		newNode->id = 2;
		newNode->next = NULL;
		return newNode;
		//Element erstellen mit id 2 -> ungültig und wird dann entfernt
	}
}
/**
 * Fügt ein Element an eine neue Stelle in new_room (Eigenschaften bleiben erhalten), Element an der alten Position wird entfernt
 * @param node
 * @param x
 * @param y
 * @param z
 */
void addItemNewRoom (item_node * node, int x, int y, int z)
{
	item_node* selected = getItem_RootNewRoom(x, y, z);

	//item_node* selected = &room[x][y];
	if (getItemID(selected) != 2)
	{
		removeItem(node);
		while (selected->next != NULL)
			selected = selected->next;
		selected->next = node;
		selected->next->prev = selected;
		selected = selected->next;
		selected->next = NULL;
	}
}
/**
 * Prüft ob Feld ein Sound Feld ist
 * @param x
 * @param y
 * @param z
 * @return
 */
int isSoundField(int x, int y, int z)
{
	int returnvalue = 0;
	if (x < x_format && y < y_format && z < z_format && x >= 0 && y >= 0 && z >= 0)
	{
		if (room[x][y][z].next != NULL) {
			//0 oder 1
			if (room[x][y][z].next->id == 0)
			{
				returnvalue = 1;
			}
		}
		else returnvalue = 1;
		//ohne jeglicher Belegung
	}
	return returnvalue;
}

void createReceipt(int (*roomtrans)[cols], int var, int x) {

	if (isSoundField(x, roomtrans[var][16], roomtrans[var][17]) == 1) {

		item_node *poo = createItem(x, roomtrans[var][16], roomtrans[var][17], 0);
		setFreq20b40(poo, roomtrans[var][1]);
		setFreq40b100(poo, roomtrans[var][2]);
		setFreq100b150(poo, roomtrans[var][3]);
		setFreq150b400(poo, roomtrans[var][4]);
		setFreq400b1000(poo, roomtrans[var][5]);
		setFreq1000b2000(poo, roomtrans[var][6]);
		setFreq2000b3500(poo, roomtrans[var][7]);
		setFreq3500b6000(poo, roomtrans[var][8]);
		setFreq6000b10000(poo, roomtrans[var][9]);
		setFreq10000b20000(poo, roomtrans[var][10]);
		setTouche(poo);
		setDirectionID(poo, roomtrans[var][12]);
		setMovement(poo, roomtrans[var][13]);
		setSideOfWave(poo, roomtrans[var][14]);
		printf("Frq: %d und Direction: %d\n", roomtrans[var][1], roomtrans[var][12]);
	}
	else {
		item_node *puh = createItem(x, roomtrans[var][16], roomtrans[var][17], 0);
		setFreq20b40(puh, roomtrans[var][1]);
		setFreq40b100(puh, roomtrans[var][2]);
		setFreq100b150(puh, roomtrans[var][3]);
		setFreq150b400(puh, roomtrans[var][4]);
		setFreq400b1000(puh, roomtrans[var][5]);
		setFreq1000b2000(puh, roomtrans[var][6]);
		setFreq2000b3500(puh, roomtrans[var][7]);
		setFreq3500b6000(puh, roomtrans[var][8]);
		setFreq6000b10000(puh, roomtrans[var][9]);
		setFreq10000b20000(puh, roomtrans[var][10]);
		setTouche(puh);
		setDirectionID(puh, getReboundID(roomtrans[var][12]));
		setMovement(puh, roomtrans[var][13]);
		setSideOfWave(puh, roomtrans[var][14]);

		absorption(puh, x, roomtrans[var][16], roomtrans[var][17], 0.76);
	}
}
int* prepareArrays(item_node *node, int side) {
	int *sarray = malloc(cols * sizeof(int));
	if (side == 1) {

		sarray[0] = getItemID(node);
		sarray[1] = getFreq20b40(node);
		sarray[2] = getFreq40b100(node);
		sarray[3] = getFreq100b150(node);
		sarray[4] = getFreq150b400(node);
		sarray[5] = getFreq400b1000(node);
		sarray[6] = getFreq1000b2000(node);
		sarray[7] = getFreq2000b3500(node);
		sarray[8] = getFreq3500b6000(node);
		sarray[9] = getFreq6000b10000(node);
		sarray[10] = getFreq10000b20000(node);
		sarray[11] = getTouch(node);
		sarray[12] = getDirectionID(node);
		sarray[13] = getMovement(node);
		sarray[14] = getSideOfWave(node);
		sarray[15] = j;
		sarray[16] = k;
		sarray[17] = l;
	}
	else if (side == 2) {

		sarray[0] = getItemID(node);
		sarray[1] = getFreq20b40(node);
		sarray[2] = getFreq40b100(node);
		sarray[3] = getFreq100b150(node);
		sarray[4] = getFreq150b400(node);
		sarray[5] = getFreq400b1000(node);
		sarray[6] = getFreq1000b2000(node);
		sarray[7] = getFreq2000b3500(node);
		sarray[8] = getFreq3500b6000(node);
		sarray[9] = getFreq6000b10000(node);
		sarray[10] = getFreq10000b20000(node);
		sarray[11] = getTouch(node);
		sarray[12] = getDirectionID(node);
		sarray[13] = getMovement(node);
		sarray[14] = getSideOfWave(node);
		sarray[15] = j;
		sarray[16] = k;
		sarray[17] = l;
	}
	return sarray;
}
/**
 * Speichert die Matrix ab. Zeitschritte werden berücksichtigt.
 */
void saveVisualisation(int x_offset)
{
	/**@see http://wiki.selfhtml.org/wiki/JavaScript/JSON */
	/**@see http://papo15.juliu5.com/ */
	if (myrank > 1)
	{
		int rows = 5;
		int cols = 4;
		int realcount = 0;
		int (*sendarray)[cols] = malloc(sizeof * sendarray * rows);
		for (int j = 0; j < x_format; ++j)
		{
			for (int k = 0; k < y_format; ++k)
			{
				for (int l = 0; l < z_format; ++l)
				{
					if (realcount == rows) {
						int newnum = (rows + 2) * 2;
						int (*newptr)[cols] = realloc(sendarray, sizeof * newptr * newnum);
						rows = newnum;
						sendarray = newptr;
					}

					//sendarray[realsize] = (int *)malloc(5 * sizeof(int));
					if (isObstacle(j, k, l)) {
						//Hinderniss mit Value 0 markieren
						sendarray[realcount][0] = j + x_offset;
						sendarray[realcount][1] = k;
						sendarray[realcount][2] = l;
						sendarray[realcount][3] = 0;
						++realcount;
					} else {
						item_node *temp;
						temp = getItem_Root(j, k, l);
						int max = 0;
						int count = 0;
						while (temp != NULL)
						{
							//TODO: auf Gegenstände reagieren...
							int itemID = getItemID(temp);
							if (itemID == 0)
							{
								if (getFreq150b400(temp) > max) {
									max = getFreq150b400(temp);
								}
							}
							temp = temp->next;
						}
						if (max > 0) {
							sendarray[realcount][0] = j + x_offset;
							sendarray[realcount][1] = k;
							sendarray[realcount][2] = l;
							sendarray[realcount][3] = max;
							++realcount;
						}
					}
				}
			}
		}
		MPI_Request req;
		MPI_Isend(sendarray, realcount * cols, MPI_INT, 1, 1, MPI_COMM_WORLD, &req);
		MPI_Wait(&req, MPI_STATUS_IGNORE);
		//freen
		free(sendarray);
	}
}
/**
 * Wird zu Beginn aufgerufen und organisiert den Start
 */
void startup()
{
	/*if (myrank == 1) {
		//alten output.json löschen
		remove("output");
		//Visualisation starten
		FILE *fp;
		fp = fopen("output", "a");
		fprintf(fp, "{" );
		fclose(fp);
	}*/

}
/**
 * Verantwortlich für das korrekte herunterfahren
 */
void shutdown()
{
	/*if (myrank == 1) {
		//Visualisation beenden
		FILE *fp;
		fp = fopen("output", "a");
		fprintf(fp, "}" );
		//printf("nenenenenene\n");
		fclose(fp);
	}*/
}

int main (int argc, char *argv[])
{
	int DebugWait = 1;
	while (DebugWait) ;
	double start_t, end_t, total_t;
	MPI_Request *request;
	MPI_Request *request_ready;
	MPI_Status status;
	MPI_Init(&argc, &argv); // bytes in 1 blocks are definitely lost in loss record 1,382 of 3,539
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	int NSimulations = size - 2;
	if (myrank == 0) {
		//! Gesamtformat
		x_format = 200;
		y_format = 200;
		z_format = 200;
		int setting_runs = 40;
		start_t = MPI_Wtime();  //Startzeit
		printf("%s\n", "-----STARTING THE ENGINE-----" );
		printf("X:%d & Y:%d & Z:%d\n", x_format, y_format, z_format);
		//-V & -Visu
		//für jeden Slave Process wird festgehalten wie viele Zahlen er am Ende zugewiesen bekommt
		int * paraarray = malloc(NSimulations * sizeof(int));
		//array nullen
		for (int j = 0; j < NSimulations; j++) {
			paraarray[j] = 0;
		}
		//um die Zahlen gleichmäßig zu verteilen werden alle Summanden durchlaufen und nacheinander auf die Prozesse 2 bis size-1 aufgeteilt
		int new_process_rank = 0;
		for (int i = 0; i < x_format; i++)
		{
			paraarray[new_process_rank] = paraarray[new_process_rank] + 1;
			//wenn alle Ranks durchlaufen wurden wird wieder auf den 0. gesprungen
			if (new_process_rank + 1 >= NSimulations) {
				new_process_rank = 0;
			} else
			{
				++new_process_rank;
			}
		}
		//Wird gleichmäßig verteilt! :)
		for (int var = 2; var < NSimulations + 2; ++var) {
			printf("Rank: %d, Values: %d\n", var, paraarray[var - 2]);
		}
		//Offset berechnen
		//Info Array berechnen
		int * SimSetting = malloc(5 * sizeof(int));
		request = malloc(sizeof(MPI_Request) * NSimulations);
		for (int t = 0; t < NSimulations; ++t) {
			//berechneter X Wert, Y_Format, Z_Format, berechneter Offset neben X
			int offset = 0;
			for (int j = 0; j < t; ++j) {
				offset = offset + paraarray[j];
			}
			SimSetting[0] = paraarray[t];
			SimSetting[1] = y_format;
			SimSetting[2] = z_format;
			SimSetting[3] = offset;
			SimSetting[4] = setting_runs;
			//1. Senden der Array Größe, da diese dem Empfänger bekannt sein muss
			//t+2 weil wir ja einen offset von 2 reservierten T haben
			MPI_Isend(SimSetting, 5, MPI_INT, t + 2, t + 2, MPI_COMM_WORLD, &request[t]);
			//MPI_Send(&paraarray[p], 1, MPI_INT, p, tag, MPI_COMM_WORLD);
			printf("Offset: %d\n", offset);
		}
		MPI_Waitall(NSimulations, request, MPI_STATUSES_IGNORE);
		printf("Tasks wurden verteilt!\n");
		//!Taktgeber
		int go = 1;
		for (int i = 1; i <= setting_runs; ++i)
		{
			MPI_Request visuGo;
			MPI_Isend(&NSimulations, 1, MPI_INT, 1, 1, MPI_COMM_WORLD, &visuGo);
			//wir erwarten keine Antwort
			MPI_Request_free(&visuGo);
			for (int t = 0; t < NSimulations; ++t) {
				MPI_Isend(&go, 1, MPI_INT, t + 2, t + 2, MPI_COMM_WORLD, &request[t]);
			}
			//Synchronisieren
			MPI_Waitall(NSimulations, request, MPI_STATUSES_IGNORE);
			int sum_tasks = 0;
			for (int t = 0; t < NSimulations; ++t) {
				int add = 0;
				MPI_Recv(&add, 1, MPI_INT, t + 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				sum_tasks = sum_tasks + add;
			}
		}
		//Iterationen beenden
		go = 0;
		MPI_Request visuGo;
		MPI_Isend(&go, 1, MPI_INT, 1, 1, MPI_COMM_WORLD, &visuGo);
		//wir erwarten keine Antwort
		MPI_Request_free(&visuGo);
		for (int t = 0; t < NSimulations; ++t) {
			MPI_Isend(&go, 1, MPI_INT, t + 2, t + 2, MPI_COMM_WORLD, &request[t]);
		}
		//bruchen wir vlt nicht mehr
		MPI_Waitall(NSimulations, request, MPI_STATUSES_IGNORE);
	} else if (myrank == 1) {
		//alten output.json löschen
		remove("output");
		//Visualisation starten
		FILE *fp;
		fp = fopen("output", "a");
		fprintf(fp, "{" );
		//go bekommt die anzahl der tasks die ihn aufrufen
		int go = 0;
		int run = 1;
		MPI_Recv(&go, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		while (go != 0) {
			fprintf(fp, "\"soundarray%d\": [", run );
			//besser mit MPI Probe?
			for (i = 2; i < go + 2; ++i) {
				int amount = 0;
				MPI_Status status;
				MPI_Probe(i, 1, MPI_COMM_WORLD, &status);
				MPI_Get_count(&status, MPI_INT, &amount);
				int cols = 4;
				//int (*recv_buf)[cols] = malloc(sizeof *recv_buf * amount);
				int (*recv_buf)[cols] = malloc(sizeof * recv_buf * amount / 4);
				MPI_Recv(recv_buf, amount, MPI_INT, i, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				for (int var = 0; var < amount / 4; ++var) {
					fprintf(fp, "{ \"x\": %d, \"y\": %d, \"z\": %d, \"value\": %d },", recv_buf[var][0], recv_buf[var][1], recv_buf[var][2], recv_buf[var][3]);
				}
				free(recv_buf);
			}
			fprintf(fp, "]," );
			++run;
			MPI_Recv(&go, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		}
		fclose(fp);
	} else if (myrank > 1) {
		int * mySimSetting = malloc(5 * sizeof(int));
		MPI_Recv(mySimSetting, 5, MPI_INT, 0, myrank, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		x_format = mySimSetting[0];
		y_format = mySimSetting[1];
		z_format = mySimSetting[2];
		//Ticks von T0 bekommen
		int x_offset = mySimSetting[3];
		int runs = mySimSetting[4];
		int go = 0;
		int run = 1;
		/*int (*sendarrayleft)[cols] = malloc(sizeof * sendarrayleft * rows);
		int (*sendarrayright)[cols] = malloc(sizeof * sendarrayright * rows);*/
		MPI_Recv(&go, 1, MPI_INT, 0, myrank, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		while (go) {
			//solange durchgehen
			createRoom();
			//createItem(1, 1, 1, 1);
			if (myrank == 2 && run == 1) {
				loudspeaker();
				//createItem(10,10,20,1);
				//createWall();
			}
			if (myrank == size-2 && run == 1) {
				//door();
			}
			unToucheAll();
			saveVisualisation(x_offset);
			createRoomNew();
			//printf("Durchgang: %d, Task: %d\n", run, myrank);
			int sendrowsleft = 5;
			int sendrowsright = 5;
			int (*sendarrayleft)[cols] = malloc(sizeof * sendarrayleft * sendrowsleft);
			int (*sendarrayright)[cols] = malloc(sizeof * sendarrayright * sendrowsright);
			
			if (myrank != 2 && myrank != size - 1 && run > 1) {
				// von links empfangen
				int amountleft = 0;
				int sourceleft = myrank - 1;
				MPI_Status status;
				MPI_Probe(sourceleft, 14, MPI_COMM_WORLD, &status);
				MPI_Get_count(&status, MPI_INT, &amountleft);
				int (*recv_bufl)[cols] = malloc(sizeof * recv_bufl * amountleft / cols);
				MPI_Recv(recv_bufl, amountleft, MPI_INT, sourceleft, 14, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				for (int var = 0; var < amountleft / cols; ++var) {
					createReceipt(recv_bufl, var, 0);
				}
				free(recv_bufl);
				// von rechts empfangen
				int amountright = 0;
				int sourceright = myrank + 1;
				MPI_Probe(sourceright, 14, MPI_COMM_WORLD, &status);
				MPI_Get_count(&status, MPI_INT, &amountright);
				int (*recv_bufr)[cols] = malloc(sizeof * recv_bufr * amountright / cols);
				MPI_Recv(recv_bufr, amountright, MPI_INT, sourceright, 14, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				for (int var = 0; var < amountright / cols; ++var) {
					createReceipt(recv_bufr, var, x_format-1);
				}
				free(recv_bufr);
			}
			else if (myrank == 2 && run > 1) {
				// darf nur von rechts Empfangen
				int amount = 0;
				int source = myrank + 1;
				MPI_Status status;
				MPI_Probe(source, 14, MPI_COMM_WORLD, &status);
				MPI_Get_count(&status, MPI_INT, &amount);
				int (*recv_buf)[cols] = malloc(sizeof * recv_buf * amount / cols);
				MPI_Recv(recv_buf, amount, MPI_INT, source, 14, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				for (int var = 0; var < amount / cols; ++var) {
					createReceipt(recv_buf, var, x_format-1);
				}
				free(recv_buf);

			} else if (myrank == size - 1 && run > 1) {
				// darf nur von links empfangen
				int amount = 0;
				int source = myrank - 1;
				MPI_Status status;
				MPI_Probe(source, 14, MPI_COMM_WORLD, &status);
				MPI_Get_count(&status, MPI_INT, &amount);
				int (*recv_buf)[cols] = malloc(sizeof * recv_buf * amount / cols);
				MPI_Recv(recv_buf, amount, MPI_INT, source, 14, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				for (int var = 0; var < amount / cols; ++var) {
					createReceipt(recv_buf, var, 0);
				}
				free(recv_buf);
			}

			for (int j = 0; j < x_format; ++j)
			{
				for (int k = 0; k < y_format; ++k)
				{
					for (int l = 0; l < z_format; ++l) {

						if (isObstacle(j, k, l) == false)
						{
							//kein Hinderniss -> fortfahren
							item_node *temp;
							temp = getItem_Root(j, k, l);
							while (temp != NULL) {
								//Richtung prüfen
								increaseMovement(temp);
								checkSoundValid(temp, j, k, l);
								if (checkSoundValid(temp, j, k, l) == true && getTouch(temp) == false) { // Damit er keine 0dB Elemente zu Wellen macht
									addWave(temp, j, k , l);
								} // Sprung in die Waveunktion
								int direction_id = getDirectionID(temp);
								//TODO: Besser nur bei Sound Objekten
								if (direction_id == 1) {
									int next_itemID = getFieldID(j, k + 1, l);
									if (next_itemID == 0 || next_itemID == 3) {
										//ist Sound Feld
										addItemNewRoom(temp, j, k + 1, l);
									} else if (next_itemID == 1) {
										//TODO Wenn Kollsion mit itemID 2
										absorption(temp, 0.78);
										//1. Sound an die Folgestelle schieben
										//2. Attribut der Richtung anpassen
										temp->data.Sound.direction_id = getReboundID(direction_id);
										changeReboundSideOfWave(temp);
										addItemNewRoom(temp, j, k, l);
									} else if (next_itemID == 2)
									{
										removeItem(temp);
									}
								}
								else if (direction_id == 2) {
									int next_itemID = getFieldID(j + 1, k + 1 , l);
									if (next_itemID == 0 || next_itemID == 3) {
										addItemNewRoom(temp, j + 1, k + 1, l);
									}
									else if (next_itemID == 1) {
										absorption(temp, 0.78);
										temp->data.Sound.direction_id = getReboundID(direction_id);
										changeReboundSideOfWave(temp);
										addItemNewRoom(temp, j, k, l);
									} else if (next_itemID == 2 && j == x_format - 1 && myrank != size - 1) {
										if (realcountright == sendrowsright) {
											int newnum = (sendrowsright + 2) * 2;
											int (*newptr)[cols] = realloc(sendarrayright, sizeof * newptr * newnum);
											sendrowsright = newnum;
											sendarrayright = newptr;
										}
										int *sendarrayright_new = prepareArrays(temp, 2);
										for (int var = 0; var < cols; ++var) {
											sendarrayright[realcountright][var] = sendarrayright_new[var];
										}
										free(sendarrayright_new);
										++realcountright;
										removeItem(temp);
									}
									else {
										removeItem(temp);
									}
								}
								else if (direction_id == 3) {
									int next_itemID = getFieldID(j + 1, k, l);
									if (next_itemID == 0 || next_itemID == 3) {
										addItemNewRoom(temp, j + 1, k, l);
									}
									else if (next_itemID == 1) {
										absorption(temp, 0.78);
										temp->data.Sound.direction_id = getReboundID(direction_id);
										changeReboundSideOfWave(temp);
										addItemNewRoom(temp, j, k, l);
									} else if (next_itemID == 2 && j == x_format - 1 && myrank != size - 1) {
										if (realcountright == sendrowsright) {
											int newnum = (sendrowsright + 2) * 2;
											int (*newptr)[cols] = realloc(sendarrayright, sizeof * newptr * newnum);
											sendrowsright = newnum;
											sendarrayright = newptr;
										}
										int *sendarrayright_new = prepareArrays(temp, 2);

										/*for (int i = 0; i < cols ; i++) {
											printf("%d Wert sendrarray right\n", sendarrayright_new[i]); // stimmt !
										}*/

										for (int var = 0; var < cols; ++var) {
											sendarrayright[realcountright][var] = sendarrayright_new[var];
											//printf("Date: %d\n", sendarrayright[realcountright][var]);
										}
										free(sendarrayright_new);
										++realcountright;
										removeItem(temp);
									}
									else {
										removeItem(temp);
									}
								}
								else if (direction_id == 4) {
									int next_itemID = getFieldID(j + 1, k - 1 , l);
									if (next_itemID == 0 || next_itemID == 3) {
										addItemNewRoom(temp, j + 1, k - 1, l);
									}
									else if (next_itemID == 1) {
										absorption(temp, 0.78);
										temp->data.Sound.direction_id = getReboundID(direction_id);
										changeReboundSideOfWave(temp);
										addItemNewRoom(temp, j, k, l);
									} else if (next_itemID == 2 && j == x_format - 1 && myrank != size - 1) {
										if (realcountright == sendrowsright) {
											int newnum = (sendrowsright + 2) * 2;
											int (*newptr)[cols] = realloc(sendarrayright, sizeof * newptr * newnum);
											sendrowsright = newnum;
											sendarrayright = newptr;
										}
										int *sendarrayright_new = prepareArrays(temp, 2);
										for (int var = 0; var < cols; ++var) {
											sendarrayright[realcountright][var] = sendarrayright_new[var];
										}
										free(sendarrayright_new);
										++realcountright;
										removeItem(temp);
									} else {
										removeItem(temp);
									}
								}
								else if (direction_id == 5)
								{
									//nächstes Feld prüfen
									//item_node* next_item = getItem_Root(j, k - 1, l);
									int next_itemID = getFieldID(j, k - 1, l);
									//printf("freq: %d, runter: %d\n", getFreq10000b20000(temp) ,next_itemID );
									//int next_itemID = getItemID(j-1,k);
									if (next_itemID == 0 || next_itemID == 3) {
										addItemNewRoom(temp, j, k - 1, l);
										//room_new[j-1][k] = getSound(j,k);
									} else if (next_itemID == 1) {

										//TODO: Winkel Abprall, Schalldämmung durch Hinderniss
										//1. Sound an die Folgestelle schieben

										//room_new[j][k] = getSound(j,k);
										absorption(temp, 0.78);
										//2. Attribut der Richtung anpassen
										temp->data.Sound.direction_id = getReboundID(direction_id);
										//room_new[j][k].data.Sound.direction_id = getReboundID(direction_id);
										changeReboundSideOfWave(temp);
										addItemNewRoom(temp, j, k, l);
									} else if (next_itemID == 2)
									{
										removeItem(temp);
									}
								}
								else if (direction_id == 6) {
									int next_itemID = getFieldID(j - 1, k - 1 , l);
									if (next_itemID == 0 || next_itemID == 3) {
										addItemNewRoom(temp, j - 1, k - 1, l);
									}
									else if (next_itemID == 1) {
										absorption(temp, 0.78);
										temp->data.Sound.direction_id = getReboundID(direction_id);
										changeReboundSideOfWave(temp);
										addItemNewRoom(temp, j, k, l);
									} else if (next_itemID == 2 && j == 0 && myrank != 2) {
										if (realcountleft == sendrowsleft) {
											int newnum = (sendrowsleft + 2) * 2;
											int (*newptr)[cols] = realloc(sendarrayleft, sizeof * newptr * newnum);
											sendrowsleft = newnum;
											sendarrayleft = newptr;
										}
										int *sendarrayleft_new = prepareArrays(temp, 2);
										for (int var = 0; var < cols; ++var) {
											sendarrayleft[realcountleft][var] = sendarrayleft_new[var];
										}
										free(sendarrayleft_new);
										++realcountleft;
										removeItem(temp);
									} else {
										removeItem(temp);
									}
								}
								else if (direction_id == 7) {
									int next_itemID = getFieldID(j - 1, k , l);
									if (next_itemID == 0 || next_itemID == 3) {
										addItemNewRoom(temp, j - 1, k, l);
									}
									else if (next_itemID == 1) {
										absorption(temp, 0.78);
										temp->data.Sound.direction_id = getReboundID(direction_id);
										changeReboundSideOfWave(temp);
										addItemNewRoom(temp, j, k, l);
									} else if (next_itemID == 2 && j == 0 && myrank != 2) {
										if (realcountleft == sendrowsleft) {
											int newnum = (sendrowsleft + 2) * 2;
											int (*newptr)[cols] = realloc(sendarrayleft, sizeof * newptr * newnum);
											sendrowsleft = newnum;
											sendarrayleft = newptr;
										}
										int *sendarrayleft_new = prepareArrays(temp, 1);
										for (int var = 0; var < cols; ++var) {
											sendarrayleft[realcountleft][var] = sendarrayleft_new[var];
										}
										++realcountleft;
										removeItem(temp);
									} else {
										removeItem(temp);
									}
								}
								else if (direction_id == 8) {
									int next_itemID = getFieldID(j - 1, k + 1 , l);
									if (next_itemID == 0 || next_itemID == 3) {
										addItemNewRoom(temp, j - 1, k + 1, l);
									}
									else if (next_itemID == 1) {
										absorption(temp, 0.78);
										temp->data.Sound.direction_id = getReboundID(direction_id);
										changeReboundSideOfWave(temp);
										addItemNewRoom(temp, j, k, l);
									} else if (next_itemID == 2 && j == 0 && myrank != 2) {
										if (realcountleft == sendrowsleft) {
											int newnum = (sendrowsleft + 2) * 2;
											int (*newptr)[cols] = realloc(sendarrayleft, sizeof * newptr * newnum);
											sendrowsleft = newnum;
											sendarrayleft = newptr;
										}
										int *sendarrayleft_new = prepareArrays(temp, 1);
										for (int var = 0; var < cols; ++var) {
											sendarrayleft[realcountleft][var] = sendarrayleft_new[var];
										}
										++realcountleft;
										removeItem(temp);
									} else {
										removeItem(temp);
									}
								}
								decSoundWithMovement(temp);
								// guckt ob der Sound noch bestehen darf.
								checkSoundValid(temp, j, k, l);
								//Item weitergehen
								//MPI_TYPE_FREE(&mpi_item_node_type);
								temp = temp->next;
							}
						}

						if (getFieldID(j, k, l) == 0) {
							interference(j, k, l); // nach allen verschiebungen überlappungen verrechnen.
						}
					}
				}
			}
			if (run < runs && myrank != 2 && myrank != size - 1) {

				int desti = myrank + 1;
				MPI_Request reqr;
				MPI_Isend(sendarrayright, realcountright * cols, MPI_INT, desti, 14, MPI_COMM_WORLD, &reqr);
				MPI_Wait(&reqr, MPI_STATUS_IGNORE);

				desti = myrank - 1;
				MPI_Request reql;
				MPI_Isend(sendarrayleft, realcountleft * cols, MPI_INT, desti, 14, MPI_COMM_WORLD, &reql);
				MPI_Wait(&reql, MPI_STATUS_IGNORE);

			}
			else if (run < runs && myrank == 2) {
				int desti = myrank + 1;
				MPI_Request reqr;
				MPI_Isend(sendarrayright, realcountright * cols, MPI_INT, desti, 14, MPI_COMM_WORLD, &reqr);
				MPI_Wait(&reqr, MPI_STATUS_IGNORE);
			}
			else if (run < runs && myrank == size - 1) {
				int desti = myrank - 1;
				MPI_Request reql;
				MPI_Isend(sendarrayleft, realcountleft * cols, MPI_INT, desti, 14, MPI_COMM_WORLD, &reql);
				MPI_Wait(&reql, MPI_STATUS_IGNORE);
			}
			//printf("TestR: %d\n", sendrowsright);
			//printf("TestL: %d\n", sendrowsleft);
			//free(sendarrayleft);
			//free(sendarrayright);
			changeRoom(room_new);
			++run;
			//Sync
			int sendready = 1;
			MPI_Send(&sendready, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
			//Takt
			MPI_Recv(&go, 1, MPI_INT, 0, myrank, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		}
	}
	MPI_Barrier(MPI_COMM_WORLD);
	if (myrank == 0) {
		end_t = MPI_Wtime();
		total_t = end_t - start_t;
		printf("Time for executing were: %f seconds\n " , total_t);
		printf("The Matrix was %d * %d * %d\n", x_format, y_format, z_format);
		printf("%s\n", "-----ENGINE STOPPED-----" );
	} else if (myrank == 1) {
		//Visualisation beenden
		FILE *fp;
		fp = fopen("output", "a");
		fprintf(fp, "}" );
		fclose(fp);
	}
	MPI_Finalize();
}

