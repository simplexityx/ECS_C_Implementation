#ifndef KEYBOARDCOMPONENT_H
#define KEYBOARDCOMPONENT_H
#include "entities.h"

typedef struct keyboardComponent keyboardComponent_t;

struct keyboardComponent{
    transformComponent_t *t;
    spriteComponent_t *s;
    void *entity;
    init_t init;
    update_t update;
    draw_t draw;
    const Uint8 *keyboard_state_array;
};

keyboardComponent_t *keyboard_create();



#endif