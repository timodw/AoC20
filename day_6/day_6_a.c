#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* INPUT_FILE_PATH = "input_6.txt";

void handle_line(const char* line, uint32_t* encountered_symbols) {
    for (;*line != '\n' && *line;line++) {
        *encountered_symbols = *encountered_symbols | (1 << (*line - 'a'));
    }
}

int main() {
    FILE* file = fopen(INPUT_FILE_PATH, "r");
    char buffer[128] = { 0 };

    uint64_t sum = 0;
    uint32_t encountered_symbols = 0;
    while (fgets(buffer, 128, file)) {
        if (buffer[0] == '\n') {
            sum += __builtin_popcount(encountered_symbols);
            encountered_symbols = 0;
        } else {
            handle_line(buffer, &encountered_symbols);
        }
    }
    sum += __builtin_popcount(encountered_symbols);

    printf("%llu\n", sum);
}