#include "../include/char.h"

base_charac_struct enemy;
int BTN_TIMER = 0;

void check_level() {
    while (player.base.xp[0] >= player.base.xp[1]) {
        player.level++;
        player.base.xp[0] = 0;
        player.base.xp[1] *= 1.5;
        player.base.hp[0] *= 1.75;
        player.base.hp[1] *= 1.75;
        player.base.atk *= 2;

        printf("Level Up! You're now level %d.\n", player.level);
    }
}

void gen_enem() {
    //random number to determine type of monster encountered
    //as your level increases, you encounter a more diverse array of enemies
    //each harder to fight then the last
    int ran = randombytes_uniform((player.level >= 5) ? 5: player.level);

    char* enem_names[] = {
        "an Imp", 
        "an Orc", 
        "a Gremlin", 
        "a Goblin", 
        "a Gremloblin"
    };
    int hps[] = {500, 800, 1200, 1400, 36000};
    int xps[] = {10, 25, 35, 22, 128};
    int pwrs[] = {1, 2, 4, 6, 12};
    int colors[][3] = {
        {25, 120, 25},
        {85, 120, 25},
        {45, 120, 55},
        {65, 120, 65},
        {125, 120, 125}
    };

    enemy = (base_charac_struct) {
        enem_names[ran], {hps[ran], hps[ran]},
        {xps[ran], 0}, pwrs[ran], 
        al_map_rgb(
            colors[ran][0], 
            colors[ran][1], 
            colors[ran][2]
        )
    };

}

void attack_button_1() {

    int givehit = randombytes_uniform(20);
    int gethit = randombytes_uniform(5);

    int dmg2 = randombytes_uniform(8 * enemy.atk);
    int dmg1 = 100 * player.base.atk;

    atk_dfnd(givehit, gethit, dmg1, dmg2);
}

void attack_button_2() {
    if (player.pwr_defend < 5) {
        printf("Tustle requires at least a PWR of 5 to use.\n");
    }
    else {
        player.pwr_defend -= 5;

        int givehit = randombytes_uniform(40);
        int gethit = randombytes_uniform(10);

        int dmg2 = randombytes_uniform(6 * enemy.atk);
        int dmg1 = 1000 * player.base.atk;
        
        atk_dfnd(givehit, gethit, dmg1, dmg2);
    }
}

void atk_dfnd(int givehit, int gethit, int dmg1, int dmg2) {

    if (givehit != 0) {
        enemy.hp[0] -= dmg1;
        printf("You attack %s for %d damage!\n\n", enemy.name, dmg1);
    }
    else {
        printf("You missed when attacking %s!\n", enemy.name);
    }

    if (gethit != 0 && dmg2 > 0) {
        player.base.hp[0] -= dmg2;
        printf("%s attacks you for %d damage!\n\n", enemy.name, dmg2);
    }
    else {
        printf("%s missed when attacking you!\n", enemy.name);
    }
}

void defend_button() {

    int pwr_points = randombytes_uniform(3);
    int gethit = randombytes_uniform(5);
    int dmg2 = randombytes_uniform(8 * enemy.atk);

    printf("You defend for one turn, and gain %d PWR points!\n", pwr_points);

    if (gethit != 0 && dmg2 > 0) { 
        player.base.hp[0] -= dmg2;
        printf("%s attacks you for %d damage!\n\n", enemy.name, dmg2);
    }
    else {
        printf("%s missed when attacking you!\n", enemy.name);
    }

    player.pwr_defend += pwr_points;
}

void info_button() {
    if (COMPARE_STR(enemy.name, "an Imp")) {
        printf("weak but can be strong in numbers.\n1 pwr / 500 hp\n");
    }
    else if (COMPARE_STR(enemy.name, "an Orc")) {
        printf("the Imp's tougher brother.\n2 pwr / 800 hp\n");
    }
    else if (COMPARE_STR(enemy.name, "a Gremlin")) {
        printf("This is an average encounter for the average traveller.\n"
               "4 pwr / 1200 hp\n");
    }
    else if (COMPARE_STR(enemy.name, "a Goblin")) {
        printf("The toughest normal enemy in this area.\n6 pwr / 1400 hp\n");
    }
    else if (COMPARE_STR(enemy.name, "a Gremloblin")) {
        printf("This is the first and only boss implemented in the game.\n"
               "I would suggest grinding a bit before fighting this guy.\n"
               "10 pwr / 36000 hp\n");
    }
}

void check_button_battle(int id) {

    //BTN_TIMER handles the delay on the 4 buttons within the Battle Scene
    if (BTN_TIMER <= 0) {
        switch(id) {
            case 0:
                if (draw_normal)
                    draw_normal = false;

                else
                    attack_button_1();

                BTN_TIMER += 5;
                break;
        
            case 1:
                if (draw_normal)
                    defend_button();

                else
                    attack_button_2();

                BTN_TIMER += 4;
                break;

            case 2:
                if (draw_normal) {
                    info_button();
                    BTN_TIMER += 12;
                }
                else {
                    draw_normal = true;
                    BTN_TIMER += 4;
                }
                break;

            default:
                ERROR_FAILED("get correct id");
        }
    }
    else {
        BTN_TIMER--;
    }

    if (player.base.hp[0] <= 0) {
        printf("\n%s has defeated you!\n", enemy.name);
    }
    else if (enemy.hp[0] <= 0) {
        printf("You killed %s! +%d XP.\n\n", enemy.name, enemy.xp[0]);
        player.base.xp[0] += enemy.xp[0];//someamount
        GAME_STATE = 1;
    }
}

void battle_check() {
    if (randombytes_uniform(40) == 0) {
        GAME_STATE = 3;

        gen_enem();
    }
}

void change_movement() {
    if (MOV_TIMER <= 0) {
        if (key[0]) {
            if (player.pos[1] > 1) {player.pos[1]--;}
            printf("Y; U: %d\n", player.pos[1]);
            battle_check();
            MOV_TIMER += 5;
        }
        if (key[1]) {
            if (player.pos[1] < (31 - (player.char_size/15) ))
                player.pos[1]++;
            printf("Y; D: %d\n", player.pos[1]);
            battle_check();
            MOV_TIMER += 5;
        }
        if (key[2]) {
            if (player.pos[0] > 15) {player.pos[0]--;}
            printf("X; L: %d\n", player.pos[0]-14);
            battle_check();
            MOV_TIMER += 5;
        }
        if (key[3]) {
            if (player.pos[0] < (43 - (player.char_size/15) ))
                player.pos[0]++;
            printf("X; R: %d\n", player.pos[0]-14);
            battle_check();
            MOV_TIMER += 5;
        }
        if (MOV_TIMER > 5) {MOV_TIMER = 5;}
    }
    else {
        MOV_TIMER--;
    }
}
