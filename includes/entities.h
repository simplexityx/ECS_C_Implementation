#ifndef ECS_H
#define ECS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct entities entities_t;

typedef enum compTypes {
    Transform,
    Sprite
}compTypes_t;

typedef struct transformComponent transformComponent_t;
typedef struct spriteComponent spriteComponent_t;

transformComponent_t *create_trans();
spriteComponent_t *create_sprite();




typedef struct Components Components_t;
struct Components{
    compTypes_t type;
    void *component;
};


typedef void (*update_t)(void*);



struct entities{
    update_t update;
    char active;
    int compCount;
    Components_t **components;
    entities_t *next, *prev;
};

entities_t *entities_create();

void add_component(entities_t *e, void *c, compTypes_t type);

Components_t *get_component(entities_t *e, compTypes_t type);





#endif