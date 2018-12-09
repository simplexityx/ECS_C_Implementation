#include "../includes/renderer.h"
#include "../includes/tileComponent.h"
#include "../includes/textComponent.h"
#include "../includes/aiComponent.h"
#include "../includes/particleComponent.h"

#define TRANSFORM_COMPONENT(pos, heading, speed)   component_create(transform_create(pos, heading, speed), transform_init, transform_update, transform_draw, transform_destroy, Transform)
#define SPRITE_COMPONENT(filepath, flags)          component_create(sprite_create(filepath, flags), sprite_init, sprite_update, sprite_draw, sprite_destroy, Sprite)
#define COLLIDER_COMPONENT(tag, flags)             component_create(collider_create(tag, flags), collider_init, collider_update, collider_draw, collider_destroy, Collision)
#define STAT_COMPONENT(hp, strength, mana)         component_create(stat_create(hp, strength, mana), stat_init, stat_update, stat_draw, stat_destroy, Stat)
#define AI_COMPONENT(node1, node2)                 component_create(ai_create(node1, node2), ai_init, ai_update, ai_draw, ai_destroy, AI)
#define KEYBOARD_COMPONENT                         component_create(keyboard_create(), keyboard_init, keyboard_update, keyboard_draw, keyboard_destroy, KeyBoard)
#define TILE_COMPONENT(type)                       component_create(tile_create(type), tile_init, tile_update, tile_draw, tile_destroy, Tile)
#define TEXT_COMPONENT(characters)                 component_create(text_create(characters), text_init, text_update, text_draw, text_destroy, Text)
#define PARTICLE_COMPONENT(duration)               component_create(particle_create(duration), particle_init, particle_update, particle_draw, particle_destroy, Particle)


int cmpfunc(void *a, void *b){
    return strcmp(a, b);
}

unsigned long hash_string(void *str)
{
    unsigned char *p = str;
    unsigned long hash = 5381;
    int c;

    while ((c = *p++) != 0)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash;
}


void am_bear_create(Vector2D_t pos, int speed, const char *filepath, Vector2D_t node1, Vector2D_t node2){
    entities_t *entity = entities_create();
    
    
    add_component(entity, TRANSFORM_COMPONENT(pos, Vector2(0,0),speed));

    add_component(entity, SPRITE_COMPONENT(filepath, NOTANIMATED));

    add_component(entity, COLLIDER_COMPONENT(CREATURE, 1));

    add_component(entity, STAT_COMPONENT(100, 20, 100));

    add_component(entity, AI_COMPONENT(node1, node2));

    manager_insert(manager, entity, CREATURE);

}


void am_player_create( Vector2D_t pos, int speed, const char* filepath){

    entities_t *entity = entities_create();

    add_component(entity, TRANSFORM_COMPONENT(pos, Vector2(0,0),speed));

    add_component(entity, SPRITE_COMPONENT(filepath, ANIMATED));

    add_component(entity, COLLIDER_COMPONENT(PLAYER, 0));

    add_component(entity, KEYBOARD_COMPONENT);

    add_component(entity, STAT_COMPONENT(100, 20, 100));

    
    
    
    
    
    manager_insert(manager, entity, PLAYER);

}

void am_obstacle_create( Vector2D_t pos, int speed, const char* filepath){

    entities_t *entity = entities_create();
    
    add_component(entity, TRANSFORM_COMPONENT(pos, Vector2(0,0),speed));

    add_component(entity, SPRITE_COMPONENT(filepath, NOTANIMATED));

    add_component(entity, COLLIDER_COMPONENT(OBSTACLE, 0));

    add_component(entity, STAT_COMPONENT(10000, 0, 0));

    manager_insert(manager, entity, OBSTACLE);
}

void am_bullet_create(Vector2D_t pos, Vector2D_t speed, int moveSpeed, const char *filepath){

    entities_t *entity = entities_create();
    add_component(entity, TRANSFORM_COMPONENT(pos, speed,moveSpeed));

    add_component(entity, SPRITE_COMPONENT(filepath, NOTANIMATED));

    add_component(entity, COLLIDER_COMPONENT(PROJECTILES, 0));

    manager_insert(manager, entity, PROJECTILES);
}

void am_tile_create(Vector2D_t pos, const char *filepath, tileTypes_t tileType){
    entities_t *entity = entities_create();

    add_component(entity, TRANSFORM_COMPONENT(pos, Vector2(0,0),0));

    add_component(entity, SPRITE_COMPONENT(filepath, NOTANIMATED));

    add_component(entity, COLLIDER_COMPONENT(TERRAIN, 0));

    add_component(entity, TILE_COMPONENT(tileType));
    
    
    manager_insert(manager, entity, TERRAIN);
}


void am_text_create(Vector2D_t pos, char *characters){

    entities_t *entity = entities_create();

    add_component(entity, TRANSFORM_COMPONENT(pos, Vector2(0,0), 0));
    
    add_component(entity, TEXT_COMPONENT(characters));

    manager_insert(manager, entity, UI);
}


void am_create_particles(Vector2D_t pos, int amountOfParticles){


    for(int i = 0; i < amountOfParticles; i++){
        entities_t *entity = entities_create();

        add_component(entity, TRANSFORM_COMPONENT(pos,Vector2(0,0), 0));

        add_component(entity, PARTICLE_COMPONENT(5000));
        manager_insert(manager, entity, PARTICLE);

    }
    
}

void destroy_tex_map(void *t){
    SDL_Texture *tex = (SDL_Texture *)t;
    SDL_DestroyTexture(tex);
    return;
}

void assetManager_destroy(assetManager_t *am){
    //leaks memory remember to destroy map at some point.
    map_destroy(am->map, NULL, destroy_tex_map);
    free(am);
}




void add_texture(char *name , char *filepath){

    SDL_Texture *tex = load_texture(filepath);
    map_put(assetmanager->map, name, tex);
    return;
}


SDL_Texture *get_texture(char *name){
    return (SDL_Texture*)map_get(assetmanager->map, name);
}

assetManager_t *assetManager_create(){

    assetManager_t *a = malloc(sizeof(assetManager_t));
    a->map = map_create(cmpfunc, hash_string);
    a->create_player = am_player_create;
    a->create_obstacle = am_obstacle_create;
    a->create_projectile = am_bullet_create;
    a->create_tile = am_tile_create;
    a->create_bear = am_bear_create;
    a->add_tex = add_texture;
    a->get_tex = get_texture;
    a->create_text = am_text_create;
    a->generate_particles = am_create_particles;
    return a;
}


