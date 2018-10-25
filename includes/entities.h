#ifndef ECS_H
#define ECS_H
#include "headers.h"
#include "transformComponent.h"
#include "spriteComponent.h"

typedef struct Components Components_t;
struct Components{
    compTypes_t type;
    void *component;
};

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