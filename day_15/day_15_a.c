#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash_map.h"

static const size_t BUCKET_COUNT = 1024;
static const size_t INPUT_LENGTH = 7;
static const uint64_t INPUT_SEQUENCE[INPUT_LENGTH] = { 9, 19, 1, 6, 0, 5, 4 };
static const size_t NUMBER_ID = 2020;

int main() {
   hash_map* last_turn_hm = hm_create_new(BUCKET_COUNT); 
   hash_map* prev_hm = hm_create_new(BUCKET_COUNT); 

    for (size_t i = 0; i < INPUT_LENGTH; i++) {
        hm_insert_element(last_turn_hm, INPUT_SEQUENCE[i], i + 1);
        hm_insert_element(prev_hm, INPUT_SEQUENCE[i], 0);
    }

    uint64_t prev_number = INPUT_SEQUENCE[INPUT_LENGTH - 1];
    for (size_t i = INPUT_LENGTH; i < NUMBER_ID; i++) {
       uint64_t prev;
       hm_get_element(prev_hm, prev_number, &prev); 
       uint64_t last_turn;
       hm_get_element(last_turn_hm, prev_number, &last_turn);
       if (prev == 0) {
           uint64_t last_zero;
           hm_get_element(last_turn_hm, 0, &last_zero);
           hm_insert_element(last_turn_hm, 0, i + 1);
           hm_insert_element(prev_hm, 0, last_zero);
           prev_number = 0;
       } else {
            uint64_t diff = last_turn - prev;
            uint64_t diff_prev;
            if (hm_get_element(prev_hm, diff, &diff_prev)) {
                uint64_t diff_last_turn;
                hm_get_element(last_turn_hm, diff, &diff_last_turn);
                hm_insert_element(prev_hm, diff, diff_last_turn);
            } else {
                hm_insert_element(prev_hm, diff, 0);
            }
            hm_insert_element(last_turn_hm, diff, i + 1);
            prev_number = diff;
       }
    }

    printf("%llu\n", prev_number);
    return 0;
}