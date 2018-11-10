#include "../includes/transformComponent.h"
#include "../includes/entities.h"

void transform_init(void *e, void *c){
    transformComponent_t *t = (transformComponent_t*)c;
    t->entity = e;
    return;
}

void transform_update(void *c){
    transformComponent_t *t = (transformComponent_t *)c;
    t->oldPos = t->pos;
    unsigned long currentTime = SDL_GetTicks();
    unsigned long deltaTime = currentTime - t->lastUpdate;
    t->pos.x += t->speed.x *(deltaTime / 1000.0f);
    t->pos.y += t->speed.y *(deltaTime / 1000.0f);
   
    t->lastUpdate = currentTime;

    return;
}


void transform_draw(void *c){
    return;
}

void set_transform(void *c, int x, int y){
    transformComponent_t *t = (transformComponent_t *)c;
    t->speed.x = x;
    t->speed.y = y;
    return;
}


transformComponent_t *transform_create(Vector2D_t pos, Vector2D_t speed){
    transformComponent_t *t = malloc(sizeof(transformComponent_t));
    t->pos = pos;
    t->speed = speed;
    t->init = transform_init;
    t->update = transform_update;
    t->draw = transform_draw;
    t->set_trans = set_transform;
    t->lastUpdate = SDL_GetTicks();

    return t;
}
