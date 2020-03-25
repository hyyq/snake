#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "snake.h"

static node_t *node_create(vector_t *v)
{
    node_t *n = (node_t *)malloc(sizeof(node_t));

    assert(n != NULL);

    memset(n, 0, sizeof(*n));

    if (v != NULL)
        n->v = *v;

    return n;
}

static node_t *node_del(node_t *nail)
{
    if (nail == NULL)
        return NULL;

    node_t *n = nail->next;

    free(nail);

    return n;
}

static inline BOOL node_cmp(node_t *n1, node_t *n2)
{
    return n1->v.p.x == n2->v.p.x && n1->v.p.y == n2->v.p.y ? TRUE : FLASE;
}

static void vector_change(vector_t *v)
{
    switch (v->dir)
    {
    case UP:
        v->p.y--;
        break;
    case DOWN:
        v->p.y++;
        break;
    case LEFT:
        v->p.x--;
        break;
    case RIGHT:
        v->p.x++;
        break;
    default:
        break;
    }
}

snake_t *snake_create(vector_t const *init_nail, uint8_t len)
{
    snake_t *sk = (snake_t *)malloc(sizeof(snake_t));
    assert(sk != NULL);

    sk->nail = node_create(init_nail);

    vector_t v = *init_nail;
    for (int i = 0; i < len - 1; i++)
        vector_change(&v);
    sk->head = node_create(&v);

    sk->nail->next = sk->head;

    return sk;
}

void snake_destroy(snake_t *sk)
{
    while (sk->nail != NULL)
    {
        sk->nail = node_del(sk->nail);
    }

    free(sk);
}

void snake_head_move(snake_t *sk, uint8_t dir, coord_t *h)
{
    if (sk->head->v.dir == dir || sk->head->v.dir == ~dir)
    {
        vector_change(&(sk->head->v));
    }
    else
    {
        sk->head->v.dir = dir;
        vector_t v = sk->head->v;
        vector_change(&v);
        sk->head->next = node_create(&v);
        sk->head = sk->head->next;
    }

    *h = sk->head->v.p;
}

void snake_nail_move(snake_t *sk, coord_t *n)
{
    *n = sk->nail->v.p;
    vector_change(&sk->nail->v);

    if (node_cmp(sk->nail, sk->nail->next) == TRUE)
    {
        sk->nail = node_del(sk->nail);
    }
}
