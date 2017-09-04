#include "../include/scenes.h"

bool draw_normal = true;

void screen_title(mouse_struct* M_PASS, 
font_struct* title_text, btn_struct* b_collection) {

    if (track_keypress) track_keypress = false;

    al_draw_filled_rectangle(0, 20, SCREEN_W, SCREEN_H, al_map_rgb(128, 128, 128));
    al_draw_filled_rectangle(5, 20, SCREEN_W-5, SCREEN_H-5, al_map_rgb(185, 185, 185));

    al_draw_text(
        title_text->font, 
        al_map_rgb(100, 100, 100), 
        title_text->font_x, 
        title_text->font_y, 
        ALLEGRO_ALIGN_CENTRE, 
        al_get_new_window_title()
    );

    char* string_arr[] = {"Start", "Info", "Exit"};
    for (int i = 0; i < 3 ;i++)
        create_button(string_arr[i], M_PASS, &b_collection[i], 5, COLOR_1, COLOR_2, 0);
}

void screen_info(mouse_struct* M_PASS, ALLEGRO_FONT* font, 
btn_struct* b_sct, char** lines) {

    al_draw_filled_rectangle(0, 20, SCREEN_W, SCREEN_H, al_map_rgb(128, 128, 128));
    al_draw_filled_rectangle(5, 20, SCREEN_W-5, SCREEN_H-5, al_map_rgb(185, 185, 185));

    int y = 80;

    for(int i = 0; i < 15; i++) {
        al_draw_text(
            font,
            al_map_rgb(100, 100, 100),
            22,
            y,
            ALLEGRO_ALIGN_LEFT,
            lines[i]
        );
        y += 26;
    }

    create_button("<==", M_PASS, b_sct, 5, COLOR_1, COLOR_2, 0);
}

void screen_start(mouse_struct* M_PASS, char* file_data, int* mapxy,
ALLEGRO_FONT* font, item_struct* item_chk, btn_struct* b_sct) {

    if (!track_keypress) track_keypress = true;
    if (!draw_normal) draw_normal = true;

    int tilesize[2] = {15, 15};
    int array_vals[2][3] = {
        {100, 100, 100}, 
        {100, 0, 0}
    };

    if (COMPARE_STR(al_get_new_window_title(), "Battle Mode!")) {
        al_set_window_title(display, "RPG");
        al_set_new_window_title("RPG");
    }

    al_draw_filled_rectangle(0, 20, 220, SCREEN_H, al_map_rgb(70, 70, 70));
    al_draw_line(217.5, 20, 217.5, SCREEN_H, al_map_rgb(90, 90, 90), 5);

    al_draw_filled_rectangle(10, 30, 165, 225, al_map_rgb(130, 130, 130));
    
    float x;
    for (int i = 0, n = 120; i < 50 && (n-x) > 70; i++, x += 1.2) {
        al_draw_filled_rectangle(160+i, 30, 161+i, 225, al_map_rgb(n-x, n-x, n-x));
    }

    al_draw_filled_rectangle(15, 35, 160, 220, al_map_rgb(120, 120, 120));
    for (int i = 0, n = 120; i < 50; i++) {
        al_draw_filled_rectangle(155+i, 35, 156+i, 220, al_map_rgb(n-i, n-i, n-i));
    }

    render_map(file_data, tilesize, mapxy, "12", array_vals);

    char* array_of_things[] = {
        format_stringf("HP: %d/%d", player.base.hp[0], player.base.hp[1]),
        format_stringf("XP: %d/%d", player.base.xp[0], player.base.xp[1]),
        format_stringf("Level: %d", player.level),
        format_stringf("DMG*: %d", player.base.atk),
        format_stringf("PWR: %d", player.pwr_defend),
        format_stringf("Char Size: %d", player.char_size/15)
    };

    int y_var = 35;
    for (int i = 0; i < 6; i++) {
        al_draw_text(
            font, 
            al_map_rgb(90, 90, 90), 
            20, 
            y_var, 
            ALLEGRO_ALIGN_LEFT, 
            array_of_things[i]
        );
        y_var += 30;
    }

    for (int j = 0; j < ITEM_NUM; j++) {
        if (ITEM_NUM == 0) break;
        al_draw_filled_rectangle(
            (item_chk[j].pos[0]*15)-5, 
            (item_chk[j].pos[1]*15)+10, 
            (item_chk[j].pos[0]*15)-5+item_chk[j].wh[0],
            (item_chk[j].pos[1]*15)+10+item_chk[j].wh[1], 
            (item_chk[j].type_name == 1) ? 
                al_map_rgb(0, 100, 255) : al_map_rgb(0, 255, 250)
        );
    }

    check_level();
    int player_x = (player.pos[0]*15)-5;
    int player_y = (player.pos[1]*15)+10;
    al_draw_filled_rectangle(
        player_x, 
        player_y, 
        player_x+player.char_size, 
        player_y+player.char_size, 
        player.base.char_color
    );

    check_item_overlap(item_chk, ITEM_NUM);

    al_draw_filled_rectangle(
        0, 430, 215, 480,
        al_map_rgb(60, 60, 60)
    );

    al_draw_line(
        0, 433, 215, 433, 
        al_map_rgb(128, 128, 128), 5
    );

    size_t COLOR3[] = {120, 120, 120};
    size_t COLOR4[] = {100, 100, 100};
    create_button("x", M_PASS, b_sct, 5, COLOR3, COLOR4, 0);

}

