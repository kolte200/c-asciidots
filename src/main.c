#include <stdio.h>
#include <string.h>

#include "main.h"
#include "runner.h"
#include "parser.h"


/* 
 * Options:
 *   -d or --debug : Enable debug mode
 *   -h or --help : Show a help message
 *   -i or --input : Specify an input filename
 */


int main(int argc, char** args)
{
    printf("C AsciiDots interpreter\n\n");
    fflush(stdout);

    // Default file to read
    char* filename = "samples/bad_apple.dots";

    bool debug = FALSE;    

    // Parse arguments
    for(int i = 1; i < argc; i++) {
        if(!strcmp(args[i], "-d") || !strcmp(args[i], "--debug")) {
            debug = TRUE;
        } else if(!strcmp(args[i], "-h") || !strcmp(args[i], "--help")) {
            printf("Command line options:\n");
            printf("  -d or --debug : Enable debug mode\n");
            printf("  -h or --help : Show this help message\n");
            fflush(stdout);
            return 0;
        } else if(!strcmp(args[i], "-i") || !strcmp(args[i], "--input")) {
            if(i == argc - 1) {
                printf("You must enter a filename after %s option!\n", args[i]);
                fflush(stdout);
                return 1;
            }
            filename = args[argc - 1];
        }
    }
    
    printf("Start loading file ...\n");
    fflush(stdout);

    map_t map = load_from_file(filename);

    if(map == NULL)
        return 1;

    printf("Loading complete\n\n");
    fflush(stdout);

    char c;
    printf("Wait for enter ...\n");
    fflush(stdout);
    scanf("%c", &c);

    if(debug)
        runner_debug(map);
    else
        runner_run(map);

    /*
    // Test queue
    QUEUE_TYPE(int) q = QUEUE_CREATE(int);
    QUEUE_ENQUEUE(q, 9);
    QUEUE_ENQUEUE(q, 8);
    QUEUE_ENQUEUE(q, 7);
    printf("QUEUE_DEQUEUE(q) = %i\n", QUEUE_DEQUEUE(q));
    printf("QUEUE_DEQUEUE(q) = %i\n", QUEUE_DEQUEUE(q));
    printf("QUEUE_DEQUEUE(q) = %i\n", QUEUE_DEQUEUE(q));
    QUEUE_ENQUEUE(q, 2);
    QUEUE_ENQUEUE(q, 3);
    printf("QUEUE_DEQUEUE(q) = %i\n", QUEUE_DEQUEUE(q));
    printf("QUEUE_LENGTH(q) = %i\n", LIST_LENGTH(q));
    QUEUE_CLEAR(q);
    printf("QUEUE_LENGTH(q) = %i\n", LIST_LENGTH(q));
    QUEUE_FREE(q);
    
    /*
    // Test list
    LIST_TYPE(int) l = LIST_CREATE(int);
    LIST_ADD(l, 9);
    LIST_ADD(l, 8);
    LIST_ADD(l, 7);
    LIST_ADD(l, 6);
    LIST_ADD(l, 5);
    printf("LIST_GET(l, 0) = %i\n", LIST_GET(l, 0));
    printf("LIST_GET(l, 2) = %i\n", LIST_GET(l, 2));
    printf("LIST_GET(l, 4) = %i\n", LIST_GET(l, 4));
    printf("LIST_LENGTH(l) = %i\n", LIST_LENGTH(l));
    LIST_CLEAR(l);
    printf("LIST_LENGTH(l) = %i\n", LIST_LENGTH(l));
    LIST_FREE(l);
    */

    return 0;
}
