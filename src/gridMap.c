#include "../includes/GridMap.h"
#include "../includes/entities.h"
#include "../includes/tileComponent.h"
#include "../includes/statComponent.h"
#include "../includes/renderer.h"
#include "../includes/textComponent.h"
#include "../includes/aiComponent.h"

int AABB(SDL_Rect *a, SDL_Rect *b){
    if(a->x < b->x  + b->w &&
       a->x + a->w > b->x &&
       a->y < b->y + b->h &&
       a->y + a->h > b->y)
    {
        return 1;
    }
    return 0;
    

}


//co1 collides, co2 is the one being collided into
//this function is fucked up must rewrite (perhaps use observables)
void collisionReaction(void *c1, void *c2){
    colliderComponent_t *co1 = (colliderComponent_t*)c1;
    colliderComponent_t *co2 = (colliderComponent_t*)c2;

    entities_t *co1Entity = co1->entity;
    entities_t *co2Entity = co2->entity;

    if(co1Entity->active == 0 || co2Entity->active == 0){
        return;
    }
    
    switch(co1->col[0].tag){
        case CREATURE:

            if(co2->col[0].tag == GOAL){
                gameWon = 1;
                printf("you lost!\n");
                return;
            }

            if(co2->col[0].tag == CREATURE || co2->col[0].tag == PLAYER){
                transformComponent_t *t1 = get_component(co1->entity, Transform);

                transformComponent_t *t2 = get_component(co2->entity, Transform);
                statComponent_t *s = get_component(co2->entity, Stat);

                //calculate amount of pushback
                Vector2D_t pushback;
                pushback.x = t2->pos.x + t1->speed.x;
                pushback.y = t2->pos.y + t1->speed.y;
                
                //calculate amount of negative pushback
                Vector2D_t nPushback;
                nPushback.x = t2->pos.x - t1->speed.x;
                nPushback.y = t2->pos.y - t1->speed.y;

                //set hp (-15)
                s->set_hp(s, 15);

                //if hp is less than 0 remove the entity (should move this to the stat component)
                if(s->hp <= 0){
                       // s->observable->unsubscribe(s->observable, NULL);
                        entities_t *entity = co2->entity;
                        entity->active = 0;
                        aiComponent_t *ai = get_component(co1Entity, AI);
                        ai->change_state(ai, GOING_FOR_GOAL);
                        return;
                }
                //set the reaction of the collision for both parties
                t2->set_point(t2, pushback, DAMAGETAKING, t2->moveSpeed);
                t1->set_point(t1, nPushback, DAMAGETAKING, t1->moveSpeed);
            }
            break;

        case PROJECTILES:
            
            if(co2->col[0].tag != PLAYER && co2->col[0].tag != TERRAIN){
                entities_t *e = (entities_t*)co1->entity;
                if(has_component(co2->entity, Stat) == 1){

                    statComponent_t *s = get_component(co2->entity, Stat);
                    //textComponent_t *text = get_component(enemy_hp_bar, Text);

                    //s->observable->subscribe(s, text->observer);
                    s->set_hp(s, 15);
                    if(s->hp <= 0){
                        //s->observable->unsubscribe(s->observable, NULL);
                        entities_t *entity = co2->entity;
                        entity->active = 0;

                        
                    }
                }
                e->active = 0;
            }
            break;  

        case PLAYER:
            
            if(has_component(co2->entity, Tile) > 0){
                tileComponent_t *tile = (tileComponent_t *)get_component(co2->entity, Tile);
                spriteComponent_t *s = (spriteComponent_t *)get_component(co1->entity, Sprite);
                if(tile->tileType == WATER){
                    s->set_tex(s, "boat");
                }else{
                    s->set_tex(s, "wizard");
                }
            }


            break;

        default:
            break;
    }
    
    return;
}


void trigger_reaction(colliderComponent_t *c1, colliderComponent_t *c2){

    if(c2->col[0].tag != PLAYER && c2->col[0].tag != CREATURE){
        return;
    }
    aiComponent_t *ai = get_component(c1->entity, AI);
    assert(c2 != NULL);
    assert(ai != NULL);
    if(ai->focus == c2->entity)
        return;

    ai->focus = c2->entity;
    ai->change_state(ai, ATTACK);

}




elem_t *elem_create(void *rect){

    elem_t *e = malloc(sizeof(elem_t));
    e->rect = rect;
    return e;
}

grid_t *grid_create(){

    grid_t *g = malloc(sizeof(grid_t));
    for(int x = 0; x < 2; x++){
        for(int y = 0; y < 2; y++){
            g->c[x][y].elem = calloc(ELEMENTS_PER_CELL, sizeof(elem_t *));
            g->c[x][y].curSize = 0;
        }
    }
    return g;
}



void check_collision2(grid_t *g, int x, int y, int idx){
    colliderComponent_t *c1 = g->c[x][y].elem[idx]->rect;
    //if(c1->col[0].tag == OBSTACLE || c1->col[0].tag == TERRAIN);
       //return;
    for(int i = 0; i < g->c[x][y].curSize; i++){
        colliderComponent_t *c2 = g->c[x][y].elem[i]->rect;
        if(i != idx){

            if(c1->vision == 1){
                if(AABB(&c1->col[1].col, &c2->col[0].col) == 1){
                    trigger_reaction(c1, c2);
                }
            }
            if(AABB(&c1->col[0].col, &c2->col[0].col) == 1){
                collisionReaction(c1, c2);
            }
        }
    }
    return;
}


void grid_check_collision(grid_t *grid){

    for(int x = 0; x < 2; x++){
        for(int y = 0; y < 2; y++){
            for(int i = 0; i < grid->c[x][y].curSize; i++){
                check_collision2(grid, x, y, i);
            }
        }
    }
}




int grid_insert(grid_t *grid, colliderComponent_t *collider){
    if(collider->col[0].col.x >= 800 || collider->col[0].col.y >= 600 || collider->col[0].col.x < 0 || collider->col[0].col.y < 0){
        return 0;
    }


    int cellX = collider->col[0].col.x / (800/2);
    int cellY = collider->col[0].col.y / (600/2);
    int currentSize = grid->c[cellX][cellY].curSize;
    elem_t *elem = elem_create(collider);
    

    grid->c[cellX][cellY].elem[currentSize] = elem;
    
    
   
    //int res = check_collision(grid, cellX , cellY, currentSize);
    grid->c[cellX][cellY].curSize++;

    return 0;
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