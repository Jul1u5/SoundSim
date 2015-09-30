//Change: Wall->Obstacle
//Return unlogisches Wertes falls keine Sound Objekt: 99999
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "main.h"
#include "soundwavefunction.h"
#include "collision.h"
#include <time.h>
/*
#include "collsion.c"*/
int x_format;
int y_format;
int j,k,i;
//Modelierung eines Fragments !

item_node *buffer;
item_node **room;
item_node **room_new;
//neuen Raum erstellen
//Parameter als Feldgröße
void createRoom(int x, int y)
{
	room = malloc(x * sizeof(item_node *));
	if (NULL == room) {
		printf("zu wenig mem");
	}
	for (j = 0; j < x_format; j++) {
		room[j] = malloc(y * sizeof(item_node));
		if (NULL == room[j]) {
			printf("zu wenig mem");
		}
	}

	for (j = 0; j < x_format; j++) {
		for (k = 0; k < y_format; k++) {
			room[j][k].id = 3;
			room[j][k].next = NULL;
		}
	}
	// buffer = malloc(sizeof(item_node)*x*y);
	// room = malloc(sizeof(item_node *)*y);
	// for(int i = 0; i<x; i++)
	// room[i] = &buffer[i*y];
	// //provisorisch, alles auf Sound setzen
	// for(int j = 0; j<x; ++j)
	// {
	// 	for(int k = 0; k<y; ++k)
	// 	{
	// 		printf("x: %d y: %d \n",j,k );
//          	room[j][k].id = 3;
	// 		room[j][k].next = NULL;
	// 	}
	// }
}
//temporärer Raum für neue Pixel
void createRoomNew(int x, int y)
{
	for(i = 0; i < x_format; i++){
		free(room[i]);
	}free(room_new);

	room_new = malloc(x * sizeof(item_node *));
	if (NULL == room_new) {
		printf("zu wenig mem");
	}
	for (j = 0; j < x_format; j++) {
		room_new[j] = malloc(y * sizeof(item_node));
		if (NULL == room_new[j]) {
			printf("Zu wenig Mem");
		}
	}
	//schöner machen!
	for (j = 0; j < x_format; j++) {
		for (k = 0; k < y_format; k++) {
			if ((room[j][k].next) != NULL) {
				if ((room[j][k].next->id)== 1) {
					room_new[j][k] = room[j][k];
				}else {
				room_new[j][k].id = 3;
				room_new[j][k].next = NULL;
				}
			}
			else {
				room_new[j][k].id = 3;
				room_new[j][k].next = NULL;
			}
		}
	}
	// free(buffer);
	// free(room_new);
	// buffer = malloc(sizeof(item_node) * x * y);
	// room_new = malloc(sizeof(item_node *)*y);
	// for (int i = 0; i < y; i++)
	// 	room_new[i] = &buffer[i * x];
	// //provisorisch
	// for (int j = 0; j < x; ++j)
	// {
	// 	for (int k = 0; k < y; ++k)
	// 	{
	// 		//Hindernisse aus altem Raum in den neuen übertragen
	// 		if (room[j][k].next != NULL) {
	// 			//printf("id: %d\n",room[j][k].next->id );
	// 			if (room[j][k].next->id == 1)
	// 			{
	// 				//dann Hinderniss
	// 				room_new[j][k] = room[j][k];
	// 			}
	// 		} else {
	// 			room_new[j][k].id = 3;
	// 			room[j][k].next = NULL;
	// 		}

	/*if(room[j][k].id==1)
	{
		room_new[j][k] = room[j][k];
	}else{
		//was kein Hinderniss ist wird auf defaul gesetzt (leerer Sound)
		room_new[j][k].id = 0;
	}*/
// }
// }
}
//neuer Raum = temporärer Raum
void changeRoom(item_node ** newRoom)
{
	room = newRoom;
}
int getItemID(item_node *node ) {
	if (node != NULL)
	{
		return node->id;
	} else return 2;
}
void setItemID(item_node *node, int id)
{
	node->id = id;
}
int getFieldID(int x, int y)
{
	int returnvalue = 2;
	if (x < x_format && y < y_format && x >= 0 && y >= 0)
	{
		if (room[x][y].next != NULL) {
			//0 oder 1
			returnvalue = room[x][y].next->id;
		}
		else returnvalue = 3;
		//ohne jeglicher Belegung
	}
	return returnvalue;
}
//den Raum zurückgeben
item_node getRoom() {
	return ** room;
}
bool isObstacle(int x, int y)
{
	bool returnvalue = false;
	if (room[x][y].next != NULL) {
		if (room[x][y].next->id == 1)
		{
			//dann Hinderniss
			returnvalue = true;
		}
	}
	return returnvalue;

}
/////////// Frequenzbereich dB ändern
void setFreq20b40(item_node *node, int value)
{
	if (getItemID(node) == 0) {
		node->data.Sound.freq_20_40 = value;
	}
}
void setFreq40b100(item_node *node, int value)
{
	if (getItemID(node) == 0) {
		node->data.Sound.freq_40_100 = value;
	}
}
void setFreq100b150(item_node *node, int value)
{
	if (getItemID(node) == 0) {
		node->data.Sound.freq_100_150 = value;
	}
}
void setFreq150b400(item_node *node, int value)
{
	if (getItemID(node) == 0) {
		node->data.Sound.freq_150_400 = value;
	}
}
void setFreq400b1000(item_node *node, int value)
{
	if (getItemID(node) == 0) {
		node->data.Sound.freq_400_1000 = value;
	}
}
void setFreq1000b2000(item_node *node, int value)
{
	if (getItemID(node) == 0) {
		node->data.Sound.freq_1000_2000 = value;
	}
}
void setFreq2000b3500(item_node *node, int value)
{
	if (getItemID(node) == 0) {
		node->data.Sound.freq_2000_3500 = value;
	}
}
void setFreq3500b6000(item_node *node, int value)
{
	if (getItemID(node) == 0) {
		node->data.Sound.freq_3500_6000 = value;
	}
}
void setFreq6000b10000(item_node *node, int value)
{
	if (getItemID(node) == 0) {
		node->data.Sound.freq_6000_10000 = value;
	}
}
void setFreq10000b20000(item_node *node, int value)
{
	if (getItemID(node) == 0) {
		node->data.Sound.freq_10000_20000 = value;
	}
}
///////// Get Methoden

