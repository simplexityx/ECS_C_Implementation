#include "../includes/renderer.h"
#include "../includes/GridMap.h"
#include "../includes/TerrainManager.h"

renderer_t *renderer_create(){
    renderer_t *r = malloc(sizeof(renderer_t));
    return r;
}


void init_textures_to_assetmanager(){

    assetmanager->add_tex("wizard", "Assets/wizardsheet1.png");
    assetmanager->add_tex("magic", "Assets/magic.png");
    assetmanager->add_tex("grass", "Assets/grass.png");
    assetmanager->add_tex("water", "Assets/water.png");
    assetmanager->add_tex("box", "Assets/box.png");
    assetmanager->add_tex("bear", "Assets/bear.png");

    return;
}


unsigned long ftimer1;

void renderer_init(const char *title, int xpos, int ypos, int screenWidth, int screenHeight, renderer_t *r){
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		r->win = SDL_CreateWindow(title, xpos, ypos, screenWidth, screenHeight, 0);
		
		renderer = SDL_CreateRenderer(r->win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}
    }
    r->running = 1;
    manager = manager_create();
    assetmanager = assetManager_create(manager);
    init_textures_to_assetmanager();
    assetmanager->create_player( Vector2(400, 200), Vector2(0,0), "wizard");

    assetmanager->create_bear(Vector2(100, 100), Vector2(0, 0), "bear");



    ParseLevel("./Map/map.map");
    ftimer1 = SDL_GetTicks();
    return;
}
void update(){
   

    grid_t *g = grid_create();
   
   
    for(entities_t *obstacles = get_group(manager, OBSTACLE); obstacles != NULL; obstacles = obstacles->next){
        obstacles->update(obstacles);
        if(has_component(obstacles, Collision)){
            grid_insert(g, get_component(obstacles, Collision));
        }

    }
    for(entities_t *tmp = get_group(manager, PLAYER);tmp != NULL; tmp = tmp->next){
        tmp->update(tmp);
        
        grid_insert(g, get_component(tmp, Collision));
    }
    
    for(entities_t *projectiles = get_group(manager, PROJECTILES); projectiles != NULL; projectiles = projectiles->next){
        projectiles->update(projectiles);
        grid_insert(g, get_component(projectiles, Collision));
    }

    
    manager_refresh(manager);
    grid_destroy(g);
    unsigned long ftimer2 = SDL_GetTicks();
    printf("FPS: %f\n", 1000.0f/((float)ftimer2 - (float)ftimer1));
    ftimer1 = ftimer2;
    return;
}

void draw(){
  
    SDL_RenderClear(renderer);
    manager_draw(manager, TERRAIN);    
    manager_draw(manager, OBSTACLE);
    manager_draw(manager, PLAYER);
    manager_draw(manager, PROJECTILES);
    SDL_RenderPresent(renderer);
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
            assetmanager->create_obstacle( Vector2(x, y),Vector2(0, 0), "box");
        }
    }
    return;
}

void clean(renderer_t *r){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(r->win);
    destroy_manager(manager);
    assetManager_destroy(assetmanager);
    free(r);
    return;
}
