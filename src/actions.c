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

#include "actions.h"


// Cell functions implementations

#define cf_op_v(prefix, op, suffix) \
    if(dot->direction & 0x1) { \
        if(QUEUE_LENGTH(data->dots)) { \
            if(data->dots_role == DOT_ROLE_LEFT) { \
                dot_t left = QUEUE_DEQUEUE(data->dots); \
                left->value = prefix left->value op dot->value suffix; \
                dot_rem(map, dot); \
                dot_free(dot); \
                dot_add(map, left); \
                dot_step(map, left); \
            } else { \
                QUEUE_ENQUEUE(data->dots, dot); \
                if(data->dots->len > 2097152) printf("Too many dot in cf_op_v right op queue!\n"); \
                dot_rem(map, dot); \
            } \
        } else { \
            QUEUE_ENQUEUE(data->dots, dot); \
            data->dots_role = DOT_ROLE_RIGHT; \
            dot_rem(map, dot); \
        } \
    } \
    else \
    { \
        if(QUEUE_LENGTH(data->dots)) { \
            if(data->dots_role == DOT_ROLE_RIGHT) { \
                dot_t right = QUEUE_DEQUEUE(data->dots); \
                dot->value = prefix dot->value op right->value suffix; \
                dot_free(right); \
                dot_step(map, dot); \
            } else { \
                QUEUE_ENQUEUE(data->dots, dot); \
                if(data->dots->len > 2097152) printf("Too many dot in cf_op_v left op queue!\n"); \
                dot_rem(map, dot); \
            } \
        } else { \
            QUEUE_ENQUEUE(data->dots, dot); \
            data->dots_role = DOT_ROLE_LEFT; \
            dot_rem(map, dot); \
        } \
    }


#define cf_op_h(prefix, op, suffix) \
    if(dot->direction & 0x1) { \
        if(QUEUE_LENGTH(data->dots)) { \
            if(data->dots_role == DOT_ROLE_RIGHT) { \
                dot_t right = QUEUE_DEQUEUE(data->dots); \
                dot->value = prefix dot->value op right->value suffix; \
                dot_free(right); \
                dot_step(map, dot); \
            } else { \
                QUEUE_ENQUEUE(data->dots, dot); \
                if(data->dots->len > 2097152) printf("Too many dot in cf_op_h left op queue!\n"); \
                dot_rem(map, dot); \
            } \
        } else { \
            QUEUE_ENQUEUE(data->dots, dot); \
            data->dots_role = DOT_ROLE_LEFT; \
            dot_rem(map, dot); \
        } \
    } \
    else \
    { \
        if(QUEUE_LENGTH(data->dots)) { \
            if(data->dots_role == DOT_ROLE_LEFT) { \
                dot_t left = QUEUE_DEQUEUE(data->dots); \
                left->value = prefix left->value op dot->value suffix; \
                dot_rem(map, dot); \
                dot_free(dot); \
                dot_add(map, left); \
                dot_step(map, left); \
            } else { \
                QUEUE_ENQUEUE(data->dots, dot); \
                if(data->dots->len > 2097152) printf("Too many dot in cf_op_h right op queue!\n"); \
                dot_rem(map, dot); \
            } \
        } else { \
            QUEUE_ENQUEUE(data->dots, dot); \
            data->dots_role = DOT_ROLE_RIGHT; \
            dot_rem(map, dot); \
        } \
    }


// Vertical operators

void cf_op_mul_v(map_t map, dot_t dot, op_data_t* data) { cf_op_v(,*,) }
void cf_op_div_v(map_t map, dot_t dot, op_data_t* data) { cf_op_v(,/,) }
void cf_op_sub_v(map_t map, dot_t dot, op_data_t* data) { cf_op_v(,-,) }
void cf_op_add_v(map_t map, dot_t dot, op_data_t* data) { cf_op_v(,+,) }
void cf_op_mod_v(map_t map, dot_t dot, op_data_t* data) { cf_op_v((int),%(int),) }

void cf_op_equ_v(map_t map, dot_t dot, op_data_t* data) { cf_op_v(,==,) }
void cf_op_gtr_v(map_t map, dot_t dot, op_data_t* data) { cf_op_v(,>,) }
void cf_op_lwr_v(map_t map, dot_t dot, op_data_t* data) { cf_op_v(,<,) }

