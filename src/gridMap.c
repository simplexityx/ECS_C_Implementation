#include "../includes/GridMap.h"

grid_t *grid_create(){

    grid_t *g = malloc(sizeof(grid_t));
    return g;
}


void check_collision(elem_t *elem, int idx){

    if(idx == 0)
        return;

    
    for(int i = 0; i < idx; i++){

        //DO AABB CHECK HERE AND CALL THE COLLISION COMPONENT FUNCTION

    }
    return;
}


void grid_insert(grid_t *grid, colliderComponent_t *rect){

    int a = grid->c[rect->col.x/PIXELSX][rect->col.y/PIXESLY].curSize;
    grid->c[rect->col.x/PIXELSX][rect->col.y/PIXESLY].elem[a];

    check_collision(&grid->c[rect->col.x/PIXELSX][rect->col.y/PIXESLY].elem[a], a);

    grid->c[rect->col.x/PIXELSX][rect->col.y/PIXESLY].curSize++;



}