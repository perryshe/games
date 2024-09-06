#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

struct player {
    char hero_name[50];
    int player_gold;
    int player_health;
    int player_attack;
    int player_defence;
    int player_experiances;
    int player_level;
    int count;
};
struct goblin {
    int goblin_gold;
    int goblin_health;
    int goblin_attack;
    int goblin_defence;
    int goblin_experiances;
    int goblin_count;
};

void battle(int* flag, struct goblin* goblin, struct player* player, char* action);
int goblin_battle(int* flag, struct goblin* goblin, struct player* player, int size);
void helloHero(struct player* player, int size);
int seedrand(int timerand);
int menu(int* game);
int get_variant(int count);
void printmenu();
void gamekey();
void compaund(char* symbol);

int seedrand(int timerand) {
    srand(time(NULL));  // seed rng 0-2kkk
    timerand = rand();
    return timerand;
}
void print_hero(struct player* player) {
    printf("+-----------+------------+-------+\n");
    printf("|  Status   |   Count    | Modif |\n");
    printf("+-----------+------------+-------+\n");
    player->count = 6;
    printf("| Name      | %10s | ----- |\n", player->hero_name);
    printf("| Gold      | %10d | ----- |\n", player->player_gold);
    printf("| Health    | %10d | ----- |\n", player->player_health);
    printf("| Attack    | %10d | ----- |\n", player->player_attack);
    printf("| Defense   | %10d | ----- |\n", player->player_defence);
    printf("| Exp       | %10d | ----- |\n", player->player_experiances);
    printf("| Level     | %10d | ----- |\n", player->player_level);
    printf("+-----------+-----------+--------+\n");
}
void gamekey() {
    int h = 10;
    int w = 21;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            if ((y == 0 && x != -1) || (y == h - 1 && x != -1 && x != w)) {
                printf("-");
            } else if ((x == 0 && y != 0) || (x == w - 1 && x != 0 && y != h - 1 && y != 2 && y != 3 &&
                                              y != 4 && y != 5 && y != 6)) {
                printf("|");
            } else if ((x == w - 6 && y != h - 1 && y == 2) || (x == w - 8 && y != h - 1 && y == 3) ||
                       (x == w - 8 && y != h - 1 && y == 4) || (x == w - 9 && y != h - 1 && y == 5) ||
                       (x == w - 8 && y != h - 1 && y == 6)) {
                printf("|");
            } else if ((x == (w / 2) - 5 && y == 2)) {
                printf("w - up");
            } else if ((x == (w / 2) - 5 && y == 3)) {
                printf("s - down");
            } else if ((x == (w / 2) - 5 && y == 4)) {
                printf("a - left");
            } else if ((x == (w / 2) - 5 && y == 5)) {
                printf("d - right");
            } else if ((x == (w / 2) - 5 && y == 6)) {
                printf("m - menu");
            } else
                printf(" ");
        }
        printf("\n");
    }
}
void gameover() {
    int h = 10;
    int w = 21;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            if ((y == 0 && x != -1) || (y == h - 1 && x != -1 && x != w)) {
                printf("-");
            } else if ((x == 0 && y != 0) || (x == w - 1 && x != 0 && y != h - 1 && y != 4) ||
                       (x == w - 1 && y == 3)) {
                printf("|");
            } else if ((x == w - 11 && y != h - 1 && y == 4)) {
                printf("|");
            } else if ((x == (w / 2) - 4 && y == 4)) {
                printf("Game over!!");
            } else
                printf(" ");
        }
        printf("\n");
    }
}
void compaund(char* sp) {
    // printf("symbol1 = %c\n", *sp);
    while ((*sp != 'm') && (*sp != 'a') && (*sp != 'A') && (*sp != 'r') && (*sp != 'R')) {
        printf("Некорректный символ. Введите 'A'ttack or 'R'un:\n ");
        // printf("symbol2 = %c\n", *sp);
        *sp = getchar();
        while (getchar() != '\n')
            ;  // Очистка буфера ввода
    }
}
void battle(int* flag, struct goblin* goblin, struct player* player, char* action) {
    int timerand = 0;
    goblin->goblin_count = 0;
    goblin->goblin_experiances = 0;
    printf("\33[0d\33[2J");
    goblin->goblin_count = seedrand(timerand) % 3 + 1;
    printf("There are %d goblins in the squad\n\n", goblin->goblin_count);
    printf("You attaked.'A'ttack or 'R'un: ");
    while (getchar() != '\n')
        ;  // Очистка буфера ввода
    *action = getchar();
    while (getchar() != '\n')
        ;  // Очистка буфера ввода

    while ((*action != 'r') && (*flag != 2) && (goblin->goblin_count != 0)) {
        compaund(action);
        if ((*action == 'a' || *action == 'A')) {
            printf("There are still %d goblins in the squad\n", goblin->goblin_count);
            goblin->goblin_gold = seedrand(timerand) % 15;
            int goblin_exp = seedrand(timerand) % 5 + 1;
            for (int goblin_hp = seedrand(timerand) % 5 + 1; goblin_hp >= 0; goblin_hp--) {
                if (goblin_hp != 5) printf("You kick goblin(%d)\n", goblin_hp);
                if (goblin_hp == 0) {
                    printf("You defeat it.\n");
                    player->player_gold += goblin->goblin_gold;
                    player->player_experiances += goblin_exp;
                    goblin->goblin_experiances += goblin_exp;
                    printf("You found %d gold, and received %d experiances\n", goblin->goblin_gold,
                           goblin->goblin_experiances);
                    printf("You have %d gold total\n", player->player_gold);
                    goblin->goblin_count = goblin->goblin_count - 1;
                    continue;
                }
            }
        }
        if ((*action != 'r') && (*action != 'm') && (goblin->goblin_count != 0)) {
            // printf("Action = %s\n", action);
            printf("\nYour next action? Goblin wait.'A'ttack or 'R'un\n ");
            while (getchar() != '\n')
                ;  // Очистка буфера ввода}
        }
        if (*action == 'm') menu(flag);
    }
    if ((*action == 'r' || *action == 'R') && (goblin->goblin_count != 0))
        printf("You've decided to run away! You Earned %d gold\n ", player->player_gold);
    if (goblin->goblin_count == 0)
        printf("\n\nYou've kill ALL goblins! You Earned %d gold and %d exp\n ", player->player_gold,
               goblin->goblin_experiances);
    getchar();
    while (getchar() != '\n')
        ;  // Очистка буфера ввода}
}
int goblin_battle(int* flag, struct goblin* goblin, struct player* player, int size) {
    int game = 0;
    menu(&game);  // cont menu
    // printf("game goblin = %d\n", game);
    *flag = game;
    if (game == 1) {
        int i, key;
        int x = 10, y = 5;
        int ox, oy;
        char action = '0';
        int timerand = 0;
        char mass[10][21];
        int ax = 0, ay = 0;
        player->player_gold = 0;
        ax = seedrand(timerand) * 1.0 / RAND_MAX * 18 + 1;
        ay = seedrand(timerand) * 1.0 / RAND_MAX * 8 + 1;
        helloHero(player, size);  // inter hero name
        // printf("Name3: %s\n", player->hero_name);
        do {
            printf("\33[0d\33[2J");
            gamekey();  // point key
            printf("\n");
            sprintf(mass[0], "====================");

            for (i = 1; i < 9; i++) sprintf(mass[i], "#                  #");

            sprintf(mass[9], "====================");

            mass[y][x] = '@';
            mass[ay][ax] = 'o';

            for (i = 0; i < 10; i++) printf("%s\n", mass[i]);
            printf("\n");
            print_hero(player);
            // printf("Status do %d\n", *flag);
            ox = x;
            oy = y;
            key = getchar();
            if (key == 'w') y--;
            if (key == 's') y++;
            if (key == 'a') x--;
            if (key == 'd') x++;
            if (key == 'm') menu(&game);
            *flag = game;
            // printf("Game do %d\n", *flag);
            if (mass[y][x] == '#' || mass[y][x] == '=') {
                x = ox;
                y = oy;
            }
            if ((x == ax && y == ay)) {
                int timerand = 0;
                ax = seedrand(timerand) * 1.0 / RAND_MAX * 18 + 1;
                ay = seedrand(timerand) * 1.0 / RAND_MAX * 8 + 1;
                battle(&game, goblin, player, &action);
                *flag = game;
            }
            // printf("Game dodo %d\n", *flag);
        } while (*flag != 2);
    }
    // printf("Game dododo %d\n", *flag);
    return 0;
}
int get_variant(int count) {
    int variant;
    char s[100];
    scanf("%s", s);
    while (sscanf(s, "%d", &variant) != 1 || variant < 1 || variant > count) {
        printf("Incorrect input. Try again: ");
        scanf("%s", s);
    }
    // printf("Variant working\n");
    return variant;
}
void printmenu() {
    int h = 10;
    int w = 21;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            if ((y == 0 && x != -1) || (y == h - 1 && x != -1 && x != w)) {
                printf("-");
            } else if ((x == 0 && y != 0) ||
                       (x == w - 1 && x != 0 && y != h - 1 && y != 3 && y != 4 && y != 5) ||
                       (x == w - 1 && y == 3)) {
                printf("|");
            } else if ((x == w - 11 && y != h - 1 && y == 4) || (x == w - 7 && y != h - 1 && y == 5)) {
                printf("|");
            } else if ((x == (w / 2) - 5 && y == 4)) {
                printf("1. PlayGame");
            } else if ((x == (w / 2) - 5 && y == 5)) {
                printf("2. Exit");
            } else
                printf(" ");
        }
        printf("\n");
    }
}
void helloHero(struct player* player, int size) {
    int h = 10;
    int w = 21;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            if ((y == 0 && x != -1) || (y == h - 1 && x != -1 && x != w)) {
                printf("-");
            } else if ((x == 0 && y != 0) ||
                       (x == w - 1 && x != 0 && y != h - 1 && y != 3 && y != 4 && y != 5)) {
                printf("|");
            } else if ((x == w - 10 && y != h - 1 && y == 3) || (x == w - 12 && y != h - 1 && y == 4) ||
                       (x == w - 11 && y != h - 1 && y == 5)) {
                printf("|");
            } else if ((x == (w / 2) - 5 && y == 3)) {
                printf("Hello!!!!!");
            } else if ((x == (w / 2) - 6 && y == 4)) {
                printf("What is your");
            } else if ((x == (w / 2) - 5 && y == 5)) {
                printf("Name Hero?!");
            } else
                printf(" ");
        }
        printf("\n");
    }
    int len;
    char c;
    printf("\n");
    fgets(player->hero_name, size, stdin);
    len = strlen(player->hero_name);
    if (player->hero_name[len - 1] == '\n')
        player->hero_name[len - 1] = '\0';
    else {
        while ((c = getchar()) != '\n' && c != EOF)
            ;
    }

    // printf("Name2: %s\n", player->hero_name);
}
int menu(int* game) {
    printf("\33[0d\33[2J");
    printmenu();
    int variant = 0;
    variant = get_variant(2);
    *game = variant;
    getchar();
    printf("\33[0d\33[2J");
    // printf("game menu = %d\n", *game);
    return 0;
}
int main() {
    int flag = -2;
    struct player* player;
    player = (struct player*)malloc(sizeof(struct player));
    struct goblin* goblin;
    goblin = (struct goblin*)malloc(sizeof(struct goblin));
    while (flag != 2) {
        goblin_battle(&flag, goblin, player, sizeof(&(player)->hero_name));
    }
    printf("\33[0d\33[2J");
    gameover();
    free(player);
    player = NULL;
    free(goblin);
    goblin = NULL;
    return 0;
}