#include <stdio.h>
#include <stdlib.h>

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
    uint8_t encountered_seat_ids[0x3FF] = { 0 };
    while (fgets(buffer, 16, file)) {
        uint16_t seat_id = get_seat_id(buffer);
        encountered_seat_ids[seat_id] = 1;
        if (seat_id > max_seat_id) max_seat_id = seat_id;
    }

    for (uint16_t i = 1; i < max_seat_id; i++) {
        if ( !encountered_seat_ids[i] && encountered_seat_ids[i - 1] && encountered_seat_ids[i + 1]) printf("%d\n", i);
    }

}