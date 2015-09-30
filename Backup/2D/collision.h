#ifndef COLLISION_H
#define COLLISION_H
#include <stdbool.h>

void absorption(item_node *node,int x, int y,float coeff);

void interference(int x, int y);

void checkSoundValid(item_node *node,int x,int y);
#endif