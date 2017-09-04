#define CHAR_H 1

//standard headers:
#ifndef STDIO_H
#define STDIO_H 1
#include <stdio.h>
#endif
//~~~~~~~~~~~~~~~~~~~~~
//allegro headers:
#ifndef ALLEGRO_H
#define ALLEGRO_H 1
#include <allegro5/allegro.h>
#endif
//~~~~~~~~~~~~~~~~~~~~~
//custom headers:
#ifndef GENERAL_H
#include "general.h"
#endif
//~~~~~~~~~~~~~~~~~~~~~

//general typedefs:
typedef struct {
    char* name;

    int hp[2];
    int xp[2]; //for enemies to hold xp values, of which will be fed to player

    unsigned int atk;

    ALLEGRO_COLOR char_color;

} base_charac_struct;

typedef struct {

    int level;

    int pwr_defend; //if you defend in battle, this increases allowing you to hit harder.

    unsigned int char_size;

    unsigned int pos[2];

    base_charac_struct base;

} character_struct;

/*
the reason this is split up is so that enemies can use the base_charac_struct
with full capability of also using that for the character through character_struct.
*/
//~~~~~~~~~~~~~~~~~~~~~

//external variables:
extern character_struct player;
extern base_charac_struct enemy;
//~~~~~~~~~~~~~~~~~~~~~

//general functions:
void check_button_battle(
    int id
);
void attack_button_1(
);
void attack_button_2(
);
void attack_button(
);
void defend_button(
);
void info_button(
);

void change_movement(
);
void battle_check(
);
void check_level(
);
void atk_dfnd(
    int givehit,
    int gethit,
    int dmg1,
    int dmg2
);
//~~~~~~~~~~~~~~~~~~~~~
