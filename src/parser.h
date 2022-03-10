#include "main.h"

byte dot_get_start_direction(map_t map, dot_t dot);


// File are read block by block and this is the block size
#define READ_BLOCK_SIZE 16384

#define FOR_EACH_FILE_CHAR_BEGIN(file, buff, buffsize) \
    len = buffsize; \
    while(len == buffsize) { \
        len = fread(buff, 1, buffsize, file); \
        for(size_t i = 0; i < len; i++) { \
            char c = buff[i];

#define FOR_EACH_FILE_CHAR_END() }}


map_t load_from_file(const char* filename);
