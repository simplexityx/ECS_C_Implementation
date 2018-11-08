#include "../includes/map.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
map_t *map_create(){
    map_t *map = malloc(sizeof(map_t));
    map->curSize = 0;
    map->maxSize = 32;

    map->nodes = calloc(map->maxSize, sizeof(map_node_t*));
    return map;
}

map_node_t *map_node_create(void *key, void *value){
    map_node_t *node = malloc(sizeof(map_node_t));
    node->key = key;
    node->value = value;
    return node;
}

unsigned long hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}


void map_enlarge(map_t *map){

    map_node_t **newNode = calloc(map->maxSize*2, sizeof(map_node_t *));

    for(int i = 0; i < map->maxSize; i++){
        if(map->nodes[i] != NULL){
            int idx = hash(map->nodes[i]->key);
            while(newNode[idx] != NULL){
               idx++;  
            }
            newNode[idx] = map->nodes[i];
        }
    }
    map->maxSize *= 2;

    free(map->nodes);
    map->nodes = newNode;
    return;
}


void map_insert(map_t *map, void *key, void *value){


    map_node_t *node = map_node_create(key, value); 
    unsigned long idx = hash(key) % map->maxSize; 
    if(map->nodes[idx] != NULL){
        while(map->nodes[idx] != NULL){
            idx++;
        }
        map->nodes[idx] = node;
    }else{
        map->nodes[idx] = node;
    }

    map->curSize++;

    if(map->curSize > (map->maxSize/2)){
        map_enlarge(map);
    }
    return;
}
void* map_get(map_t *map, void* key);
void map_destroy(map_t *map){
    for(int i = 0; i < map->maxSize; i++){
        if(map->nodes[i] != NULL){
            free(map->nodes[i]);
        }
    }
    free(map->nodes);
    free(map);
}

void map_print(map_t *map){
    
    for(int i = 0; i < map->maxSize; i++){
        if(map->nodes[i] != NULL){
            //printf("key: %d\t value: %d\n", *(int*)map->nodes[i]->key, *(int*)map->nodes[i]->value);
        }
    }

    return;
}


int main(){

    map_t *map = map_create();

    map_insert(map, 0, 0);
    
    map_print(map);
    map_destroy(map);
    return 0;
}