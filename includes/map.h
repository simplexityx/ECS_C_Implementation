#ifndef MAP_H
#define MAP_H

typedef struct map_node{
    void *value;
    void* key;
}map_node_t;

typedef struct map {
    int maxSize;
    int curSize;
    map_node_t **nodes;
}map_t;


map_t *map_create();
void map_insert(map_t *map, void *key, void *value);
void* map_get(map_t *map, void* key);
void map_destroy(map_t *map);
void map_print(map_t *map);

#endif