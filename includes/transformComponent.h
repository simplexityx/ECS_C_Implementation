#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H
#include "headers.h"

typedef void (*set_trans_t) (void *,int, int);

struct transformComponent{
    char idx;
    int x, y, speedX, speedY, oldX, oldY;
    void *entity;
    init_t init;
    update_t update;
    draw_t draw;
    set_trans_t set_trans;
};

transformComponent_t *transform_create(int x, int y, int speedX, int speedY);





#endif