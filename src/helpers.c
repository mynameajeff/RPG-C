#include "../include/helpers.h"

void create_button(char* text, mouse_struct* m_struct, btn_struct* b_struct, 
float border, size_t* rgb, size_t* rgb2, int type) {

    size_t r = rgb[0], g = rgb[1], b = rgb[2];
    size_t r2 = rgb2[0], g2 = rgb2[1], b2 = rgb2[2];
    float x1 = b_struct->button_p1[0];
    float y1 = b_struct->button_p1[1];
    float x2 = b_struct->button_p2[0];
    float y2 = b_struct->button_p2[1];
    int x = m_struct->mouse_pos[0];
    int y = m_struct->mouse_pos[1];
    int ac = 0, bc = 0;

    ALLEGRO_COLOR acolor, bcolor;

    if (border < 0)
        ERROR_FAILED("load border value, lower than 0")

    if (r > 255 || g > 255 || b > 255)
        ERROR_FAILED("load rgb values, not within 0-255")

    if (rangem(x, (x1-border), (x2+border)) && rangem(y, (y1-border), (y2+border))) {
        acolor = al_map_rgb(r2, g2, b2);

        if ((r-40) < 255 || (g-40) < 255 || (b-40) < 255) {
            bcolor = al_map_rgb(r2-20, g2-20, b2-20);
        }
        else {
            bcolor = al_map_rgb(r2-40, g2-40, b2-40);
        }

        if (m_struct->mouse_state) {
            switch(type){
                case 0: 
                    GAME_STATE = b_struct->state_id+1; //changes stages of screen
                    break;
                case 1:
                    check_button_battle(b_struct->state_id); //makes button do things onscreen
                    break;
            }
        }
    }
    else {
        acolor = al_map_rgb(r, g, b);
        bcolor = al_map_rgb(r2, g2, b2);
    }

    al_draw_filled_rectangle(x1-border, y1-border, x2+border, y2+border, acolor);
    al_draw_filled_rectangle(x1, y1, x2, y2, bcolor);
    al_draw_text(
        b_struct->font_pos.font,
        (rangem_eq(r, 80, 120) && rangem_eq(g, 80, 120) && rangem_eq(b, 80, 120)) ?
            al_map_rgb(60, 60, 60): al_map_rgb(100, 100, 100), 
        b_struct->font_pos.font_x, 
        b_struct->font_pos.font_y,
        ALLEGRO_ALIGN_LEFT, 
        text
    );
}

void render_map(char* file_data, int tile_wh[2], int map_xy[2], 
char* array_chars, int array_vals[][3]) {

    int l_map_x = map_xy[0];
    int l_map_y = map_xy[1];

    for (int i = 0; i < strlen(file_data); i++) {
        if (file_data[i] != ' ') {
            for (int j = 0; j < strlen(array_chars); j++) {
                if (file_data[i] == array_chars[j]) {
                    al_draw_filled_rectangle(
                        l_map_x,
                        l_map_y,
                        (l_map_x + tile_wh[0]),
                        (l_map_y + tile_wh[1]),
                        al_map_rgb(
                            array_vals[j][0], 
                            array_vals[j][1], 
                            array_vals[j][2]
                        )
                    );
                }
            }
            if (file_data[i] == '\n') {
                l_map_x = map_xy[0];
                l_map_y += tile_wh[1];
            }
            else l_map_x += tile_wh[0];
        }
    }

}

char* format_stringf(const char string[], ...) {

    char* buffer = calloc(80, 1);
    va_list args;

    va_start(args, string);
    vsprintf(buffer, string, args);
    va_end(args);

    return buffer;
}

char* get_file_data(char* file_path) {

    FILE* file_pointer = fopen(file_path, "r");
    if (!file_pointer) exit(EXIT_FAILURE);

    int noc = no_of_chars(file_pointer);
    char* file_data = calloc(noc, 1);

    fread(file_data, noc+1, 1, file_pointer);
    fclose(file_pointer);

    return file_data;
}

int no_of_chars(FILE* fp) {
    size_t characters = 0;

    while(fgetc(fp) != EOF) characters++;

    rewind(fp);
    return characters;
}
