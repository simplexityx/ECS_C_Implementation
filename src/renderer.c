#include "../includes/renderer.h"
#include "../includes/GridMap.h"
#include "../includes/TerrainManager.h"
#include "../includes/tileComponent.h"
#include "../includes/textComponent.h"
#include <assert.h>
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
    assetmanager->add_tex("boat", "Assets/boat.png");

    return;
}



void setup_ui(){
    if(TTF_Init() == -1){
        printf("failed to init TTF\n");
        return;
    }
    font = TTF_OpenFont("./Fonts/lazy.ttf", 28);
    assert(font != NULL);

    hp_bar = entities_create();
    enemy_hp_bar = entities_create();
    add_component(hp_bar, component_create(transform_create(Vector2(100, 500), Vector2(0, 0)), transform_init, transform_update, transform_draw, transform_update, Transform));
    add_component(hp_bar, component_create(text_create("placeholder"), text_init, text_update, text_draw, text_destroy, Text));


    add_component(enemy_hp_bar, component_create(transform_create(Vector2(600, 500), Vector2(0, 0)), transform_init, transform_update, transform_draw, transform_update, Transform));
    add_component(enemy_hp_bar, component_create(text_create("placeholder"), text_init, text_update, text_draw, text_destroy, Text));

    manager_insert(manager, hp_bar, UI);
    manager_insert(manager, enemy_hp_bar, UI);

    entities_t *tmp = get_group(manager, PLAYER);
    statComponent_t *stat = get_component(tmp, Stat);
    textComponent_t *text = get_component(hp_bar, Text);

    stat->observable->subscribe(stat, text->observer);
    stat->set_hp(stat, 0);
}



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

    setup_ui();

    ParseLevel("./Map/map.map");
    return;
}
void update(){
    
    

    grid_t *g = grid_create();
   
    for(entities_t *terrain = get_group(manager, TERRAIN); terrain != NULL; terrain = terrain->next){
        terrain->update(terrain);
        tileComponent_t *t = get_component(terrain, Tile);
        grid_insert(g, get_component(terrain, Collision));
    }


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

    for(entities_t *creatures = get_group(manager, CREATURE); creatures != NULL; creatures = creatures->next){
        creatures->update(creatures);
        grid_insert(g, get_component(creatures, Collision));
    }
    
    
    for(entities_t *projectiles = get_group(manager, PROJECTILES); projectiles != NULL; projectiles = projectiles->next){
        projectiles->update(projectiles);
        grid_insert(g, get_component(projectiles, Collision));
    }

    for(entities_t *particles = get_group(manager, PARTICLE); particles != NULL; particles = particles->next){
        particles->update(particles);
    }
    
    manager_refresh(manager);
    grid_destroy(g);
    
    return;
}

void draw(){
  
    SDL_RenderClear(renderer);
    manager_draw(manager, TERRAIN);    
    manager_draw(manager, OBSTACLE);
    manager_draw(manager, PLAYER);
    manager_draw(manager, CREATURE);
    manager_draw(manager, PROJECTILES);
    manager_draw(manager, UI);
    manager_draw(manager, PARTICLE);
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
            //assetmanager->create_obstacle( Vector2(x, y),Vector2(0, 0), "box");
            assetmanager->generate_particles(Vector2(x, y), 100);
        }
    }
    return;
}

void clean(renderer_t *r){
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(r->win);
    destroy_manager(manager);
    assetManager_destroy(assetmanager);
    free(r);
    return;
}
