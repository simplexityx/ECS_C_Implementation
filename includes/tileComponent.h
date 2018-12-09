#ifndef TILECOMPONENT_H
#define TILECOMPONENT_H

#include "headers.h"

typedef void (*colliding_reaction_t)(void *, void*);

struct tileComponent{
    tileTypes_t tileType;
    colliding_reaction_t colReact;
};

tileComponent_t *tile_create(tileTypes_t type);

void tile_init(void *e, void *c);
void tile_update(void *c);
void tile_draw(void *c);
void tile_destroy(void *c);

#endif