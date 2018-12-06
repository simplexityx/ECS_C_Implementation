#include "../includes/colliderComponent.h"
#include "../includes/entities.h"
#include "../includes/statComponent.h"
#include "../includes/headers.h"

void collider_init(void *e, void *c){
    colliderComponent_t *co = (colliderComponent_t*)c;
    co->t = get_component(e, Transform);
    co->s = get_component(e, Sprite);
    co->col[0].col.x = co->t->pos.x;
    co->col[0].col.y = co->t->pos.y;
    co->col[0].col.w = co->s->src.w;
    co->col[0].col.h = co->s->src.h;
    
    if(co->vision == 1){

        co->col[1].col.x = co->col[0].col.x - 200;
        co->col[1].col.y = co->col[0].col.y - 200;
        co->col[1].col.w = 200 * 2;
        co->col[1].col.h = 200 *2;
    }else{

        co->col[1].col.x = co->col[1].col.y = co->col[1].col.w = co->col[1].col.h = 0;

    }
    co->entity = e;
    return;
}


void collider_update(void *c){
    colliderComponent_t *co = (colliderComponent_t*)c;
    co->col[0].col.x = co->t->pos.x;
    co->col[0].col.y = co->t->pos.y;
    if(co->vision == 1){
        co->col[1].col.x = co->col[0].col.x - 200;
        co->col[1].col.y = co->col[0].col.y - 200;
    }

    if(co->col[0].col.x > 800 || co->col[0].col.x < 0 || co->col[0].col.y > 600 || co->col[0].col.y < 0){
        entities_t *e = co->entity;
        e->active = 0;
    }

    return;
}

void collider_draw(void *c){
    return;
}


colliderComponent_t * collider_create(Groups_t tag, char vision){
    colliderComponent_t *c = malloc(sizeof(colliderComponent_t));
    c->vision = vision;
    c->col[0].tag = tag;
    c->col[1].tag = TRIGGER;

    return c;
}