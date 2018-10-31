#include "../includes/textureManager.h"
#include <SDL2/SDL_image.h>


SDL_Texture *load_texture(const char *filepath, SDL_Renderer *rend){
    SDL_Surface *s = IMG_Load(filepath);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(rend, s);
    SDL_FreeSurface(s);
    return tex;
}

void draw_texture(SDL_Texture *tex, SDL_Rect src, SDL_Rect dst, SDL_Renderer *rend){
    SDL_RenderCopy(rend, tex, &src, &dst);
}

