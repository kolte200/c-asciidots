#ifndef DOT_HEADER_INCLUDED
#define DOT_HEADER_INCLUDED


#include "main.h"


dot_t dot_create();

void dot_add(map_t map, dot_t dot);

void dot_rem(map_t map, dot_t dot);

bool dot_step(map_t map, dot_t dot);

void dot_free(dot_t dot);


#endif
