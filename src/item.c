#include "../include/item.h"

void check_item_overlap(item_struct* item_chk, int ITEM_NUM) {

    int px = player.pos[0];
    int py = player.pos[1];
    int pz = player.char_size/15;

    for (int k = 0; k < ITEM_NUM ; k++ ) {
        if ((px + pz) > item_chk[k].pos[0] && item_chk[k].pos[0] >= px &&
            (py + pz) > item_chk[k].pos[1] && item_chk[k].pos[1] >= py) {

            switch(item_chk[k].type_name) {
                case 1:
                    player.char_size += 15;
                    printf("mcdonalds collected\n");
                    break;
                case 2:
                    if (player.base.hp[0] + 40 >= player.base.hp[1]) {
                        player.base.hp[0] = player.base.hp[1];
                    }
                    else player.base.hp[0] += 40;

                    printf("health collected\n");
                    break;
            }
            
            item_chk[k] = item_chk[ITEM_NUM];
        }
    }

}

item_struct* gen_items(int num) {
    //generates the item structs used on the screen_start scene
    item_struct* genit = calloc(num, sizeof(item_struct));
    char name[10];

    for (int i = 0; i < num; i++) {
        item_struct itemtemp = {
            ( (randombytes_uniform(2) == 1) ? 1: 2),
            {15, 15},
            {15 + randombytes_uniform(28), 1 + randombytes_uniform(30)}
        };

        genit[i] = itemtemp;
    }

    return genit;
}
