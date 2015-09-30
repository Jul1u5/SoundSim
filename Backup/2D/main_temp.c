//Change: Wall->Obstacle


#include <stdio.h>
#include <stdlib.h> 
/*#include "soundwavefunction.c"
#include "collsion.c"*/
int x_format;
int y_format;
//Modelierung eines Fragments !
typedef struct{
	//id = 0 -> Sound Item, 1 = Hinderniss, 2 = out of bounds
	int id;
	struct item_node *next;
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
            int freq_6000_10000; // also jeder Frequenzbereich hat ein dB Wert
            int freq_10000_20000;
		   	int dB;
		   	int direction_id;
            int movement = 0 // Anzahl an Verschiebungen, welche die dB Zahl reduziert TODO Methoden.
            int sideofwave = 0;
		} Sound;
		struct{
			float reduce = 0.80; // muss ein Absoprtionsfaktor sein ≥ 1 und für die Frequenz angepasst werden
		} Obstacle;
	} data;
}item_node;
struct item_node *buffer;
struct item_node **room;
struct item_node **room_new;
//neuen Raum erstellen
//Parameter als Feldgröße
void createRoom(int x, int y)
{
	buffer = malloc(sizeof(struct item_node)*x*y);
	room = malloc(sizeof(struct item_node *)*y);
	for(int i = 0; i<y; i++)
	room[i] = &buffer[i*x];
	//provisorisch, alles auf Sound setzen
	for(int j = 0; j<x; ++j)
	{
		for(int k = 0; k<y; ++k)
		{
			room[j][k].next = NULL;
		}
	}
}
//temporärer Raum für neue Pixel
void createRoomNew(int x, int y)
{
	buffer = malloc(sizeof(struct Item)*x*y);
	room_new = malloc(sizeof(struct Item *)*y);
	for(int i = 0; i<y; i++)
	room_new[i] = &buffer[i*x]; 
	//provisorisch
	for(int j = 0; j<x; ++j)
	{
		for(int k = 0; k<y; ++k)
		{
			//Hindernisse aus altem Raum in den neuen übertragen
			if(room[j][k].id!=0)
			{
				room_new[j][k] = room[j][k];
			}else{
				//was kein Hinderniss ist wird auf defaul gesetzt (leerer Sound)
				room_new[j][k].id = 0;
			}
		}
	}
}
int getItemID(int x, int y){
	if(x<x_format && y<y_format && x>=0 && y>=0)
	{
		return room[x][y].id;
	}else return 2;	
}
void setItemID(int x, int y, int id)
{
	if(x<x_format && y<y_format)
	{
		room[x][y].id = id;
	}
}
//den Raum zurückgeben
struct Item getRoom(){
	return ** room;
}

//////////////////
// Anzahl der Teilchenverschiebunngen
/*void increaseMovement(int x, int y){
    if(getItemID(x,y)==0){
        room[x][y].data.Sound.movement += 1; // Funktioniert das so ? =D
    }
}

int getMovement(int x, int y){
    if(getItemID(x,y)==0){
        return room[x][y].data.Sound.movement;
    }
}*/

//////////// Frequenzbereich dB ändern
void setFreq20b40(int x, int y, int value)
{
	if(getItemID(x,y)==0){
		room[x][y].data.Sound.freq_20_40 = value;
	}
}
void setFreq40b100(int x, int y, int value)
{
    if(getItemID(x,y)==0){
        room[x][y].data.Sound.freq_40_100 = value;
    }
}
void setFreq100b150(int x, int y, int value)
{
    if(getItemID(x,y)==0){
        room[x][y].data.Sound.freq_100_150 = value;
    }
}
void setFreq150b400(int x, int y, int value)
{
    if(getItemID(x,y)==0){
        room[x][y].data.Sound.freq_150_400 = value;
    }
}
void setFreq400b1000(int x, int y, int value)
{
    if(getItemID(x,y)==0){
        room[x][y].data.Sound.freq_400_1000 = value;
    }
}
void setFreq1000b2000(int x, int y, int value)
{
    if(getItemID(x,y)==0){
        room[x][y].data.Sound.freq_1000_2000 = value;
    }
}
void setFreq2000b3500(int x, int y, int value)
{
    if(getItemID(x,y)==0){
        room[x][y].data.Sound.freq_2000_3500 = value;
    }
}
void setFreq3500b6000(int x, int y, int value)
{
    if(getItemID(x,y)==0){
        room[x][y].data.Sound.freq_3500_6000 = value;
    }
}
void setFreq6000b10000(int x, int y, int value)
{
    if(getItemID(x,y)==0){
        room[x][y].data.Sound.freq_6000_10000 = value;
    }
}
void setFreq10000b20000(int x, int y, int value)
{
    if(getItemID(x,y)==0){
        room[x][y].data.Sound.freq_10000_20000 = value;
    }
}
///////// Get Methoden

int getFreq20b40(int x, int y)
{
    if(getItemID(x,y)==0){
        return room[x][y].data.Sound.freq_20_40;
    }
}
int getFreq40b100(int x, int y)
{
    if(getItemID(x,y)==0){
        return room[x][y].data.Sound.freq_40_100;
    }
}
int getFreq100b150(int x, int y)
{
    if(getItemID(x,y)==0){
        return room[x][y].data.Sound.freq_100_150;
    }
}
int getFreq150b400(int x, int y)
{
    if(getItemID(x,y)==0){
        return room[x][y].data.Sound.freq_150_400;
    }
}
int getFreq400b1000(int x, int y)
{
    if(getItemID(x,y)==0){
        return room[x][y].data.Sound.freq_400_1000;
    }
}
int getFreq1000b2000(int x, int y)
{
    if(getItemID(x,y)==0){
        return room[x][y].data.Sound.freq_1000_2000;
    }
}
int getFreq2000b3500(int x, int y)
{
    if(getItemID(x,y)==0){
        return room[x][y].data.Sound.freq_2000_3500;
    }
}
int getFreq3500b6000(int x, int y)
{
    if(getItemID(x,y)==0){
        return room[x][y].data.Sound.freq_3500_6000;
    }
}
int getFreq6000b10000(int x, int y)
{
    if(getItemID(x,y)==0){
        return room[x][y].data.Sound.freq_6000_10000;
    }
}
int getFreq10000b20000(int x, int y)
{
    if(getItemID(x,y)==0){
        return room[x][y].data.Sound.freq_10000_20000;
    }
}


