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


#include <stdlib.h>
#include <stdio.h>

#include "dot.h"


// Dot's functions

static size_t _current_dot_id = 0;

dot_t dot_create() {
    dot_t dot;
    dot = (dot_t) malloc(sizeof(struct dot_s));
    dot->direction = UP;
    dot->id = ++_current_dot_id;
    dot->index = 0;
    dot->value = 0;
    dot->x = 0;
    dot->y = 0;
    return dot;
}

// Add a dots to map's dots list
void dot_add(map_t map, dot_t dot) {
    dot->index = LIST_LENGTH(map->dots);
    if(dot->index > 100) {
        printf("Too many dots! Be sure to not make an infinite loop with duplicator.\n");
        dot_free(dot);
        return;
    }
    LIST_ADD(map->dots, dot);
}

// Remove a dots from the map's dot list
// Be carefull, you can't remove a dot that you just have
// added to the dots list in the same frame!
void dot_rem(map_t map, dot_t dot) {
    if(dot->index == LIST_LENGTH(map->dots) - 1) {
        LIST_POP(map->dots);
        map->dots_li--;
    } else {
        if(LIST_LENGTH(map->dots) == map->dots_ri)
            map->dots_li--;
        dot_t last = LIST_POP(map->dots);
        LIST_SET(map->dots, dot->index, last);
        last->index = dot->index;
    }
    map->dots_ri--;
}

bool dot_step(map_t map, dot_t dot) {
    switch (dot->direction)
    {
        case UP:
            if(dot->y > 0) {
                dot->y--;
                return TRUE;
            }
            break;

        case RIGHT:
            if(dot->x < map->width - 1) {
                dot->x++;
                return TRUE;
            }
            break;

        case DOWN:
            if(dot->y < map->height - 1) {
                dot->y++;
                return TRUE;
            }
            break;

        case LEFT:
            if(dot->x > 0) {
                dot->x--;
                return TRUE;
            }
            break;
    }

    dot_rem(map, dot);
    dot_free(dot);
    return FALSE;
}

void dot_free(dot_t dot) {
    free(dot);
}
