//Change: Wall->Obstacle
//Return unlogisches Wertes falls keine Sound Objekt: 99999
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "main.h"
#include "soundwavefunction.h"
/*
#include "collsion.c"*/
int x_format;
int y_format;
//Modelierung eines Fragments !

item_node *buffer;
item_node **room;
item_node **room_new;
//neuen Raum erstellen
//Parameter als Feldgröße
void createRoom(int x, int y)
{
	buffer = malloc(sizeof(item_node)*x*y);
	room = malloc(sizeof(item_node *)*y);
	for(int i = 0; i<y; i++)
	room[i] = &buffer[i*x];
	//provisorisch, alles auf Sound setzen
	for(int j = 0; j<x; ++j)
	{
		for(int k = 0; k<y; ++k)
		{
          	room[j][k].id = 3;
			room[j][k].next = NULL;
		}
	}
}
//temporärer Raum für neue Pixel
void createRoomNew(int x, int y)
{
	buffer = malloc(sizeof(item_node)*x*y);
	room_new = malloc(sizeof(item_node *)*y);
	for(int i = 0; i<y; i++)
	room_new[i] = &buffer[i*x]; 
	//provisorisch
	for(int j = 0; j<x; ++j)
	{
		for(int k = 0; k<y; ++k)
		{
			//Hindernisse aus altem Raum in den neuen übertragen
			if(room[j][k].next != NULL){
				//printf("id: %d\n",room[j][k].next->id );
				if(room[j][k].next->id == 1)
				{
					//dann Hinderniss
					room_new[j][k] = room[j][k];
				}
			}else{
				room_new[j][k].id = 3;
			}
			
			/*if(room[j][k].id==1)
			{
				room_new[j][k] = room[j][k];
			}else{
				//was kein Hinderniss ist wird auf defaul gesetzt (leerer Sound)
				room_new[j][k].id = 0;
			}*/
		}
	}
}
//neuer Raum = temporärer Raum
void changeRoom(item_node ** newRoom)
{
	room = newRoom;
}
int getItemID(item_node *node ){
	if(node != NULL)
	{
		return node->id;
	}else return 2;	
}
void setItemID(item_node *node, int id)
{
	node->id = id;
}
int getFieldID(int x, int y)
{
	int returnvalue = 2;
	if(x<x_format && y<y_format && x>=0 && y>=0)
	{
		if(room[x][y].next != NULL){
			//0 oder 1
			returnvalue = room[x][y].next->id;
		}
		else returnvalue = 3;
		//ohne jeglicher Belegung
	}
	return returnvalue;
}
//den Raum zurückgeben
item_node getRoom(){
	return ** room;
}
bool isObstacle(int x, int y)
{
	bool returnvalue = false;
	if(room[x][y].next != NULL){
		if(room[x][y].next->id == 1)
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
	if(getItemID(node)==0){
    	node->data.Sound.freq_20_40 = value;
    }
}
void setFreq40b100(item_node *node, int value)
{
	if(getItemID(node)==0){
    	node->data.Sound.freq_40_100 = value;
    }
}
void setFreq100b150(item_node *node, int value)
{
	if(getItemID(node)==0){
    	node->data.Sound.freq_100_150 = value;
    }
}
void setFreq150b400(item_node *node, int value)
{
	if(getItemID(node)==0){
    	node->data.Sound.freq_150_400 = value;
    }
}
void setFreq400b1000(item_node *node, int value)
{
	if(getItemID(node)==0){
    	node->data.Sound.freq_400_1000 = value;
    }
}
void setFreq1000b2000(item_node *node, int value)
{
	if(getItemID(node)==0){
    	node->data.Sound.freq_1000_2000 = value;
    }
}
void setFreq2000b3500(item_node *node, int value)
{
	if(getItemID(node)==0){
    	node->data.Sound.freq_2000_3500 = value;
    }
}
void setFreq3500b6000(item_node *node, int value)
{
	if(getItemID(node)==0){
    	node->data.Sound.freq_3500_6000 = value;
    }
}
void setFreq6000b10000(item_node *node, int value)
{
	if(getItemID(node)==0){
    	node->data.Sound.freq_6000_10000 = value;
    }
}
void setFreq10000b20000(item_node *node, int value)
{
	if(getItemID(node)==0){
    	node->data.Sound.freq_10000_20000 = value;
    }
}
///////// Get Methoden

int getFreq20b40(item_node *node)
{
	if(getItemID(node)==0){
    	return node->data.Sound.freq_20_40;
    }else{
    	return 99999;
    }
}
int getFreq40b100(item_node *node)
{
	if(getItemID(node)==0){
    	return node->data.Sound.freq_40_100;
    }else{
    	return 99999;
    }
}
int getFreq100b150(item_node *node)
{
	if(getItemID(node)==0){
    	return node->data.Sound.freq_100_150;
    }else{
    	return 99999;
    }
}
int getFreq150b400(item_node *node)
{
	if(getItemID(node)==0){
    	return node->data.Sound.freq_150_400;
    }else{
    	return 99999;
    }
}
int getFreq400b1000(item_node *node)
{
	if(getItemID(node)==0){
    	return node->data.Sound.freq_400_1000;
    }else{
    	return 99999;
    }
}
int getFreq1000b2000(item_node *node)
{
	if(getItemID(node)==0){
    	return node->data.Sound.freq_1000_2000;
    }else{
    	return 99999;
    }
}
int getFreq2000b3500(item_node *node)
{
	if(getItemID(node)==0){
    	return node->data.Sound.freq_2000_3500;
    }else{
    	return 99999;
    }
}
int getFreq3500b6000(item_node *node)
{
	if(getItemID(node)==0){
    	return node->data.Sound.freq_3500_6000;
    }else{
    	return 99999;
    }
}
int getFreq6000b10000(item_node *node)
{
	if(getItemID(node)==0){
    	return node->data.Sound.freq_6000_10000;
    }else{
    	return 99999;
    }
}
int getFreq10000b20000(item_node *node)
{
	if(getItemID(node)==0){
    	return node->data.Sound.freq_10000_20000;
    }else{
    	return 99999;
    } 
}

////////
void setDirectionID(item_node *node, int value)
{
	if(getItemID(node)==0){
		node->data.Sound.direction_id = value;
	}
}
int getDirectionID(item_node *node)
{
	if(getItemID(node)==0){
		return node->data.Sound.direction_id;
	}else return 9;
}
int getReboundID(int currentDirectionID)
{
	switch(currentDirectionID)
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
	if(x<x_format && y<y_format && x>=0 && y>=0)
	{
		return &room[x][y];
	}else{
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
	item_node* selected = getItem_Root(x,y);
	while(selected->next != NULL)
            selected = selected->next;
   	selected->next = malloc(sizeof(item_node));
    selected = selected->next;
    selected->id = id; 
    selected->next = NULL;
    return selected;

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
void addItem (item_node *node, int x, int y)
{
	item_node* selected = getItem_Root(x,y);
	//item_node* selected = &room[x][y];
    while(selected->next != NULL)
        selected = selected->next;
    selected->next = node;
    selected = selected->next;
    selected->next = NULL;
}
item_node *getItem_RootNewRoom(int x, int y)
{
	if(x<x_format && y<y_format && x>=0 && y>=0)
	{
		return &room_new[x][y];
	}else{
		item_node* newNode = malloc(sizeof(item_node));
		newNode->id = 2;
		newNode->next = NULL;
		return newNode;
		//Element erstellen mit id 2 -> ungültig und wird dann entfernt
	}
}
void addItemNewRoom (item_node *node, int x, int y)
{
	item_node* selected = getItem_RootNewRoom(x,y);
	//item_node* selected = &room[x][y];
    while(selected->next != NULL)
        selected = selected->next;
    selected->next = node;
    selected = selected->next;
    selected->next = NULL;
}
int main (int argc, char *argv[])
{
	x_format = 11;
	y_format = 11;

	createRoom(x_format,y_format);
	item_node *itemtest1 = createItem(10,1,1);
	item_node *itemtest2 = createItem(0,1,1);
	item_node *itemtest3 = createItem(5,1,0);
	item_node *itemtest4 = createItem(5,1,0);
	setFreq10000b20000(itemtest3,10000);
	setFreq10000b20000(itemtest4,11100);
	setDirectionID(itemtest3,1);
	setDirectionID(itemtest4,1);
	item_node *temp;
	temp = getItem_Root(5,1);
	while(temp != NULL){
	    printf("lol: %d\n",temp->id);
	    if(temp->id != 3){
	    	printf("freq: %d\n", getFreq10000b20000(temp));
	    }
	    temp = temp->next;
	}
	for(int i = 1; i<=100; ++i)
	{
		createRoomNew(x_format,y_format);
		//alle Pixel durchgehen
		for(int j = 0; j<x_format; ++j)
		{
			for(int k = 0; k<y_format; ++k)
			{
				//NEU: Alle Items auf einem Feld durchgehen WENN KEIN Hinderniss
				if(isObstacle(j,k)==false)
				{
					//kein Hinderniss -> fortfahren
					item_node *temp;
					item_node backup;
					temp = getItem_Root(j,k);
			    	while(temp != NULL){
			    		//printf("%d\n",temp->id);
			    		//Richtung prüfen
						int direction_id = getDirectionID(temp);
						//printf("%d\n",direction_id );
						if(direction_id==1){
							item_node* next_item = getItem_Root(j+1,k);
							int next_itemID = getFieldID(j+1,k);
							printf("freq: %d, hoch: %d\n",getFreq10000b20000(temp) , next_itemID );
							if(next_itemID==0 || next_itemID==3){
								//ist Sound Feld
	                            // addWave(temp,j,k); // Sprung in die Waveunktion
	                            //Überprüfen der Überlappungen
								//TODO: Zusammenrechnen von Kollisionen in collision.c
	                            //interference();
								
	                            addItemNewRoom(temp, j+1, k);
								//room_new[j+1][k] = temp;
	                            //increaseMovement(j+1,k); // Anzahl der Schritte eines Teilchens
							}else if(next_itemID==1){
								//TODO: Winkel Abprall, Schalldämmung durch Hinderniss in class collision.c
	                            //TODO Wenn Kollsion mit itemID 2
	                            //absoption(j,k, room_new[j][k].data.Wall.reduce);
								//1. Sound an die Folgestelle schieben
								
								addItemNewRoom(temp, j, k);
								//room_new[j][k] = getSound(j,k);
								//2. Attribut der Richtung anpassen
								temp->data.Sound.direction_id = getReboundID(direction_id);
								//room_new[j][k].data.Sound.direction_id = getReboundID(direction_id);
							}else if(next_itemID==2)
							{
								//TODO: Sound verlässt die Map, entfernen
								//error drin
	                            //if( (j||k) > x_format || y_format) || ((j || k) < 0) ){
	                                
	                                // Buffer noch free'n
									//TODO: Pointer umsetzen
	                                //delete room_new[j][k].data.Sound;
	                            //}
							}
						}else if(direction_id==5)
						{
							//nächstes Feld prüfen
							item_node* next_item = getItem_Root(j-1,k);
							int next_itemID = getFieldID(j-1,k);
							printf("freq: %d, runter: %d\n", getFreq10000b20000(temp) ,next_itemID );
							//int next_itemID = getItemID(j-1,k);
							if(next_itemID==0 || next_itemID==3){
								//ist Sound Feld
								//TODO: Zusammenrechnen von Kollisionen
							
								addItemNewRoom(temp, j-1, k);
								//room_new[j-1][k] = getSound(j,k);
							}else if(next_itemID==1){
	                            
								//TODO: Winkel Abprall, Schalldämmung durch Hinderniss
								//1. Sound an die Folgestelle schieben
								
								addItemNewRoom(temp, j, k);
								//room_new[j][k] = getSound(j,k);
								//2. Attribut der Richtung anpassen
								temp->data.Sound.direction_id = getReboundID(direction_id);
								//room_new[j][k].data.Sound.direction_id = getReboundID(direction_id);
							}else if(next_itemID==2)
							{
	                        
							}
						}
						//Item weitergehen
			        	temp = temp->next;
			        }
			    }
			}
		}
		changeRoom(room_new);
	}




	/*int id = getItemID(itemtest);
	printf("%d\n", 2 );*/
	printf("%s\n", "----");

    //createRoomNew(x_format,y_format);
    //changeRoom(room_new);

	free(room);
	free(buffer);
}