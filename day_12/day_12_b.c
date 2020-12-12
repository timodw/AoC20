#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* INPUT_FILE_PATH = "input_12.txt";

const int8_t cos_rot[4] = {1, 0, -1, 0};
const int8_t sin_rot[4] = {0, 1, 0, -1};

int main() {
    FILE* file = fopen(INPUT_FILE_PATH, "r");
    char buffer[128] = { 0 };

    int64_t x = 10;
    int64_t y = 1;

    int64_t ship_x = 0;
    int64_t ship_y = 0;

    while (fgets(buffer, 128, file)) {
        uint8_t instr = buffer[0];
        int64_t val = atoll(buffer + 1);
        int64_t x_old = x;
        int64_t y_old = y;
        switch (instr) {
            case 'N':
                y += val;
                break;
            case 'E':
                x += val;
                break;
            case 'S':
                y -= val;
                break;
            case 'W':
                x -= val;
                break;
            case 'L':
                x = x_old * cos_rot[val / 90] - y_old * sin_rot[val / 90];
                y = x_old * sin_rot[val / 90] + y_old * cos_rot[val / 90];
                break;
            case 'R':
                x = x_old * cos_rot[-val / 90 + 4] - y_old * sin_rot[-val / 90 + 4];
                y = x_old * sin_rot[-val / 90 + 4] + y_old * cos_rot[-val / 90 + 4];
                break;
            case 'F':
                ship_x += x * val;
                ship_y += y * val;
                break;
        };
    }

    printf("%llu\n", llabs(ship_x) + llabs(ship_y));
}