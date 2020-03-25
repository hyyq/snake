#ifndef _DISPLAY_H
#define _DISPLAY_H

#include <stdint.h>

void display_update(uint16_t x, uint16_t y, uint8_t c);
void refresh(void);

#endif
