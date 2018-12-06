#ifndef VECTOR2D_H
#define VECTOR2D_H
typedef struct Vector2D Vector2D_t;
struct Vector2D{
    float x, y;
};

Vector2D_t Vector2(float x, float y);

void add(Vector2D_t *v1, Vector2D_t *v2);
void sub(Vector2D_t *v1, Vector2D_t *v2);

void mul(Vector2D_t *v1, Vector2D_t *v2);
void divide(Vector2D_t *v1, Vector2D_t *v2);


double calculate_distance(Vector2D_t v1, Vector2D_t v2);

void printVector(Vector2D_t *v);

Vector2D_t normalizeVector(Vector2D_t v);

#endif

