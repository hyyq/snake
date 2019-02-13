#include <stdio.h>
#include <stdlib.h>

#include "display.h"
#include "input.h"
#include "map.h"
#include "snake.h"

snake *sk = NULL;

uint32_t score;

uint32_t cycle;

BOOL got_food;
BOOL erase_nail;

uint32_t old_nail_x, old_nail_y;
uint32_t food[2];
uint32_t oldfood[2];

void init_game(void); //初始化游戏

void generate_food(uint32_t *food);

void end_game(void); //游戏结束处理

uint32_t main(uint32_t argc, const char *argv[])
{
    uint32_t key;
    status st = Fine;

    init_game();

    while (st != Exit)
    {
        switch (key = get_key())
        {
        case PAUSE:
            st = Pause;
            break;
        case EXIT:
            st = Exit;
            break;
        default:
            st = snake_move(sk, key);
            break;
        }

        //TODO

        refresh();
    }

    end_game();
    return 0;
}

void init_game(void)
{
    map_init();
    sk = snake_create(INITIAL_X, INTIAL_Y, INITIAL_DIR, 4);
}

void generate_food(uint32_t *food)
{
}

void end_game(void)
{
    snake_destroy(sk);
}
