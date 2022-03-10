#ifndef MAIN_HEADER_INCLUDED
#define MAIN_HEADER_INCLUDED


#include <inttypes.h>

#include "list.h"
#include "queue.h"

typedef unsigned char byte;

#define TRUE 1
#define FALSE 0



// Directions

#define UP    0
#define RIGHT 1
#define DOWN  2
#define LEFT  3


// Role of queued dot in dot_queue_data_t type

#define DOT_ROLE_UNKNOW 0
#define DOT_ROLE_VALUE 1
#define DOT_ROLE_COMPARATOR 2
#define DOT_ROLE_LEFT 3
#define DOT_ROLE_RIGHT 4



// Types


// map_t->cells type
typedef uint32_t cell_t;
typedef unsigned char bool;


// Per cell data : character, function and cell's data (if any)
struct cell_data_struct;

typedef struct dot_s {
    int x, y;
    byte direction;
    double value;
    int32_t id;
    size_t index; // Index in map's list
} *dot_t;


typedef QUEUE_TYPE(dot_t, dot_queue_s, dot_queue_entry_s) *dot_queue_t;
typedef QUEUE_TYPE(char, char_queue_s, char_queue_entry_s) *char_queue_t;
typedef struct dot_queue_entry_s *dot_queue_entry_t;
typedef struct char_queue_entry_s *char_queue_entry_t;

typedef LIST_TYPE(dot_t, dot_list_s) *dot_list_t;


typedef struct map_s {
    int width, height;
    cell_t* cells;

    size_t nb_type;
    struct cell_data_struct* types;

    dot_list_t dots;
    size_t dots_li; // Dots left index
    size_t dots_ri; // Dots right index
} *map_t;

typedef struct {
    dot_queue_t dots;
    byte dots_role; // Role of dots in dots queue
} dot_queue_data_t;

typedef dot_queue_data_t op_data_t;
typedef dot_queue_data_t cond_data_t;

typedef void (*cell_func_t)(map_t, dot_t);
typedef void (*cell_dfunc_t)(map_t, dot_t, void*);
typedef void (*cell_opfunc_t)(map_t, dot_t, op_data_t*);

// Per cell data : character, function and cell's data (if any)
typedef struct cell_data_struct {
    void* func;
    char chr;
    void* data; // Can be null
} cell_type_t;

typedef struct {
    int x, y;
} vector2i_t;


#endif
