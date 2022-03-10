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


#ifndef DOT_HEADER_INCLUDED
#define DOT_HEADER_INCLUDED


#include "main.h"


dot_t dot_create();

void dot_add(map_t map, dot_t dot);

void dot_rem(map_t map, dot_t dot);

bool dot_step(map_t map, dot_t dot);

void dot_free(dot_t dot);


#endif
