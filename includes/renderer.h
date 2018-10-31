#ifndef RENDERER_H
#define RENDERER_H
#include <SDL2/SDL.h>
#include <stdlib.h>
#include "manager.h"
typedef struct renderer{
    SDL_Renderer *renderer;
    SDL_Window *win;
    char running;
    SDL_Event event;
    manager_t *manager;

}renderer_t;

renderer_t *renderer_create();

void renderer_init(const char *title, int xpos, int ypos, int screenWidth, int screenHeight, renderer_t *r);

void update(void *r);

void draw(void *r);

void eventHandler(void *r);

void clean(renderer_t *r);

void create_box(SDL_Renderer *rend, manager_t *m, int x, int y, int speed, const char *filepath);



#endif