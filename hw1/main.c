#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TOKEN_LEN 100

int is_keyword(const char *str) {
    return strcmp(str, "int") == 0 ||
           strcmp(str, "main") == 0 ||
           strcmp(str, "if") == 0 ||
           strcmp(str, "else") == 0 ||
           strcmp(str, "while") == 0;
}

void print_token(const char *str) {
    if (strcmp(str, "int") == 0) printf("%s: TYPE_TOKEN\n", str);
    else if (strcmp(str, "main") == 0) printf("%s: MAIN_TOKEN\n", str);
    else if (strcmp(str, "if") == 0) printf("%s: IF_TOKEN\n", str);
    else if (strcmp(str, "else") == 0) printf("%s: ELSE_TOKEN\n", str);
    else if (strcmp(str, "while") == 0) printf("%s: WHILE_TOKEN\n", str);
    else printf("%s: ID_TOKEN\n", str);
}

int main() {
    FILE *file = fopen("test.c", "r");
    if (!file) {
        printf("Cannot open file.\n");
        return 1;
    }

    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == ' ' || ch == '\t' || ch == '\n') continue;
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_') {
            char buffer[MAX_TOKEN_LEN] = {0};
            int len = 0;
            buffer[len++] = ch;
            while ((ch = fgetc(file)) != EOF &&
                   ((ch >= 'a' && ch <= 'z') || 
                    (ch >= 'A' && ch <= 'Z') || 
                    (ch >= '0' && ch <= '9') || 
                    ch == '_')) {
                if (len < MAX_TOKEN_LEN - 1) {
                    buffer[len++] = ch;
                }
            }
            buffer[len] = '\0';
            print_token(buffer);
            if (ch != EOF) ungetc(ch, file);
        }
        else if (ch >= '0' && ch <= '9') {
            char buffer[MAX_TOKEN_LEN] = {0};
            int len = 0;
            buffer[len++] = ch;
            while ((ch = fgetc(file)) != EOF && (ch >= '0' && ch <= '9')) {
                if (len < MAX_TOKEN_LEN - 1) {
                    buffer[len++] = ch;
                }
            }
            buffer[len] = '\0';
            printf("%s: LITERAL_TOKEN\n", buffer);
            if (ch != EOF) ungetc(ch, file);
        }
        else {
            char next = fgetc(file);
            switch (ch) {
                case '=':
                    if (next == '=') printf("==: EQUAL_TOKEN\n");
                    else {
                        printf("=: ASSIGN_TOKEN\n");
                        if (next != EOF) ungetc(next, file);
                    }
                    break;
                case '>':
                    if (next == '=') printf(">=: GREATEREQUAL_TOKEN\n");
                    else {
                        printf(">: GREATER_TOKEN\n");
                        if (next != EOF) ungetc(next, file);
                    }
                    break;
                case '<':
                    if (next == '=') printf("<=: LESSEQUAL_TOKEN\n");
                    else {
                        printf("<: LESS_TOKEN\n");
                        if (next != EOF) ungetc(next, file);
                    }
                    break;
                case '+':
                    printf("+: PLUS_TOKEN\n");
                    if (next != EOF) ungetc(next, file);
                    break;
                case '-':
                    printf("-: MINUS_TOKEN\n");
                    if (next != EOF) ungetc(next, file);
                    break;
                case '(':
                    printf("(: LEFTPAREN_TOKEN\n");
                    if (next != EOF) ungetc(next, file);
                    break;
                case ')':
                    printf("): REFTPAREN_TOKEN\n");
                    if (next != EOF) ungetc(next, file);
                    break;
                case '{':
                    printf("{: LEFTBRACE_TOKEN\n");
                    if (next != EOF) ungetc(next, file);
                    break;
                case '}':
                    printf("}: REFTBRACE_TOKEN\n");
                    if (next != EOF) ungetc(next, file);
                    break;
                case ';':
                    printf(";: SEMICOLON_TOKEN\n");
                    if (next != EOF) ungetc(next, file);
                    break;
                default:
                    if (next != EOF) ungetc(next, file);
                    break;
            }
        }
    }

    fclose(file);
    return 0;
}
