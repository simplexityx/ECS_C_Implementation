#include "../includes/transformComponent.h"
#include "entities.h"

void transform_init(void *e, void *c){
    transformComponent_t *t = (transformComponent_t*)c;
    t->entity = e;
    return;
}

void transform_update(void *c){
    transformComponent_t *t = (transformComponent_t *)c;
    t->x += t->speedX;
    t->y += t->speedY;
    return;
}


void transform_draw(void *c){
    return;
}

void set_transform(void *c, int x, int y){
    transformComponent_t *t = (transformComponent_t *)c;
    t->speedX = x;
    t->speedY = y;
    return;
}


transformComponent_t *transform_create(int x, int y, int speedX, int speedY){
    static int i;
    transformComponent_t *t = malloc(sizeof(transformComponent_t));
    t->speedX = speedX;
    t->speedY = speedY;
    t->x = x;
    t->y = y;
    t->init = transform_init;
    t->update = transform_update;
    t->draw = transform_draw;
    t->set_trans = set_transform;

    if(i == 0){
        idxgiver++;
        i = idxgiver;
    }
    t->idx = i;

    return t;
}
