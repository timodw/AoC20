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

bool check_ray(uint8_t* seat_layout, size_t ver_dim, size_t hor_dim, int8_t hor_delta, int8_t ver_delta, size_t hor_co, size_t ver_co) {
    hor_co += hor_delta;
    ver_co += ver_delta;
    while (hor_co < hor_dim && ver_co < ver_dim) {
        if (seat_layout[ver_co * hor_dim + hor_co] == '#') return true;
        if (seat_layout[ver_co * hor_dim + hor_co] == 'L') return false;
        hor_co += hor_delta;
        ver_co += ver_delta;
    }
    return false;
}

bool update_grid(uint8_t* seat_layout_old, uint8_t* seat_layout_new, size_t ver_dim, size_t hor_dim) {
    bool updated = false;

    for (size_t i = 0; i < ver_dim; i++) {
        for (size_t j = 0; j < hor_dim; j++) {
            if (seat_layout_old[i * hor_dim + j] != '.') {
                uint8_t occupied_count = 0;
                // Top left ray
                if (check_ray(seat_layout_old, ver_dim, hor_dim, -1, -1, j, i)) occupied_count++;
                // Top ray
                if (check_ray(seat_layout_old, ver_dim, hor_dim, 0, -1, j, i)) occupied_count++;
                // Top right ray
                if (check_ray(seat_layout_old, ver_dim, hor_dim, 1, -1, j, i)) occupied_count++;

                // Left ray
                if (check_ray(seat_layout_old, ver_dim, hor_dim, -1, 0, j, i)) occupied_count++;
                // Right ray
                if (check_ray(seat_layout_old, ver_dim, hor_dim, 1, 0, j, i)) occupied_count++;

                // Bottom left ray
                if (check_ray(seat_layout_old, ver_dim, hor_dim, -1, 1, j, i)) occupied_count++;
                // Bottom ray
                if (check_ray(seat_layout_old, ver_dim, hor_dim, 0, 1, j, i)) occupied_count++;
                // Bottom right ray
                if (check_ray(seat_layout_old, ver_dim, hor_dim, 1, 1, j, i)) occupied_count++;

                if (seat_layout_old[i * hor_dim + j] == 'L' && occupied_count == 0) {
                    seat_layout_new[i * hor_dim + j] = '#';
                    updated = true;
                } else if (seat_layout_old[i * hor_dim + j] == '#' && occupied_count >= 5) {
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