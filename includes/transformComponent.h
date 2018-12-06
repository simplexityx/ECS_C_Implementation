#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H
#include "headers.h"
#include "vector2D.h"
typedef void (*set_trans_t) (void *,int, int);
typedef int (*set_point_t) (transformComponent_t *, Vector2D_t, char);

struct transformComponent{
    Vector2D_t pos, speed, oldPos;
    int moveSpeed, moving;
    set_trans_t set_speed;
    set_point_t set_point;
    uint32_t lastUpdate, timerId;
};

transformComponent_t *transform_create(Vector2D_t pos, Vector2D_t speed, int moveSpeed);

void transform_init(void *e, void *c);

void transform_update(void *c);


void transform_draw(void *c);

void transform_destroy(void *c);


#endif