////////
void setDirectionID(int x, int y, int value)
{
	if(getItemID(x,y)==0){
		room[x][y].data.Sound.direction_id = value;
	}
}
int getDirectionID(int x, int y)
{
	if(getItemID(x,y)==0){
		return room[x][y].data.Sound.direction_id;
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
struct Item getSound(int x, int y)
{
	return room[x][y];
}
struct Item getObstacle(int x, int y)
{
	return room[x][y];
}
//neuer Raum = temporärer Raum
void changeRoom(struct Item ** newRoom)
{
	room = newRoom;
}
int main (int argc, char *argv[])
{
	x_format = 100;
	y_format = 100;
	//direction_id: 1 = oben, 2 = oben rechts, 3 = rechts, 4 = unten rechts, 5 = unten, 6 = unten links, 7 = links, 8 = links oben, 0 = nichts
	//Ausfallwinkel: 1 -> 5, 2 -> 4, 3 -> 7, 4 -> 2, 5 -> 1, 6 -> 8, 7 -> 3, 8 -> 6
	createRoom(x_format,y_format);
	setFreq20b40(1, 1, 120);
    setFreq40b100(1, 1, 120);
    setFreq100b150(1,1, 120);
    setFreq150b400(1,1,120);
    setFreq400b1000(1,1,120);
    setFreq1000b2000(1,1,120);
    setFreq2000b3500(1,1,120);
    setFreq3500b6000(1,1,120);
    setFreq6000b10000(1,1,120);
    setFreq10000b20000(1,1,120);
	setDirectionID(1, 1, 1);
    
	setFreq20b40(5, 1, 120);
    setFreq40b100(5, 1, 120);
    setFreq100b150(5,1, 120);
    setFreq150b400(5,1,120);
    setFreq400b1000(5,1,120);
    setFreq1000b2000(5,1,120);
    setFreq2000b3500(5,1,120);
    setFreq3500b6000(5,1,120);
    setFreq6000b10000(5,1,120);
    setFreq10000b20000(5,1,120);
	setDirectionID(5, 1, 1);
	setItemID(99, 1, 1);
	setItemID(0, 1, 1);
	//Test: 10 Verschiebungen
	for(int i = 1; i<=100; ++i)
	{
		createRoomNew(x_format,y_format);
		//alle Pixel durchgehen
		for(int j = 0; j<x_format; ++j)
		{
			for(int k = 0; k<y_format; ++k)
			{
				//Prüfen ob Item Sound ist, Wände nicht bewegen
				if(getItemID(j,k)==0)
				{
					//Richtung prüfen
					int direction_id = getDirectionID(j,k);
					if(direction_id==1){
						int next_itemID = getItemID(j+1,k);
						if(next_itemID==0){
							//ist Sound Feld
                            /*addWave(); // Sprung in die Waveunktion
                            //Überprüfen der Überlappungen
							//TODO: Zusammenrechnen von Kollisionen in collision.c
                            interference();*/
							room_new[j+1][k] = getSound(j,k);
                            increaseMovement(j+1,k); // Anzahl der Schritte eines Teilchens
						}else if(next_itemID==1){
							//TODO: Winkel Abprall, Schalldämmung durch Hinderniss in class collision.c
                                //TODO Wenn Kollsion mit itemID 2
                            // absoption(j,k, room_new[j][k].data.Obstacle.reduce);
							//1. Sound an die Folgestelle schieben
							room_new[j][k] = getSound(j,k);
							//2. Attribut der Richtung anpassen
							room_new[j][k].data.Sound.direction_id = getReboundID(direction_id);
						}else if(next_itemID==2)
						{
							//TODO: Sound verlässt die Map, entfernen
                            if( (j||k) > x_format || y_format) || ((j || k) < 0) ){
                                
                                // Buffer noch free'n
                                //delete room_new[j][k].data.Sound;
                            }
						}
					}else if(direction_id==5)
					{
						//nächstes Feld prüfen
						int next_itemID = getItemID(j-1,k);
						if(next_itemID==0){
							//ist Sound Feld
							//TODO: Zusammenrechnen von Kollisionen
							room_new[j-1][k] = getSound(j,k);
						}else if(next_itemID==1){
                            
							//TODO: Winkel Abprall, Schalldämmung durch Hinderniss
							//1. Sound an die Folgestelle schieben
							room_new[j][k] = getSound(j,k);
							//2. Attribut der Richtung anpassen
							room_new[j][k].data.Sound.direction_id = getReboundID(direction_id);
						}else if(next_itemID==2)
						{
                        
						}
					}
				}else{
					//Item ist ein Hinderniss oder verlässt den Raum
				}
			}
		}
		changeRoom(room_new);
	}
	//-------
	//Testausgabe
	int c = 0;
	for(int j = 0; j<x_format; ++j)
	{
		for(int k = 0; k<y_format; ++k)
		{
			printf("feld:x:%d y:%d, ID:%d, directionID:%d\n", j,k, getItemID(j,k), getDirectionID(j,k));
			++c;
		}
	}
	printf("count %d\n", c );
	//-------
	free(room);
	free(buffer);
}