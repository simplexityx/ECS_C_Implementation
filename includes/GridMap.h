#ifndef GRIDMAP_H
#define GRIDMAP_H
#include <SDL2/SDL.h>
#define START_CELL_AMOUNT 10
#include "colliderComponent.h"
#define PIXELSX 128
#define PIXESLY 128
typedef struct elem elem_t;
struct elem{
    void *rect;
    elem_t *next;
};


typedef struct cell cell_t;
struct cell{
    elem_t elem[10];
    int curSize;
};

typedef struct grid grid_t;

struct grid{
    cell_t c[7][5];
};

grid_t *grid_create();

void grid_insert(grid_t *grid, colliderComponent_t *rect);






#endif