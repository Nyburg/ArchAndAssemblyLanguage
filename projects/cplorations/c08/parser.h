/****************************************
 * C-ploration 6 for CS 271
 * 
 * [NAME] Nicholas Nyburg
 * [TERM] FALL 2025
 * 
 ****************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include "symtable.h"

#define MAX_LINE_LENGTH  200
#define MAX_LABEL_LENGTH (MAX_LINE_LENGTH - 2)

typedef int16_t opcode;

char *strip(char *s);
void parse(FILE * file);

bool is_Atype(const char *line);
bool is_label(const char *line);
bool is_Ctype(const char *line);

char *extract_label(const char *line, char *label);

typedef enum instr_type {
    INSTR_INVALID = -1,
    INSTR_A = 0,
    INSTR_C = 1
} instr_type;

typedef struct c_instruction {
    opcode a    : 1;
    opcode comp : 6;
    opcode dest : 3;
    opcode jump : 3;
} c_instruction;

typedef struct a_instruction {
    union {
        hack_addr address;
        char *label;
    } data;
    bool is_addr;
} a_instruction;

typedef struct instruction {
    union {
        a_instruction a;
        c_instruction c;
    } as;
    instr_type type;
} instruction;
