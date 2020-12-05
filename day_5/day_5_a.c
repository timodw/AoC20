#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* INPUT_FILE_PATH = "input_5.txt";

uint16_t get_seat_id(const char* boarding_pass_id) {
    uint16_t seat_id = 0;
    for (uint16_t i = 0; i < 10; i++) {
        const char char_at_this_point = boarding_pass_id[i];
        if (char_at_this_point == 'B' || char_at_this_point == 'R') {
            seat_id |= 1 << (9 - i);
        }
    }
    return seat_id;
}

int main() {
    FILE* file = fopen(INPUT_FILE_PATH, "r");
    char buffer[16] = { 0 };

    uint16_t max_seat_id = 0;
    while (fgets(buffer, 16, file)) {
        uint16_t seat_id = get_seat_id(buffer);
        if (seat_id > max_seat_id) max_seat_id = seat_id;
    }

    printf("%d\n", max_seat_id);
}