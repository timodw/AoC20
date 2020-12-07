#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Bag {
    char* adj;
    char* noun;
    uint64_t contains_shiny_gold;
    uint64_t hash;
} Bag;

typedef struct BagLinkedListNode {
    Bag bag;
    struct BagLinkedListNode* next;
} BagLinkedListNode;

typedef struct BagLinkedList {
    BagLinkedListNode* head;
    BagLinkedListNode* tail;
} BagLinkedList;

typedef struct TreeSetNode {
    BagLinkedList* val;
    struct TreeSetNode* l_child;
    struct TreeSetNode* r_child;
} TreeSetNode;

typedef struct TreeSet {
    TreeSetNode* root;
} TreeSet;

const char* INPUT_FILE_PATH = "test.txt";

void tree_set_insert(TreeSet* tree_set, BagLinkedList* bag_ll) {
    if (tree_set->root) {
        uint64_t hash = bag_ll->head->bag.hash;
        TreeSetNode* prev = tree_set->root;
        TreeSetNode* next = (hash <= tree_set->root->val->head->bag.hash) ? tree_set->root->l_child: tree_set->root->r_child;
        while (next) {
            prev = next;
            next = (hash <= next->val->head->bag.hash) ? next->l_child: next->r_child;
        }
        TreeSetNode* new_node = (TreeSetNode*) calloc(1, sizeof(TreeSetNode));
        new_node->val = bag_ll;
        if (hash < prev->val->head->bag.hash) {
            prev->l_child = new_node;
        } else if (hash > prev->val->head->bag.hash) {
            prev->r_child = new_node;
        }
        
    } else {
        TreeSetNode* root_node = (TreeSetNode*) calloc(1, sizeof(TreeSetNode));
        root_node->val = bag_ll; 
        tree_set->root = root_node;
    }
}

BagLinkedList* tree_get(TreeSet* tree_set, uint64_t hash) {
    TreeSetNode* node = tree_set->root;
    while (node->val->head->bag.hash != hash) {
        if (node->val->head->bag.hash < hash) {
            node = node->l_child;
        } else {
            node = node->r_child;
        }
    }
    return node->val;
}

bool tree_dfs_update(TreeSetNode* tree_node) {
    Bag bag = tree_node->val->head->bag;
    bool updated_l = false;
    bool updated_r = false;

    if (tree_node->l_child) updated_l = tree_dfs_update(tree_node->l_child);

    printf("%llu: %s - %s$\n", bag.hash, bag.adj, bag.noun);
    BagLinkedListNode* next = tree_node->val->head->next;
    bool updated = false;
    while (next) {
        printf("TEST %d\n", next);
        if (!bag.contains_shiny_gold && ((strstr(next->bag.adj, "shiny") && strstr(next->bag.noun, "gold")) ||
             next->bag.contains_shiny_gold)) {
                 bag.contains_shiny_gold = 1;
                 tree_node->val->head->bag = bag;
                 updated = true;
             }
        next = next->next;
    }
    
    if (tree_node->r_child) updated_r = tree_dfs_update(tree_node->r_child);

    return updated || updated_l || updated_r;
}

uint64_t tree_dfs_count(TreeSetNode* tree_node) {
    return 69;
}

bool parse_bag(char* descr, Bag* bag) {
    if (strstr(descr, "other")) return false;
    char* space = strchr(descr, ' ');
    *space = '\0';
    bag->adj = (char*) calloc(strlen(descr) + 1, sizeof(char));
    bag->noun = (char*) calloc(1, sizeof(char));
    strcpy(bag->adj, descr);
    strcpy(bag->noun, space + 1);

    uint64_t hash = 0;
    for (uint8_t i = 0; i < 4 && bag->adj[i] != '\0'; i++) {
        hash |= bag->adj[i] << (i * 8);
    }
    for (uint8_t i = 0; i < 4 && bag->noun[i] != '\0'; i++) {
        hash |= bag->adj[i] << (i * 8 + 32);
    }
    bag->hash = hash;
    return true;
}

void handle_line(char* line, TreeSet* bag_set) {
    char* end_of_first_bag = strstr(line, "bags") - 1;
    *end_of_first_bag = '\0';
    Bag bag = { 0 };
    parse_bag(line, &bag);
    BagLinkedListNode* ll_head = (BagLinkedListNode*) calloc(1, sizeof(BagLinkedListNode));
    ll_head->bag = bag;
    BagLinkedList* bag_list = (BagLinkedList*) calloc(1, sizeof(BagLinkedList));
    bag_list->head = ll_head;
    bag_list->tail = ll_head;
    char* next_space = strchr(end_of_first_bag + 1, ' ');
    next_space = strchr(next_space + 1, ' ');
    while (next_space) {
        next_space = strchr(next_space + 1, ' ');
        char* end_of_bag = strstr(next_space, "bag") - 1;
        *end_of_bag = '\0';
        Bag next_bag = { 0 };
        if (parse_bag(next_space + 1, &bag)) {
            BagLinkedListNode* next_bag_ll = (BagLinkedListNode*) calloc(1, sizeof(BagLinkedListNode));
            next_bag_ll->bag = next_bag;
            bag_list->tail->next = next_bag_ll;
            bag_list->tail = next_bag_ll;
        }
        next_space = strchr(end_of_bag + 1, ' ');
    }

    tree_set_insert(bag_set, bag_list);
}

int main() {
    FILE* file = fopen(INPUT_FILE_PATH, "r");
    char buffer[128] = { 0 };

    TreeSet bag_set = { 0 };    

    while (fgets(buffer, 128, file)) {
        handle_line(buffer, &bag_set);
    }

    bool changed = true;
    while (changed) {
        changed = tree_dfs_update(bag_set.root);
    }
    printf("%llu\n", tree_dfs_count(bag_set.root));
}