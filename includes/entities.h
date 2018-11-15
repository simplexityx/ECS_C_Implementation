#ifndef ECS_H
#define ECS_H
#include "headers.h"
#include "transformComponent.h"
#include "spriteComponent.h"
#include "colliderComponent.h"
#include "keyboardComponent.h"

typedef struct component component_t;
struct component{

    void *cData;
    compTypes_t type;

    entities_t *owner;

    init_t init;
    update_t update;
    draw_t draw;
    destroy_t destroy;
};

component_t *component_create(void *cData, init_t init, update_t update, draw_t draw, destroy_t destroy, compTypes_t type);


struct entities{

    update_t update;
    draw_t draw;
    destroy_t destroy;
    char active;
    uint32_t map;
    component_t **components;
    entities_t *next, *prev;
};


entities_t *entities_create();

void add_component(entities_t *entity, component_t *component);

void *get_component(entities_t *entity, compTypes_t type);

int has_component(entities_t *entity, compTypes_t type);

void remove_component(entities_t *entity, compTypes_t type);



#endif