#include <stdio.h>
#include <stdlib.h>

#include "display.h"
#include "input.h"
#include "map.h"
#include "snake.h"

#define INITIAL_X 0u
#define INTIAL_Y 0u
#define INITIAL_DIR LEFT
#define INITIAL_LEN 4

snake_t *sk = NULL;

uint32_t score;
coord_t food;
uint32_t cycle;

void generate_food(coord_t *food)
{
}

void game_init(void)
{
    map_init();
    //display_init();
    //input_set_event_filter();

    vector_t const v = {.dir = INITIAL_DIR, .p.x = INITIAL_X, .p.y = INTIAL_Y};
    sk = snake_create(&v, INITIAL_LEN);

    generate_food(&food);
    map_update(food.x, food.y, FOOD);
    display_update(food.x, food.y, FOOD);
}

int game_over(void)
{
    snake_destroy(sk);
}

void pause();
BOOL is_exit();
void you_died();

int game_start(void)
{
    coord_t h, n;
    volatile uint8_t s;

    input_event_t e;
    BOOL quit = FLASE;

    while (!quit)
    {
        while (input_event_poll(&e))
        {
            s = 0;

            switch (e)
            {
            case PAUSE:
                pause();
                break;
            case EXIT:
                quit = is_exit();
                break;
            default:
                snake_head_move(sk, event_decode(&e), &h);
                s = map_query(h.x, h.y);
                map_update(h.x, h.y, BODY);
                display_update(h.x, h.y, BODY);
                break;
            }

            switch (s)
            {
            case 0:
                break;
            case PASS:
                snake_nail_move(sk, &n);
                map_update(n.x, n.y, PASS);
                display_update(n.x, n.y, PASS);
                break;
            case FOOD:
                score += 1;
                generate_food(&food);
                map_update(food.x, food.y, FOOD);
                display_update(food.x, food.y, FOOD);
                break;
            case BODY:
            case OBSTACLE:
                you_died();
                quit = TRUE;
                break;
            }

            refresh();
        }
    }

    return 0;
}

int main(uint32_t argc, const char *argv[])
{
    game_init();
    game_start();
    game_over();

    return 0;
}
