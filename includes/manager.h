#ifndef MANAGER_H
#define MANAGER_H
#include "headers.h"
#include "entities.h"
typedef struct manager manager_t;

struct manager{
    int size;
    entities_t *head, *tail;
};


manager_t *manager_create();

void add_entity(manager_t *m, entities_t *e);


void manager_refresh(manager_t *m);

void print_manager(manager_t *m);

void destroy_manager(manager_t *m);

#endif