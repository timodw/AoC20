#include <stdio.h>

#include "hash_map.h"

hash_map* hm_create_new(size_t bucket_count) {
    hash_map* hm = (hash_map*) calloc(1, sizeof(hash_map));

    hm->bucket_heads = (hash_map_bucket**) calloc(bucket_count, sizeof(hash_map_bucket));
    hm->mask = bucket_count - 1;

    return hm;
}

void hm_insert_element(hash_map* hm, uint64_t key, uint64_t value) {
    hash_map_element hm_new_element = (hash_map_element) { key, value };

    size_t bucket_id = key & hm->mask;
    if (hm->bucket_heads[bucket_id]) {
        hash_map_bucket* cur_bucket = hm->bucket_heads[bucket_id];
        while (cur_bucket->content.key != key && cur_bucket->next) cur_bucket = cur_bucket->next;
        if (cur_bucket->content.key == key) {
            cur_bucket->content.value = value;
        } else {
            hash_map_bucket* bucket = (hash_map_bucket*) calloc(1, sizeof(hash_map_bucket));
            bucket->content = hm_new_element;
            cur_bucket->next = bucket;
            hm->size++;
        }
    } else {
        hash_map_bucket* bucket = (hash_map_bucket*) calloc(1, sizeof(hash_map_bucket));
        bucket->content = hm_new_element;
        hm->bucket_heads[bucket_id] = bucket;
        hm->size++;
    }
}

bool hm_get_element(hash_map* hm, uint64_t key, uint64_t* return_val) {
    size_t bucket_id = key & hm->mask;
    if (hm->bucket_heads[bucket_id]) {
        hash_map_bucket* cur_bucket = hm->bucket_heads[bucket_id];
        while (cur_bucket->content.key != key && cur_bucket->next) cur_bucket = cur_bucket->next;
        if (cur_bucket->content.key == key) {
            *return_val = cur_bucket->content.value;
            return true;
        }
    }
    return false;
}

bool hm_contains_element(hash_map* hm, uint64_t key) {
    size_t bucket_id = key & hm->mask;
    if (hm->bucket_heads[bucket_id]) {
        hash_map_bucket* cur_bucket = hm->bucket_heads[bucket_id];
        while (cur_bucket->content.key != key && cur_bucket->next) cur_bucket = cur_bucket->next;
        if (cur_bucket->content.key == key) {
            return true;
        }
    }
    return false;
}