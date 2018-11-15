#include "../includes/GridMap.h"
#include "../includes/entities.h"
int AABB(colliderComponent_t *a, colliderComponent_t *b){

    if(a->col.x < b->col.x  + b->col.w &&
       a->col.x + a->col.w > b->col.x &&
       a->col.y < b->col.y + b->col.h &&
       a->col.y + a->col.h > b->col.y)
    {
        return 1;
    }
    return 0;
}

void n(){
    return;
}

//co1 collides, co2 is the one being collided into
void collisionReaction(void *c1, void *c2){
    colliderComponent_t *co1 = (colliderComponent_t*)c1;
    colliderComponent_t *co2 = (colliderComponent_t*)c2;

    switch(co1->tag){
        
        case PROJECTILES:
            n();
            if(co2->tag != PLAYER){
                entities_t *e = (entities_t*)co1->entity;
                e->active = 0;
            }
            
            break;    
            //remove entity 
        case PLAYER:
            co1->t->pos = co1->t->oldPos;
            break;
        default:
            break;
    }
    
    return;
}




elem_t *elem_create(void *rect){

    elem_t *e = malloc(sizeof(elem_t));
    e->rect = rect;
    return e;
}

grid_t *grid_create(){

    grid_t *g = malloc(sizeof(grid_t));
    g->collision = AABB;
    for(int x = 0; x < 2; x++){
        for(int y = 0; y < 2; y++){
            g->c[x][y].elem = calloc(ELEMENTS_PER_CELL, sizeof(elem_t *));
            g->c[x][y].curSize = 0;
        }
    }
    return g;
}


int check_collision(grid_t *g, int x, int y, int idx){
    if(idx == 0){
        return 0;
    }
    for(int i = 0; i < idx; i++){
        //DO AABB CHECK HERE AND CALL THE COLLISION COMPONENT FUNCTION
        if(g->collision(g->c[x][y].elem[i]->rect, g->c[x][y].elem[idx]->rect) == 1){
            colliderComponent_t *c = (colliderComponent_t *) g->c[x][y].elem[idx]->rect;
            colliderComponent_t *c2 = (colliderComponent_t *) g->c[x][y].elem[i]->rect;
            collisionReaction(c, c2);
        }
    }

    return 0;
}


int grid_insert(grid_t *grid, colliderComponent_t *collider){
    if(collider->col.x >= 800 || collider->col.y >= 600 || collider->col.x < 0 || collider->col.y < 0){
        return 0;
    }

    int cellX = collider->col.x / (800/2);
    int cellY = collider->col.y / (600/2);
    int currentSize = grid->c[cellX][cellY].curSize;
    elem_t *elem = elem_create(collider);
   
    grid->c[cellX][cellY].elem[currentSize] = elem;
    

    int res = check_collision(grid, cellX , cellY, currentSize);
    grid->c[cellX][cellY].curSize++;

    return res;
}


void cell_destroy(cell_t cell){

    for(int i = 0; i < cell.curSize; i++){
        free(cell.elem[i]);
    }
    free(cell.elem);
    return;
}


void grid_destroy(grid_t *grid){
     for(int x = 0; x < 2; x++){
        for(int y = 0; y < 2; y++){
            cell_destroy(grid->c[x][y]);
        }
    }
    free(grid);
}