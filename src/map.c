#include <stdlib.h>
#include <stdio.h>

#include "map.h"


// Map's functions

map_t map_create() {
    map_t map;
    map = (map_t) malloc(sizeof(struct map_s));
    map->dots = LIST_CREATE(dot_list_s);
    map->dots_li = 0;
    map->dots_ri = 0;
    return map;
}

void map_free(map_t map) {
    free(map->cells);
    free(map->types);
    for(int i = 0; i < LIST_LENGTH(map->dots); i++)
        dot_free(LIST_GET(map->dots, i));
    LIST_FREE(map->dots);
    free(map);
}


char map_get_char(map_t map, int x, int y) {
    cell_t a = map->cells[map->width * y + x];
    return map->types[a].chr;
}

cell_func_t map_get_func(map_t map, int x, int y) {
    return map->types[map->cells[map->width * y + x]].func;
}

void* map_get_data(map_t map, int x, int y) {
    return map->types[map->cells[map->width * y + x]].data;
}

cell_type_t map_get_type(map_t map, int x, int y) {
    return map->types[map->cells[map->width * y + x]];
}


void map_goto_first_dot(map_t map) {
    map->dots_li = 0;
    map->dots_ri = LIST_LENGTH(map->dots);
}

bool map_has_next_dot(map_t map) {
    return map->dots_li < map->dots_ri;
}

dot_t map_next_dot(map_t map) {
    dot_t dot = LIST_GET(map->dots, map->dots_li);
    map->dots_li++;
    return dot;
}


/* /!\ Slow function used for debugging /!\ */
dot_t map_get_dot(map_t map, int x, int y) {
    size_t i = LIST_LENGTH(map->dots);
    while(i--) {
        dot_t dot = LIST_GET(map->dots, i);
        if(dot->x == x && dot->y == y)
            return dot;
    }
    return NULL;
}

const char* colors[] = {
    "\033[33m",
    "\033[34m",
    "\033[35m",
    "\033[32m",
    "\033[36m"
};


const char valid_chars[] = {'$','.','+','-','*','/','=','}','~','#','{','[','|','`','\\','^','@',']','}','^','%','!',':','/',';','.',',','?',')','_','-','(','\'','"','&','<','>'};
char valid_chars_map[255];

void map_init_debug() {
    for(int i = 0; i < 255; i++)
        valid_chars_map[i] = ' ';

    for(char c = '0'; c <= '9'; c++)
        valid_chars_map[c] = c;

    for(char c = 'a'; c <= 'z'; c++)
        valid_chars_map[c] = c;

    for(char c = 'A'; c <= 'Z'; c++)
        valid_chars_map[c] = c;

    for(int i = 0; i < sizeof(valid_chars); i++)
        valid_chars_map[valid_chars[i]] = valid_chars[i];
}


/* /!\ Slow function used for debugging /!\ */
void map_print(map_t map) {
    fputs("\e[2J", stdout);
    fputs("\e[H", stdout);

    // Print map
    for(int y = 0; y < map->height; y++) {
        for(int x = 0; x < map->width; x++) {
            dot_t dot = map_get_dot(map, x, y);
            if(dot) {
                fputs(colors[dot->index % 5], stdout);
            } else {
                dot_queue_data_t* data = map_get_data(map, x, y);
                if(data && QUEUE_LENGTH(data->dots)) {
                    fputs("\033[31m", stdout);
                } else {
                    fputs("\033[0m", stdout);
                }
            }
            fputc(valid_chars_map[map->types[map->cells[map->width * y + x]].chr], stdout);
        }
        fputc('\n', stdout);
    }

    // Print dots informations
    fputc('\n', stdout);
    for(int i = 0; i < LIST_LENGTH(map->dots); i++) {
        dot_t dot = LIST_GET(map->dots, i);
        fputs(colors[dot->index % 5], stdout);
        fprintf(stdout, "* : value = %f", dot->value);
        fputc('\n', stdout);
    }

    fflush(stdout);
}
