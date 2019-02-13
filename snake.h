#ifndef _SNAKE_H
#define _SNAKE_H

#include <stdint.h>

#include "input.h"
#include "map.h"

#define BOOL uint32_t
#define TRUE 1u
#define FLASE 0u

#define INITIAL_X 0u
#define INTIAL_Y 0u
#define INITIAL_DIR LEFT

typedef struct vector
{
    uint32_t x, y;
    uint8_t dir;
} vector;

typedef struct node
{
    vector n;
    struct node *next;
} node;

typedef struct snake
{
    node *head;
    node *nail;
} snake;

snake *snake_create(uint8_t init_x, uint8_t init_y, uint8_t init_dir, uint8_t len);
void snake_destroy(snake *sk);

typedef enum status
{
    Fine,
    Got_Food,
    Clash,
    Speed_Up,
    Pause,
    Exit
} status;

status snake_move(snake *sk, uint8_t dir);

#endif
