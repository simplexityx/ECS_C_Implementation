#ifndef MANAGER_H
#define MANAGER_H
#include "entities.h"
#include "headers.h"
#define GROUPMAX    32

typedef struct group group_t;
typedef struct manager manager_t;

struct group{
    entities_t *head, *tail;
    int currentSize;
};

struct manager{
    group_t groups[GROUPMAX];
    int currentActiveGroups;
};


manager_t *manager_create();

void manager_insert(manager_t *m, entities_t *e, Groups_t group);

void manager_update(manager_t *m, Groups_t group);

void manager_draw(manager_t *m, Groups_t group);

void manager_refresh(manager_t *m);

void destroy_manager(manager_t *m);

void print_manager(manager_t *m);

#endif