int getFreq20b40(item_node *node)
{
	if (getItemID(node) == 0) {
		return node->data.Sound.freq_20_40;
	} else {
		return 99999;
	}
}
int getFreq40b100(item_node *node)
{
	if (getItemID(node) == 0) {
		return node->data.Sound.freq_40_100;
	} else {
		return 99999;
	}
}
int getFreq100b150(item_node *node)
{
	if (getItemID(node) == 0) {
		return node->data.Sound.freq_100_150;
	} else {
		return 99999;
	}
}
int getFreq150b400(item_node *node)
{
	if (getItemID(node) == 0) {
		return node->data.Sound.freq_150_400;
	} else {
		return 99999;
	}
}
int getFreq400b1000(item_node *node)
{
	if (getItemID(node) == 0) {
		return node->data.Sound.freq_400_1000;
	} else {
		return 99999;
	}
}
int getFreq1000b2000(item_node *node)
{
	if (getItemID(node) == 0) {
		return node->data.Sound.freq_1000_2000;
	} else {
		return 99999;
	}
}
int getFreq2000b3500(item_node *node)
{
	if (getItemID(node) == 0) {
		return node->data.Sound.freq_2000_3500;
	} else {
		return 99999;
	}
}
int getFreq3500b6000(item_node *node)
{
	if (getItemID(node) == 0) {
		return node->data.Sound.freq_3500_6000;
	} else {
		return 99999;
	}
}
int getFreq6000b10000(item_node *node)
{
	if (getItemID(node) == 0) {
		return node->data.Sound.freq_6000_10000;
	} else {
		return 99999;
	}
}
int getFreq10000b20000(item_node *node)
{
	if (getItemID(node) == 0) {
		return node->data.Sound.freq_10000_20000;
	} else {
		return 99999;
	}
}

