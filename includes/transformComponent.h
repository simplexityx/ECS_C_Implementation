#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H
#include "headers.h"
#include "vector2D.h"
typedef void (*set_trans_t) (void *,int, int);

struct transformComponent{
    //float x, y, speedX, speedY, oldX, oldY;
    Vector2D_t pos, speed, oldPos;
    void *entity;
    init_t init;
    update_t update;
    draw_t draw;
    set_trans_t set_trans;
    uint32_t lastUpdate;
};

//transformComponent_t *transform_create(int x, int y, int speedX, int speedY);
transformComponent_t *transform_create(Vector2D_t pos, Vector2D_t speed);





#endif