#ifndef MAP_HEADER_INCLUDED
#define MAP_HEADER_INCLUDED


#include "main.h"
#include "dot.h"



// Map's functions

map_t map_create();

void map_free(map_t map);


char map_get_char(map_t map, int x, int y);

cell_func_t map_get_func(map_t map, int x, int y);

void* map_get_data(map_t map, int x, int y);

cell_type_t map_get_type(map_t map, int x, int y);


// Set current dots pointer at the begining
void map_goto_first_dot(map_t map);

// Check if there dot remaining to process in runner
bool map_has_next_dot(map_t map);

// Get next dot to process in runner
dot_t map_next_dot(map_t map);

void map_init_debug();


void map_print(map_t map);

#endif