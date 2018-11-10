#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include "manager.h"
#include "map.h"
typedef struct assetManager assetManager_t;
typedef void(*create_object_t)(  Vector2D_t, Vector2D_t, const char*);
typedef void(*create_tile_t)(Vector2D_t, const char*);
typedef SDL_Texture * (*get_texture_t)(char *);
typedef void (*add_texture_t)( char *, char *);
struct assetManager{
    map_t *map;
    create_object_t create_player;
    create_object_t create_bear;
    create_object_t create_obstacle;
    create_object_t create_projectile;
    create_tile_t create_tile;
    add_texture_t add_tex;
    get_texture_t get_tex;
};


assetManager_t *assetManager_create();

void assetManager_destroy(assetManager_t *am);
#endif