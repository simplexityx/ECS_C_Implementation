#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include "manager.h"

typedef struct assetManager assetManager_t;
typedef void(*create_player_t)(SDL_Renderer*, manager_t*, int, int, int, int, const char*);
typedef void(*create_obstacle_t)(SDL_Renderer*, manager_t*, int, int, int, int, const char*);
typedef void (*create_magic_t)(SDL_Renderer *, manager_t *, int, int, int, int, const char *);

struct assetManager{
    manager_t *manager;
    create_magic_t create_magic;
    create_player_t create_player;
    create_obstacle_t create_obstacle;
};


assetManager_t *assetManager_create(manager_t *m);

#endif