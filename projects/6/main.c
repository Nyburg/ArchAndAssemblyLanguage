/****************************************
 * Project 6 for CS 271
 * 
 * [NAME] Nicholas Nyburg
 * [TERM] FALL 2025
 * 
 ****************************************/
#include "parser.h"
#include "error.h"

#define MAX_INSTRUCTION_COUNT 30000

int main(int argc, const char *argv[])
{		
    if (argc != 2) {   
        exit_program(EXIT_INCORRECT_ARGUMENTS, argv[0]);
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        exit_program(EXIT_CANNOT_OPEN_FILE, argv[1]);
    }

    instruction *instructions = malloc(MAX_INSTRUCTION_COUNT * sizeof(instruction));
    if (instructions == NULL) {
        fclose(fp);
        exit_program(EXIT_TOO_MANY_INSTRUCTIONS, MAX_INSTRUCTION_COUNT);
    }

    int num_instructions = parse(fp, instructions);

    (void)num_instructions;

    //symtable_print_labels();

    free(instructions);
    fclose(fp);
    return 0;
}