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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"

#include "actions.h"
#include "map.h"
#include "dot.h"


byte dot_get_start_direction(map_t map, dot_t dot) {
    char c;
    
    if(dot->y > 0) {
        c = map_get_char(map, dot->x, dot->y - 1);
        if(c == '|' || c == '+') return UP;
    }

    if(dot->x < map->width - 1) {
        c = map_get_char(map, dot->x + 1, dot->y);
        if(c == '-' || c == '+') return RIGHT;
    }

    if(dot->y < map->height - 1) {
        c = map_get_char(map, dot->x, dot->y + 1);
        if(c == '|' || c == '+') return DOWN;
    }

    if(dot->x > 0) {
        c = map_get_char(map, dot->x - 1, dot->y);
        if(c == '-' || c == '+') return LEFT;
    }

    return 5;
}



// Map char to functions
const cell_type_t cell_types[] = {
    {.chr = ' ',  .func = cf_empty, .data = NULL},
    {.chr = '-',  .func = cf_path_h, .data = NULL},
    {.chr = '+',  .func = cf_path_c, .data = NULL},
    {.chr = '.',  .func = cf_path_c, .data = NULL},
    {.chr = '|',  .func = cf_path_v, .data = NULL},
    {.chr = '>',  .func = cf_insertor_r, .data = NULL},
    {.chr = '<',  .func = cf_insertor_l, .data = NULL},
    {.chr = 'v',  .func = cf_insertor_d, .data = NULL},
    {.chr = '^',  .func = cf_insertor_u, .data = NULL},
    {.chr = '(',  .func = cf_reflector_l, .data = NULL},
    {.chr = ')',  .func = cf_reflector_r, .data = NULL},
    {.chr = '/',  .func = cf_mirror_f, .data = NULL},
    {.chr = '\\', .func = cf_mirror_b, .data = NULL},
    {.chr = '&',  .func = cf_end, .data = NULL},
    {.chr = '$',  .func = cf_print, .data = NULL},
    {.chr = '#',  .func = cf_value, .data = NULL},
    {.chr = '*',  .func = cf_duplicator, .data = NULL}
};

const int nb_cell_type = sizeof(cell_types) / sizeof(cell_type_t);


// Map operations char to function for vertical operators
cell_opfunc_t lkup_op_func_v[256];

// Map operations char to function for horizontal operators
cell_opfunc_t lkup_op_func_h[256];


void init_lkup_op_func() {
    memset(lkup_op_func_v, 0, 256 * sizeof(cell_dfunc_t));
    lkup_op_func_v['*'] = cf_op_mul_v;
    lkup_op_func_v['-'] = cf_op_sub_v;
    lkup_op_func_v['+'] = cf_op_add_v;
    lkup_op_func_v['/'] = cf_op_div_v;
    lkup_op_func_v['%'] = cf_op_mod_v;
    lkup_op_func_v['&'] = cf_op_and_v;
    lkup_op_func_v['o'] = cf_op_or_v;
    lkup_op_func_v['x'] = cf_op_xor_v;
    //lkup_op_func_v['^'] = cf_op_pow_v;

    memset(lkup_op_func_h, 0, 256 * sizeof(cell_dfunc_t));
    lkup_op_func_h['*'] = cf_op_mul_h;
    lkup_op_func_h['-'] = cf_op_sub_h;
    lkup_op_func_h['+'] = cf_op_add_h;
    lkup_op_func_h['/'] = cf_op_div_h;
    lkup_op_func_h['%'] = cf_op_mod_h;
    lkup_op_func_h['&'] = cf_op_and_h;
    lkup_op_func_h['o'] = cf_op_or_h;
    lkup_op_func_h['x'] = cf_op_xor_h;
    //lkup_op_func_h['^'] = cf_op_pow_h;
}



// File are read block by block and this is the block size
#define READ_BLOCK_SIZE 16384


void set_lkup_cell(cell_t *lkup_cell) {
    memset(lkup_cell, 0, 256 * sizeof(cell_t));
    for(int i = 0; i < nb_cell_type; i++) {
        cell_type_t type = cell_types[i];
        lkup_cell[type.chr] = i + 1;
    }
}



