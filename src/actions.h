#ifndef ACTIONS_HEADER_INCLUDED
#define ACTIONS_HEADER_INCLUDED


#include "main.h"

#include "dot.h"
#include "map.h"


// Cell functions declarations

// Vertical operators

void cf_op_mul_v(map_t map, dot_t dot, op_data_t* data); // Multiplication '*'
void cf_op_div_v(map_t map, dot_t dot, op_data_t* data); // Division '/'
void cf_op_sub_v(map_t map, dot_t dot, op_data_t* data); // Substraction '-'
void cf_op_add_v(map_t map, dot_t dot, op_data_t* data); // Addition '+'
void cf_op_mod_v(map_t map, dot_t dot, op_data_t* data); // Modulo '%'
//void cf_op_pow_v(map_t map, dot_t dot, op_data_t* data); // Modulo '^'

void cf_op_equ_v(map_t map, dot_t dot, op_data_t* data); // Equal to '='
void cf_op_gtr_v(map_t map, dot_t dot, op_data_t* data); // Greater than '>'
void cf_op_lwr_v(map_t map, dot_t dot, op_data_t* data); // Lower than '<'

void cf_op_and_v(map_t map, dot_t dot, op_data_t* data); // Logical and '&'
void cf_op_or_v (map_t map, dot_t dot, op_data_t* data); // Logical or 'o'
void cf_op_xor_v(map_t map, dot_t dot, op_data_t* data); // Logical xor 'x'


// Horizontal operators

void cf_op_mul_h(map_t map, dot_t dot, op_data_t* data); // Multiplication '*'
void cf_op_div_h(map_t map, dot_t dot, op_data_t* data); // Division '/'
void cf_op_sub_h(map_t map, dot_t dot, op_data_t* data); // Substraction '-'
void cf_op_add_h(map_t map, dot_t dot, op_data_t* data); // Addition '+'
void cf_op_mod_h(map_t map, dot_t dot, op_data_t* data); // Modulo '%'
//void cf_op_pow_h(map_t map, dot_t dot, op_data_t* data); // Modulo '^'

void cf_op_equ_h(map_t map, dot_t dot, op_data_t* data); // Equal to '='
void cf_op_gtr_h(map_t map, dot_t dot, op_data_t* data); // Greater than '>'
void cf_op_lwr_h(map_t map, dot_t dot, op_data_t* data); // Lower than '<'

void cf_op_and_h(map_t map, dot_t dot, op_data_t* data); // Logical and '&'
void cf_op_or_h (map_t map, dot_t dot, op_data_t* data); // Logical or 'o'
void cf_op_xor_h(map_t map, dot_t dot, op_data_t* data); // Logical xor 'x'


void cf_conditional(map_t map, dot_t dot, cond_data_t* data); // Contional equal to 0 '~'

void cf_duplicator(map_t map, dot_t dot); // Duplicate incoming dot '*'

void cf_path_h(map_t map, dot_t dot); // Horizontale path '-' (h for horizontal)
void cf_path_v(map_t map, dot_t dot); // Vertical path '|' (v for vertical)
void cf_path_c(map_t map, dot_t dot); // Cross path '+' or any unknow char (c for cross)

void cf_mirror_b(map_t map, dot_t dot); // Mirror '\' (b for back[slash])
void cf_mirror_f(map_t map, dot_t dot); // Mirror '/' (f for front[slash])

void cf_reflector_l(map_t map, dot_t dot); // Left reflector ')'
void cf_reflector_r(map_t map, dot_t dot); // Left reflector '('

void cf_value(map_t map, dot_t dot); // Value '#'
void cf_print(map_t map, dot_t dot); // Print '$'

void cf_end(map_t map, dot_t dot); // Terminate program '&'
void cf_empty(map_t map, dot_t dot); // A space ' '

void cf_insertor_l(map_t map, dot_t dot); // Left insertor '<'
void cf_insertor_r(map_t map, dot_t dot); // Right insertor '>'
void cf_insertor_d(map_t map, dot_t dot); // Down insertor 'v'
void cf_insertor_u(map_t map, dot_t dot); // Up insertor '^'


#endif
