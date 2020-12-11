#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* INPUT_FILE_PATH = "input_11.txt";

void print_grid(uint8_t* seat_layout, size_t ver_dim, size_t hor_dim) {
    for (size_t i = 0; i < ver_dim; i++) {
        for (size_t j = 0; j < hor_dim; j++) {
            printf("%c", seat_layout[i * hor_dim + j]);
        }
        printf("\n");
    }
}

bool update_grid(uint8_t* seat_layout_old, uint8_t* seat_layout_new, size_t ver_dim, size_t hor_dim) {
    bool updated = false;

    for (size_t i = 0; i < ver_dim; i++) {
        for (size_t j = 0; j < hor_dim; j++) {
            if (seat_layout_old[i * hor_dim + j] != '.') {
                uint8_t occupied_count = 0;
                if (i > 0) {
                    // Top left neighbour
                    if (j > 0 && seat_layout_old[(i - 1) * hor_dim + j - 1] == '#') occupied_count++;
                    // Top neighbour
                    if (seat_layout_old[(i - 1) * hor_dim + j] == '#') occupied_count++;
                    // Top right neighbour
                    if (j + 1 < hor_dim && seat_layout_old[(i - 1) * hor_dim + j + 1] == '#') occupied_count++;
                }

                // Left neighbour
                if (j > 0 && seat_layout_old[i * hor_dim + j - 1] == '#') occupied_count++;
                // Right neighbour
                if (j + 1 < hor_dim && seat_layout_old[i * hor_dim + j + 1] == '#') occupied_count++;

                if (i + 1 < ver_dim) {
                    // Bottom left neighbour
                    if (j > 0 && seat_layout_old[(i + 1) * hor_dim + j - 1] == '#') occupied_count++;
                    // Bottom neighbour
                    if (seat_layout_old[(i + 1) * hor_dim + j] == '#') occupied_count++;
                    // Bottom right neighbour
                    if (j + 1 < hor_dim && seat_layout_old[(i + 1) * hor_dim + j + 1] == '#') occupied_count++;
                }

                if (seat_layout_old[i * hor_dim + j] == 'L' && occupied_count == 0) {
                    seat_layout_new[i * hor_dim + j] = '#';
                    updated = true;
                } else if (seat_layout_old[i * hor_dim + j] == '#' && occupied_count >= 4) {
                    seat_layout_new[i * hor_dim + j] = 'L';
                    updated = true;
                }
            }
        }
    } 

    return updated;
}

uint64_t count_seats(uint8_t* seat_layout, size_t ver_dim, size_t hor_dim) {
    uint64_t count = 0;

    for (size_t i = 0; i < ver_dim; i++) {
        for (size_t j = 0; j < hor_dim; j++) {
            if (seat_layout[i * hor_dim + j] == '#') count++;
        }
    }
    return count;
}

int main() {
    FILE* file = fopen(INPUT_FILE_PATH, "r");
    char buffer[128] = { 0 };

    uint8_t* seat_layout_old = (uint8_t*) calloc(128 * 128, sizeof(uint8_t));
    uint8_t* seat_layout_updated = (uint8_t*) calloc(128 * 128, sizeof(uint8_t));
    uint8_t ver_dim = 0;
    uint8_t hor_dim = 0;
    while (fgets(buffer, 128, file)) {
        if (hor_dim == 0) hor_dim = strlen(buffer) - 1;
        memcpy(&seat_layout_old[ver_dim * hor_dim], buffer, hor_dim * sizeof(uint8_t));
        memcpy(&seat_layout_updated[ver_dim * hor_dim], buffer, hor_dim * sizeof(uint8_t));
        ver_dim++;
    }

    bool updated = false;
    do {
        updated = update_grid(seat_layout_old, seat_layout_updated, ver_dim, hor_dim);
        memcpy(seat_layout_old, seat_layout_updated, hor_dim * ver_dim * sizeof(uint8_t));
    } while (updated);

    printf("%llu\n", count_seats(seat_layout_updated, ver_dim, hor_dim));

    free(seat_layout_old);
    free(seat_layout_updated);
}