////////
void setDirectionID(item_node *node, int value)
{
	if (getItemID(node) == 0) {
		node->data.Sound.direction_id = value;
	}
}
int getDirectionID(item_node *node)
{
	if (getItemID(node) == 0) {
		return node->data.Sound.direction_id;
	} else return -1;
}
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
item_node getSound(item_node *node)
{
	//Absicherung fehlt
	return *node;
}
item_node getObstacle(item_node *node)
{
	//Absicherung fehlt
	return *node;
}
item_node *getItem_Root(int x, int y)
{
	if (x < x_format && y < y_format && x >= 0 && y >= 0)
	{
		return &room[x][y];
	} else {
		item_node* newNode = malloc(sizeof(item_node));
		newNode->id = 2;
		newNode->next = NULL;
		return newNode;
		//Element erstellen mit id 2 -> ungültig und wird dann entfernt
	}
}
//Create Item
item_node* createItem (int x, int y, int id)
{
	item_node* selected = getItem_Root(x, y);
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
		setMovement(selected, 0);
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
void removeItem(item_node *node) {
	if (node->next == NULL) {
		//letztes item: vorletztes next->NULL
		if(node->prev == NULL){
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
item_node* addItem (item_node *node, int x, int y)
{
	item_node* selected = getItem_Root(x, y);
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
item_node *getItem_RootNewRoom(int x, int y)
{
	if (x < x_format && y < y_format && x >= 0 && y >= 0)
	{
		return &room_new[x][y];
	} else {
		item_node* newNode = malloc(sizeof(item_node));
		newNode->id = 2;
		newNode->next = NULL;
		return newNode;
		//Element erstellen mit id 2 -> ungültig und wird dann entfernt
	}
}
void addItemNewRoom (item_node *node, int x, int y)
{
	item_node* selected = getItem_RootNewRoom(x, y);

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
int isSoundField(int x, int y)
{
	int returnvalue = 0;
	if (x < x_format && y < y_format && x >= 0 && y >= 0)
	{
		if (room[x][y].next != NULL) {
			//0 oder 1
			if (room[x][y].next->id == 0)
			{
				returnvalue = 1;
			}
		}
		else returnvalue = 1;
		//ohne jeglicher Belegung
	}
	return returnvalue;
}

clock_t clock(void);

int main (int argc, char *argv[])
{
	double start_t, end_t, total_t;

	printf("%s\n", "-----STARTING THE ENGINE-----" );

	start_t = clock();  //Startzeit

	x_format = 100;
	y_format = 100;

	createRoom(x_format, y_format);

	/*for(int k=0; k<x_format; k++){
		item_node *itemA = createItem(x_format-1,k,1);
		item_node *itemB = createItem(k,1,1);
		item_node *itemC = createItem(1,k,1);
		item_node *itemD = createItem(y_format-1,k,1);
	}*/
	printf("id #1: %d\n", getFieldID(50, 50) );
	item_node *itemtest1 = createItem(10, 20, 0);
	item_node *itemtest2 = createItem(50, 50, 0);
	item_node *itemtest3 = createItem(50, 30, 1);

	item_node *itemtest4 = createItem(10, 21, 0);
	setDirectionID(itemtest4, 1);
	//item_node *itemtest3 = createItem(5,1,0);
	//item_node *itemtest4 = createItem(5,1,0);
	//setFreq10000b20000(itemtest3,80);
	//setFreq10000b20000(itemtest4,40);


	setFreq20b40(itemtest1, 70);
	setFreq40b100(itemtest1, 70);
	setFreq100b150(itemtest1, 70);
	setFreq150b400(itemtest1, 70);
	setFreq400b1000(itemtest1, 70);
	setFreq1000b2000(itemtest1, 70);
	setFreq2000b3500(itemtest1, 70);
	setFreq3500b6000(itemtest1, 70);
	setFreq6000b10000(itemtest1, 70);
	setFreq10000b20000(itemtest1, 70);

	setFreq20b40(itemtest2, 100);
	setFreq40b100(itemtest2, 100);
	setFreq100b150(itemtest2, 100);
	setFreq150b400(itemtest2, 100);
	setFreq400b1000(itemtest2, 100);
	setFreq1000b2000(itemtest2, 100);
	setFreq2000b3500(itemtest2, 90);
	setFreq3500b6000(itemtest2, 90);
	setFreq6000b10000(itemtest2, 97);
	setFreq10000b20000(itemtest2, 89);

	setDirectionID(itemtest1, 1);
	setDirectionID(itemtest2, 4);
	setSideOfWave(itemtest2, 0);
	setSideOfWave(itemtest1, 0);
	printf("id #2: %d\n", getFieldID(50, 50) );
	removeItem(itemtest2);
	printf("id #3: %d\n", getFieldID(50, 50) );
	//setDirectionID(itemtest3,1);
	//setDirectionID(itemtest4,1);


	/*item_node *temp;
	temp = getItem_Root(0,5);
	while(temp != NULL){
	    printf("lol: %d\n",temp->id);
	    if(temp->id != 3){
	    	printf("freq: %d\n", getFreq10000b20000(temp));
	    }
	    temp = temp->next;
	}*/
	for (int i = 1; i <= 100; ++i)
	{
		createRoomNew(x_format, y_format);
		//alle Pixel durchgehen
		for (int j = 0; j < x_format; ++j)
		{
			for (int k = 0; k < y_format; ++k)
			{
				//NEU: Alle Items auf einem Feld durchgehen WENN KEIN Hinderniss
				if (isObstacle(j, k) == false)
				{
					//kein Hinderniss -> fortfahren
					item_node *temp;
					temp = getItem_Root(j, k);
					while (temp != NULL) {
						//printf("%d\n",temp->id);
						//Richtung prüfen
						int direction_id = getDirectionID(temp);
						//printf("%d\n",direction_id );
						//TODO: Besser nur bei Sound Objekten
						increaseMovement(temp);
						if (direction_id == 1) {
							//TODO: Diese Zeile brauchen wir garnicht!
							item_node* next_item = getItem_Root(j, k + 1);
							int next_itemID = getFieldID(j, k + 1);
							//increaseMovement(temp);
							//printf("x:%d y:%d freq: %d, hoch: %d\n",j, k, getFreq10000b20000(temp) , next_itemID );

							if (next_itemID == 0 || next_itemID == 3) {
								//ist Sound Feld
								//interference(temp,j,k);
								//Überprüfen der Überlappungen
								//TODO: Zusammenrechnen von Kollisionen in collision.c
								addItemNewRoom(temp, j, k + 1);
								//room_new[j+1][k] = temp;
							} else if (next_itemID == 1) {
								//Seitenzugehörigkeit wird geändert
								//TODO Wenn Kollsion mit itemID 2
								absorption(temp, j, k, 0.78);
								//1. Sound an die Folgestelle schieben
								addItemNewRoom(temp, j, k);
								//room_new[j][k] = getSound(j,k);
								//2. Attribut der Richtung anpassen
								temp->data.Sound.direction_id = getReboundID(direction_id);
								//room_new[j][k].data.Sound.direction_id = getReboundID(direction_id);
								changeReboundSideOfWave(temp);
							} else if (next_itemID == 2)
							{
								//printf("Sound wird entfernt\n");
								//TODO: Sound verlässt die Map, entfernen
								//error drin
								// Buffer noch free'n
								//TODO: Pointer umsetzen
								//delete room_new[j][k].data.Sound;
							}
						} else if (direction_id == 5)
						{
							//nächstes Feld prüfen
							item_node* next_item = getItem_Root(j, k - 1);
							int next_itemID = getFieldID(j, k - 1);
							//printf("freq: %d, runter: %d\n", getFreq10000b20000(temp) ,next_itemID );
							//int next_itemID = getItemID(j-1,k);
							if (next_itemID == 0 || next_itemID == 3) {
								//ist Sound Feld
								//TODO: Zusammenrechnen von Kollisionen
								//interference(temp,j,k);

								addItemNewRoom(temp, j, k - 1);
								//room_new[j-1][k] = getSound(j,k);
							} else if (next_itemID == 1) {

								//TODO: Winkel Abprall, Schalldämmung durch Hinderniss
								//1. Sound an die Folgestelle schieben

								addItemNewRoom(temp, j, k);
								//room_new[j][k] = getSound(j,k);
								absorption(temp, j, k, 0.78);
								//2. Attribut der Richtung anpassen
								temp->data.Sound.direction_id = getReboundID(direction_id);
								//room_new[j][k].data.Sound.direction_id = getReboundID(direction_id);
								changeReboundSideOfWave(temp);
							} else if (next_itemID == 2)
							{

							}
						}
						checkSoundValid(temp, j, k); // Damit er keine 0dB Elemente zu Wellen macht
						addWave(temp, j, k); // Sprung in die Waveunktion
						//decSoundWithMovement(temp);
						// guckt ob der Sound noch bestehen darf.
						checkSoundValid(temp, j, k);
						//Item weitergehen
						temp = temp->next;
					}
					//interference(j,k); // nach allen verschiebungen überlappungen verrechnen.
				}
			}
		}
		changeRoom(room_new);
	}


	end_t = clock();
	total_t = (double)(end_t - start_t ) / CLOCKS_PER_SEC;
	printf("Time for executing was: %f\n " , total_t);
	printf("The Matrix was %d * %d", x_format,y_format);


	/*int id = getItemID(itemtest);
	printf("%d\n", 2 );*/
	printf("%s\n", "----");

	//createRoomNew(x_format,y_format);
	//changeRoom(room_new);
	free(room);
	free(buffer);
}