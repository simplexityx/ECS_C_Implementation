#ifndef COLLIDER_COMPONENT_H
#define COLLIDER_COMPONENT_H
#include "headers.h"
typedef struct colliderComponent colliderComponent_t;

struct colliderComponent{
    SDL_Rect col;
    void *entity;
    init_t init;
    update_t update;
    draw_t draw;
};

colliderComponent_t *collider_create();



#endif