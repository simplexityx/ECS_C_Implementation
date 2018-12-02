#include "../includes/textureManager.h"
#include <SDL2/SDL_image.h>
#include "../includes/renderer.h"

SDL_Texture *load_texture(const char *filepath){
    SDL_Surface *s = IMG_Load(filepath);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, s);
    SDL_FreeSurface(s);
    return tex;
}

void draw_texture(SDL_Texture *tex, SDL_Rect src, SDL_Rect dst, char flip){
    SDL_RenderCopyEx(renderer, tex, &src, &dst, 0, NULL, flip);
}

SDL_Texture *load_UI_text(char *text, SDL_Color textColor){

    SDL_Surface *s = TTF_RenderText_Solid(font, text, textColor);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, s);
    SDL_FreeSurface(s);
    return tex;
}