#define GENERAL_H 1

//libsodium header:
#include <sodium.h>
//allegro headers: 
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
//~~~~~~~~~~~~~~~~~~~~~
//custom headers:
#ifndef CHAR_H
#include "char.h"
#endif
//~~~~~~~~~~~~~~~~~~~~~

//macros: 
#define rangem(var, min, max) (var > min && var < max)
#define rangem_eq(var, min, max) (var >= min && var <= max)

#define ERROR_FAILED(arg1) { \
    fprintf(stderr, "failed to %s!\n", arg1); \
    exit(1); \
}
#define COMPARE_STR(arg1, arg2) ({ \
    strncmp(arg1, arg2, strlen(arg2)+1) == 0; \
})
//~~~~~~~~~~~~~~~~~~~~~

//external variables:
extern ALLEGRO_DISPLAY* display;

extern size_t COLOR_1[3];
extern size_t COLOR_2[3];

extern const int SCREEN_W;
extern const int SCREEN_H;

extern int track_keypress;
extern int GAME_STATE;
extern int BTN_TIMER;
extern int MOV_TIMER;
extern int ITEM_NUM;

extern bool draw_normal;
extern bool key[4];
//~~~~~~~~~~~~~~~~~~~~~

//general typedefs: 
typedef struct {
    ALLEGRO_FONT* font;
    int font_x;
    int font_y;
} font_struct;

typedef struct {
    font_struct font_pos;
    int button_p1[2];
    int button_p2[2];
    int state_id;
} btn_struct;

typedef struct {
    int* mouse_pos;
    int mouse_state;
} mouse_struct;
//~~~~~~~~~~~~~~~~~~~~~
