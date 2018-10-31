#include <stdio.h>
#include "../includes/renderer.h"
#include <stdarg.h>


int main(){
    
    renderer_t *r = renderer_create();
    renderer_init("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, r);
    while(r->running != 0){

        eventHandler(r);
        update(r);
        draw(r);
        SDL_Delay(1000 / 60);
    }
    clean(r);
    
    return 0;
}


