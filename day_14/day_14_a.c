#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash_map.h"

const size_t BUCKET_COUNT = 1024;

const char* INPUT_FILE_PATH = "input_14.txt";

int main() {
    FILE* file = fopen(INPUT_FILE_PATH, "r");
    char buffer[128] = { 0 };

    uint64_t one_mask = 0;
    uint64_t zero_mask = 0;
    hash_map* hm = hm_create_new(BUCKET_COUNT);
    while (fgets(buffer, 128, file)) {
        if (strstr(buffer, "mask")) {
            one_mask = 0;
            zero_mask = 0;
            for (size_t i = 0; i < 36; i++) {
                char bit = buffer[i + 7];
                if (bit == '1') {
                    one_mask |= ((uint64_t) 1) << (35 - i);
                } else if (bit == '0') {
                    zero_mask |= ((uint64_t) 1) << (35 - i);
                }
            }
            zero_mask = ~zero_mask;
            zero_mask &= 68719476735;
        } else {
            uint64_t address;
            uint64_t value;
            sscanf(buffer, "mem[%llu] = %llu\n", &address, &value);
            value &= zero_mask;
            value |= one_mask;

            hm_insert_element(hm, address, value);
        }
    }

    uint64_t sum = 0;
    for (size_t i = 0; i < BUCKET_COUNT; i++) {
        hash_map_bucket* bucket = hm->bucket_heads[i];
        while (bucket) {
            sum += bucket->content.value;
            bucket = bucket->next;
        }
    }

    printf("%llu\n", sum);
}