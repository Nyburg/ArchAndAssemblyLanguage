/****************************************
 * C-ploration 6 for CS 271
 * 
 * [NAME] Nicholas Nyburg
 * [TERM] FALL 2025
 * 
 ****************************************/
#include "parser.h"

int main(int argc, const char *argv[])
{		

	if (argc < 2) {
		fprintf(stderr, "Usage: %s <input-file>\n", argv[0]);
		return 1;
	}

	FILE *fp = fopen(argv[1], "r");
	if (!fp) {
		perror("fopen");
		return 1;
	}

	parse(fp);
	symtable_print_labels();
	fclose(fp);
	return 0;
			
}


