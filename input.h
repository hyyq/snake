#ifndef _INPUT_H
#define _INPUT_H

#include <stdint.h>

#define PAUSE 'p'
#define EXIT 'x'

#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'
#define INVALID 'i'

//uint8_t get_key(void); //获取键盘输入
typedef uint8_t input_event_t;
int input_event_poll(input_event_t *e);
uint32_t event_decode(input_event_t *e);

#endif
