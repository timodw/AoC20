#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* INPUT_FILE_PATH = "input_13.txt";

int main() {
    FILE* file = fopen(INPUT_FILE_PATH, "r");
    char buffer[128] = { 0 };

    fgets(buffer, 128, file);
    uint64_t start_time = atoll(buffer);

    uint64_t bus_times[16] = { 0 };

    fgets(buffer, 128, file);
    char* buffer_end = buffer + strlen(buffer) - 1;
    char* str_i = buffer;
    size_t bus_count = 0;
    while (str_i >= buffer && str_i < buffer_end) {
        if (*str_i != 'x') {
            char* next_comma = strchr(str_i, ',');
            if (next_comma > buffer) *next_comma = '\0';
            uint64_t bus_id = atoll(str_i);
            bus_times[bus_count++] = bus_id;
            str_i = next_comma + 1;
        } else {
            str_i = strchr(str_i, ',') + 1;
        }
    }

    uint64_t closest_id = 0;
    uint64_t min_time_diff = ~0;
    for (size_t i = 0; i < bus_count; i++) {
        uint64_t next_time = bus_times[i] * (start_time / bus_times[i] + 1);
        if (next_time - start_time < min_time_diff) {
            closest_id = bus_times[i];
            min_time_diff = next_time - start_time;
        }
    }

    printf("%llu\n", closest_id * min_time_diff);
}