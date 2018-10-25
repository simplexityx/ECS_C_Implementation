#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H
#include "headers.h"

struct spriteComponent{

    char *filepath;
    void *entity;
    update_t update;
    draw_t draw;
};

spriteComponent_t *sprite_create();

#endif