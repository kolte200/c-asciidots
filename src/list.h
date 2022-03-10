#ifndef LIST_HEADER_INCLUDED
#define LIST_HEADER_INCLUDED


#include <stdlib.h>


// Fast list implementation

#define LIST_BLOCK_LEN 256 // Must be a power of 2 because it's faster! (because of divisions and modulos)
#define LIST_BLOCK_COUNT 256 // So there is a maximum of 256 * 256 element in a list

// tmp is used in LIST_POP
#define LIST_TYPE(T, SNAME) struct SNAME { \
    size_t len; \
    size_t block_size; \
    T tmp; \
    size_t nb_block; \
    T* blocks[LIST_BLOCK_COUNT]; \
}

#define LIST_CREATE(SNAME) ({ \
    struct SNAME *a; \
    a = malloc(sizeof(*a)); \
    a->len = 0; \
    a->nb_block = 0; \
    a->block_size = sizeof(a->tmp) * LIST_BLOCK_LEN; \
    a; \
})

#define LIST_GET(a, index) \
    (a->blocks[index / LIST_BLOCK_LEN][index % LIST_BLOCK_LEN])

#define LIST_SET(a, index, value) { \
    a->blocks[index / LIST_BLOCK_LEN][index % LIST_BLOCK_LEN] = value; \
}

#define LIST_ADD(a, value) { \
    if(a->len % LIST_BLOCK_LEN == 0) \
        a->blocks[a->nb_block++] = malloc(a->block_size); \
    a->blocks[a->nb_block - 1][a->len % LIST_BLOCK_LEN] = value; \
    a->len++; \
}

#define LIST_POP(a) ({ \
    a->len--; \
    size_t i = a->len % LIST_BLOCK_LEN; \
    a->tmp = a->blocks[a->nb_block - 1][i]; \
    if(i == 0) { \
        a->nb_block--; \
        free(a->blocks[a->nb_block]); \
    } \
    a->tmp; \
})

/*
// Currently don't work well with LIST_ADD
#define LIST_ALLOC(a, len) { \
    size_t m = (len - 1) / LIST_BLOCK_LEN + 1; \
    while(a->nb_blocks < m) \
        a->blocks[a->nb_blocks++] = malloc(a->block_size); \
}
*/

#define LIST_CLEAR(a) { \
    for(size_t i = 0; i < a->nb_block; i++) \
        free(a->blocks[i]); \
    a->nb_block = 0; \
    a->len = 0; \
}

#define LIST_FREE(a) { \
    for(size_t i = 0; i < a->nb_block; i++) \
        free(a->blocks[i]); \
    free(a); \
}

#define LIST_LENGTH(a) (a->len)


#endif
