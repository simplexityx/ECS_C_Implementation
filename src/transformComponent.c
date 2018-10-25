#include "../includes/transformComponent.h"
#include "entities.h"

void transform_init(void *e, void *c){
    transformComponent_t *t = (transformComponent_t*)c;
    t->entity = e;
    return;
}

void transform_update(void *c){

    transformComponent_t *t = (transformComponent_t *)c;
    entities_t *e = (entities_t*)t->entity;
    printf("current position: %d, %d this component belongs to: %d\n",t->x, t->y, e->id);
    t->x++;
    t->y = t->y;
    return;
}


void transform_draw(void *c){
    printf("in draw in transform component %d no need to do anything\n", *(int*)c);
    return;
}


transformComponent_t *transform_create(){
    
    transformComponent_t *t = malloc(sizeof(transformComponent_t));
    
    t->x = 25;
    t->y = 250;
    t->init = transform_init;
    t->update = transform_update;
    t->draw = transform_draw;
    return t;
}
