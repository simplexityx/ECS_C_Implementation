#include "../includes/vector2D.h"
#include <stdio.h>
#include <math.h>
Vector2D_t Vector2(float x, float y){
    Vector2D_t v;
    v.x = x;
    v.y = y;
    return v;
}

void add(Vector2D_t *v1, Vector2D_t *v2){
    v1->x += v2->x;
    v1->y += v2->y;
}

void sub(Vector2D_t *v1, Vector2D_t *v2){
    v1->x -= v2->x;
    v1->y -= v2->y;
}

void mul(Vector2D_t *v1, Vector2D_t *v2){
    v1->x *= v2->x;
    v1->y *= v2->y;
}
void divide(Vector2D_t *v1, Vector2D_t *v2){
    if(v2->x == 0 || v2->y == 0){
        printf("dividing by zero\n");
        return;
    }
    v1->x /= v2->x;
    v1->y /= v2->y;
}


double calculate_distance(Vector2D_t v1, Vector2D_t v2){
    Vector2D_t vTmp = v1;
    sub(&vTmp, &v2);
    return sqrt(pow(vTmp.x, 2) + pow(vTmp.y, 2));
}

Vector2D_t normalizeVector(Vector2D_t v){

    Vector2D_t vr;

    if(v.x > 0){
        vr.x = 1;
    }else if(v.x < 0){
        vr.x = -1;
    }else if(v.x == 0){
        vr.x = 0;
    }

    if(v.y > 0){
        vr.y = 1;
    }else if(v.y < 0){
        vr.y = -1;
    }else if(v.y == 0){
        vr.y = 0;
    }

    return vr;
}

void printVector(Vector2D_t *v){
    printf("%f, %f\n", v->x, v->y);
}
