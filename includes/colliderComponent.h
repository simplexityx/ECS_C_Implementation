#ifndef COLLIDER_COMPONENT_H
#define COLLIDER_COMPONENT_H
#include "headers.h"
typedef struct colliderComponent colliderComponent_t;
typedef struct collider collider_t;
struct collider{
    SDL_Rect col;
    Groups_t tag;
};


typedef void (*col_t) (void *, void*);
struct colliderComponent{
    collider_t col[2];
    transformComponent_t *t;
    spriteComponent_t *s;
    void *entity;
    char vision;
};

colliderComponent_t *collider_create(Groups_t tag, char vision);

void collider_init(void *e, void *c);

void collider_update(void *c);

void collider_draw(void *c);

void collider_destroy(void *c);

#endif