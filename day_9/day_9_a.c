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

int main() {
    FILE* file = fopen(INPUT_FILE_PATH, "r");
    char buffer[128] = { 0 };

    size_t number_read = 0;
    uint64_t preamble[PREAMBLE_SIZE];
    while (fgets(buffer, 128, file)) {
        uint64_t val = atoll(buffer);
        if (number_read >= PREAMBLE_SIZE && !check_validness(val, preamble)) {
            printf("%llu\n", val);
            break;
        }
        preamble[number_read++ % PREAMBLE_SIZE] = val;
    }

}