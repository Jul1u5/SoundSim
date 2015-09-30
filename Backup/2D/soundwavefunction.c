#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "soundwavefunction.h"

// Anzahl der Teilchenverschiebunngen
void increaseMovement(item_node *node) {
    if (getItemID(node) == 0) {
        node->data.Sound.movement++;
    }
}

int getMovement(item_node *node) {
    if (getItemID(node) == 0) {
        return node->data.Sound.movement;
    } else {
        return -1;
    }
}

void setMovement(item_node *node, int m) {
    if (getItemID(node) == 0) {
        node->data.Sound.movement = m;
    }
}

void copyMovement(item_node *node, item_node *newnode) {
    // Fällt sicherlich mit addItem Weg
    if (getItemID(node) == 0) {
        setMovement(newnode, getMovement(node));
    }
}

void setWaveRoot(item_node *node, item_node *rootnode) {
    if (getItemID(node) == 0) {
        node->data.Sound.waveroot = rootnode;
    }
}

item_node * getWaveRoot(item_node *node) {
    if (getItemID(node) == 0) {
        return node->data.Sound.waveroot;
    }
    else
    {
        return NULL;
    }
}

void decSoundWithMovement(item_node *node) {
    if (getItemID(node) == 0) {
        setFreq20b40(node, getFreq20b40(node) - getMovement(node));
        setFreq40b100(node, getFreq40b100(node) - getMovement(node));
        setFreq100b150(node, getFreq100b150(node) - getMovement(node));
        setFreq150b400(node, getFreq150b400(node) - getMovement(node));
        setFreq400b1000(node, getFreq400b1000(node) - getMovement(node));
        setFreq1000b2000(node, getFreq1000b2000(node) - getMovement(node));
        setFreq2000b3500(node, getFreq2000b3500(node) - getMovement(node));
        setFreq3500b6000(node, getFreq3500b6000(node) - getMovement(node));
        setFreq6000b10000(node, getFreq6000b10000(node) - getMovement(node));
        setFreq10000b20000(node, getFreq10000b20000(node) - getMovement(node));
    }
}


// Seite der "Welle" 0 = nicht von betroffen , 1 == Links , 2 = Rechts
void setSideOfWave(item_node *node, int side) {
    if (getItemID(node) == 0) {
        node->data.Sound.sideofwave = side;
    }
}

int getSideOfWave(item_node *node) {
    if (getItemID(node) == 0) {
        return node->data.Sound.sideofwave;
    } else {
        return -1;
    }
}

void changeReboundSideOfWave(item_node *node)
{
    if (getSideOfWave(node) == 1)
// der Rebound der Teilchen muss auch die Seitenzugehörigkeit ändern.
    {
        setSideOfWave(node, 2);
    }
    else if (getSideOfWave(node) == 2) {
        setSideOfWave(node, 1);
    }
    else if (getSideOfWave(node) == 0) {
        setSideOfWave(node, 0);
    }
    else {
        setSideOfWave(node, 3);
    }
}

void setFreqAll(item_node *node, item_node *newnode) {

    float reduction = 0.96; // Wert der die anderen Teilchen schwächt.

    setFreq20b40(newnode, getFreq20b40(node) * reduction);
    setFreq40b100(newnode, getFreq40b100(node) * reduction);
    setFreq100b150(newnode, getFreq100b150(node) * reduction);
    setFreq150b400(newnode, getFreq150b400(node) * reduction);
    setFreq400b1000(newnode, getFreq400b1000(node) * reduction);
    setFreq1000b2000(newnode, getFreq1000b2000(node) * reduction);
    setFreq2000b3500(newnode, getFreq2000b3500(node) * reduction);
    setFreq3500b6000(newnode, getFreq3500b6000(node) * reduction);
    setFreq6000b10000(newnode, getFreq6000b10000(node) * reduction);
    setFreq10000b20000(newnode, getFreq10000b20000(node) * reduction);
}


