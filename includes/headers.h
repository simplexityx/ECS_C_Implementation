#ifndef HEADERS_H
#define HEADERS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXCOMPONENTS   32
#include <SDL2/SDL.h>

typedef enum collisionTypes {
    SOLID,
    DESTRUCTIBLE,
    TRIGGER,
    HUMANOID

}collisionTypes_t;

typedef enum compTypes {
    Transform,
    Sprite,
    Collision,
    KeyBoard
}compTypes_t;


typedef enum Groups{
    PLAYER,
    OBSTACLE,
    PROJECTILES,
    TERRAIN,
}Groups_t;
int idxgiver;
typedef struct entities entities_t;

typedef struct spriteComponent spriteComponent_t;
typedef struct transformComponent transformComponent_t;
typedef void(*init_t) (void*, void*);
typedef void(*update_t) (void*);
typedef void(*draw_t) (void*);



#endif