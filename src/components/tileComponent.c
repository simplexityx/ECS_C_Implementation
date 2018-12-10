#include "../../includes/tileComponent.h"


void tile_collide_reaction(void *tileComponent, void *entityColliding){

    tileComponent_t *tile = tileComponent;
    entities_t *e = entityColliding;

    if(tile->tileType == GRASS){
        return;
    }

    


}


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

    free(c);
}