#ifndef COLLISION_H
#define COLLISION_H
#include <stdbool.h>

void absorption(item_node *node,float coeff);
void interference(int x, int y, int z);
bool checkSoundValid(item_node *node,int x,int y, int z);
#endif
