#include "../includes/colliderComponent.h"
#include "../includes/entities.h"

void n(){
    return;
}

void collisionReaction(void *c){
    colliderComponent_t *co = (colliderComponent_t*)c;

    switch(co->tag){
        case SOLID:
            break;
        case DESTRUCTIBLE:
            n();
            //remove entity
            entities_t *e = (entities_t*)co->entity;

            e->active = 0;
            break;
        case HUMANOID:
            co->t->x = co->t->oldX;
            co->t->y = co->t->oldY;
            break;
        case TRIGGER:

            break;
    }
    
    return;
}


void collider_init(void *e, void *c){
    colliderComponent_t *co = (colliderComponent_t*)c;
    co->entity = e;
    co->t = get_component(e, Transform);
    co->col.x = co->t->x;
    co->col.y = co->t->y;
    if(co->tag == DESTRUCTIBLE){
        co->col.w = 16;
        co->col.h = 16;
    }
    co->col.w = 32;
    co->col.h = 32;

    return;
}




void collider_update(void *c){
    colliderComponent_t *co = (colliderComponent_t*)c;

    transformComponent_t *t = (transformComponent_t *) get_component(co->entity, Transform); 
    
    co->col.x = t->x;
    co->col.y = t->y;

    if(co->col.x > 800 || co->col.x < 0 || co->col.y > 600 || co-> col.y < 0){
        entities_t *e = (entities_t *)co->entity;
        e->active = 0;
    }
    return;
}

void collider_draw(void *c){
    return;
}


colliderComponent_t * collider_create(collisionTypes_t tag){
    colliderComponent_t *c = malloc(sizeof(colliderComponent_t));
    c->init = collider_init;
    c->update = collider_update;
    c->draw = collider_draw;
    c->collision = collisionReaction;
    c->tag = tag;
    
    return c;
}