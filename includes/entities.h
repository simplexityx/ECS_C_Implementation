#ifndef ECS_H
#define ECS_H
#include "headers.h"
#include "transformComponent.h"
#include "spriteComponent.h"
#include "colliderComponent.h"
#include "keyboardComponent.h"
#include <stdarg.h>

typedef struct Components Components_t;
struct Components{
    compTypes_t type;
    void *component;
};

struct entities{

    update_t update;
    draw_t draw;
    char active;
    int compCount;
    Components_t **components;
    entities_t *next, *prev;
  
};

entities_t *entities_create();

void add_component(entities_t *e, compTypes_t type, void *c);

void *get_component(void *e, compTypes_t type);

int has_component(entities_t *e, compTypes_t type);

void destroy_entity(entities_t *e);



#endif