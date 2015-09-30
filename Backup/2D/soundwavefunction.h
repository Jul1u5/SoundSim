
#ifndef SOUNDWAVEFUNCTION_H
#define SOUNDWAVEFUNCTION_H
void increaseMovement(item_node *node);

int getMovement(item_node *node);

void setMovement(item_node *node,int m);

void decSoundWithMovement(item_node *node);

void setSideOfWave(item_node *node, int side);

int getSideOfWave(item_node *node);

void changeReboundSideOfWave(item_node *node);

void setWaveRoot(item_node *node, item_node *rootnode);

item_node * getWaveRoot(item_node *node);

void addWave(item_node *node,int x, int y);
#endif