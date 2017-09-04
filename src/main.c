#include "../include/main.h"

size_t COLOR_1[3] = {255, 255, 255};
size_t COLOR_2[3] = {235, 235, 235};

const int SCREEN_W = 640;
const int SCREEN_H = 480;

int track_keypress = false;
int GAME_STATE = 0;
int ITEM_NUM = 10;
int MOV_TIMER = 0;

bool key[4];

ALLEGRO_DISPLAY* display;
character_struct player;

int main() {

    init_als();

    ALLEGRO_EVENT_QUEUE* e_queue;
    ALLEGRO_MOUSE_STATE state;
    ALLEGRO_TIMER* timer;
    ALLEGRO_FONT* font_0;
    ALLEGRO_FONT* font_1;
    ALLEGRO_FONT* font_2;
    ALLEGRO_FONT* font_3;
    ALLEGRO_FONT* gfont;
    ALLEGRO_EVENT event;

    btn_struct b_collection_1[3];
    btn_struct b_collection_2[4];
    btn_struct b_collection_3[3];

    int mouse_pos[2] = {0, 0};
    bool looping = true;
    bool flip = true;

    e_queue = al_create_event_queue();
    if (!e_queue) {ERROR_FAILED("create event-queue")}

    display = al_create_display(SCREEN_W, SCREEN_H);
    if (!display) {ERROR_FAILED("create display")}

    al_set_new_window_title("RPG");

    timer = al_create_timer(1.0 / 60);
    if (!timer) {ERROR_FAILED("create timer")}

    font_0 = al_load_ttf_font("./fonts/pxlvetica.ttf", 128, 0);
    if (!font_0) {ERROR_FAILED("load pxlvetica-font")}

    font_struct title_text = {font_0, SCREEN_W / 2, SCREEN_H / 6};

    font_0 = al_load_ttf_font("./fonts/munro.ttf", 40, 0);
    if (!font_0) {ERROR_FAILED("load munro-font")}

    int text_move[3] = {60, 70, 70};
    float scr_divide[3] = {2, 1.5, 1.2};
    int typed[3] = {0, 1, 4};

    for (int i = 0; i < 3 ;i++) {
        btn_struct button = {
            {font_0, (SCREEN_W/3)+text_move[i], (SCREEN_H/scr_divide[i])-3},
            {SCREEN_W/3, SCREEN_H/scr_divide[i]},
            {(SCREEN_W/3)*2, (SCREEN_H/scr_divide[i])+40},
            typed[i]
        };
        b_collection_1[i] = button;
    }

    font_0 = al_load_ttf_font("./fonts/freesans.ttf", 18, 0);
    if (!font_0) {ERROR_FAILED("load freesans-font")}

    ALLEGRO_FONT* font_static_0 = font_0;

    font_0 = al_load_ttf_font("./fonts/munro.ttf", 45, 0);
    if (!font_0) {ERROR_FAILED("load munro-font")}

    btn_struct back_sct = {
        {font_0, 45, 26},
        {25, 30},
        {(SCREEN_W/5)+15, 70},
        -1
    };

    font_0 = al_load_ttf_font("./fonts/munro.ttf", 70, 0);
    if (!font_0) {ERROR_FAILED("load munro-font")}

    int xymov[] = {-16, 15};
    btn_struct back_sct_2 = {
        {font_0, 21+xymov[0], 397+xymov[1]},
        {16+xymov[0], 420+xymov[1]},
        {60+xymov[0], 465+xymov[1]},
        -1
    };

    int mapxy[2] = {220, 25};
    char* file_data = get_file_data("./maps/level.map");
    player = (character_struct) {1, 0, 15, {17,6},
        {"Player", {100, 100}, {0, 25}, 1, al_map_rgb(120, 240, 68)}};

    font_0 = al_load_ttf_font("./fonts/munro.ttf", 30, 0);
    if (!font_0) {ERROR_FAILED("load munro-font")}
    item_struct* item_chk = gen_items(ITEM_NUM);

    gfont = al_load_ttf_font("./fonts/freesans.ttf", 40, 0);
    if (!gfont) {ERROR_FAILED("load freesans-font")}

    int mapxy2[2] = {180, 135};
    char* file_data_2 = get_file_data("./maps/battle.map");

    font_1 = al_load_ttf_font("./fonts/munro.ttf", 40, 0);
    if (!font_1) {ERROR_FAILED("load munro-font")}

    int addon[4] = {0, 0, 20, 20};
    int ypos[3] = {28, 30, 70};
    int typen[4] = {0, 1, 2, 0};
    for (int i = 0; i < 4 ; i++, ypos[0] += 55, ypos[1] += 55, ypos[2] += 55) {
        btn_struct button2 = {
            {font_1, 32.5+addon[i], ypos[0]},
            {10, ypos[1]},
            {165, ypos[2]},
            typen[i]
        };
        b_collection_2[i] = button2;
    }

    font_2 = al_load_ttf_font("./fonts/munro.ttf", 20, 0);
    if (!font_2) {ERROR_FAILED("load munro-font")}

    font_3 = al_load_ttf_font("./fonts/freesans.ttf", 11, 0);
    if (!font_3) {ERROR_FAILED("load freesans-font")}

    char* lines[] = {
        "This is a little project trying to be a little RPG thingy.",
        "Written entirely by \"Occasional Projects\" "
        "using Allegro 5.2.2, LibSodium & C.",
        "",
        "When you press \"start\", you will see a screen of which you are placed on.",
        "On this screen you are represented as a bright green square,",
        "upon a checkered surface.",
        "",
        "Cyan squares give you a health boost,",
        "and Ocean blue squares increase your size.",
        "use either Arrows or WASD to control your character.",
        "",
        "As time goes on in the game, your level will increase and you will",
        "encounter stronger enemies, alongside a boss.",
        "",
        "When in combat, you can increase PWR with the defend button."
    };

    int addon_2[4] = {8, 8, 20};
    int ypos_2[3] = {28, 30, 70};
    int typen_2[4] = {0, 1, 2, 0};
    for (int i = 0; i < 3 ; i++, ypos_2[0] += 55, ypos_2[1] += 55, ypos_2[2] += 55) {
        btn_struct button3 = {
            {font_1, 32.5+addon_2[i], ypos_2[0]},
            {10, ypos_2[1]},
            {165, ypos_2[2]},
            typen_2[i]
        };
        b_collection_3[i] = button3;
    }

    al_set_window_title(display, "RPG");
    al_register_event_source(e_queue, al_get_display_event_source(display));
    al_register_event_source(e_queue, al_get_timer_event_source(timer));
    al_register_event_source(e_queue, al_get_keyboard_event_source());
    al_register_event_source(e_queue, al_get_mouse_event_source());
    al_start_timer(timer);


    while (looping) {
        al_wait_for_event(e_queue, &event);
        al_get_mouse_state(&state);

        if (player.base.hp[0] <= 0) {
            GAME_STATE = 4;
        }

        switch(event.type) {
            case ALLEGRO_EVENT_TIMER:
                change_movement(MOV_TIMER);

                flip = true;
                break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                looping = false;
                break;

            case ALLEGRO_EVENT_MOUSE_AXES:
            case ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY:
                mouse_pos[0] = event.mouse.x;
                mouse_pos[1] = event.mouse.y;
                break;
        }

        if (track_keypress) {

            int arrtemp[2] = {ALLEGRO_EVENT_KEY_DOWN, ALLEGRO_EVENT_KEY_UP};
            bool arrtmp2[2] = {true, false};
            for (int i = 0; i < 2; i++) {
                if (event.type == arrtemp[i]) {
                    switch(event.keyboard.keycode) {

                        case ALLEGRO_KEY_W:
                        case ALLEGRO_KEY_UP: 
                            key[0] = arrtmp2[i];
                            break;

                        case ALLEGRO_KEY_S:
                        case ALLEGRO_KEY_DOWN: 
                            key[1] = arrtmp2[i];
                            break;

                        case ALLEGRO_KEY_A:
                        case ALLEGRO_KEY_LEFT: 
                            key[2] = arrtmp2[i];
                            break;

                        case ALLEGRO_KEY_D:
                        case ALLEGRO_KEY_RIGHT: 
                            key[3] = arrtmp2[i];
                            break;
                    }
                }
            }
        }

        if (flip && al_is_event_queue_empty(e_queue)) {
            al_clear_to_color(al_map_rgb(185, 185, 185));
            al_draw_line(0, 10, SCREEN_W, 10, al_map_rgb(128, 128, 128), 20);
            mouse_struct M_PASS = {mouse_pos, state.buttons};

            switch (GAME_STATE) {
                case 0:
                    screen_title(&M_PASS, &title_text, b_collection_1);
                    break;

                case 1:
                    screen_start(&M_PASS, file_data, mapxy, font_0, item_chk, &back_sct_2);
                    break;

                case 2:
                    screen_info(&M_PASS, font_static_0, &back_sct, lines);
                    break;

                case 3:
                    screen_battle(&M_PASS, file_data_2, mapxy2, font_1, font_2, 
                        font_3, b_collection_2, b_collection_3);
                    break;

                case 4:
                    screen_gameover(gfont); 
                    break;

                case 5:
                    looping = false;
                    break;

                default:
                    ERROR_FAILED("get game_state")
            }

            al_flip_display();

            flip = false;
        }
    }


    al_destroy_event_queue(e_queue);
    al_destroy_display(display);
    al_destroy_timer(timer);
    free(file_data);
    free(item_chk);

    return 0;
}

void init_als() {
    if (sodium_init() == -1) {ERROR_FAILED("initialize libsodium")}
    if (!al_init()) {ERROR_FAILED("initialize allegro")}
    if (!al_install_mouse()) {ERROR_FAILED("initialize mouse")}
    if (!al_install_keyboard()) {ERROR_FAILED("initialize keyboard")}
    if (!al_init_primitives_addon()) {ERROR_FAILED("initialize primitives-addon")}
    if (!al_init_font_addon()) {ERROR_FAILED("initialize font-addon")}
    if (!al_init_ttf_addon()) {ERROR_FAILED("initialize ttf-addon")}
}
