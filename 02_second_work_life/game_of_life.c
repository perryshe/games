#include <stdio.h>
#include <unistd.h>

int matrix_init(char *filename, int h, int w, int matrix[h][w]);
void draw_field(int h, int w, int matrix[h][w]);
void create_new_gen(int h, int w, int arch_field[h][w], int field[h][w]);
void slee(int s);

int main(int argc, char *argv[]) {
    int error = 0;
    int height = 25, width = 80, speed;
    int arch_field[height][width], arch_field2[height][width], field[height][width];
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            arch_field2[i][j] = 0;
        }
    }

    if (argc != 2) {
        printf("¯|_(ツ)_|¯  Вы неверно указали название файла!\n");
        error = 1;
    } else if (matrix_init(argv[1], height, width, arch_field) == 0) {
        printf("(*・‿・) Пожалуйста выберите скорость игры (от 1 до 5)\n");
        if (scanf("%d", &speed) != 1 || speed < 1 || speed > 5) {
            error = 1;
        } else {
            while (1) {
                printf("\033[2J\033[H");
                draw_field(height, width, arch_field);
                slee(speed);
                create_new_gen(height, width, arch_field, field);
                int coincidences = 0, coincidences2 = 0;
                for (int i = 0; i < height; i++) {
                    for (int j = 0; j < width; j++) {
                        if (arch_field[i][j] == field[i][j]) {
                            coincidences++;
                        }
                        if (arch_field2[i][j] == field[i][j]) {
                            coincidences2++;
                        }
                    }
                }
                if (coincidences == height * width || coincidences2 == height * width) {
                    printf("☺︎ ИГРА ОКОНЧЕНА! ☺︎\n");
                    break;
                }
                for (int i = 0; i < height; i++) {
                    for (int j = 0; j < width; j++) {
                        arch_field2[i][j] = arch_field[i][j];
                        arch_field[i][j] = field[i][j];
                    }
                }
            }
        }
    } else {
        error = 1;
    }

    return error;
}

int matrix_init(char *filename, int h, int w, int matrix[h][w]) {
    int error = 0;
    FILE *file;
    file = fopen(filename, "r");
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (fscanf(file, "%d", &matrix[i][j]) != 1 || matrix[i][j] < 0 || matrix[i][j] > 1) {
                printf("¯|_(ツ)_|¯ Ошибка! Проверьте корректность файла.\n");
                error = 1;
                break;
            }
        }
        if (error == 1) {
            break;
        }
    }
    fclose(file);
    return error;
}

void draw_field(int h, int w, int matrix[h][w]) {
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (matrix[i][j] == 0) {
                printf(".");
            } else {
                printf("0");
            }
        }
        printf("\n");
    }
}

void create_new_gen(int h, int w, int arch_field[h][w], int field[h][w]) {
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            int count = 0;
            for (int x = -1; x <= 1; x++) {
                for (int y = -1; y <= 1; y++) {
                    if (x == 0 && y == 0) continue;
                    int ni = (i + x + h) % h;
                    int nj = (j + y + w) % w;
                    if (arch_field[ni][nj] == 1) {
                        count++;
                    }
                }
            }
            if (arch_field[i][j] == 0) {
                if (count == 3) {
                    field[i][j] = 1;
                } else {
                    field[i][j] = 0;
                }
            } else {
                if (count == 2 || count == 3) {
                    field[i][j] = 1;
                } else {
                    field[i][j] = 0;
                }
            }
        }
    }
}

void slee(int s) {
    if (s == 5) {
        usleep(10000);
    } else if (s == 4) {
        usleep(70000);
    } else if (s == 3) {
        usleep(200000);
    } else if (s == 2) {
        usleep(500000);
    } else {
        usleep(1000000);
    }
}