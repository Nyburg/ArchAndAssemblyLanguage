/****************************************
 * C-ploration 9 for CS 271
 * 
 * [NAME] Nicholas Nyburg
 * [TERM] FALL 2025
 * 
 ****************************************/
#include "parser.h"
#include "error.h"

int main(int argc, const char *argv[])
{		

	if (argc != 2) {   
		exit_program(EXIT_INCORRECT_ARGUMENTS, argv[0]);
	}

	FILE *fp = fopen(argv[1], "r");
	if (!fp) {
		exit_program(EXIT_CANNOT_OPEN_FILE, argv[1]);
	}

	parse(fp);

	symtable_print_labels();

	fclose(fp);
	return 0;
			
}


