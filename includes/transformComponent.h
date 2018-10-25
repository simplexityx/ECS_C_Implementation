#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H
#include "headers.h"


struct transformComponent{
    int x, y;
    void *entity;
    init_t init;
    update_t update;
    draw_t draw;
};

transformComponent_t *transform_create();





#endif