#ifndef _SNAKE_H
#define _SNAKE_H

#include <stdint.h>

#define BOOL uint32_t
#define TRUE 1u
#define FLASE 0u

#define UP 0u
#define DOWN ~0u
#define LEFT 1u
#define RIGHT ~1u

typedef struct coord
{
    uint16_t x, y;
} coord_t;

typedef struct vector
{
    uint8_t dir;
    coord_t p;
} vector_t;

typedef struct node
{
    vector_t v;
    struct node *next;
} node_t;

typedef struct snake
{
    node_t *head;
    node_t *nail;
} snake_t;

snake_t *snake_create(vector_t const *init_nail, uint8_t len);
void snake_destroy(snake_t *sk);
void snake_head_move(snake_t *sk, uint8_t dir, coord_t *h);
void snake_nail_move(snake_t *sk, coord_t *n);

#endif