void cf_op_and_v(map_t map, dot_t dot, op_data_t* data) { cf_op_v(,&&,) }
void cf_op_or_v (map_t map, dot_t dot, op_data_t* data) { cf_op_v(,||,) }
void cf_op_xor_v(map_t map, dot_t dot, op_data_t* data) { cf_op_v((int),^(int),?1:0) }


// Horizontal operators

void cf_op_mul_h(map_t map, dot_t dot, op_data_t* data) { cf_op_h(,*,) }
void cf_op_div_h(map_t map, dot_t dot, op_data_t* data) { cf_op_h(,/,) }
void cf_op_sub_h(map_t map, dot_t dot, op_data_t* data) { cf_op_h(,-,) }
void cf_op_add_h(map_t map, dot_t dot, op_data_t* data) { cf_op_h(,+,) }
void cf_op_mod_h(map_t map, dot_t dot, op_data_t* data) { cf_op_h((int),%(int),) }

void cf_op_equ_h(map_t map, dot_t dot, op_data_t* data) { cf_op_h(,==,) }
void cf_op_gtr_h(map_t map, dot_t dot, op_data_t* data) { cf_op_h(,>,) }
void cf_op_lwr_h(map_t map, dot_t dot, op_data_t* data) { cf_op_h(,<,) }

void cf_op_and_h(map_t map, dot_t dot, op_data_t* data) { cf_op_h(,&&,) }
void cf_op_or_h (map_t map, dot_t dot, op_data_t* data) { cf_op_h(,||,) }
void cf_op_xor_h(map_t map, dot_t dot, op_data_t* data) { cf_op_h((int),^(int),?1:0) }




void cf_conditional(map_t map, dot_t dot, cond_data_t* data) { // '~'
    if(dot->direction & 0x1) {
        if(QUEUE_LENGTH(data->dots)) {
            if(data->dots_role == DOT_ROLE_COMPARATOR) {
                dot_t comparator = QUEUE_DEQUEUE(data->dots);
                if(comparator->value != 0)
                    dot->direction = UP;
                dot_free(comparator);
                dot_step(map, dot);
            } else {
                QUEUE_ENQUEUE(data->dots, dot);
                if(data->dots->len > 2097152) printf("Too many dot in cf_conditional value queue!\n");
                dot_rem(map, dot);
            }
        } else {
            QUEUE_ENQUEUE(data->dots, dot);
            data->dots_role = DOT_ROLE_VALUE;
            dot_rem(map, dot);
        }
    }
    else
    {
        if(QUEUE_LENGTH(data->dots)) {
            if(data->dots_role == DOT_ROLE_VALUE) {
                dot_t value = QUEUE_DEQUEUE(data->dots);
                if(dot->value != 0)
                    value->direction = UP;
                dot_rem(map, dot);
                dot_free(dot);
                dot_add(map, value);
                dot_step(map, value);
            } else {
                QUEUE_ENQUEUE(data->dots, dot);
                if(data->dots->len > 2097152) printf("Too many dot in cf_conditional comparator queue at %i %i !\n", dot->x, dot->y);
                dot_rem(map, dot);
            }
        } else {
            QUEUE_ENQUEUE(data->dots, dot);
            data->dots_role = DOT_ROLE_COMPARATOR;
            dot_rem(map, dot);
        }
    }
}


void cf_duplicator(map_t map, dot_t dot) { // '*'
    dot_t a = dot_create();
    dot_t b = dot_create();

    a->x = b->x = dot->x;
    a->y = b->y = dot->y;
    a->value = b->value = dot->value;

    dot_add(map, a);
    dot_add(map, b);

    switch(dot->direction) {
        case UP:
            a->direction = LEFT;
            b->direction = RIGHT;
            break;
        case RIGHT:
            a->direction = UP;
            b->direction = DOWN;
            break;
        case DOWN:
            a->direction = LEFT;
            b->direction = RIGHT;
            break;
        case LEFT:
            a->direction = UP;
            b->direction = DOWN;
            break;
    }

    dot_step(map, a);
    dot_step(map, b);
    dot_step(map, dot);
}


