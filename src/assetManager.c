#include "../includes/AssetManager.h"
#include "renderer.h"
void am_player_create( int x, int y, int sx, int sy, const char* filepath){

    entities_t *entity = entities_create();
    
    transformComponent_t *t = transform_create(x, y, sx, sy);
    add_component(entity, Transform, t);

    spriteComponent_t *s = sprite_create(filepath);
    add_component(entity, Sprite, s);

    colliderComponent_t *c = collider_create();
    add_component(entity, Collision, c);

    keyboardComponent_t *k = keyboard_create();
    add_component(entity, KeyBoard, k);

    manager_insert(manager, entity, PLAYER);

}

void am_obstacle_create( int x, int y, int sx, int sy, const char* filepath){

    entities_t *entity = entities_create();
    
    transformComponent_t *t = transform_create(x, y, sx, sy);
    add_component(entity, Transform, t);

    spriteComponent_t *s = sprite_create(filepath);
    add_component(entity, Sprite, s);

    colliderComponent_t *c = collider_create();
    add_component(entity, Collision, c);

    manager_insert(manager, entity, OBSTACLE);
}



assetManager_t *assetManager_create(){

    assetManager_t *a = malloc(sizeof(assetManager_t));
    a->create_player = am_player_create;
    a->create_obstacle = am_obstacle_create;
    return a;
}
