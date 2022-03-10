#ifndef QUEUE_HEADER_INCLUDED
#define QUEUE_HEADER_INCLUDED


#include <stdlib.h>


// Fast queue implementation

// I use a small number because the queue is only used by cell data to store a list of dot waiting in operator or '~'
#define QUEUE_BLOCK_SIZE 256

// tmp is used in QUEUE_DEQUEUE
#define QUEUE_TYPE(T, QNAME, ENAME) struct QNAME { \
    size_t len; \
    T tmp; \
    struct ENAME {T data[QUEUE_BLOCK_SIZE]; struct ENAME* next; size_t start; size_t end;} *first; \
    struct ENAME *last; \
}

#define QUEUE_CREATE(SNAME) ({ \
    struct SNAME *q; \
    q = malloc(sizeof(*q)); \
    q->len = 0; \
    q->first = NULL; \
    q->last = NULL; \
    q; \
})

#define QUEUE_DEQUEUE(q) ({ \
    q->tmp = q->first->data[q->first->start++]; \
    if(q->first->start == q->first->end) { \
        void* next = q->first->next; \
        free(q->first); \
        q->first = next; \
        if(!next) q->last = NULL; \
    } \
    q->len--; \
    q->tmp; \
})

#define QUEUE_ENQUEUE(q, value) { \
    if(q->last == NULL) { \
        q->last = q->first = malloc(sizeof(*q->last)); \
        q->last->start = 0; \
        q->last->end = 0; \
        q->last->next = NULL; \
    } \
    else if(q->last->end == QUEUE_BLOCK_SIZE) { \
        q->last->next = malloc(sizeof(*q->last)); \
        q->last = q->last->next; \
        q->last->start = 0; \
        q->last->end = 0; \
        q->last->next = NULL; \
    } \
    q->last->data[q->last->end++] = value; \
    q->len++; \
}

#define QUEUE_LENGTH(q) (q->len)

#define QUEUE_CLEAR(q) { \
    while(q->first) { \
        void* first = q->first; \
        q->first = q->first->next; \
        free(first); \
    } \
    q->len = 0; \
}

#define QUEUE_FREE(q) { \
    while(q->first) { \
        void* first = q->first; \
        q->first = q->first->next; \
        free(first); \
    } \
    free(q); \
}


#endif
