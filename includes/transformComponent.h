#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H
#include "headers.h"
#include "vector2D.h"
typedef void (*set_trans_t) (void *,int, int);

struct transformComponent{
    Vector2D_t pos, speed, oldPos;
    
    set_trans_t set_trans;
    uint32_t lastUpdate;
};

transformComponent_t *transform_create(Vector2D_t pos, Vector2D_t speed);

void transform_init(void *e, void *c);

void transform_update(void *c);


void transform_draw(void *c);




#endif