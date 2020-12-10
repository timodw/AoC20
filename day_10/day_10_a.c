#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* INPUT_FILE_PATH = "input_10.txt";

int cmp(const void* a, const void* b) {
    return (int) (*((uint64_t*) a) - *((uint64_t*) b));
}

int main() {
    FILE* file = fopen(INPUT_FILE_PATH, "r");
    char buffer[128] = { 0 };

    size_t number_read = 0;
    uint64_t adapter_jolts[256] = { 0 };
    while (fgets(buffer, 128, file)) {
        adapter_jolts[number_read++] = atoll(buffer);
    }
    qsort(adapter_jolts, number_read + 1, sizeof(uint64_t), cmp);

    uint64_t diff_count[2] = { 0 };
    for (size_t i = 1; i < number_read + 1; i++) {
        if (adapter_jolts[i] - adapter_jolts[i-1] == 1) {
            diff_count[0]++;
        } else {
            diff_count[1]++;
        }
    }

    printf("%llu\n", diff_count[0] * (diff_count[1] + 1));
}