void cf_path_h(map_t map, dot_t dot) { // '-'
    if(dot->direction & 0x1) {
        dot_step(map, dot);
    } else {
        dot_rem(map, dot);
        dot_free(dot);
    }
}

void cf_path_v(map_t map, dot_t dot) { // '|'
    if(dot->direction & 0x1) {
        dot_rem(map, dot);
        dot_free(dot);
    } else {
        dot_step(map, dot);
    }
}

void cf_path_c(map_t map, dot_t dot) { // '+'
    dot_step(map, dot);
}


void cf_mirror_b(map_t map, dot_t dot) { // '\'
    dot->direction = dot->direction ^ 0x3;
    dot_step(map, dot);
}

void cf_mirror_f(map_t map, dot_t dot) { // '/'
    dot->direction = dot->direction ^ 0x1;
    dot_step(map, dot);
}


void cf_reflector_l(map_t map, dot_t dot) { // ')'
    if(dot->direction == RIGHT)
        dot->direction = LEFT;
    dot_step(map, dot);
}

void cf_reflector_r(map_t map, dot_t dot) { // '('
    if(dot->direction == LEFT)
        dot->direction = RIGHT;
    dot_step(map, dot);
}


void cf_insertor_l(map_t map, dot_t dot) { // '<'
    if(!(dot->direction & 0x1))
        dot->direction = LEFT;
    dot_step(map, dot);
}

void cf_insertor_r(map_t map, dot_t dot) { // '>'
    if(!(dot->direction & 0x1))
        dot->direction = RIGHT;
    dot_step(map, dot);
}

void cf_insertor_d(map_t map, dot_t dot) { // 'v'
    if(dot->direction & 0x1)
        dot->direction = DOWN;
    dot_step(map, dot);
}

void cf_insertor_u(map_t map, dot_t dot) { // '^'
    if(dot->direction & 0x1)
        dot->direction = UP;
    dot_step(map, dot);
}



void cf_value(map_t map, dot_t dot) { // '#'
    dot->value = 0;

    while(1) {
        if(!dot_step(map, dot))
            return;

        char c = map_get_char(map, dot->x, dot->y);
        if(c == '?') {
            scanf("%lf", &dot->value);
        } else if(c <= '9' && c >= '0') {
            dot->value = dot->value * 10.0 + c - '0';
        } else {
            break;
        }
    }
}


// Read str until a specific char
char_queue_t read_str(map_t map, dot_t dot, const char endchar) {
    char_queue_t queue = QUEUE_CREATE(char_queue_s);
    char c;
    if(!dot_step(map, dot)) return FALSE;
    while((c = map_get_char(map, dot->x, dot->y)) != endchar) {
        QUEUE_ENQUEUE(queue, c);
        if(!dot_step(map, dot)) return NULL;
    }
    return queue;
}

// Print a list of char as a string
#define print_char_queue(q) { \
    char_queue_entry_t next = (char_queue_entry_t) q->first; \
    while(next) { \
        fwrite(&next->data[next->start], 1, next->end - next->start, stdout); \
        next = next->next; \
    } \
}

void cf_print(map_t map, dot_t dot) { // '$'
    bool nl = TRUE;
    bool a = FALSE;

    while(1) {
        if(!dot_step(map, dot))
            return;

        char c = map_get_char(map, dot->x, dot->y);
        switch(c) {
            case '_': {
                nl = FALSE;
                break;
            }

            case 'a': {
                a = TRUE;
                break;
            }

            case '\'':
            case '"': {
                char_queue_t queue = read_str(map, dot, c);
                if(queue == NULL) return;
                print_char_queue(queue);
                if(nl) fputc('\n', stdout);
                fflush(stdout);
                QUEUE_FREE(queue);
                goto end_of_cf_print;
            }

            case '#': {
                if(a) {
                    fputc((int) dot->value, stdout);
                } else {
                    printf("%f", dot->value);
                }
                if(nl) fputc('\n', stdout);
                fflush(stdout);
                goto end_of_cf_print;
            }
        }
    }

    end_of_cf_print:
    dot_step(map, dot);
}



void cf_end(map_t map, dot_t dot) { // '&'
    map_free(map);
    // TODO : Do a clean exit (free everything)
    exit(0);
}

void cf_empty(map_t map, dot_t dot) { // ' '
    dot_rem(map, dot);
    dot_free(dot);
}