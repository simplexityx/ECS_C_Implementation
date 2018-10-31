#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include <SDL2/SDL.h>


SDL_Texture *load_texture(const char *filepath, SDL_Renderer *rend);
void draw_texture(SDL_Texture *tex, SDL_Rect src, SDL_Rect dst, SDL_Renderer *rend);

#endif