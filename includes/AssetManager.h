#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include "manager.h"

typedef struct assetManager assetManager_t;
typedef void(*create_player_t)(  int, int, int, int, const char*);
typedef void(*create_obstacle_t)( int, int, int, int, const char*);

struct assetManager{
    
    create_player_t create_player;
    create_obstacle_t create_obstacle;
};


assetManager_t *assetManager_create();

#endif