#include "../includes/tileComponent.h"


tileComponent_t *tile_create(tileTypes_t tile){

    tileComponent_t *t = malloc(sizeof(tileComponent_t));

    t->tileType = tile;
    return t;
}


void tile_init(void *e, void *c){
}
void tile_update(void *c){
}
void tile_draw(void *c){
}
void tile_destroy(void *c){
}