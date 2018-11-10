#include "../includes/colliderComponent.h"
#include "../includes/entities.h"

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


void collider_init(void *e, void *c){
    colliderComponent_t *co = (colliderComponent_t*)c;
    co->entity = e;
    co->t = get_component(e, Transform);
    co->col.x = co->t->pos.x;
    co->col.y = co->t->pos.y;
    if(co->tag == PROJECTILES){
        co->col.w = 8;
        co->col.h = 8;
    }
    co->col.w = 32;
    co->col.h = 32;

    return;
}




void collider_update(void *c){
    colliderComponent_t *co = (colliderComponent_t*)c;

    transformComponent_t *t = (transformComponent_t *) get_component(co->entity, Transform); 
    
    co->col.x = t->pos.x;
    co->col.y = t->pos.y;

    if(co->col.x > 800 || co->col.x < 0 || co->col.y > 600 || co-> col.y < 0){
        entities_t *e = (entities_t *)co->entity;
        e->active = 0;
    }
    return;
}

void collider_draw(void *c){
    return;
}


colliderComponent_t * collider_create(Groups_t tag){
    colliderComponent_t *c = malloc(sizeof(colliderComponent_t));
    c->init = collider_init;
    c->update = collider_update;
    c->draw = collider_draw;
    c->collision = collisionReaction;
    c->tag = tag;
    
    return c;
}