/****************************************
 * Symbol table for CS 271 Assembler
 ****************************************/
#ifndef SYMTABLE_H
#define SYMTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define SYMBOL_TABLE_SIZE 1000

// bind int16_t to hack_addr
typedef int16_t hack_addr;

typedef struct Symbol {
    char *name;
    hack_addr addr;
} Symbol;

// hash and symtable API
int hash(char *str);
struct Symbol *symtable_find(char *key);
void symtable_insert(char *key, hack_addr addr);
void symtable_display_table();
void symtable_print_labels();

#endif