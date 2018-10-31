#include "../includes/renderer.h"


int get_random(){

    int n = rand() % 5;
    if(rand() % 2 == 0){
        n *= -1;
    }
    return n;
}


renderer_t *renderer_create(){
    renderer_t *r = malloc(sizeof(renderer_t));
    
    r->manager = manager_create();
    return r;
}

void renderer_init(const char *title, int xpos, int ypos, int screenWidth, int screenHeight, renderer_t *r){
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		r->win = SDL_CreateWindow(title, xpos, ypos, screenWidth, screenHeight, 0);
		
		r->renderer = SDL_CreateRenderer(r->win, -1, 0);
		if (r->renderer) {
			SDL_SetRenderDrawColor(r->renderer, 255, 255, 255, 255);
		}
    }
    r->running = 1;
    assetmanager = assetManager_create(r->manager);
    assetmanager->create_player(r->renderer, r->manager, 400, 200, 0,0, "Assets/wizardsheet1.png");

    return;
}

void update(void *r){
    renderer_t *re = (renderer_t *)r;
    manager_update(re->manager, GROUP1);
    manager_update(re->manager, GROUP2);
    manager_refresh(re->manager);
    return;
}

void draw(void *r){
    renderer_t *re = (renderer_t *)r;
    SDL_RenderClear(re->renderer);
    manager_draw(re->manager, GROUP1);
    manager_draw(re->manager, GROUP2);

    SDL_RenderPresent(re->renderer);
    return;
}

void eventHandler(void *r){
    renderer_t *re = r;
    int x, y;
    while(SDL_PollEvent(&re->event)){
        if (re->event.type == SDL_QUIT) {
            re->running = 0;
        }else if(re->event.type == SDL_MOUSEBUTTONDOWN){
            SDL_GetMouseState(&x, &y);
            assetmanager->create_obstacle(re->renderer, re->manager, x, y, get_random(), get_random(), "Assets/box.png");
        }
    }
    return;
}

void clean(renderer_t *r){
    SDL_DestroyRenderer(r->renderer);
    SDL_DestroyWindow(r->win);
    destroy_manager(r->manager);
    free(r);
    return;
}
