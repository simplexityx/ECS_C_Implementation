#include "../includes/collisions.h"
#include "../includes/colliderComponent.h"
#include "../includes/statComponent.h"
#include "../includes/entities.h"
#include <assert.h>


void handle_tile_collisions(entities_t *e1, entities_t *e2){

    

    return;
}


void handle_collisions(void *col1, void *col2){

    colliderComponent_t *c1 = col1;
    colliderComponent_t *c2 = col2;

    entities_t *e1 = c1->entity;
    entities_t *e2 = c2->entity;

    //if either of them are inactive (died previously on same frame and is scheduled to be removed) we ignore this collision
    if(e1->active == 0 || e2->active = 0){
        return;
    }

    //check if we are colliding with a tile
    if(has_component(e2, Tile)){
        if(c1->col[0].tag != PROJECTILES){
            
        }
    }
    






}



void handle_triggercollisions(void *col1, void *col2){




}

