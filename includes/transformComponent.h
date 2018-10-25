#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H



    typedef struct transformComponent transformComponent_t;
    typedef (void)(update_t*)(void*);
    typedef (void)(draw_t*)(void*);
    struct transformComponent{
        int x, y;
        void *entity;
        update_t update;
        draw_t draw;
    };

    transformComponent_t *transform_create();





#endif