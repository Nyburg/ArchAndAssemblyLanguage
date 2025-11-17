/****************************************
 * C-ploration 6 for CS 271
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

/* Function: extract_label
 * -------------
 * expects a label declaration
 *
 *  Writes LABEL into label and returns it
 */
char *extract_label(const char *line, char *label) {
    const unsigned char *p = (const unsigned char *)line;

    // skip leading spaces
    while (*p && isspace(*p)) p++;

    // skip '(' if present
    if (*p == '(') p++;

    // copy until ')' or EOL
    const unsigned char *start = p;
    while (*p && *p != ')' && *p != '\n' && *p != '\r') p++;

    size_t len = (size_t)(p - start);
    if (len > (size_t)MAX_LABEL_LENGTH) len = (size_t)MAX_LABEL_LENGTH;

    memcpy(label, start, len);
    label[len] = '\0';
    return label;
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
            char lbl[MAX_LABEL_LENGTH + 1];
            extract_label(line, lbl);
            strcpy(line, lbl);
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