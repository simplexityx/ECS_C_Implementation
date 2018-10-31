#include "../includes/transformComponent.h"
#include "entities.h"

void transform_init(void *e, void *c){
    transformComponent_t *t = (transformComponent_t*)c;
    t->entity = e;
    return;
}

void transform_update(void *c){
    transformComponent_t *t = (transformComponent_t *)c;
    t->x += t->speed;
    t->y += t->speed;
    return;
}


void transform_draw(void *c){
    return;
}


transformComponent_t *transform_create(int x, int y, int speed){
    
    transformComponent_t *t = malloc(sizeof(transformComponent_t));
    t->speed = speed;
    t->x = x;
    t->y = y;
    t->init = transform_init;
    t->update = transform_update;
    t->draw = transform_draw;
    return t;
}
