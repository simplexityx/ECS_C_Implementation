#include "../includes/TerrainManager.h"
#include "../includes/renderer.h"
#include <stdio.h>

void ParseLevel(char *filepath){

    FILE *f = fopen(filepath, "r");
    if(f == NULL){
        printf("couldnt find file exiting");
        return;
    }
    for(int y = 0; y < 19; y++){
        for(int x = 0; x < 26; x++){
            int k = fgetc(f);
            k -= 48;
            switch(k){
                case GRASS:
                    assetmanager->create_tile(Vector2(x * 32, y * 32), "grass", GRASS);
                    break;
                case WATER:
                    assetmanager->create_tile(Vector2(x * 32, y * 32), "water", WATER);
                    break;
                case ROCK:
                    assetmanager->create_tile(Vector2(x * 32, y * 32), "rock", ROCK);
                    break;
            }
        }
    }
    fclose(f);
    return;
}
