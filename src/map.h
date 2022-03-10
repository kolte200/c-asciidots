/*
This file is part of C-AsciiDots.

C-AsciiDots is free software: you can redistribute it and/or
modify it under the terms of the GNU Affero General Public License as
published by the Free Software Foundation, either version 3 of
the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program. If not, see <https://www.gnu.org/licenses/>
*/


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