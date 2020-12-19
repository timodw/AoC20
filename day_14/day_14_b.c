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
    size_t float_indices[10] = { 0 };
    uint64_t* one_masks = (uint64_t*) calloc(1024, sizeof(uint64_t));
    uint64_t* zero_masks = (uint64_t*) calloc(1024, sizeof(uint64_t));
    size_t mask_count = 0;
    while (fgets(buffer, 128, file)) {
        size_t float_count = 0;
        if (strstr(buffer, "mask")) {
            mask_count = 0;
            one_mask = 0;
            zero_mask = 0;
            for (size_t i = 0; i < 36; i++) {
                char bit = buffer[i + 7];
                if (bit == '1') {
                    one_mask |= ((uint64_t) 1) << (35 - i);
                } else if (bit == 'X') {
                    float_indices[float_count++] = i;
                }
            }

            for (size_t i = 0; i < (uint64_t) 1 << float_count; i++) {
                uint64_t zm = zero_mask;
                uint64_t om = one_mask;
                for (size_t j = 0; j < float_count; j++) {
                    if (i & ((uint64_t) 1) << j) {
                        om |= ((uint64_t) 1) << (35 - float_indices[j]);
                    } else {
                        zm |= ((uint64_t) 1) << (35 - float_indices[j]);
                    }
                }

                zm = ~zm;
                zm &= 68719476735;

                zero_masks[i] = zm;
                one_masks[i] = om;
                mask_count++;
            } 
        } else {
            uint64_t address;
            uint64_t value;
            sscanf(buffer, "mem[%llu] = %llu\n", &address, &value);
            for (size_t i = 0; i < mask_count; i++) {
                uint64_t mod_address = address & zero_masks[i];
                mod_address |= one_masks[i];

                hm_insert_element(hm, mod_address, value);
            } 
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