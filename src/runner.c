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