void addWave(item_node *temp, int x, int y)
/*
 addwave lässt die Welle bis zu einer bestimmten Verschiebungsweite ungekrümmt, danach werden die resultierenden
 Teilchen "Kugelfunktionsartig" erzeugt und haben eine zugehörgkeit zur rechten oder linken Seite.
 */
{
    item_node *tempAdd; // ein temporäres Teilchen was hinzugefügt wird.

    if (getItemID(temp) == 0)
    {
        // Wenn das Hauptteilchen noch nicht weit genug gewandert ist, bleibt die Welle ungekrümmt.
        // Teichen erzeugt 2 Nahcbarn die die Wellenausbreitung Linear darstellen.
        if (getMovement(temp) < 3)
        {
            // oben
            if (getDirectionID(temp) == 1)
            {
                if ((getSideOfWave(temp) == 0))
                {
                    //next_itemID==0 || next_itemID==3
                    if (isSoundField(x + 1, y) == 1)
                    {
                        printf("Bewegungen: %d \n ", getMovement(temp));
                        //tempAdd = addItem(temp, x+1,y);
                        //tempAdd = addItem(temp, x,y+1);
                        tempAdd = createItem(x + 1, y, 0); // Neues Teilchen der rechten Seite
                        setSideOfWave(tempAdd, 2); // der Zelle wird eine Zugehörigkeit zur Rechtenseite = 2
                        setDirectionID(tempAdd, getDirectionID(temp));
                        setWaveRoot(tempAdd, temp);
                        copyMovement(temp, tempAdd);
                        setFreqAll(temp, tempAdd);
                        printf("Haupt Rechte Seite,Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                        printf("Position temp %d ,%d \n", x , y);
                        printf("Position tempAdd %d ,%d \n", x + 1 , y);
                    } if (isSoundField(x + 1, y) != 1) {
                        printf("Not a Place to Create a Soundwaveparticle");
                    }

                }

                if (isSoundField(x - 1, y) == 1)
                {
                    tempAdd = addItem(temp, x - 1, y);
                    //tempAdd = createItem(x-1, y, 0); // neues Teilchen der linken Seite
                    setSideOfWave(tempAdd, 1);
                    setDirectionID(tempAdd, getDirectionID(temp));
                    setWaveRoot(tempAdd, temp);
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("Haupt Linke Seite, Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                    printf("Position temp %d ,%d \n", x , y);
                    printf("Position tempAdd %d ,%d \n", x - 1 , y);
                } else if(isSoundField(x - 1,y) != 1){}
            }
            // linke Seite
            else if (getSideOfWave(temp) == 1)
            {
                if (isSoundField(x - 1, y) == 1)
                {
                    printf("Bewegungen: %d \n ", getMovement(temp));
                    //tempAdd = addItem(temp, x-1,y);
                    tempAdd = createItem(x - 1, y, 0); // neues Teilchen der linken Seite
                    setSideOfWave(tempAdd, 1);
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("Left Linke Seite, Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                    printf("Position temp %d ,%d \n", x , y);
                    printf("Position tempAdd %d ,%d \n", x - 1 , y);
                } else if(isSoundField(x - 1,y) != 1){}
            }
            //Rechte Seitenzugehörigkeit
            else if (getSideOfWave(temp) == 2)
            {
                if (isSoundField(x + 1, y) == 1)
                {
                    printf("Bewegungen: %d \n ", getMovement(temp));
                    //tempAdd = addItem(temp, x+1,y);
                    //tempAdd = addItem(temp, x,y+1);
                    tempAdd = createItem(x + 1, y, 0); // Neues Teilchen der rechten Seite
                    setSideOfWave(tempAdd, 2); // der Zelle wird eine Zugehörigkeit zur Rechtenseite = 2
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("Right Rechte Seite ,Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                    printf("Position temp %d ,%d \n", x , y);
                    printf("Position tempAdd %d ,%d \n", x + 1 , y);
                } else if(isSoundField(x + 1,y) != 1){}
            }
        }
        else if ( getDirectionID(temp) == 2)
        {
            // Nach oben rechts
            if ((getSideOfWave(temp) == 0))
            {
                //next_itemID==0 || next_itemID==3
                if (isSoundField(x + 1, y - 1) == 1)
                {
                    //tempAdd = addItem(temp, x+1,y);
                    //tempAdd = addItem(temp, x,y+1);
                    tempAdd = createItem(x + 1, y - 1, 0); // Neues Teilchen der rechten Seite
                    setSideOfWave(tempAdd, 2); // der Zelle wird eine Zugehörigkeit zur Rechtenseite = 2
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("Haupt Rechte Seite,Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                } else if(isSoundField(x + 1,y - 1) != 1){}
                if (isSoundField(x - 1, y + 1) == 1)
                {
                    tempAdd = addItem(temp, x - 1, y + 1);
                    //tempAdd = createItem(x-1, y, 0); // neues Teilchen der linken Seite
                    setSideOfWave(tempAdd, 1);
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("Haupt Linke Seite, Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                } else if(isSoundField(x - 1,y + 1) != 1){}

            }
            // linke Seite
            // Wenn du kein Seitenteil bist oder zur Linken seite gehörst
            else if (getSideOfWave(temp) == 1)
            {
                if (isSoundField(x - 1, y + 1) == 1)
                {
                    //tempAdd = addItem(temp, x-1,y);
                    tempAdd = createItem(x - 1, y + 1, 0); // neues Teilchen der linken Seite
                    setSideOfWave(tempAdd, 1);
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("Left Linke Seite, Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                } else if(isSoundField(x - 1,y + 1) != 1){}
            }
            //Rechte Seitenzugehörigkeit
            else if (getSideOfWave(temp) == 2)
            {
                if (isSoundField(x + 1, y - 1) == 1)
                {
                    //tempAdd = addItem(temp, x+1,y);
                    //tempAdd = addItem(temp, x,y+1);
                    tempAdd = createItem(x + 1, y - 1, 0); // Neues Teilchen der rechten Seite
                    setSideOfWave(tempAdd, 2); // der Zelle wird eine Zugehörigkeit zur Rechtenseite = 2
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("Right Rechte Seite,Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                } else if(isSoundField(x + 1,y - 1) != 1){}
            }
        }
        else if ( getDirectionID(temp) == 3) {
            // Nach Rechts
            if ((getSideOfWave(temp) == 0))
            {
                //next_itemID==0 || next_itemID==3
                if (isSoundField(x, y + 1) == 1)
                {
                    //tempAdd = addItem(temp, x+1,y);
                    //tempAdd = addItem(temp, x,y+1);
                    tempAdd = createItem(x, y + 1, 0); // Neues Teilchen der rechten Seite
                    setSideOfWave(tempAdd, 2); // der Zelle wird eine Zugehörigkeit zur Rechtenseite = 2
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("Haupt Rechte Seite,Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                } else if(isSoundField(x,y + 1) != 1){}
                if (isSoundField(x, y - 1) == 1)
                {
                    tempAdd = addItem(temp, x, y - 1);
                    //tempAdd = createItem(x-1, y, 0); // neues Teilchen der linken Seite
                    setSideOfWave(tempAdd, 1);
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd); copyMovement(temp, tempAdd);
                    printf("Haupt Linke Seite, Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                } else if(isSoundField(x,y - 1) != 1){}

            }
            // linke Seite
            // Wenn du kein Seitenteil bist oder zur Linken seite gehörst
            else if (getSideOfWave(temp) == 1)
            {
                if (isSoundField(x, y - 1) == 1)
                {
                    //tempAdd = addItem(temp, x-1,y);
                    tempAdd = createItem(x - 1, y, 0); // neues Teilchen der linken Seite
                    setSideOfWave(tempAdd, 1);
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("Left Linke Seite, Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                } else if(isSoundField(x - 1,y) != 1){}
            }
            //Rechte Seitenzugehörigkeit
            else if (getSideOfWave(temp) == 2)
            {
                if (isSoundField(x, y + 1) == 1)
                {
                    //tempAdd = addItem(temp, x+1,y);
                    //tempAdd = addItem(temp, x,y+1);
                    tempAdd = createItem(x + 1, y, 0); // Neues Teilchen der rechten Seite
                    setSideOfWave(tempAdd, 2); // der Zelle wird eine Zugehörigkeit zur Rechtenseite = 2
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("Right Rechte Seite,Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                } else if(isSoundField(x,y + 1) != 1){}
            }
        }
        else if ( getDirectionID(temp) == 4)
        {
            // unten rechts
            if ((getSideOfWave(temp) == 0))
            {
                //next_itemID==0 || next_itemID==3
                if (isSoundField(x - 1, y - 1) == 1)
                {
                    //tempAdd = addItem(temp, x+1,y);
                    //tempAdd = addItem(temp, x,y+1);
                    tempAdd = createItem(x - 1, y - 1, 0); // Neues Teilchen der rechten Seite
                    setSideOfWave(tempAdd, 2); // der Zelle wird eine Zugehörigkeit zur Rechtenseite = 2
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("Haupt Rechte Seite,Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                } else if(isSoundField(x - 1,y - 1) != 1){}
                if (isSoundField(x + 1, y + 1) == 1)
                {
                    tempAdd = addItem(temp, x + 1, y + 1);
                    //tempAdd = createItem(x-1, y, 0); // neues Teilchen der linken Seite
                    setSideOfWave(tempAdd, 1);
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("Haupt Linke Seite, Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                } else if(isSoundField(x + 1,y + 1) != 1){}

            }
            // linke Seite
            // Wenn du kein Seitenteil bist oder zur Linken seite gehörst
            else if (getSideOfWave(temp) == 1)
            {
                if (isSoundField(x + 1, y + 1) == 1)
                {
                    //tempAdd = addItem(temp, x-1,y);
                    tempAdd = createItem(x - 1, y - 1, 0); // neues Teilchen der linken Seite
                    setSideOfWave(tempAdd, 1);
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("Left Linke Seite, Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                } else if(isSoundField(x + 1,y + 1) != 1){}
            }
            //Rechte Seitenzugehörigkeit
            else if (getSideOfWave(temp) == 2)
            {
                if (isSoundField(x + 1, y + 1) == 1)
                {
                    //tempAdd = addItem(temp, x+1,y);
                    //tempAdd = addItem(temp, x,y+1);
                    tempAdd = createItem(x + 1, y + 1, 0); // Neues Teilchen der rechten Seite
                    setSideOfWave(tempAdd, 2); // der Zelle wird eine Zugehörigkeit zur Rechtenseite = 2
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("Right Rechte Seite,Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                } else if(isSoundField(x + 1,y + 1) != 1){}
            }
        }
        else if ( getDirectionID(temp) == 5) {
            //unten
            if ((getSideOfWave(temp) == 0))
            {
                //next_itemID==0 || next_itemID==3
                if (isSoundField(x - 1, y) == 1)
                {
                    //tempAdd = addItem(temp, x+1,y);
                    //tempAdd = addItem(temp, x,y+1);
                    tempAdd = createItem(x - 1, y, 0); // Neues Teilchen der rechten Seite
                    setSideOfWave(tempAdd, 2); // der Zelle wird eine Zugehörigkeit zur Rechtenseite = 2
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("Haupt Rechte Seite,Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                } else if(isSoundField(x - 1,y) != 1){}
                if (isSoundField(x + 1, y) == 1)
                {
                    tempAdd = addItem(temp, x + 1, y);
                    //tempAdd = createItem(x-1, y, 0); // neues Teilchen der linken Seite
                    setSideOfWave(tempAdd, 1);
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("Haupt Linke Seite, Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                } else if(isSoundField(x + 1,y) != 1){}

            }
            // linke Seite
            // Wenn du kein Seitenteil bist oder zur Linken seite gehörst
            else if (getSideOfWave(temp) == 1)
            {
                if (isSoundField(x + 1, y) == 1)
                {
                    //tempAdd = addItem(temp, x-1,y);
                    tempAdd = createItem(x + 1, y, 0); // neues Teilchen der linken Seite
                    setSideOfWave(tempAdd, 1);
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("JO Left Linke Seite, Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                } else if(isSoundField(x + 1,y) != 1){}
            }
            //Rechte Seitenzugehörigkeit
            else if (getSideOfWave(temp) == 2)
            {
                if (isSoundField(x - 1, y) == 1)
                {
                    //tempAdd = addItem(temp, x+1,y);
                    //tempAdd = addItem(temp, x,y+1);
                    tempAdd = createItem(x - 1, y, 0); // Neues Teilchen der rechten Seite
                    setSideOfWave(tempAdd, 2); // der Zelle wird eine Zugehörigkeit zur Rechtenseite = 2
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("KO Right Rechte Seite,Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                } else if(isSoundField(x - 1,y) != 1){}
            }
        }
        else if ( getDirectionID(temp) == 6)
        {
            //unten links
            // rechte Seite der Welle für neue ID
            if ((getSideOfWave(temp) == 0))
            {
                //next_itemID==0 || next_itemID==3
                if (isSoundField(x - 1, y + 1) == 1)
                {
                    //tempAdd = addItem(temp, x+1,y);
                    //tempAdd = addItem(temp, x,y+1);
                    tempAdd = createItem(x - 1, y + 1, 0); // Neues Teilchen der rechten Seite
                    setSideOfWave(tempAdd, 2); // der Zelle wird eine Zugehörigkeit zur Rechtenseite = 2
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("Haupt Rechte Seite,Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                    printf("Position temp %d ,%d \n", x , y);
                    printf("Position tempAdd %d ,%d \n", x - 1 , y + 1);
                } else if(isSoundField(x - 1,y + 1) != 1){}
                if (isSoundField(x + 1, y - 1) == 1)
                {
                    tempAdd = addItem(temp, x + 1, y - 1);
                    //tempAdd = createItem(x-1, y, 0); // neues Teilchen der linken Seite
                    setSideOfWave(tempAdd, 1);
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("Haupt Linke Seite, Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                    printf("Position temp %d ,%d \n", x , y);
                    printf("Position tempAdd %d ,%d \n", x + 1 , y - 1);
                } else if(isSoundField(x + 1,y - 1) != 1){}

            }
            // linke Seite
            // Wenn du kein Seitenteil bist oder zur Linken seite gehörst
            else if (getSideOfWave(temp) == 1)
            {
                if (isSoundField(x + 1, y - 1) == 1)
                {
                    //tempAdd = addItem(temp, x-1,y);
                    tempAdd = createItem(x + 1, y - 1, 0); // neues Teilchen der linken Seite
                    setSideOfWave(tempAdd, 1);
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("Left Linke Seite, Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                    printf("Position temp %d ,%d \n", x , y);
                    printf("Position tempAdd %d ,%d \n", x + 1 , y - 1);
                } else if(isSoundField(x + 1,y - 1) != 1){}
            }
            //Rechte Seitenzugehörigkeit
            else if (getSideOfWave(temp) == 2)
            {
                if (isSoundField(x - 1, y + 1) == 1)
                {
                    //tempAdd = addItem(temp, x+1,y);
                    //tempAdd = addItem(temp, x,y+1);
                    tempAdd = createItem(x - 1, y + 1, 0); // Neues Teilchen der rechten Seite
                    setSideOfWave(tempAdd, 2); // der Zelle wird eine Zugehörigkeit zur Rechtenseite = 2
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("Right Rechte Seite,Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                    printf("Position temp %d ,%d \n", x , y);
                    printf("Position tempAdd %d ,%d \n", x - 11 , y + 1);
                } else if(isSoundField(x - 1,y + 1) != 1){}
            }
        }
        else if ( getDirectionID(temp) == 7)
        {
            // links
            // rechte Seite der Welle für neue ID
            if ((getSideOfWave(temp) == 0))
            {
                //next_itemID==0 || next_itemID==3
                if (isSoundField(x, y + 1) == 1)
                {
                    //tempAdd = addItem(temp, x+1,y);
                    //tempAdd = addItem(temp, x,y+1);
                    tempAdd = createItem(x, y + 1, 0); // Neues Teilchen der rechten Seite
                    setSideOfWave(tempAdd, 2); // der Zelle wird eine Zugehörigkeit zur Rechtenseite = 2
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("Haupt Rechte Seite,Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                } else if(isSoundField(x,y + 1) != 1){}
                if (isSoundField(x, y - 1) == 1)
                {
                    tempAdd = addItem(temp, x, y - 1);
                    //tempAdd = createItem(x-1, y, 0); // neues Teilchen der linken Seite
                    setSideOfWave(tempAdd, 1);
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("Haupt Linke Seite, Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                } else if(isSoundField(x,y - 1) != 1){}

            }
            // linke Seite
            // Wenn du kein Seitenteil bist oder zur Linken seite gehörst
            else if (getSideOfWave(temp) == 1)
            {
                if (isSoundField(x, y - 1) == 1)
                {
                    //tempAdd = addItem(temp, x-1,y);
                    tempAdd = createItem(x, y - 1, 0); // neues Teilchen der linken Seite
                    setSideOfWave(tempAdd, 1);
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("Left Linke Seite, Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                } else if(isSoundField(x,y - 1) != 1){}
            }
            //Rechte Seitenzugehörigkeit
            else if (getSideOfWave(temp) == 2)
            {
                if (isSoundField(x, y + 1) == 1)
                {
                    //tempAdd = addItem(temp, x+1,y);
                    //tempAdd = addItem(temp, x,y+1);
                    tempAdd = createItem(x, y + 1, 0); // Neues Teilchen der rechten Seite
                    setSideOfWave(tempAdd, 2); // der Zelle wird eine Zugehörigkeit zur Rechtenseite = 2
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("Right Rechte Seite,Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                } else if(isSoundField(x,y + 1) != 1){}
            }
        }
        else if ( getDirectionID(temp) == 8) {
            //oben links
            if ((getSideOfWave(temp) == 0))
            {
                //next_itemID==0 || next_itemID==3
                if (isSoundField(x + 1, y - 1) == 1)
                {
                    //tempAdd = addItem(temp, x+1,y);
                    //tempAdd = addItem(temp, x,y+1);
                    tempAdd = createItem(x + 1, y, 0); // Neues Teilchen der rechten Seite
                    setSideOfWave(tempAdd, 2); // der Zelle wird eine Zugehörigkeit zur Rechtenseite = 2
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("Haupt Rechte Seite,Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                } else if(isSoundField(x + 1,y - 1) != 1){}
                if (isSoundField(x - 1, y + 1) == 1)
                {
                    tempAdd = addItem(temp, x - 1, y);
                    //tempAdd = createItem(x-1, y, 0); // neues Teilchen der linken Seite
                    setSideOfWave(tempAdd, 1);
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("Haupt Linke Seite, Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                } else if(isSoundField(x - 1,y + 1) != 1){}

            }
            // linke Seite
            // Wenn du kein Seitenteil bist oder zur Linken seite gehörst
            else if (getSideOfWave(temp) == 1)
            {
                if (isSoundField(x - 1, y + 1) == 1)
                {
                    //tempAdd = addItem(temp, x-1,y);
                    tempAdd = createItem(x - 1, y, 0); // neues Teilchen der linken Seite
                    setSideOfWave(tempAdd, 1);
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("Left Linke Seite, Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                } else if(isSoundField(x - 1,y + 1) != 1){}
            }
            //Rechte Seitenzugehörigkeit
            else if (getSideOfWave(temp) == 2)
            {
                if (isSoundField(x + 1, y - 1) == 1)
                {
                    //tempAdd = addItem(temp, x+1,y);
                    //tempAdd = addItem(temp, x,y+1);
                    tempAdd = createItem(x + 1, y, 0); // Neues Teilchen der rechten Seite
                    setSideOfWave(tempAdd, 2); // der Zelle wird eine Zugehörigkeit zur Rechtenseite = 2
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("Right Rechte Seite,Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                } else if(isSoundField(x + 1,y - 1) != 1){}
            }
        }
    }
    else if (getMovement(getWaveRoot(temp)) > 3)
    {
        // evtl merken ob ein teil zur rechten oder linken seite gehört und dann nur noch einseitig
        // weiter verbreitet - neue variable die das anzeigt !

        if ( getDirectionID(temp) == 1) {
            // Nach oben
            if ((getSideOfWave(temp) == 0))
            {
                //next_itemID==0 || next_itemID==3
                if (isSoundField(x + 1, y - 1) == 1)
                {
                    printf("Bewegungen: %d \n ", getMovement(temp));
                    //tempAdd = addItem(temp, x+1,y);
                    //tempAdd = addItem(temp, x,y+1);
                    tempAdd = createItem(x + 1, y - 1, 0); // Neues Teilchen der rechten Seite
                    setSideOfWave(tempAdd, 2); // der Zelle wird eine Zugehörigkeit zur Rechtenseite = 2
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("Weit Haupt Rechte Seite,Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                    printf("Position %d ,%d \n", x , y);
                    printf("Position tempAdd %d ,%d \n", x + 1 , y - 1);
                } else if(isSoundField(x + 1,y - 1) != 1){}
                if (isSoundField(x - 1, y - 1) == 1)
                {
                    printf("Bewegungen: %d \n ", getMovement(temp));
                    tempAdd = addItem(temp, x - 1, y - 1);
                    //tempAdd = createItem(x-1, y, 0); // neues Teilchen der linken Seite
                    setSideOfWave(tempAdd, 1);
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("Weit Haupt Linke Seite, Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                    printf("Position %d ,%d \n", x , y);
                    printf("Position tempAdd %d ,%d \n", x - 1 , y - 1);
                } else if(isSoundField(x - 1,y - 1) != 1){}

            }
            // linke Seite
            // Wenn du kein Seitenteil bist oder zur Linken seite gehörst
            else if (getSideOfWave(temp) == 1)
            {
                if (isSoundField(x - 1, y - 1) == 1)
                {
                    printf("Bewegungen: %d \n ", getMovement(temp));
                    //tempAdd = addItem(temp, x-1,y);
                    tempAdd = createItem(x - 1, y, 0); // neues Teilchen der linken Seite
                    setSideOfWave(tempAdd, 1);
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("Weit Left Linke Seite, Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                    printf("Position tempAdd %d ,%d \n", x - 1 , y);
                } else if(isSoundField(x - 1,y) != 1){}
            }
            //Rechte Seitenzugehörigkeit
            else if (getSideOfWave(temp) == 2)
            {
                if (isSoundField(x + 1, y - 1) == 1)
                {
                    printf("Bewegungen: %d \n ", getMovement(temp));
                    //tempAdd = addItem(temp, x+1,y);
                    //tempAdd = addItem(temp, x,y+1);
                    tempAdd = createItem(x + 1, y, 0); // Neues Teilchen der rechten Seite
                    setSideOfWave(tempAdd, 2); // der Zelle wird eine Zugehörigkeit zur Rechtenseite = 2
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("Weit Right Rechte Seite,Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                    printf("Position tempAdd %d ,%d \n", x + 1 , y - 1);
                } else if(isSoundField(x + 1,y - 1) != 1){}
            }
        }
        else if ( getDirectionID(temp) == 2) {
            // Nach oben rechts
            if ((getSideOfWave(temp) == 0))
            {
                //next_itemID==0 || next_itemID==3
                if (isSoundField(x, y - 1) == 1)
                {
                    //tempAdd = addItem(temp, x+1,y);
                    //tempAdd = addItem(temp, x,y+1);
                    tempAdd = createItem(x, y - 1, 0); // Neues Teilchen der rechten Seite
                    setSideOfWave(tempAdd, 2); // der Zelle wird eine Zugehörigkeit zur Rechtenseite = 2
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("Haupt Rechte Seite,Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                } else if(isSoundField(x,y - 1) != 1){}
                if (isSoundField(x - 1, y) == 1)
                {
                    tempAdd = addItem(temp, x - 1, y);
                    //tempAdd = createItem(x-1, y, 0); // neues Teilchen der linken Seite
                    setSideOfWave(tempAdd, 1);
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("Haupt Linke Seite, Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                } else if(isSoundField(x - 1,y) != 1){}

            }
            // linke Seite
            // Wenn du kein Seitenteil bist oder zur Linken seite gehörst
            else if (getSideOfWave(temp) == 1)
            {
                if (isSoundField(x - 1, y) == 1)
                {
                    //tempAdd = addItem(temp, x-1,y);
                    tempAdd = createItem(x - 1, y, 0); // neues Teilchen der linken Seite
                    setSideOfWave(tempAdd, 1);
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("Left Linke Seite, Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                } else if(isSoundField(x - 1,y) != 1){}
            }
            //Rechte Seitenzugehörigkeit
            else if (getSideOfWave(temp) == 2)
            {
                if (isSoundField(x, y - 1) == 1)
                {
                    //tempAdd = addItem(temp, x+1,y);
                    //tempAdd = addItem(temp, x,y+1);
                    tempAdd = createItem(x, y - 1, 0); // Neues Teilchen der rechten Seite
                    setSideOfWave(tempAdd, 2); // der Zelle wird eine Zugehörigkeit zur Rechtenseite = 2
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("Right Rechte Seite,Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                } else if(isSoundField(x,y - 1) != 1){}
            }
        }
        else if ( getDirectionID(temp) == 4) {
            // unten rechts
            if ((getSideOfWave(temp) == 0))
            {
                //next_itemID==0 || next_itemID==3
                if (isSoundField(x - 1, y) == 1)
                {
                    //tempAdd = addItem(temp, x+1,y);
                    //tempAdd = addItem(temp, x,y+1);
                    tempAdd = createItem(x - 1, y, 0); // Neues Teilchen der rechten Seite
                    setSideOfWave(tempAdd, 2); // der Zelle wird eine Zugehörigkeit zur Rechtenseite = 2
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("Haupt Rechte Seite,Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                } else if(isSoundField(x - 1,y) != 1){}
                if (isSoundField(x, y + 1) == 1)
                {
                    tempAdd = addItem(temp, x, y + 1);
                    //tempAdd = createItem(x-1, y, 0); // neues Teilchen der linken Seite
                    setSideOfWave(tempAdd, 1);
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("Haupt Linke Seite, Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                } else if(isSoundField(x,y + 1) != 1){}

            }
            // linke Seite
            // Wenn du kein Seitenteil bist oder zur Linken seite gehörst
            else if (getSideOfWave(temp) == 1)
            {
                if (isSoundField(x, y + 1) == 1)
                {
                    //tempAdd = addItem(temp, x-1,y);
                    tempAdd = createItem(x, y + 1, 0); // neues Teilchen der linken Seite
                    setSideOfWave(tempAdd, 1);
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("Left Linke Seite, Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                } else if(isSoundField(x,y + 1) != 1){}
            }
            //Rechte Seitenzugehörigkeit
            else if (getSideOfWave(temp) == 2)
            {
                if (isSoundField(x - 1, y) == 1)
                {
                    //tempAdd = addItem(temp, x+1,y);
                    //tempAdd = addItem(temp, x,y+1);
                    tempAdd = createItem(x - 1, y, 0); // Neues Teilchen der rechten Seite
                    setSideOfWave(tempAdd, 2); // der Zelle wird eine Zugehörigkeit zur Rechtenseite = 2
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("Right Rechte Seite,Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                } else if(isSoundField(x - 1,y) != 1){}
            }
        }
        else if ( getDirectionID(temp) == 3) {
            // Nach Rechts
            if ((getSideOfWave(temp) == 0))
            {
                //next_itemID==0 || next_itemID==3
                if (isSoundField(x - 1, y - 1) == 1)
                {
                    //tempAdd = addItem(temp, x+1,y);
                    //tempAdd = addItem(temp, x,y+1);
                    tempAdd = createItem(x - 1, y - 1, 0); // Neues Teilchen der rechten Seite
                    setSideOfWave(tempAdd, 2); // der Zelle wird eine Zugehörigkeit zur Rechtenseite = 2
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("Haupt Rechte Seite,Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                } else if(isSoundField(x - 1,y - 1) != 1){}
                if (isSoundField(x - 1, y + 1) == 1)
                {
                    tempAdd = addItem(temp, x - 1, y + 1);
                    //tempAdd = createItem(x-1, y, 0); // neues Teilchen der linken Seite
                    setSideOfWave(tempAdd, 1);
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("Haupt Linke Seite, Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                } else if(isSoundField(x - 1,y + 1) != 1){}

            }
            // linke Seite
            // Wenn du kein Seitenteil bist oder zur Linken seite gehörst
            else if (getSideOfWave(temp) == 1)
            {
                if (isSoundField(x - 1, y + 1) == 1)
                {
                    //tempAdd = addItem(temp, x-1,y);
                    tempAdd = createItem(x - 1, y + 1, 0); // neues Teilchen der linken Seite
                    setSideOfWave(tempAdd, 1);
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("Left Linke Seite, Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                } else if(isSoundField(x - 1,y + 1) != 1){}
            }
            //Rechte Seitenzugehörigkeit
            else if (getSideOfWave(temp) == 2)
            {
                if (isSoundField(x - 1, y - 1) == 1)
                {
                    //tempAdd = addItem(temp, x+1,y);
                    //tempAdd = addItem(temp, x,y+1);
                    tempAdd = createItem(x - 1, y - 1, 0); // Neues Teilchen der rechten Seite
                    setSideOfWave(tempAdd, 2); // der Zelle wird eine Zugehörigkeit zur Rechtenseite = 2
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("Right Rechte Seite,Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                } else if(isSoundField(x - 1,y - 1) != 1){}
            }
        }
        else if ( getDirectionID(temp) == 5) {
            //unten
            if ((getSideOfWave(temp) == 0))
            {
                //next_itemID==0 || next_itemID==3
                if (isSoundField(x - 1, y + 1) == 1)
                {
                    //tempAdd = addItem(temp, x+1,y);
                    //tempAdd = addItem(temp, x,y+1);
                    tempAdd = createItem(x - 1, y + 1, 0); // Neues Teilchen der rechten Seite
                    setSideOfWave(tempAdd, 2); // der Zelle wird eine Zugehörigkeit zur Rechtenseite = 2
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("Haupt Rechte Seite,Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                } else if(isSoundField(x - 1,y + 1) != 1){}
                if (isSoundField(x + 1, y + 1) == 1)
                {
                    tempAdd = addItem(temp, x + 1, y + 1);
                    //tempAdd = createItem(x-1, y, 0); // neues Teilchen der linken Seite
                    setSideOfWave(tempAdd, 1);
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("Haupt Linke Seite, Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                } else if(isSoundField(x + 1,y + 1) != 1){}

            }
            // linke Seite
            // Wenn du kein Seitenteil bist oder zur Linken seite gehörst
            else if (getSideOfWave(temp) == 1)
            {
                if (isSoundField(x + 1, y + 1) == 1)
                {
                    //tempAdd = addItem(temp, x-1,y);
                    tempAdd = createItem(x + 1, y + 1, 0); // neues Teilchen der linken Seite
                    setSideOfWave(tempAdd, 1);
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("Left Linke Seite, Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                } else if(isSoundField(x + 1,y + 1) != 1){}
            }
            //Rechte Seitenzugehörigkeit
            else if (getSideOfWave(temp) == 2)
            {
                if (isSoundField(x - 1, y + 1) == 1)
                {
                    //tempAdd = addItem(temp, x+1,y);
                    //tempAdd = addItem(temp, x,y+1);
                    tempAdd = createItem(x - 1, y + 1, 0); // Neues Teilchen der rechten Seite
                    setSideOfWave(tempAdd, 2); // der Zelle wird eine Zugehörigkeit zur Rechtenseite = 2
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("Right Rechte Seite,Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                } else if(isSoundField(x - 1,y + 1) != 1){}
            }
        }
        else if ( getDirectionID(temp) == 6) {
            //unten links
            if ((getSideOfWave(temp) == 0))
            {
                //next_itemID==0 || next_itemID==3
                if (isSoundField(x, y + 1) == 1)
                {
                    //tempAdd = addItem(temp, x+1,y);
                    //tempAdd = addItem(temp, x,y+1);
                    tempAdd = createItem(x, y + 1, 0); // Neues Teilchen der rechten Seite
                    setSideOfWave(tempAdd, 2); // der Zelle wird eine Zugehörigkeit zur Rechtenseite = 2
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("Haupt Rechte Seite,Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                } else if(isSoundField(x,y + 1) != 1){}
                if (isSoundField(x + 1, y) == 1)
                {
                    tempAdd = addItem(temp, x + 1, y);
                    //tempAdd = createItem(x-1, y, 0); // neues Teilchen der linken Seite
                    setSideOfWave(tempAdd, 1);
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("Haupt Linke Seite, Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                } else if(isSoundField(x + 1,y) != 1){}

            }
            // linke Seite
            // Wenn du kein Seitenteil bist oder zur Linken seite gehörst
            else if (getSideOfWave(temp) == 1)
            {
                if (isSoundField(x + 1, y) == 1)
                {
                    //tempAdd = addItem(temp, x-1,y);
                    tempAdd = createItem(x + 1, y, 0); // neues Teilchen der linken Seite
                    setSideOfWave(tempAdd, 1);
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("Left Linke Seite, Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                } else if(isSoundField(x + 1,y) != 1){}
            }
            //Rechte Seitenzugehörigkeit
            else if (getSideOfWave(temp) == 2)
            {
                if (isSoundField(x, y + 1) == 1)
                {
                    //tempAdd = addItem(temp, x+1,y);
                    //tempAdd = addItem(temp, x,y+1);
                    tempAdd = createItem(x, y + 1, 0); // Neues Teilchen der rechten Seite
                    setSideOfWave(tempAdd, 2); // der Zelle wird eine Zugehörigkeit zur Rechtenseite = 2
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("Right Rechte Seite,Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                } else if(isSoundField(x,y + 1) != 1){}
            }
        }
        else if ( getDirectionID(temp) == 7) {
            // links
            if ((getSideOfWave(temp) == 0))
            {
                //next_itemID==0 || next_itemID==3
                if (isSoundField(x - 1, y + 1) == 1)
                {
                    //tempAdd = addItem(temp, x+1,y);
                    //tempAdd = addItem(temp, x,y+1);
                    tempAdd = createItem(x - 1, y + 1, 0); // Neues Teilchen der rechten Seite
                    setSideOfWave(tempAdd, 2); // der Zelle wird eine Zugehörigkeit zur Rechtenseite = 2
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("Haupt Rechte Seite,Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                } else if(isSoundField(x - 1,y + 1) != 1){}
                if (isSoundField(x + 1, y - 1) == 1)
                {
                    tempAdd = addItem(temp, x + 1, y - 1);
                    //tempAdd = createItem(x-1, y, 0); // neues Teilchen der linken Seite
                    setSideOfWave(tempAdd, 1);
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("Haupt Linke Seite, Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                } else if(isSoundField(x + 1,y - 1) != 1){}

            }
            // linke Seite
            // Wenn du kein Seitenteil bist oder zur Linken seite gehörst
            else if (getSideOfWave(temp) == 1)
            {
                if (isSoundField(x + 1, y - 1) == 1)
                {
                    //tempAdd = addItem(temp, x-1,y);
                    tempAdd = createItem(x + 1, y, 0); // neues Teilchen der linken Seite
                    setSideOfWave(tempAdd, 1);
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("Left Linke Seite, Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                } else if(isSoundField(x + 1,y - 1) != 1){}
            }
            //Rechte Seitenzugehörigkeit
            else if (getSideOfWave(temp) == 2)
            {
                if (isSoundField(x - 1, y + 1) == 1)
                {
                    //tempAdd = addItem(temp, x+1,y);
                    //tempAdd = addItem(temp, x,y+1);
                    tempAdd = createItem(x - 1, y + 1, 0); // Neues Teilchen der rechten Seite
                    setSideOfWave(tempAdd, 2); // der Zelle wird eine Zugehörigkeit zur Rechtenseite = 2
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("Right Rechte Seite,Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                } else if(isSoundField(x - 1,y + 1) != 1){}
            }
        }
        else if ( getDirectionID(temp) == 8) {
            //oben links
            if ((getSideOfWave(temp) == 0))
            {
                //next_itemID==0 || next_itemID==3
                if (isSoundField(x + 1, y) == 1)
                {
                    //tempAdd = addItem(temp, x+1,y);
                    //tempAdd = addItem(temp, x,y+1);
                    tempAdd = createItem(x + 1, y, 0); // Neues Teilchen der rechten Seite
                    setSideOfWave(tempAdd, 2); // der Zelle wird eine Zugehörigkeit zur Rechtenseite = 2
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("Haupt Rechte Seite,Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                } else if(isSoundField(x + 1,y) != 1){}
                if (isSoundField(x, y - 1) == 1)
                {
                    tempAdd = addItem(temp, x, y - 1);
                    //tempAdd = createItem(x-1, y, 0); // neues Teilchen der linken Seite
                    setSideOfWave(tempAdd, 1);
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("Haupt Linke Seite, Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                } else if(isSoundField(x,y - 1) != 1){}

            }
            // linke Seite
            // Wenn du kein Seitenteil bist oder zur Linken seite gehörst
            else if (getSideOfWave(temp) == 1)
            {
                if (isSoundField(x, y - 1) == 1)
                {
                    //tempAdd = addItem(temp, x-1,y);
                    tempAdd = createItem(x, y - 1, 0); // neues Teilchen der linken Seite
                    setSideOfWave(tempAdd, 1);
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("Left Linke Seite, Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                } else if(isSoundField(x,y - 1) != 1){}

            }
            //Rechte Seitenzugehörigkeit
            else if (getSideOfWave(temp) == 2)
            {
                if (isSoundField(x + 1, y) == 1)
                {
                    //tempAdd = addItem(temp, x+1,y);
                    //tempAdd = addItem(temp, x,y+1);
                    tempAdd = createItem(x + 1, y, 0); // Neues Teilchen der rechten Seite
                    setSideOfWave(tempAdd, 2); // der Zelle wird eine Zugehörigkeit zur Rechtenseite = 2
                    setDirectionID(tempAdd, getDirectionID(temp));
                    copyMovement(temp, tempAdd);
                    setFreqAll(temp, tempAdd);
                    printf("Right Rechte Seite,Richtung %d, Freq: %d \n", getDirectionID(tempAdd), getFreq400b1000(tempAdd));
                } else if(isSoundField(x + 1,y) != 1){}
            }
        }
    }
}

