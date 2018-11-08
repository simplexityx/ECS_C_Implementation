#ifndef RENDERER_H
#define RENDERER_H
#include <SDL2/SDL.h>
#include <stdlib.h>
#include "AssetManager.h"
typedef struct renderer{
    SDL_Renderer *renderer;
    SDL_Window *win;
    char running;
    SDL_Event event;
}renderer_t;

SDL_Renderer *renderer;
assetManager_t *assetmanager;
manager_t *manager;
renderer_t *renderer_create();

void renderer_init(const char *title, int xpos, int ypos, int screenWidth, int screenHeight, renderer_t *r);

void update();

void draw();

void eventHandler(void *r);

void clean(renderer_t *r);




#endif