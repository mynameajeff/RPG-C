#define HELPERS_H 1

//standard headers:
#ifndef STDIO_H
#define STDIO_H 1
#include <stdio.h>
#endif
#ifndef STRING_H
#define STRING_H 1
#include <string.h>
#endif
#ifndef STDLIB_H
#define STDLIB_H 1
#include <stdlib.h>
#endif
#ifndef STDARG_H
#define STDARG_H 1
#include <stdarg.h>
#endif
//~~~~~~~~~~~~~~~~~~~~~
//custom headers:
#ifndef GENERAL_H
#include "general.h"
#endif
//~~~~~~~~~~~~~~~~~~~~~

//helper function defs: 
int create_button(
    char* text,
    mouse_struct* m_struct, 
    btn_struct* b_struct, 
    float border, 
    size_t* rgb,
    size_t* rgb2,
    int type
);

void render_map(
    char* file_data, 
    int tile_wh[2], 
    int map_xy[2], 
    char* array_chars, 
    int array_vals[][3]
);
char* get_file_data(
    char* file_path
);
int no_of_chars(
    FILE* file_ptr
);

char* format_stringf(
    const char string[], 
    ...
);
//~~~~~~~~~~~~~~~~~~~~~
