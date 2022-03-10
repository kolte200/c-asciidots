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


#include "runner.h"

#include <stdio.h>


void runner_update(map_t map) {
    map_goto_first_dot(map);
    while(map_has_next_dot(map)) {
        dot_t dot = map_next_dot(map);
        cell_type_t type = map_get_type(map, dot->x, dot->y);
        type.data ? ((cell_dfunc_t)type.func)(map, dot, type.data) : ((cell_func_t)type.func)(map, dot);
    }
}

void runner_run(map_t map) {
    while(LIST_LENGTH(map->dots)) {
        runner_update(map);
    }
}

void runner_debug(map_t map) {
    map_init_debug();
    char c;
    while(LIST_LENGTH(map->dots)) {
        map_print(map);
        scanf("%c", &c);
        runner_update(map);
    }
}
