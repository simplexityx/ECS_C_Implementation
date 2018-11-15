#include "../includes/renderer.h"
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


void am_bear_create(Vector2D_t pos, Vector2D_t speed, const char *filepath){
    entities_t *entity = entities_create();
    
    transformComponent_t *t = transform_create(pos, speed);
    add_component(entity, component_create(t, transform_init, transform_update, transform_draw, transform_draw, Transform));

    spriteComponent_t *s = sprite_create(filepath, NOTANIMATED);
    add_component(entity, component_create(s, sprite_init, sprite_update, sprite_draw, sprite_draw, Sprite));

    colliderComponent_t *c = collider_create(PLAYER);
    add_component(entity, component_create(c, collider_init, collider_update, collider_draw, collider_draw, Collision));

    manager_insert(manager, entity, PLAYER);

}


void am_player_create( Vector2D_t pos, Vector2D_t speed, const char* filepath){

    entities_t *entity = entities_create();

    transformComponent_t *t = transform_create(pos, speed);
    add_component(entity, component_create(t, transform_init, transform_update, transform_draw, transform_draw, Transform));

    spriteComponent_t *s = sprite_create(filepath, NOTANIMATED);
    add_component(entity, component_create(s, sprite_init, sprite_update, sprite_draw, sprite_draw, Sprite));

    colliderComponent_t *c = collider_create(PLAYER);
    add_component(entity, component_create(c, collider_init, collider_update, collider_draw, collider_draw, Collision));
    
    keyboardComponent_t *k = keyboard_create();
    add_component(entity, component_create(k, keyboard_init, keyboard_update, keyboard_draw, keyboard_draw, KeyBoard));

    manager_insert(manager, entity, PLAYER);

}

void am_obstacle_create( Vector2D_t pos, Vector2D_t speed, const char* filepath){

    entities_t *entity = entities_create();
    
    transformComponent_t *t = transform_create(pos, speed);
    add_component(entity, component_create(t, transform_init, transform_update, transform_draw, transform_draw, Transform));

    spriteComponent_t *s = sprite_create(filepath, NOTANIMATED);
    add_component(entity, component_create(s, sprite_init, sprite_update, sprite_draw, sprite_draw, Sprite));

    colliderComponent_t *c = collider_create(OBSTACLE);
    add_component(entity, component_create(c, collider_init, collider_update, collider_draw, collider_draw, Collision));

    manager_insert(manager, entity, OBSTACLE);
}

void am_bullet_create(Vector2D_t pos, Vector2D_t speed, const char *filepath){

    entities_t *entity = entities_create();
    transformComponent_t *t = transform_create(pos, speed);
    add_component(entity, component_create(t, transform_init, transform_update, transform_draw, transform_draw, Transform));

    spriteComponent_t *s = sprite_create(filepath, NOTANIMATED);
    add_component(entity, component_create(s, sprite_init, sprite_update, sprite_draw, sprite_draw, Sprite));

    colliderComponent_t *c = collider_create(PROJECTILES);
    add_component(entity, component_create(c, collider_init, collider_update, collider_draw, collider_draw, Collision));
    manager_insert(manager, entity, PROJECTILES);
}

void am_tile_create(Vector2D_t pos, const char *filepath){
    entities_t *entity = entities_create();
    
     transformComponent_t *t = transform_create(pos, Vector2(0,0));
    add_component(entity, component_create(t, transform_init, transform_update, transform_draw, transform_draw, Transform));

    spriteComponent_t *s = sprite_create(filepath, NOTANIMATED);
    add_component(entity, component_create(s, sprite_init, sprite_update, sprite_draw, sprite_draw, Sprite));

    colliderComponent_t *c = collider_create(TERRAIN);
    add_component(entity, component_create(c, collider_init, collider_update, collider_draw, collider_draw, Collision));

    manager_insert(manager, entity, TERRAIN);
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
    
    return a;
}


