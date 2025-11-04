/****************************************
 * C-ploration 5 for CS 271
 * 
 * [NAME] Nicholas Nyburg
 * [TERM] FALL 2025
 * 
 ****************************************/
#include "parser.h"

/* Function: strip
 * -------------
 * remove whitespace and comments from a line
 *
 * s: the char* string to strip
 *
 * returns: the stripped char* string
 */
char *strip(char *s){	

	char s_new[MAX_LINE_LENGTH];
    int i = 0;

    for (char *s2 = s; *s2; s2++) {
        if (*s2 == '/' && *(s2 + 1) == '/') {
            break;
        }
        if (!isspace((unsigned char)*s2)) {
            s_new[i++] = *s2;
        }
    }

    s_new[i] = '\0';
    strcpy(s, s_new);	
	
    return s;	
}

/* Function: parse
 * -------------
 * iterate each line in the file and strip whitespace and comments. 
 *
 * file: pointer to FILE to parse
 *
 * returns: nothing
 */
void parse(FILE * file){
	
	char line[MAX_LINE_LENGTH];

    while (fgets(line, sizeof(line), file) != NULL) {
        strip(line);
        if (!*line) {
            continue;
        }
        char inst_type = ' ';
        if (is_Atype(line)){
            inst_type = 'A';
        } else if (is_label(line)) {
            inst_type = 'L';
        } else if (is_Ctype(line)) {
            inst_type = 'C';
        }
        printf("%c  %s\n", inst_type, line);
    }
	
}

bool is_Atype(const char *line) {
    return line && line[0] == '@';
}

bool is_label(const char *line) {
    if (!line || !*line) return false;
    size_t len = strlen(line);
    if (len < 2) return false;
    return line[0] == '(' && line[len - 1] == ')';
}

bool is_Ctype(const char *line) {
    if (!line || !*line) return false;
    if (is_Atype(line)) return false;
    if (is_label(line)) return false;
    return true;
}