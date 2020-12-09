#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* INPUT_FILE_PATH = "input_9.txt";
const uint8_t PREAMBLE_SIZE = 25;

bool check_validness(uint64_t val, uint64_t* preamble) {
    for (size_t i = 0; i < PREAMBLE_SIZE - 1; i++) {
        for (size_t j = i; j < PREAMBLE_SIZE; j++) {
            if (preamble[i] + preamble[j] == val) return true;
        }
    }
    return false;
}

void get_min_max_range(uint64_t val, uint64_t* list, uint64_t number_read, uint64_t* min, uint64_t* max) {
    for (size_t window_size = 2; window_size <= number_read; window_size++) {
        for (size_t start = 0; start <= number_read - window_size + 1; start++) {
            uint64_t sum = 0;
            *min = ~0;
            *max = 0;
            for (size_t i = start; i < window_size; i++) {
               sum += list[i];
               if (list[i] < *min) {
                   *min = list[i];
               } else if (list[i] > *max) {
                   *max = list[i];
               }
            }
            if (sum == val) return;
        }
    }
}

int main() {
    FILE* file = fopen(INPUT_FILE_PATH, "r");
    char buffer[128] = { 0 };

    size_t number_read = 0;
    uint64_t preamble[PREAMBLE_SIZE];
    uint64_t list[2048];
    uint64_t wrong_val;
    while (fgets(buffer, 128, file)) {
        uint64_t val = atoll(buffer);
        if (number_read >= PREAMBLE_SIZE && !check_validness(val, preamble)) {
            wrong_val = val;
        }
        list[number_read] = val;
        preamble[number_read % PREAMBLE_SIZE] = val;
        number_read++;
    }
    uint64_t min;
    uint64_t max;
    get_min_max_range(wrong_val, list, number_read, &min, &max);
    printf("%llu - %llu - %llu\n", min + max, min, max);

}