void phase1_parsing(FILE* file, char **_data, size_t *data_size, map_t map) {
    // Get file size
    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    if(ferror(file)) {
        perror("fseek");
        return;
    }

    *data_size = file_size;

    // Allocate buffer for readed data (because there are exploited later)
    // Allocate a multiple of READ_BLOCK_SIZE
    char *data = (char*) malloc((1 + (file_size - 1) / READ_BLOCK_SIZE) * READ_BLOCK_SIZE);
    *_data = data;

    // Types array has an initial size
    size_t nb_type = nb_cell_type + 1;

    // Variable used for detecting operation cell
    char op_close = '\0'; // ] or }
    char op_code = '\0'; // operation char

    // Initialize lookup table to know if a char has already been added to type lists
    cell_t lkup_cell[256];
    set_lkup_cell(lkup_cell);

    // Grid size
    int w = 0;
    int h = 1;

    // Current width
    int cw = 0;

    // Read file and compute number of type
    size_t len = READ_BLOCK_SIZE;
    size_t readed = 0;
    while(len == READ_BLOCK_SIZE) {
        len = fread(&data[readed], 1, READ_BLOCK_SIZE, file);

        if(ferror(file)) {
            perror("fread");
            return;
        }

        size_t i = readed;
        readed += len;
        for(; i < readed; i++) {
            char c = data[i];
            
            if(c == '\r') continue;
            if(c == '\n') {
                h++;
                if(cw > w) w = cw;
                cw = 0;
                op_close = '\0';
                op_code = '\0';
            }
            else {
                if(op_close) {
                    if(op_code) {
                        if(c == op_close) {
                            // It's an operation
                            nb_type++;
                        }
                        op_close = '\0';
                        op_code = '\0';
                    } else if(lkup_op_func_v[c]) {
                        // We don't know yet if it's an operation
                        op_code = c;
                    }
                }

                if(c == '[' || c == '{') {
                    op_close = c + 2; // + 2 to get ']' from '[' and '}' from '{' in ascii
                }

                if(!lkup_cell[c]) {
                    if(c != '~')
                        lkup_cell[c] = 1;
                    nb_type++;
                }

                cw++;
            }

        }
    }

    // Initialize map
    map->width = w;
    map->height = h;
    map->types = (cell_type_t*) malloc(nb_type * sizeof(cell_type_t));
    map->nb_type = nb_type;
    map->cells = (cell_t*) malloc(w * h * sizeof(cell_t));

    // Fill map->cells with empty cell
    cell_t empty_cell = lkup_cell[' '];
    size_t i = w * h;
    while(i--)
        map->cells[i] = empty_cell;

    // Fill map->types with base types
    for(int i = 0; i < nb_cell_type; i++) {
        map->types[i + 1] = cell_types[i];
    }
}


void phase2_parsing(char *data, size_t data_size, map_t map) {
    // Current coordinate
    int x = 0;
    int y = 0;

    // Variable used for detecting operation cell
    char op_close = '\0'; // ] or }
    char op_code = '\0'; // operation char

    // Initialize lookup table to know if a char has already been added to type lists
    cell_t lkup_cell[256];
    set_lkup_cell(lkup_cell);
    
    // Current number of type
    size_t current_type_index = nb_cell_type + 1;

    for(size_t i = 0; i < data_size; i++) {
        char c = data[i];
        if(c == '\r')
            continue;
        if(c == '\n') {
            y++;
            x = 0;
            op_close = '\0';
            op_code = '\0';
        }
        else {
            if(op_close) {
                if(op_code) {
                    if(c == op_close) {
                        // It's an operation
                        op_data_t* fdata = (op_data_t*) malloc(sizeof(op_data_t));
                        fdata->dots = QUEUE_CREATE(dot_queue_s);
                        fdata->dots_role = DOT_ROLE_UNKNOW;
                        cell_type_t type = {.chr = op_code, .data = fdata};
                        if(c == '}')
                            type.func = lkup_op_func_h[op_code];
                        else // c = ']'
                            type.func = lkup_op_func_v[op_code];
                        map->types[current_type_index] = type;
                        map->cells[y * map->width + x - 1] = current_type_index++;
                    }
                    op_close = '\0';
                    op_code = '\0';
                } else {
                    if(lkup_op_func_v[c]) {
                        // We don't know yet if it's an operation
                        op_code = c;
                    } else {
                        // It's not an operation
                        op_close = '\0';
                    }
                }
            }

            if(c == '[' || c == '{') {
                op_close = c + 2; // + 2 to get ']' from '[' and '}' from '{' in ascii
            }

            if(c == '.') {
                dot_t dot = dot_create();
                dot->x = x;
                dot->y = y;
                dot_add(map, dot);
            }

            cell_t cell = lkup_cell[c];
            if(cell) {
                // We know what this char do
                map->cells[y * map->width + x] = cell;
            }
            else {
                if(c == '~') {
                    cond_data_t* fdata = (cond_data_t*) malloc(sizeof(cond_data_t));
                    fdata->dots = QUEUE_CREATE(dot_queue_s);
                    fdata->dots_role = DOT_ROLE_UNKNOW;
                    cell_type_t type = {.chr = '~', .func = cf_conditional, .data = fdata};
                    map->types[current_type_index] = type;
                }
                else {
                    // We don't know what is this char
                    // so act like a '+' path and add
                    // this char to lkup_cell_value and map->types
                    cell_type_t type = {.chr = c, .func = cf_path_c, .data = NULL};
                    lkup_cell[c] = current_type_index;
                    map->types[current_type_index] = type;
                }
                map->cells[y * map->width + x] = current_type_index++;
            }

            x++;
        }
    }
}


map_t load_from_file(const char* filename) {
    init_lkup_op_func();

    map_t map = map_create();

    char* data;
    size_t data_size;

    // It's important to open the file in binary mode because in text mode on
    // Windows the \r\n is replaced by \n and this create segmentation fault because
    // the i variable isn't incremented correctly and buffer for data is preallocated.
    FILE* file = fopen(filename, "rb");

    if(!file) {
        printf("Can't find file %s!\n", filename);
        fflush(stdout);
        return NULL;
    }

    phase1_parsing(file, &data, &data_size, map);
    fclose(file);

    phase2_parsing(data, data_size, map);
    free(data);

    // Compute dots start direction
    int m = LIST_LENGTH(map->dots);
    for(int i = 0; i < m;) {
        dot_t dot = LIST_GET(map->dots, i);
        dot->direction = dot_get_start_direction(map, dot);
        if(dot->direction == 5) // Can't find valid start direction
            dot_rem(map, dot); // so delete the dot
        else
            i++;
    }

    return map;
}
