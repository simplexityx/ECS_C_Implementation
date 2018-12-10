#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include "manager.h"
#include "map.h"
typedef struct assetManager assetManager_t;
typedef void(*create_object_t)(  Vector2D_t, int, const char*);
typedef void (*create_bullet_t) (Vector2D_t, Vector2D_t, int, const char *);
typedef void(*create_tile_t)(Vector2D_t, const char*,  tileTypes_t tileType);
typedef SDL_Texture * (*get_texture_t)(char *);
typedef void (*add_texture_t)( char *, char *);
typedef void (*generate_particles_t)(Vector2D_t, int);
typedef void (*create_ai_t)(Vector2D_t, int, const char*);
typedef void (*create_goal_t)(Vector2D_t);

typedef void (*create_text_t)(Vector2D_t, char *);


struct assetManager{
    map_t *map;
    create_object_t create_player;
    create_ai_t create_bear;
    create_object_t create_obstacle;
    create_bullet_t create_projectile;
    create_tile_t create_tile;

    create_goal_t create_goal;
    create_text_t create_text;
    
    generate_particles_t generate_particles;

    add_texture_t add_tex;
    get_texture_t get_tex;

    
};


assetManager_t *assetManager_create();

void assetManager_destroy(assetManager_t *am);
#endif