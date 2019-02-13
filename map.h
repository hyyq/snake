#ifndef _MAP_H
#define _MAP_H

#include <stdint.h>

#define W 80
#define H 80

#define OBSTACLE '-'
#define PASS ' '
#define FOOD '.'
#define BODY '*'

void map_init();
void map_update(uint32_t x, uint32_t y, uint8_t c);
uint8_t map_query(uint32_t x, uint32_t y);

#endif
