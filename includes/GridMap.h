#ifndef GRIDMAP_H
#define GRIDMAP_H
#include <SDL2/SDL.h>
#define START_CELL_AMOUNT 10
#include "colliderComponent.h"
#include "transformComponent.h"

#define PIXELSX 128
#define PIXESLY 128
#define ELEMENTS_PER_CELL 100
typedef int (*collision_t) (colliderComponent_t *, colliderComponent_t *);

typedef struct elem elem_t;
struct elem{
    void *rect;
};


typedef struct cell cell_t;
struct cell{
    elem_t **elem;
    int curSize;
};

typedef struct grid grid_t;

struct grid{
    cell_t c[2][2];
    collision_t collision;
};

grid_t *grid_create();

int grid_insert(grid_t *grid, colliderComponent_t *rect);

void grid_destroy(grid_t *grid);




#endif