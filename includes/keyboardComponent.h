#ifndef KEYBOARDCOMPONENT_H
#define KEYBOARDCOMPONENT_H
#include "entities.h"
#include <assert.h>

typedef struct keyboardComponent keyboardComponent_t;

struct keyboardComponent{
    transformComponent_t *t;
    spriteComponent_t *s;
    const Uint8 *keyboard_state_array;
};

keyboardComponent_t *keyboard_create();


void keyboard_init(void *e, void *c);
void keyboard_update(void *c);
void keyboard_draw(void *c);
void keyboard_destroy(void *c);

#endif