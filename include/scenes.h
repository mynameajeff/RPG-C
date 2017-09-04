#define SCENES_H 1

//allegro headers:
#ifndef ALLEGRO_H
#define ALLEGRO_H 1
#include <allegro5/allegro.h>
#endif
//~~~~~~~~~~~~~~~~~~~~~
//custom headers:
#ifndef CHAR_H
#include "char.h"
#endif
#ifndef HELPERS_H
#include "helpers.h"
#endif
#ifndef ITEM_H
#include "item.h"
#endif
//~~~~~~~~~~~~~~~~~~~~~

//general functions:
void screen_title(
    mouse_struct* M_PASS, 
    font_struct* title_text, 
    btn_struct* b_collection
);
void screen_info(
    mouse_struct* M_PASS, 
    ALLEGRO_FONT* font,
    btn_struct* b_sct,
    char** lines
);
void screen_start(
    mouse_struct* M_PASS,
    char* file_data,
    int* mapxy,
    ALLEGRO_FONT* font,
    item_struct* item_chk,
    btn_struct* back_sct
);
void screen_battle(
    mouse_struct* M_PASS,
    char* file_data,
    int* mapxy,
    ALLEGRO_FONT* font_1,
    ALLEGRO_FONT* font_2,
    ALLEGRO_FONT* font_3,
    btn_struct* b_sct,
    btn_struct* b_sct_2
);
void screen_gameover(
    ALLEGRO_FONT* font
);
//~~~~~~~~~~~~~~~~~~~~~
