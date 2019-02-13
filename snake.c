#include <assert.h>
#include <stdlib.h>

#include "snake.h"

static node* create_node(node **head);

static void del_node(node **nail);

static BOOL cmp_node(node *node);

static inline void vector_change(vector *v);

snake *snake_create(uint8_t init_x, uint8_t init_y, uint8_t init_dir, uint8_t len)
{
    snake *sk = (snake *)malloc(sizeof(snake));

    assert(sk != NULL);

    sk->head = NULL;

    create_node(&(sk->head));
    sk->head->n.x = init_x;
    sk->head->n.y = init_y;
    sk->head->n.dir = init_dir;

    sk->nail = create_node(&(sk->head));

    vector v = {.x = init_x, .y = init_y, .dir = init_dir};
    for (int i = 0; i < len - 1; i++)
    {
        vector_change(&v);
    }
    sk->head->n.x = v.x;
    sk->head->n.y = v.y;
    sk->head->n.dir = v.dir;

    return sk;
}

status snake_move(snake *sk, uint8_t dir)
{
    status st = Fine;

    if ((dir == UP && sk->head->n.dir != DOWN) || (dir == DOWN && sk->head->n.dir != UP) || (dir == LEFT && sk->head->n.dir != RIGHT) || (dir == LEFT && sk->head->n.dir != RIGHT))
    {
        if(dir == sk->head->n.dir)
        {
            st = Speed_Up;
            vector_change(&(sk->head->n));
        }
        else
        {
            sk->head->n.dir = dir;
            node *n = create_node(&(sk->head));
            sk->head->n.x = n->n.x;
            sk->head->n.y = n->n.y;
            sk->head->n.dir = n->n.dir;
        }
    }

    vector_change(&(sk->head->n));

    //TODO

    return st;
}

void snake_destroy(snake *sk)
{
    while(sk->nail != NULL){
        del_node(&(sk->nail));
    }

    free(sk);
}

static node* create_node(node **head)
{
    if (*head == NULL)
    {
        *head = (node *)molloc(sizeof(node));

        assert(*head != NULL);

        (*head)->next = NULL;
        return *head;
    }

    node *n = (node *)malloc(sizeof(node));

    assert(n != NULL);

    n->next = NULL;

    (*head)->next = n;
    n = *head;
    *head = (*head)->next;

    return n;
}

static void del_node(node **nail)
{
    node *n = *nail;

    if(n == NULL)
        return;
    
    *nail = (*nail)->next;

    free(n);
}

static inline void vector_change(vector *v)
{
    switch (v->dir)
    {
        case UP:
            v->y--;
            break;
        case DOWN:
            v->y++;
            break;
        case LEFT:
            v->x--;
            break;
        case RIGHT:
            v->x++;
            break;
        default:
            break;
    }
}
