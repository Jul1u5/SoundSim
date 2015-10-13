#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "main.h"
#include "soundwavefunction.h"

int j, k, l;
// Anzahl der Teilchenverschiebunngen
/**
 * Erhöhung des Movements
 * @param node
 */
void increaseMovement(item_node *node) {
    if (getItemID(node) == 0) {
        node->data.Sound.movement++;
    }else{}
}
/**
 * Getter für Movement
 * @param node
 * @return
 */
int getMovement(item_node *node) {
    if (getItemID(node) == 0) {
        return node->data.Sound.movement;
    } else {
        return -1;
    }
}
/**
 * Setter für Movement
 * @param node
 * @param m
 */
void setMovement(item_node *node, int m) {
    if (getItemID(node) == 0) {
        node->data.Sound.movement = m;
    }
}
/**
 * Kopiert das Movement von einem Item zum anderen
 * @param node
 * @param newnode
 */
void copyMovement(item_node *node, item_node *newnode) {
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
/**
 * Touched Element...
 * @param node
 */
void setTouche(item_node *node) {
    if (getItemID(node) == 0) {
        node->data.Sound.touched = true;
    }
}
/**
 * Untouched Element...
 * @param node
 */
void unTouche(item_node *node) {
    if (getItemID(node) == 0) {
        node->data.Sound.touched = false;
    }else{}
}
/**
 * Untouched alle Elemente
 */
void unToucheAll() {

    for (int i = 0; i < x_format; i++) {
        for (int j = 0; j < y_format; j++) {
            for (int k = 0; k < z_format; k++) {
                item_node *temp;
                temp = getItem_Root(i, j, k);
                while (temp != NULL) {
                    if (getItemID(temp) == 0) {
                        unTouche(temp);
                    }
                    temp = temp->next;
                }
            }
        }
    }
}
/**
 * Getter für Touched Status
 * @param node
 * @return
 */
bool getTouch(item_node *node) {
    if (getItemID(node) == 0) {
        return node->data.Sound.touched;
    } else {
        return -1;
    }
}
/**
 * Verringert die Frequenzen während des Movements
 * @param node
 */
void decSoundWithMovement(item_node *node) {
    float faktor = 0.12;

    if (getItemID(node) == 0) {
        if (getFreq20b40 > 0) {
            setFreq20b40(node, getFreq20b40(node) * 0.88 - (getMovement(node)*faktor));
        } else setFreq20b40(node, 0);
        if (getFreq40b100 > 0) {
            setFreq40b100(node, getFreq40b100(node) * 0.89 - (getMovement(node)*faktor));
        }    else setFreq40b100(node, 0);
        if (getFreq100b150 > 0) {
            setFreq100b150(node, getFreq100b150(node) * 0.90 - (getMovement(node)*faktor));
        } else setFreq100b150(node, 0);
        if (getFreq150b400 > 0) {
            setFreq150b400(node, getFreq150b400(node) * 0.91 - (getMovement(node)*faktor));
        } else setFreq150b400(node, 0);
        if (getFreq400b1000 > 0) {
            setFreq400b1000(node, getFreq400b1000(node) * 0.92 - (getMovement(node)*faktor));
        } else setFreq400b1000(node, 0);
        if (getFreq1000b2000 > 0) {
            setFreq1000b2000(node, getFreq1000b2000(node) * 0.93 - (getMovement(node)*faktor));
        } else setFreq1000b2000(node, 0);
        if (getFreq2000b3500 > 0) {
            setFreq2000b3500(node, getFreq2000b3500(node) * 0.94 - (getMovement(node)*faktor));
        } else setFreq2000b3500(node, 0);
        if (getFreq3500b6000 > 0) {
            setFreq3500b6000(node, getFreq3500b6000(node) * 0.95 - (getMovement(node)*faktor));
        } else setFreq3500b6000(node, 0);
        if (getFreq6000b10000 > 0) {
            setFreq6000b10000(node, getFreq6000b10000(node) * 0.96 - (getMovement(node)*faktor));
        } else setFreq6000b10000(node, 0);
        if (getFreq10000b20000 > 0) {
            setFreq10000b20000(node, getFreq10000b20000(node) * 0.97 - (getMovement(node)*faktor));
        } else setFreq10000b20000(node, 0);
    }
}
/**
 * Legt die Seite der Welle für ein SoundItem fest
 * @param node betroffenes Item
 * @param side Seite der "Welle" 0 = nicht von betroffen , 1 == Links , 2 = Rechts, 3 = Oben, 4 = Unten
 */
void setSideOfWave(item_node * node, int side) {
    if (getItemID(node) == 0) {
        node->data.Sound.sideofwave = side;
    }
}
/**
 * Getter für die Seite der Welle
 * @param node
 * @return
 */
int getSideOfWave(item_node * node) {
    if (getItemID(node) == 0) {
        return node->data.Sound.sideofwave;
    } else {
        return -1;
    }
}
/**
 * Ähnlich wie Rebound der Teilchen. Seitenzugehörigkeit wird verändert
 * @param node
 */
void changeReboundSideOfWave(item_node * node)
{
    if (getSideOfWave(node) == 1)
    {
        setSideOfWave(node, 2);
    }
    else if (getSideOfWave(node) == 2) {
        setSideOfWave(node, 1);
    }
    else if (getSideOfWave(node) == 0) {
        setSideOfWave(node, 0);
    }
    else if (getSideOfWave(node) == 3) {
        setSideOfWave(node, 3);
    }
    else if (getSideOfWave(node) == 4) {
        setSideOfWave(node, 4);
    }
    else {
        setSideOfWave(node, 5);
    }
}
/**
 * Frequenzen eines Teilchen wird von anderem Teilchen übernommen und um einen Faktor reduziert
 * @param node
 * @param newnode
 */
void setFreqAll(item_node * node, item_node * newnode) {

    float reduction = 0.99; // Wert der die anderen Teilchen schwächt.

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
/**
 * Zeugs
 * @param temp
 * @param x
 * @param y
 * @param z
 * @param side
 */
void procedureH(item_node *temp, int x , int y, int z, int side) {

    item_node *tempAdd; // ein temporäres Teilchen was hinzugefügt wird.

    tempAdd = createItem(x, y, z, 0); // Neues Teilchen der rechten Seite
    setTouche(tempAdd);
    setSideOfWave(tempAdd, side);
    setDirectionID(tempAdd, getDirectionID(temp));
    setWaveRoot(tempAdd, temp);
    copyMovement(temp, tempAdd);
    setFreqAll(temp, tempAdd);
    addItemNewRoom(tempAdd, x, y, z);
}
/**
 * Zeugs 2 :D
 * @param temp
 * @param x
 * @param y
 * @param z
 * @param side
 */
void procedure(item_node *temp, int x , int y, int z, int side) {

    item_node *tempAdd; // ein temporäres Teilchen was hinzugefügt wird.

    tempAdd = createItem(x, y, z, 0);
    setTouche(tempAdd);
    setSideOfWave(tempAdd, side);
    setDirectionID(tempAdd, getDirectionID(temp));
    copyMovement(temp, tempAdd);
    setFreqAll(temp, tempAdd);
    addItemNewRoom(tempAdd, x, y, z);
}

/**
 * Welle eines SoundItem wird erzeugt
 * addwave lässt die Welle bis zu einer bestimmten Verschiebungsweite ungekrümmt, danach werden die resultierenden Teilchen "Kugelfunktionsartig" erzeugt und haben eine zugehörgkeit zur rechten oder linken Seite.
 * @param temp
 * @param x
 * @param y
 * @param z
 */
void addWave(item_node * temp, int x, int y, int z)
{
    if (getItemID(temp) == 0 && x + 1 < x_format)
    {
        // Wenn das Hauptteilchen noch nicht weit genug gewandert ist, bleibt die Welle ungekrümmt.
        if (getMovement(temp) < 10)
        {
            // 0°
            if (getDirectionID(temp) == 1)
            {

                if ((getSideOfWave(temp) == 0) && getItemID(temp) == 0)
                {
                    setTouche(temp);
                    if (isSoundField(x + 1, y, z) == 1)
                    {
                        procedureH(temp, x + 1, y, z, 2);
                    } if (isSoundField(x + 1, y, z) != 1) {}
                    if (isSoundField(x - 1, y, z) == 1)
                    {
                        procedureH(temp, x - 1, y, z, 1);
                    } if (isSoundField(x - 1, y, z) != 1) {}
                    if (isSoundField(x, y, z + 1) == 1)
                    {
                        procedureH(temp, x, y, z + 1, 3);
                    } if (isSoundField(x, y, z + 1) != 1) {}
                    if (isSoundField(x, y, z - 1) == 1)
                    {
                        procedureH(temp, x, y, z - 1, 4);
                    } if (isSoundField(x, y, z - 1) != 1) {}
                }
                // linke Seite
                else if (getSideOfWave(temp) == 1 && getItemID(temp) == 0)
                {
                    setTouche(temp);
                    if (isSoundField(x - 1, y, z) == 1)
                    {
                        procedure(temp, x - 1, y, z, 1);
                    } if (isSoundField(x - 1, y, z) != 1) {}
                }
                //Rechte Seitenzugehörigkeit
                else if (getSideOfWave(temp) == 2 && getItemID(temp) == 0)
                {
                    setTouche(temp);
                    if (isSoundField(x + 1, y, z) == 1)
                    {
                        procedure(temp, x + 1, y, z, 2);
                    } if (isSoundField(x + 1, y, z) != 1) {}
                }
                else if (getSideOfWave(temp) == 3 && getItemID(temp) == 0)
                {
                    setTouche(temp);
                    if (isSoundField(x, y, z + 1) == 1)
                    {
                        procedure(temp, x, y, z + 1, 3);
                    } if (isSoundField(x, y, z + 1) != 1) {}
                }
                else if (getSideOfWave(temp) == 4 && getItemID(temp) == 0)
                {
                    setTouche(temp);
                    if (isSoundField(x, y, z - 1) == 1)
                    {
                        procedure(temp, x, y, z - 1, 4);
                    } if (isSoundField(x, y, z - 1) != 1) {}
                }
            }
            else if ( getDirectionID(temp) == 2)
            {
                // Nach oben rechts
                if ((getSideOfWave(temp) == 0) && getItemID(temp) == 0)
                {
                    if (isSoundField(x + 1, y - 1, z) == 1)
                    {
                        procedureH(temp, x + 1, y - 1, z, 2);
                    } if (isSoundField(x + 1, y - 1, z) != 1) {}
                    if (isSoundField(x - 1, y + 1, z) == 1)
                    {
                        procedureH(temp, x - 1, y + 1, z, 1);
                    } if (isSoundField(x - 1, y + 1, z) != 1) {}
                    if (isSoundField(x, y, z + 1) == 1)
                    {
                        procedureH(temp, x, y, z + 1, 3);
                    } if (isSoundField(x , y , z + 1) != 1) {}
                    if (isSoundField(x, y, z - 1) == 1)
                    {
                        procedureH(temp, x, y, z - 1, 4);
                    } if (isSoundField(x, y, z - 1) != 1) {}

                }
                // linke Seite
                else if (getSideOfWave(temp) == 1 && getItemID(temp) == 0)
                {
                    if (isSoundField(x - 1, y + 1, z) == 1)
                    {
                        procedure(temp, x - 1, y + 1, z, 1);
                    } if (isSoundField(x - 1, y + 1, z) != 1) {}
                }
                //Rechte Seitenzugehörigkeit
                else if (getSideOfWave(temp) == 2 && getItemID(temp) == 0)
                {
                    if (isSoundField(x + 1, y - 1, z) == 1)
                    {
                        procedure(temp, x + 1, y - 1, z, 2);
                    } if (isSoundField(x + 1, y - 1, z) != 1) {}
                }
                else if (getSideOfWave(temp) == 3 && getItemID(temp) == 0)
                {
                    if (isSoundField(x, y, z + 1) == 1)
                    {
                        procedure(temp, x, y, z + 1, 3);
                    } if (isSoundField(x, y, z + 1) != 1) {}
                }
                else if (getSideOfWave(temp) == 4 && getItemID(temp) == 0)
                {
                    if (isSoundField(x , y , z - 1) == 1)
                    {
                        procedure(temp, x, y, z - 1, 4);
                    } if (isSoundField(x , y , z - 1) != 1) {}
                }
            }
            else if ( getDirectionID(temp) == 3) {
                // Nach Rechts
                if ((getSideOfWave(temp) == 0) && getItemID(temp) == 0)
                {
                    if (isSoundField(x, y + 1, z) == 1)
                    {
                        procedureH(temp, x, y + 1, z, 2);
                    } if (isSoundField(x, y + 1, z) != 1) {}
                    if (isSoundField(x, y - 1, z) == 1)
                    {
                        procedureH(temp, x, y - 1, z, 1);
                    } if (isSoundField(x, y - 1, z) != 1) {}
                    if (isSoundField(x, y, z + 1) == 1)
                    {
                        procedureH(temp, x, y, z + 1, 3);
                    } if (isSoundField(x , y , z + 1) != 1) {}
                    if (isSoundField(x, y, z - 1) == 1)
                    {
                        procedureH(temp, x, y, z - 1, 4);
                    } if (isSoundField(x, y, z - 1) != 1) {}

                }
                // linke Seite
                else if (getSideOfWave(temp) == 1 && getItemID(temp) == 0)
                {
                    if (isSoundField(x, y - 1, z) == 1)
                    {
                        procedure(temp, x, y - 1, z, 1);
                    } else if (isSoundField(x , y - 1, z) != 1) {}
                }
                //Rechte Seitenzugehörigkeit
                else if (getSideOfWave(temp) == 2 && getItemID(temp) == 0)
                {
                    if (isSoundField(x, y + 1, z) == 1)
                    {
                        procedure(temp, x, y + 1, z, 2);
                    } else if (isSoundField(x, y + 1, z) != 1) {}
                }
                else if (getSideOfWave(temp) == 3 && getItemID(temp) == 0)
                {
                    if (isSoundField(x, y, z + 1) == 1)
                    {
                        procedure(temp, x, y, z + 1, 3);
                    } else if (isSoundField(x, y, z + 1) != 1) {}
                }
                else if (getSideOfWave(temp) == 4 && getItemID(temp) == 0)
                {
                    if (isSoundField(x, y, z - 1) == 1)
                    {
                        procedure(temp, x, y, z - 1, 4);
                    } else if (isSoundField(x, y, z - 1) != 1) {}
                }

            }
            else if ( getDirectionID(temp) == 4)
            {
                // unten rechts
                if ((getSideOfWave(temp) == 0) && getItemID(temp) == 0)
                {
                    if (isSoundField(x - 1, y - 1, z) == 1)
                    {
                        procedureH(temp, x - 1, y - 1, z, 2);
                    } if (isSoundField(x - 1, y - 1, z) != 1) {}
                    if (isSoundField(x + 1, y + 1, z) == 1)
                    {
                        procedureH(temp, x + 1, y + 1, z, 1);
                    } if (isSoundField(x + 1, y + 1, z) != 1) {}
                    if (isSoundField(x, y, z + 1) == 1)
                    {
                        procedureH(temp, x, y, z + 1, 3);
                    } if (isSoundField(x , y , z + 1) != 1) {}
                    if (isSoundField(x, y, z - 1) == 1)
                    {
                        procedureH(temp, x, y, z - 1, 4);
                    } if (isSoundField(x, y, z - 1) != 1) {}
                }
                // linke Seite
                else if (getSideOfWave(temp) == 1 && getItemID(temp) == 0)
                {
                    if (isSoundField(x + 1, y + 1, z) == 1)
                    {
                        procedure(temp, x + 1, y + 1, z, 1);
                    } if (isSoundField(x + 1, y + 1, z) != 1) {}
                }
                //Rechte Seitenzugehörigkeit
                else if (getSideOfWave(temp) == 2 && getItemID(temp) == 0)
                {
                    if (isSoundField(x + 1, y + 1, z) == 1)
                    {
                        procedure(temp, x + 1, y + 1, z, 2);
                    } if (isSoundField(x + 1, y + 1, z) != 1) {}
                }
                else if (getSideOfWave(temp) == 3)
                {
                    if (isSoundField(x, y, z + 1) == 1)
                    {
                        procedure(temp, x, y, z + 1, 3);
                    } if (isSoundField(x, y, z + 1) != 1) {}
                }
                else if (getSideOfWave(temp) == 4 && getItemID(temp) == 0)
                {
                    if (isSoundField(x, y, z - 1) == 1)
                    {
                        procedure(temp, x, y, z - 1, 3);
                    } if (isSoundField(x, y, z - 1) != 1) {}
                }
            }
            else if ( getDirectionID(temp) == 5) {
                //unten
                if ((getSideOfWave(temp) == 0) && getItemID(temp) == 0)
                {
                    if (isSoundField(x - 1, y, z) == 1)
                    {
                        procedureH(temp, x - 1, y, z, 2);
                    } if (isSoundField(x - 1, y, z) != 1) {}
                    if (isSoundField(x + 1, y, z) == 1)
                    {
                        procedureH(temp, x + 1, y, z, 1);
                    } if (isSoundField(x + 1, y, z) != 1) {}
                    if (isSoundField(x, y, z + 1) == 1)
                    {
                        procedureH(temp, x, y, z + 1, 3);
                    } if (isSoundField(x , y , z + 1) != 1) {}
                    if (isSoundField(x, y, z - 1) == 1)
                    {
                        procedureH(temp, x, y, z - 1, 4);
                    } if (isSoundField(x, y, z - 1) != 1) {}

                }
                // linke Seite
                else if (getSideOfWave(temp) == 1 && getItemID(temp) == 0)
                {
                    if (isSoundField(x + 1, y, z) == 1)
                    {
                        procedure(temp, x + 1, y, z, 1);
                    } if (isSoundField(x + 1, y, z) != 1) {}
                }
                //Rechte Seitenzugehörigkeit
                else if (getSideOfWave(temp) == 2 && getItemID(temp) == 0)
                {
                    if (isSoundField(x - 1, y, z) == 1)
                    {
                        procedure(temp, x - 1, y, z, 2);
                    } if (isSoundField(x - 1, y, z) != 1) {}
                }
                else if (getSideOfWave(temp) == 3 && getItemID(temp) == 0)
                {
                    if (isSoundField(x, y, z + 1) == 1)
                    {
                        procedure(temp, x, y, z + 1, 3);
                    } if (isSoundField(x, y, z + 1) != 1) {}
                }
                else if (getSideOfWave(temp) == 4 && getItemID(temp) == 0)
                {
                    if (isSoundField(x, y, z - 1) == 1)
                    {
                        procedure(temp, x, y, z - 1, 4);
                    } if (isSoundField(x, y, z - 1) != 1) {}
                }
            }
            else if ( getDirectionID(temp) == 6)
            {
                //unten links
                // rechte Seite der Welle für neue ID
                if ((getSideOfWave(temp) == 0) && getItemID(temp) == 0)
                {
                    if (isSoundField(x - 1, y + 1, z) == 1)
                    {
                        procedureH(temp, x - 1, y + 1, z, 2);
                    } if (isSoundField(x - 1, y + 1, z) != 1) {}
                    if (isSoundField(x + 1, y - 1, z) == 1)
                    {
                        procedureH(temp, x + 1, y - 1, z, 1);
                    } if (isSoundField(x + 1, y - 1, z) != 1) {}
                    if (isSoundField(x, y, z + 1) == 1)
                    {
                        procedureH(temp, x, y, z + 1, 3);
                    } if (isSoundField(x , y , z + 1) != 1) {}
                    if (isSoundField(x, y, z - 1) == 1)
                    {
                        procedureH(temp, x, y, z - 1, 2);
                    } if (isSoundField(x, y, z - 1) != 1) {}

                }
                // linke Seite
                else if (getSideOfWave(temp) == 1 && getItemID(temp) == 0)
                {
                    if (isSoundField(x + 1, y - 1, z) == 1)
                    {
                        procedure(temp, x + 1, y - 1, z, 1);
                    } if (isSoundField(x + 1, y - 1, z) != 1) {}
                }
                //Rechte Seitenzugehörigkeit
                else if (getSideOfWave(temp) == 2 && getItemID(temp) == 0)
                {
                    if (isSoundField(x - 1, y + 1, z) == 1)
                    {
                        procedure(temp, x - 1, y + 1, z, 2);
                    } if (isSoundField(x - 1, y + 1, z) != 1) {}
                }
                else if (getSideOfWave(temp) == 3 && getItemID(temp) == 0)
                {
                    if (isSoundField(x, y, z + 1) == 1)
                    {
                        procedure(temp, x, y, z + 1, 3);
                    } if (isSoundField(x, y, z + 1) != 1) {}
                }
                else if (getSideOfWave(temp) == 4 && getItemID(temp) == 0)
                {
                    if (isSoundField(x, y, z - 1) == 1)
                    {
                        procedure(temp, x, y, z - 1, 4);
                    } if (isSoundField(x, y, z - 1) != 1) {}
                }

            }
            else if ( getDirectionID(temp) == 7)
            {
                // links
                // rechte Seite der Welle für neue ID
                if ((getSideOfWave(temp) == 0) && getItemID(temp) == 0)
                {
                    if (isSoundField(x, y + 1, z) == 1)
                    {
                        procedureH(temp, x, y + 1, z, 2);
                    } if (isSoundField(x, y + 1, z) != 1) {}
                    if (isSoundField(x, y - 1, z) == 1)
                    {
                        procedureH(temp, x, y - 1, z, 1);
                    } if (isSoundField(x, y - 1, z) != 1) {}
                    if (isSoundField(x, y, z + 1) == 1)
                    {
                        procedureH(temp, x, y, z + 1, 3);
                    } if (isSoundField(x , y , z + 1) != 1) {}
                    if (isSoundField(x, y, z - 1) == 1)
                    {
                        procedureH(temp, x, y, z - 1 , 4);
                    } if (isSoundField(x, y, z - 1) != 1) {}

                }
                // linke Seite
                else if (getSideOfWave(temp) == 1 && getItemID(temp) == 0)
                {
                    if (isSoundField(x, y - 1, z) == 1)
                    {
                        procedure(temp, x, y - 1, z, 1);
                    } if (isSoundField(x, y - 1, z) != 1) {}
                }
                //Rechte Seitenzugehörigkeit
                else if (getSideOfWave(temp) == 2 && getItemID(temp) == 0)
                {
                    if (isSoundField(x, y + 1, z) == 1)
                    {
                        procedure(temp, x, y + 1, z, 2);
                    } if (isSoundField(x, y + 1, z) != 1) {}
                }
                else if (getSideOfWave(temp) == 3 && getItemID(temp) == 0)
                {
                    if (isSoundField(x, y, z + 1) == 1)
                    {
                        procedure(temp, x, y, z + 1, 3);
                    } if (isSoundField(x, y, z + 1) != 1) {}
                }
                else if (getSideOfWave(temp) == 4 && getItemID(temp) == 0)
                {
                    if (isSoundField(x, y, z - 1) == 1)
                    {
                        procedure(temp, x, y, z - 1, 4);
                    } if (isSoundField(x, y, z - 1) != 1) {}
                }
            }
            else if ( getDirectionID(temp) == 8) {
                //oben links
                if ((getSideOfWave(temp) == 0) && getItemID(temp) == 0)
                {
                    if (isSoundField(x + 1, y - 1, z) == 1)
                    {
                        procedureH(temp, x + 1, y - 1, z, 2);
                    } if (isSoundField(x + 1, y - 1, z) != 1) {}
                    if (isSoundField(x - 1, y + 1, z) == 1)
                    {
                        procedureH(temp, x - 1, y, z, 1);
                    } if (isSoundField(x - 1, y + 1, z) != 1) {}
                    if (isSoundField(x, y, z + 1) == 1)
                    {
                        procedureH(temp, x, y, z + 1, 3);
                    } if (isSoundField(x , y , z + 1) != 1) {}
                    if (isSoundField(x, y, z - 1) == 1)
                    {
                        procedureH(temp, x, y, z - 1, 4);
                    } if (isSoundField(x, y, z - 1) != 1) {}

                }
                // linke Seite
                else if (getSideOfWave(temp) == 1 && getItemID(temp) == 0)
                {
                    if (isSoundField(x - 1, y + 1, z) == 1)
                    {
                        procedure(temp, x - 1, y + 1, z, 1);
                    } if (isSoundField(x - 1, y + 1, z) != 1) {}
                }
                //Rechte Seitenzugehörigkeit
                else if (getSideOfWave(temp) == 2 && getItemID(temp) == 0)
                {
                    if (isSoundField(x + 1, y - 1, z) == 1)
                    {
                        procedure(temp, x + 1, y - 1, z, 2);
                    } if (isSoundField(x + 1, y - 1, z) != 1) {}
                }
                else if (getSideOfWave(temp) == 3 && getItemID(temp) == 0)
                {
                    if (isSoundField(x, y, z + 1) == 1)
                    {
                        procedure(temp, x, y, z + 1, 3);
                    } if (isSoundField(x, y, z + 1) != 1) {}
                }
                else if (getSideOfWave(temp) == 4 && getItemID(temp) == 0)
                {
                    if (isSoundField(x, y, z - 1) == 1)
                    {
                        procedure(temp, x, y, z - 1, 4);
                    } if (isSoundField(x, y, z - 1) != 1) {}
                }
            }
        }
        else if (getMovement(temp) > 10)
        {
            if ( getDirectionID(temp) == 1) {
                // Nach oben
                if ((getSideOfWave(temp) == 0) && getItemID(temp) == 0)
                {
                    setTouche(temp);
                    if (isSoundField(x + 1, y - 1, z) == 1)
                    {
                        procedureH(temp, x + 1, y - 1, z, 2);
                    } if (isSoundField(x + 1, y - 1, z) != 1) {}
                    if (isSoundField(x - 1, y - 1, z) == 1)
                    {
                        procedureH(temp, x - 1, y - 1, z, 1);
                    } if (isSoundField(x - 1, y - 1, z) != 1) {}
                    if (isSoundField(x, y - 1, z + 1) == 1)
                    {
                        procedureH(temp, x , y - 1, z + 1, 3);
                    } if (isSoundField(x, y - 1, z + 1) != 1) {}
                    if (isSoundField(x, y - 1, z - 1) == 1)
                    {
                        procedureH(temp, x , y - 1, z - 1, 4);
                    } if (isSoundField(x, y - 1, z - 1) != 1) {}

                }
                // linke Seite
                else if (getSideOfWave(temp) == 1 && getItemID(temp) == 0)
                {
                    setTouche(temp);
                    if (isSoundField(x - 1, y - 1, z) == 1)
                    {
                        procedure(temp, x - 1, y - 1, z, 1);
                    } if (isSoundField(x - 1, y - 1, z) != 1) {}
                }
                //Rechte Seitenzugehörigkeit
                else if (getSideOfWave(temp) == 2 && getItemID(temp) == 0)
                {
                    setTouche(temp);
                    if (isSoundField(x + 1, y - 1, z) == 1)
                    {
                        procedure(temp, x + 1, y - 1, z, 2);
                    } if (isSoundField(x + 1, y - 1, z) != 1) {}
                }
                else if (getSideOfWave(temp) == 3 && getItemID(temp) == 0)
                {
                    setTouche(temp);
                    if (isSoundField(x, y - 1, z + 1) == 1)
                    {
                        procedure(temp, x, y - 1, z + 1, 3);
                    } if (isSoundField(x, y - 1, z + 1) != 1) {}
                }
                else if (getSideOfWave(temp) == 4 && getItemID(temp) == 0)
                {
                    setTouche(temp);
                    if (isSoundField(x, y - 1, z - 1) == 1)
                    {
                        procedure(temp, x, y - 1, z - 1, 4);
                    } if (isSoundField(x, y - 1, z - 1) != 1) {}
                }
            }
            else if ( getDirectionID(temp) == 2) {
                // Nach oben rechts
                if ((getSideOfWave(temp) == 0) && getItemID(temp) == 0)
                {
                    if (isSoundField(x, y - 1, z) == 1)
                    {
                        procedureH(temp, x , y - 1, z, 2);
                    } if (isSoundField(x, y - 1, z) != 1) {}
                    if (isSoundField(x - 1, y, z) == 1)
                    {
                        procedureH(temp, x - 1 , y, z + 1, 1);
                    } if (isSoundField(x - 1, y, z) != 1) {}
                    if (isSoundField(x - 1, y - 1, z + 1) == 1)
                    {
                        procedureH(temp, x - 1 , y - 1, z + 1, 3);
                    } if (isSoundField(x - 1, y - 1, z + 1) != 1) {}
                    if (isSoundField(x - 1, y - 1, z - 1) == 1)
                    {
                        procedureH(temp, x - 1 , y - 1, z - 1, 4);
                    } if (isSoundField(x - 1, y - 1, z - 1) != 1) {}

                }
                // linke Seite
                else if (getSideOfWave(temp) == 1 && getItemID(temp) == 0)
                {
                    if (isSoundField(x - 1, y, z) == 1)
                    {
                        procedure(temp, x - 1, y, z, 1);
                    } if (isSoundField(x - 1, y, z) != 1) {}
                }
                //Rechte Seitenzugehörigkeit
                else if (getSideOfWave(temp) == 2 && getItemID(temp) == 0)
                {
                    if (isSoundField(x, y - 1, z) == 1)
                    {
                        procedure(temp, x, y - 1, z, 2);
                    } if (isSoundField(x, y - 1, z) != 1) {}
                }
                else if (getSideOfWave(temp) == 3 && getItemID(temp) == 0)
                {
                    if (isSoundField(x - 1, y - 1, z + 1) == 1)
                    {
                        procedure(temp, x - 1, y - 1, z + 1, 3);
                    } if (isSoundField(x - 1, y - 1, z + 1) != 1) {}
                }
                else if (getSideOfWave(temp) == 4 && getItemID(temp) == 0)
                {
                    if (isSoundField(x - 1, y - 1, z - 1) == 1)
                    {
                        procedure(temp, x - 1, y - 1, z - 1, 4);
                    } if (isSoundField(x - 1, y - 1, z - 1) != 1) {}
                }
            }
            else if ( getDirectionID(temp) == 4) {
                // unten rechts
                if ((getSideOfWave(temp) == 0) && getItemID(temp) == 0)
                {
                    if (isSoundField(x - 1, y, z) == 1)
                    {
                        procedureH(temp, x - 1 , y, z, 2);
                    } if (isSoundField(x - 1, y, z) != 1) {}
                    if (isSoundField(x, y + 1, z) == 1)
                    {
                        procedureH(temp, x , y + 1, z, 1);
                    } if (isSoundField(x, y + 1, z) != 1) {}
                    if (isSoundField(x - 1, y + 1, z + 1) == 1)
                    {
                        procedureH(temp, x - 1, y + 1, z + 1, 3);
                    } if (isSoundField(x - 1, y + 1, z + 1) != 1) {}
                    if (isSoundField(x - 1, y + 1, z - 1) == 1)
                    {
                        procedureH(temp, x - 1, y + 1, z - 1, 4);
                    } else if (isSoundField(x - 1, y + 1, z - 1) != 1) {}

                }
                // linke Seite
                else if (getSideOfWave(temp) == 1 && getItemID(temp) == 0)
                {
                    if (isSoundField(x, y + 1, z) == 1)
                    {
                        procedure(temp, x, y + 1, z, 1);
                    } if (isSoundField(x, y + 1, z) != 1) {}
                }
                //Rechte Seitenzugehörigkeit
                else if (getSideOfWave(temp) == 2 && getItemID(temp) == 0)
                {
                    if (isSoundField(x - 1, y, z) == 1)
                    {
                        procedure(temp, x - 1, y, z, 2);
                    } if (isSoundField(x - 1, y, z) != 1) {}
                }
                else if (getSideOfWave(temp) == 3 && getItemID(temp) == 0)
                {
                    if (isSoundField(x - 1, y + 1, z + 1) == 1)
                    {
                        procedure(temp, x - 1, y + 1, z + 1, 3);
                    } if (isSoundField(x, y, z + 1) != 1) {}
                }
                else if (getSideOfWave(temp) == 4 && getItemID(temp) == 0)
                {
                    if (isSoundField(x - 1, y + 1, z - 1) == 1)
                    {
                        procedure(temp, x - 1, y + 1, z - 1, 4);
                    } if (isSoundField(x - 1, y + 1, z - 1) != 1) {}
                }
            }
            else if ( getDirectionID(temp) == 3) {
                // Nach Rechts
                if ((getSideOfWave(temp) == 0) && getItemID(temp) == 0)
                {
                    if (isSoundField(x - 1, y - 1, z) == 1)
                    {
                        procedureH(temp, x - 1 , y - 1, z, 2);
                    } if (isSoundField(x - 1, y - 1, z) != 1) {}
                    if (isSoundField(x - 1, y + 1, z) == 1)
                    {
                        procedureH(temp, x - 1 , y + 1, z, 1);
                    } if (isSoundField(x - 1, y + 1, z) != 1) {}
                    if (isSoundField(x - 1, y, z + 1) == 1)
                    {
                        procedureH(temp, x - 1 , y, z + 1, 3);
                    } if (isSoundField(x - 1, y, z + 1) != 1) {}
                    if (isSoundField(x - 1, y, z - 1) == 1)
                    {
                        procedureH(temp, x - 1 , y , z - 1, 4);
                    } if (isSoundField(x - 1, y, z - 1) != 1) {}

                }
                // linke Seite
                else if (getSideOfWave(temp) == 1 && getItemID(temp) == 0)
                {
                    if (isSoundField(x - 1, y + 1, z) == 1)
                    {
                        procedure(temp, x - 1, y + 1, z, 1);
                    } if (isSoundField(x - 1, y + 1, z) != 1) {}
                }
                //Rechte Seitenzugehörigkeit
                else if (getSideOfWave(temp) == 2 && getItemID(temp) == 0)
                {
                    if (isSoundField(x - 1, y - 1, z) == 1)
                    {
                        procedure(temp, x - 1, y - 1, z, 2);
                    } if (isSoundField(x - 1, y - 1, z) != 1) {}
                }
                else if (getSideOfWave(temp) == 3 && getItemID(temp) == 0)
                {
                    if (isSoundField(x - 1, y, z + 1) == 1)
                    {
                        procedure(temp, x - 1, y, z + 1, 3);
                    } if (isSoundField(x - 1, y, z + 1) != 1) {}
                }
                else if (getSideOfWave(temp) == 4 && getItemID(temp) == 0)
                {
                    if (isSoundField(x - 1, y, z - 1) == 1)
                    {
                        procedure(temp, x - 1, y, z - 1, 4);
                    } if (isSoundField(x - 1, y, z - 1) != 1) {}
                }
            }
            else if ( getDirectionID(temp) == 5) {
                //unten
                if ((getSideOfWave(temp) == 0) && getItemID(temp) == 0)
                {
                    if (isSoundField(x - 1, y + 1, z) == 1)
                    {
                        procedureH(temp, x  - 1, y + 1, z, 2);
                    } if (isSoundField(x - 1, y + 1, z) != 1) {}
                    if (isSoundField(x + 1, y + 1, z) == 1)
                    {
                        procedureH(temp, x + 1 , y + 1, z, 1);
                    } if (isSoundField(x + 1, y + 1, z) != 1) {}
                    if (isSoundField(x, y + 1, z + 1) == 1)
                    {
                        procedureH(temp, x , y + 1, z + 1, 3);
                    } if (isSoundField(x, y + 1, z + 1) != 1) {}
                    if (isSoundField(x, y + 1, z - 1) == 1)
                    {
                        procedureH(temp, x , y + 1, z - 1, 4);
                    } if (isSoundField(x, y + 1, z - 1) != 1) {}

                }
                // linke Seite
                else if (getSideOfWave(temp) == 1 && getItemID(temp) == 0)
                {
                    if (isSoundField(x + 1, y + 1, z) == 1)
                    {
                        procedure(temp, x + 1, y + 1, z, 1);
                    } if (isSoundField(x + 1, y + 1, z) != 1) {}
                }
                //Rechte Seitenzugehörigkeit
                else if (getSideOfWave(temp) == 2 && getItemID(temp) == 0)
                {
                    if (isSoundField(x - 1, y + 1, z) == 1)
                    {
                        procedure(temp, x - 1, y + 1, z, 2);
                    } if (isSoundField(x - 1, y + 1, z) != 1) {}
                }
                else if (getSideOfWave(temp) == 3 && getItemID(temp) == 0)
                {
                    if (isSoundField(x, y + 1, z + 1) == 1)
                    {
                        procedure(temp, x, y + 1, z + 1, 3);
                    } if (isSoundField(x, y + 1, z + 1) != 1) {}
                }
                else if (getSideOfWave(temp) == 4 && getItemID(temp) == 0)
                {
                    if (isSoundField(x, y + 1, z - 1) == 1)
                    {
                        procedure(temp, x, y + 1, z - 1, 4);
                    } if (isSoundField(x, y + 1, z - 1) != 1) {}
                }
            }
            if ( getDirectionID(temp) == 6) {
                //unten links
                if ((getSideOfWave(temp) == 0) && getItemID(temp) == 0)
                {
                    if (isSoundField(x, y + 1, z) == 1)
                    {
                        procedureH(temp, x , y + 1, z, 2);
                    } if (isSoundField(x, y + 1, z) != 1) {}
                    if (isSoundField(x + 1, y, z) == 1)
                    {
                        procedureH(temp, x + 1 , y, z, 1);
                    } if (isSoundField(x + 1, y, z) != 1) {}
                    if (isSoundField(x - 1, y - 1, z + 1) == 1)
                    {
                        procedureH(temp, x , y - 1, z + 1, 3);
                    } if (isSoundField(x - 1, y - 1, z + 1) != 1) {}
                    if (isSoundField(x - 1, y - 1, z - 1) == 1)
                    {
                        procedureH(temp, x - 1 , y - 1, z - 1, 4);
                    } if (isSoundField(x - 1, y - 1, z - 1) != 1) {}

                }
                // linke Seite
                else if (getSideOfWave(temp) == 1 && getItemID(temp) == 0)
                {
                    if (isSoundField(x + 1, y, z) == 1)
                    {
                        procedure(temp, x + 1, y, z, 1);
                    } if (isSoundField(x + 1, y, z) != 1) {}
                }
                //Rechte Seitenzugehörigkeit
                else if (getSideOfWave(temp) == 2 && getItemID(temp) == 0)
                {
                    if (isSoundField(x, y + 1, z) == 1)
                    {
                        procedure(temp, x, y + 1, z, 2);
                    } if (isSoundField(x, y + 1, z) != 1) {}
                }
                else if (getSideOfWave(temp) == 3 && getItemID(temp) == 0)
                {
                    if (isSoundField(x + 1, y + 1, z + 1) == 1)
                    {
                        procedure(temp, x + 1, y + 1, z + 1, 3);
                    } if (isSoundField(x + 1, y + 1, z + 1) != 1) {}
                }
                else if (getSideOfWave(temp) == 4 && getItemID(temp) == 0)
                {
                    if (isSoundField(x + 1, y + 1, z - 1) == 1)
                    {
                        procedure(temp, x + 1, y + 1, z - 1, 4);
                    } if (isSoundField(x + 1, y + 1, z - 1) != 1) {}
                }
            }
            else if ( getDirectionID(temp) == 7) {
                // links
                if ((getSideOfWave(temp) == 0) && getItemID(temp) == 0)
                {
                    if (isSoundField(x - 1, y + 1, z) == 1)
                    {
                        procedureH(temp, x - 1 , y + 1, z, 2);
                    } if (isSoundField(x - 1, y + 1, z) != 1) {}
                    if (isSoundField(x + 1, y - 1, z) == 1)
                    {
                        procedureH(temp, x + 1 , y - 1, z, 1);
                    } if (isSoundField(x + 1, y - 1, z) != 1) {}
                    if (isSoundField(x, y, z + 1) == 1)
                    {
                        procedureH(temp, x , y, z + 1, 3);
                    } if (isSoundField(x - 1, y, z + 1) != 1) {}
                    if (isSoundField(x - 1, y, z - 1) == 1)
                    {
                        procedureH(temp, x - 1, y, z - 1, 4);
                    } if (isSoundField(x - 1, y, z - 1) != 1) {}

                }
                // linke Seite
                // Wenn du kein Seitenteil bist oder zur Linken seite gehörst
                else if (getSideOfWave(temp) == 1 && getItemID(temp) == 0)
                {
                    if (isSoundField(x + 1, y - 1, z) == 1)
                    {
                        procedure(temp, x + 1, y - 1, z, 1);
                    } if (isSoundField(x + 1, y - 1, z) != 1) {}
                }
                //Rechte Seitenzugehörigkeit
                else if (getSideOfWave(temp) == 2 && getItemID(temp) == 0)
                {
                    if (isSoundField(x - 1, y + 1, z) == 1)
                    {
                        procedure(temp, x - 1, y + 1, z, 2);
                    } if (isSoundField(x - 1, y + 1, z) != 1) {}
                }
                else if (getSideOfWave(temp) == 3 && getItemID(temp) == 0)
                {
                    if (isSoundField(x + 1, y, z + 1) == 1)
                    {
                        procedure(temp, x + 1, y, z + 1, 3);
                    } if (isSoundField(x + 1, y, z + 1) != 1) {}
                }
                else if (getSideOfWave(temp) == 4 && getItemID(temp) == 0)
                {
                    if (isSoundField(x + 1, y, z - 1) == 1)
                    {
                        procedure(temp, x + 1, y, z - 1, 4);
                    } if (isSoundField(x + 1, y, z - 1) != 1) {}
                }
            }
            else if ( getDirectionID(temp) == 8) {
                //oben links
                if ((getSideOfWave(temp) == 0) && getItemID(temp) == 0)
                {
                    if (isSoundField(x + 1, y, z) == 1)
                    {
                        procedureH(temp, x + 1 , y, z, 2);
                    } if (isSoundField(x + 1, y, z) != 1) {}
                    if (isSoundField(x, y - 1, z) == 1)
                    {
                        procedureH(temp, x , y - 1, z, 1);
                    } if (isSoundField(x, y - 1, z) != 1) {}
                    if (isSoundField(x - 1, y - 1, z + 1) == 1)
                    {
                        procedureH(temp, x - 1 , y - 1, z + 1, 3);
                    } if (isSoundField(x - 1, y - 1, z + 1) != 1) {}
                    if (isSoundField(x - 1, y - 1, z - 1) == 1)
                    {
                        procedureH(temp, x - 1 , y - 1, z - 1, 4);
                    } if (isSoundField(x - 1, y - 1, z - 1) != 1) {}

                }
                // linke Seite
                else if (getSideOfWave(temp) == 1 && getItemID(temp) == 0)
                {
                    if (isSoundField(x, y - 1, z) == 1)
                    {
                        procedure(temp, x, y - 1, z, 1);
                    } if (isSoundField(x, y - 1, z) != 1) {}

                }
                //Rechte Seitenzugehörigkeit
                else if (getSideOfWave(temp) == 2 && getItemID(temp) == 0)
                {
                    if (isSoundField(x + 1, y, z) == 1)
                    {
                        procedure(temp, x + 1, y, z, 2);
                    } if (isSoundField(x + 1, y, z) != 1) {}
                }
                else if (getSideOfWave(temp) == 3 && getItemID(temp) == 0)
                {
                    if (isSoundField(x - 1, y + 1, z + 1) == 1)
                    {
                        procedure(temp, x - 1, y + 1, z + 1, 3);
                    } if (isSoundField(x - 1, y + 1, z + 1) != 1) {}
                }
                else if (getSideOfWave(temp) == 4 && getItemID(temp) == 0)
                {
                    if (isSoundField(x - 1, y + 1, z - 1) == 1)
                    {
                        procedure(temp, x - 1, y + 1, z - 1, 4);
                    } if (isSoundField(x - 1, y + 1, z - 1) != 1) {}
                }
            }
        }
    } else {}
}
