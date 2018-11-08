#ifndef TERRAIN_H
#define TERRAIN_H
    typedef enum terrain {
        GRASS,
        WATER,
        ROCKS
    }terrain_t;
    void ParseLevel(char *filepath);
    

#endif