#pragma once

#include <stdlib.h>
#include <stdbool.h>

typedef struct hash_map_element {
    uint64_t key;
    uint64_t value;
} hash_map_element;

typedef struct hash_map_bucket {
    struct hash_map_element content;
    struct hash_map_bucket* next;
} hash_map_bucket;

typedef struct hash_map {
    struct hash_map_bucket** bucket_heads;
    size_t size;
    uint64_t mask;
} hash_map;

hash_map* hm_create_new(size_t bucket_count);

void hm_insert_element(hash_map* hm, uint64_t key, uint64_t value);

bool hm_get_element(hash_map* hm, uint64_t key, uint64_t* return_val);

bool hm_contains_element(hash_map* hm, uint64_t key);