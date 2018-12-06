#include "../includes/renderer.h"
#include "../includes/tileComponent.h"
#include "../includes/textComponent.h"
#include "../includes/aiComponent.h"
#include "../includes/particleComponent.h"
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


void am_bear_create(Vector2D_t pos, int speed, const char *filepath){
    entities_t *entity = entities_create();
    
    transformComponent_t *t = transform_create(pos, Vector2(0,0), speed);
    add_component(entity, component_create(t, transform_init, transform_update, transform_draw, transform_destroy, Transform));

    spriteComponent_t *s = sprite_create(filepath, NOTANIMATED);
    add_component(entity, component_create(s, sprite_init, sprite_update, sprite_draw, sprite_draw, Sprite));

    colliderComponent_t *c = collider_create(CREATURE, 1);
    add_component(entity, component_create(c, collider_init, collider_update, collider_draw, collider_draw, Collision));

    statComponent_t *stat = stat_create(100, 20, 100);
    add_component(entity, component_create(stat, stat_init, stat_update, stat_draw, stat_destroy, Stat));

    

    aiComponent_t *ai = ai_create();
    add_component(entity, component_create(ai, ai_init, ai_update, ai_draw, ai_destroy, AI));

    manager_insert(manager, entity, CREATURE);

}


void am_player_create( Vector2D_t pos, int speed, const char* filepath){

    entities_t *entity = entities_create();

    transformComponent_t *t = transform_create(pos,Vector2(0,0), speed);
    add_component(entity, component_create(t, transform_init, transform_update, transform_draw,  transform_destroy, Transform));

    spriteComponent_t *s = sprite_create(filepath, ANIMATED);
    add_component(entity, component_create(s, sprite_init, sprite_update, sprite_draw, sprite_draw, Sprite));

    colliderComponent_t *c = collider_create(PLAYER, 0);
    add_component(entity, component_create(c, collider_init, collider_update, collider_draw, collider_draw, Collision));
    
    keyboardComponent_t *k = keyboard_create();
    add_component(entity, component_create(k, keyboard_init, keyboard_update, keyboard_draw, keyboard_draw, KeyBoard));

    statComponent_t *stat = stat_create(100, 20, 100);
    add_component(entity, component_create(stat, stat_init, stat_update, stat_draw, stat_destroy, Stat));
    
    manager_insert(manager, entity, PLAYER);

}

void am_obstacle_create( Vector2D_t pos, int speed, const char* filepath){

    entities_t *entity = entities_create();
    
    transformComponent_t *t = transform_create(pos,Vector2(0,0), speed);
    add_component(entity, component_create(t, transform_init, transform_update, transform_draw,  transform_destroy, Transform));

    spriteComponent_t *s = sprite_create(filepath, NOTANIMATED);
    add_component(entity, component_create(s, sprite_init, sprite_update, sprite_draw, sprite_draw, Sprite));

    colliderComponent_t *c = collider_create(OBSTACLE, 0);
    add_component(entity, component_create(c, collider_init, collider_update, collider_draw, collider_draw, Collision));

    manager_insert(manager, entity, OBSTACLE);
}

void am_bullet_create(Vector2D_t pos, Vector2D_t speed, int moveSpeed, const char *filepath){

    entities_t *entity = entities_create();
    transformComponent_t *t = transform_create(pos, speed, moveSpeed);
    add_component(entity, component_create(t, transform_init, transform_update, transform_draw,  transform_destroy, Transform));

    spriteComponent_t *s = sprite_create(filepath, NOTANIMATED);
    add_component(entity, component_create(s, sprite_init, sprite_update, sprite_draw, sprite_draw, Sprite));

    colliderComponent_t *c = collider_create(PROJECTILES, 0);
    add_component(entity, component_create(c, collider_init, collider_update, collider_draw, collider_draw, Collision));
    manager_insert(manager, entity, PROJECTILES);
}

void am_tile_create(Vector2D_t pos, const char *filepath, tileTypes_t tileType){
    entities_t *entity = entities_create();
    
    transformComponent_t *t = transform_create(pos, Vector2(0,0),0);
    add_component(entity, component_create(t, transform_init, transform_update, transform_draw,  transform_destroy, Transform));

    spriteComponent_t *s = sprite_create(filepath, NOTANIMATED);
    add_component(entity, component_create(s, sprite_init, sprite_update, sprite_draw, sprite_draw, Sprite));

    colliderComponent_t *c = collider_create(TERRAIN, 0);
    add_component(entity, component_create(c, collider_init, collider_update, collider_draw, collider_draw, Collision));

    tileComponent_t *tile = tile_create(tileType);
    add_component(entity, component_create(tile, tile_init, tile_update, tile_draw, tile_destroy, Tile));

    
    manager_insert(manager, entity, TERRAIN);
}


void am_text_create(Vector2D_t pos, char *characters){

    entities_t *entity = entities_create();

    transformComponent_t *t = transform_create(pos, Vector2(0,0), 0);
    add_component(entity, component_create(t, transform_init, transform_update, transform_draw,  transform_destroy, Transform));
    textComponent_t *te = text_create(characters);
    add_component(entity, component_create(te, text_init, text_update, text_draw, text_destroy, Text));


    manager_insert(manager, entity, UI);
}


void am_create_particles(Vector2D_t pos, int amountOfParticles){


    for(int i = 0; i < amountOfParticles; i++){
        entities_t *entity = entities_create();

        transformComponent_t *t = transform_create(pos,Vector2(0,0), 0);
        add_component(entity, component_create(t, transform_init, transform_update, transform_draw,  transform_destroy, Transform));

        particleComponent_t *p = particle_create(5000);
        add_component(entity, component_create(p, particle_init, particle_update, particle_draw, particle_destroy, Particle));
        manager_insert(manager, entity, PARTICLE);

    }
    
}


void assetManager_destroy(assetManager_t *am){
    //leaks memory remember to destroy map at some point.
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


