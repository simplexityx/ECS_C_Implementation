#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include "manager.h"

typedef struct assetManager assetManager_t;
typedef void(*create_object_t)(  int, int, int, int, const char*);
typedef void(*create_tile_t)(int, int, const char*);
struct assetManager{
    
    create_object_t create_player;
    create_object_t create_obstacle;
    create_object_t create_projectile;
    create_tile_t create_tile;
};


assetManager_t *assetManager_create();

#endif