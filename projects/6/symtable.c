/****************************************
 * C-ploration 9 for CS 271
 * 
 * [NAME] Nicholas Nyburg
 * [TERM] FALL 2025
 * 
 ****************************************/
#include "symtable.h"

Symbol *hashArray[SYMBOL_TABLE_SIZE];

int hash(char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = (unsigned char)*str++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return (int)(hash % SYMBOL_TABLE_SIZE);
}

void symtable_insert(char *key, hack_addr addr) {
    Symbol *item = malloc(sizeof(Symbol));
    if (!item) {
        fprintf(stderr, "symtable_insert: malloc failed\n");
        exit(1);
    }

    item->name = strdup(key);
    item->addr = addr;

    int index = hash(key);

    while (hashArray[index] != NULL) {
        if (strcmp(hashArray[index]->name, key) == 0) {
            hashArray[index]->addr = addr;
            free(item->name);
            free(item);
            return;
        }
        index++;

        if (index >= SYMBOL_TABLE_SIZE) {
            index = 0;
        }
    }

    hashArray[index] = item;
}

Symbol *symtable_find(char *key) {
    int index = hash(key);

    while (hashArray[index] != NULL) {
        if (strcmp(hashArray[index]->name, key) == 0) {
            return hashArray[index];
        }

        index++;
        if (index >= SYMBOL_TABLE_SIZE) {
            index = 0;
        }
    }

    return NULL;
}

void symtable_display_table() {
    for (int i = 0; i < SYMBOL_TABLE_SIZE; i++) {
        if (hashArray[i] != NULL) {
            printf("Index %d: {%s,%d}\n",
                   i, hashArray[i]->name, hashArray[i]->addr);
        } else {
            printf("Index %d: ~~\n", i);
        }
    }
}

void symtable_print_labels() {
    for (int i = 0; i < SYMBOL_TABLE_SIZE; i++) {
        if (hashArray[i] != NULL) {
            printf("{%s,%d}\n", hashArray[i]->name, hashArray[i]->addr);
        }
    }
}