void screen_battle(mouse_struct* M_PASS, char* file_data, int* mapxy, 
ALLEGRO_FONT* font_1, ALLEGRO_FONT* font_2, ALLEGRO_FONT* font_3, 
btn_struct* b_sct, btn_struct* b_sct_2) {

    if (track_keypress) track_keypress = false;
    
    for (int i = 0; i <= 4; i++) {
        if (key[i]) {key[i] = false;}
    }

    if (COMPARE_STR(al_get_new_window_title(), "RPG")) {
        al_set_window_title(display, "Battle Mode!");
        al_set_new_window_title("Battle Mode!");
    }

    al_draw_filled_rectangle(0, 20, 180, SCREEN_H, al_map_rgb(70, 70, 70));
    al_draw_filled_rectangle(175, 20, 180, SCREEN_H, al_map_rgb(90, 90, 90));

    char* string_arr[] = {"Attack", "Defend", "Info", "Run"};
    int typebutton[] = {1, 1, 1, 0};
    size_t COLOR3[] = {155, 155, 155};
    size_t COLOR4[] = {135, 135, 135};

    char* string_arr2[] = {"Punch", "Tustle", "<=="};
    int typebtn_2[] = {1, 1, 1};

    if (draw_normal) {
        for (int i = 0; i < 4; i++) {
            create_button(
                string_arr[i], 
                M_PASS, 
                &b_sct[i], 
                5, 
                COLOR3,
                COLOR4, 
                typebutton[i]
            );
        }
    }
    else {
        for (int i = 0; i < 3; i++) {
            create_button(
                string_arr2[i],
                M_PASS,
                &b_sct_2[i],
                5,
                COLOR3,
                COLOR4,
                typebtn_2[i]
            );
        }
    }

    int tilesize[2] = {20, 15};
    int array_vals[][3] = {
        {0, 110, 0},
        {0, 100, 0}, 
        {120, 120, 255}
    };

    render_map(file_data, tilesize, mapxy, "345", array_vals);

    al_draw_filled_rectangle(
        250, 180, 330, 375, 
        enemy.char_color
    ); //enemy

    al_draw_filled_rectangle(
        460, 300, 535, 375, 
        al_map_rgb(120, 240, 68)
    ); //player

    //red hp bars
    al_draw_filled_rectangle(
        460, 280, 535, 290,
        al_map_rgb(255, 0, 0)
    );

    al_draw_filled_rectangle(
        250, 160, 330, 170, 
        al_map_rgb(255, 0, 0)
    );
    //~~~~~~~~~~~~~~~~~

    //names of enemy and you
    float coords[4] = {290, 138, 500, 258};

    for (int x = 0; x < 3; x+=2) {
        al_draw_text(
            font_2,
            al_map_rgb(200, 200, 200), 
            coords[x], 
            coords[x+1], 
            ALLEGRO_ALIGN_CENTRE, 
            (x == 0) ? enemy.name : player.base.name
        );
    }
    //~~~~~~~~~~~~~~~~~
    
    //green hp bars:
    float fl_1 = (float) 75/player.base.hp[1];

    float fl_l2 = (enemy.hp[1] > 10000) ? 
        (float) 80/(enemy.hp[1]/100) : (float) 80/enemy.hp[1];

    float var2 = (enemy.hp[1] > 10000) ? 
    enemy.hp[0]/100 : enemy.hp[0];

    for (float i = 0, n = 0; i < player.base.hp[0]; i++, n += fl_1) {
        al_draw_filled_rectangle(
            460 + n, 
            SCREEN_H - 200, 
            460 + n + fl_1, 
            SCREEN_H - 190,
            al_map_rgb(0, 255, 0)
        );
    }

    for (float i = 0, n = 0; i < var2; i++, n += fl_l2) {
        al_draw_filled_rectangle(
            250 + n, 
            160, 
            250 + n + fl_l2, 
            170,
            al_map_rgb(0, 255, 0)
        );
    }
    //~~~~~~~~~~~~~~~~~
    //text hp beside bars:
    float coords_2[4] = {334, 158, 540, 278};
    char* str1 = format_stringf("%d/%d", 
        enemy.hp[0], enemy.hp[1]);
    char* str2 = format_stringf("%d/%d", 
        player.base.hp[0], player.base.hp[1]);
    
    for (int y = 0; y < 3; y+=2) {
        al_draw_text(
            font_3,
            al_map_rgb(0, 0, 0), 
            coords_2[y], 
            coords_2[y+1], 
            ALLEGRO_ALIGN_LEFT, 
            (y == 0) ? str1 : str2
        );
    }

    if (str1) free(str1);
    if (str2) free(str2);
    //~~~~~~~~~~~~~~~~~

}

void screen_gameover(ALLEGRO_FONT* gofont) {
    if (track_keypress) track_keypress = false;
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_text(
        gofont, 
        al_map_rgb(255, 255, 255), 
        SCREEN_W/2, 
        SCREEN_H/2-50, 
        ALLEGRO_ALIGN_CENTRE, 
        "GAME OVER"
    );
}
