/****************************************
 * C-ploration 8 for CS 271
 * 
 * [NAME] Nicholas Nyburg
 * [TERM] FALL 2025
 * 
 ****************************************/
#include "parser.h"
#include "error.h"

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

void add_predefined_symbols(void) {
    for (int i = 0; i < NUM_PREDEFINED_SYMBOLS; i++) {
        const predefined_symbol *ps = &predefined_symbols[i];
        symtable_insert((char *)ps->name, (hack_addr)ps->address);
    }
}

bool parse_A_instruction(const char *line, a_instruction *instr) {

    char *s = malloc(strlen(line));
    strcpy(s, line + 1);

    char *s_end = NULL;
    long result = strtol(s, &s_end, 10);

    if (s == s_end) {
        instr->data.label = malloc(strlen(s) + 1);
        strcpy(instr->data.label, s);
        instr->is_addr = false;
    }

    else if(*s_end != 0){
        return false;
    }

    else{
        instr->data.address = result;
        instr->is_addr = true;
    }

    return true;
}

void parse_C_instruction(char *line, c_instruction *instr)
{
    char *jump_str = NULL;
    char *dest_str = NULL;
    char *comp_str = NULL;

    /* First split on ';' into temp (dest=comp) and jump part */
    char *temp = strtok(line, ";");
    jump_str = strtok(NULL, ";");

    /* Now split temp on '=' into dest and comp */
    dest_str = strtok(temp, "=");
    comp_str = strtok(NULL, "=");

    /* If there was no '=', then temp is really just comp */
    if (comp_str == NULL) {
        comp_str = dest_str;
        dest_str = NULL;
    }

    int a_bit = 0;

    instr->jump = str_to_jumpid(jump_str);
    instr->dest = str_to_destid(dest_str);
    instr->comp = str_to_compid(comp_str, &a_bit);
    instr->a    = a_bit;
}

/* Function: parse
 * -------------
 * iterate each line in the file and strip whitespace and comments. 
 *
 * file: pointer to FILE to parse
 *
 * returns: nothing
 */
int parse(FILE * file, instruction *instructions){
	
	char line[MAX_LINE_LENGTH];
    hack_addr rom_addr = 0;
    unsigned int line_num = 0;        
    unsigned int instr_num = 0;     
    instruction instr;


    add_predefined_symbols();

    while (fgets(line, sizeof(line), file) != NULL) {
        line_num++;

        if (instr_num > MAX_INSTRUCTIONS) {
            exit_program(EXIT_TOO_MANY_INSTRUCTIONS,
                         MAX_INSTRUCTIONS + 1);
        }

        strip(line);
        if (!*line) {
            continue;
        }

        if (is_label(line)) {
            char lbl[MAX_LABEL_LENGTH + 1];
            extract_label(line, lbl);

            if (!isalpha((unsigned char)lbl[0])) {
                exit_program(EXIT_INVALID_LABEL, line_num, lbl);
            }

            if (symtable_find(lbl) != NULL) {
                exit_program(EXIT_SYMBOL_ALREADY_EXISTS,
                             line_num, lbl);
            }

            symtable_insert(lbl, rom_addr);
            continue;
        }

        if (is_Atype(line)) {
            rom_addr++;
            if (!parse_A_instruction(line, &instr.as.a)) {
                exit_program(EXIT_INVALID_A_INSTR, line_num, line);
            }
            instr.itype = INSTR_A;

            if (instr.as.a.is_addr) {
                printf("A: %d\n", instr.as.a.data.address);
            } else {
                printf("A: %s\n", instr.as.a.data.label);
            }

        } else if (is_Ctype(line)) {
            rom_addr++;

            char tmp_line[MAX_LINE_LENGTH];
            strcpy(tmp_line, line);

            parse_C_instruction(tmp_line, &instr.as.c);

            if (instr.as.c.dest == DEST_INVALID) {
                exit_program(EXIT_INVALID_C_DEST, line_num, line);
            }
            if (instr.as.c.comp == COMP_INVALID) {
                exit_program(EXIT_INVALID_C_COMP, line_num, line);
            }
            if (instr.as.c.jump == JMP_INVALID) {
                exit_program(EXIT_INVALID_C_JUMP, line_num, line);
            }

            instr.itype = INSTR_C;

            printf("C: d=%d, c=%d, j=%d\n",
                   instr.as.c.dest,
                   instr.as.c.comp,
                   instr.as.c.jump);
        }

        instructions[instr_num++] = instr;
    }

    return instr_num;
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