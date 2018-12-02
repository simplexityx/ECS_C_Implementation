#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include <SDL2/SDL.h>

SDL_Texture *load_UI_text(char *text, SDL_Color textColor);

SDL_Texture *load_texture(const char *filepath);
void draw_texture(SDL_Texture *tex, SDL_Rect src, SDL_Rect dst, char flip);

#endif