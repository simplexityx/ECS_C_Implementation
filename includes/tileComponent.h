#ifndef TILECOMPONENT_H
#define TILECOMPONENT_H

#include "headers.h"

struct tileComponent{
    tileTypes_t tileType;
};

tileComponent_t *tile_create(tileTypes_t type);

void tile_init(void *e, void *c);
void tile_update(void *c);
void tile_draw(void *c);
void tile_destroy(void *c);

#endif