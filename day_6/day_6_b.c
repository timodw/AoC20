#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* INPUT_FILE_PATH = "input_6.txt";

uint32_t handle_line(const char* line) {
    uint32_t answers = 0;
    for (;*line != '\n' && *line;line++) {
        answers = answers | (1 << (*line - 'a'));
    }
    return answers;
}

int main() {
    FILE* file = fopen(INPUT_FILE_PATH, "r");
    char buffer[128] = { 0 };

    uint64_t sum = 0;
    uint32_t encountered_symbols = 0x3FFFFFF;
    while (fgets(buffer, 128, file)) {
        if (buffer[0] == '\n') {
            sum += __builtin_popcount(encountered_symbols);
            encountered_symbols = 0x3FFFFFF;
        } else {
            encountered_symbols &= handle_line(buffer);
        }
    }
    sum += __builtin_popcount(encountered_symbols);

    printf("%llu\n", sum);
}