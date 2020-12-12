#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* INPUT_FILE_PATH = "input_12.txt";

const int8_t x_dir_vec[4] = {1, 0, -1, 0};
const int8_t y_dir_vec[4] = {0, -1, 0, 1};

int main() {
    FILE* file = fopen(INPUT_FILE_PATH, "r");
    char buffer[128] = { 0 };

    int64_t x = 0;
    int64_t y = 0;

    uint8_t direction = 0;
    while (fgets(buffer, 128, file)) {
        uint8_t instr = buffer[0];
        uint64_t val = atoll(buffer + 1);
        switch (instr) {
            case 'N':
                y -= val;
                break;
            case 'E':
                x += val;
                break;
            case 'S':
                y += val;
                break;
            case 'W':
                x -= val;
                break;
            case 'L':
                direction = (direction + val / 90) % 4;
                break;
            case 'R':
                direction = (direction - val / 90) % 4;
                break;
            case 'F':
                x += x_dir_vec[direction] * val;
                y += y_dir_vec[direction] * val;
                break;
        };
    }

    printf("%llu\n", llabs(x) + llabs(y));
}