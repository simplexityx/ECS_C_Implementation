#ifndef COLLIDER_COMPONENT_H
#define COLLIDER_COMPONENT_H
#include "headers.h"
typedef struct colliderComponent colliderComponent_t;
typedef void (*col_t) (void *, void*);
struct colliderComponent{
    SDL_Rect col;
    void *entity;
    init_t init;
    update_t update;
    draw_t draw;
    transformComponent_t *t;
    col_t collision;
    Groups_t tag;
};

colliderComponent_t *collider_create(Groups_t tag);

void collider_init(void *e, void *c);



void collider_update(void *c);

void collider_draw(void *c);


#endif