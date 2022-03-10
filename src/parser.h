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
