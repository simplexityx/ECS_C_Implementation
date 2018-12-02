#include "../includes/colliderComponent.h"
#include "../includes/entities.h"




void collider_init(void *e, void *c){
    colliderComponent_t *co = (colliderComponent_t*)c;
    co->t = get_component(e, Transform);
    co->col.x = co->t->pos.x;
    co->col.y = co->t->pos.y;
    if(co->tag == PROJECTILES){
        co->col.w = 8;
        co->col.h = 8;
    }
    co->col.w = 32;
    co->col.h = 32;
    co->entity = e;
    return;
}


void collider_update(void *c){
    colliderComponent_t *co = (colliderComponent_t*)c;
    co->col.x = co->t->pos.x;
    co->col.y = co->t->pos.y;
    return;
}

void collider_draw(void *c){
    return;
}


colliderComponent_t * collider_create(Groups_t tag){
    colliderComponent_t *c = malloc(sizeof(colliderComponent_t));
   
    c->tag = tag;
    
    return c;
}