#ifndef COLLIDER_COMPONENT_H
#define COLLIDER_COMPONENT_H
#include "headers.h"
typedef struct colliderComponent colliderComponent_t;
typedef void (*col_t) (void *);
struct colliderComponent{
    char idx;
    SDL_Rect col;
    void *entity;
    init_t init;
    update_t update;
    draw_t draw;
    transformComponent_t *t;
    col_t collision;
};

colliderComponent_t *collider_create();



#endif