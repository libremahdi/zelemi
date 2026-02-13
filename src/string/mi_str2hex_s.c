#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "colors.h"

static int is_hexadecimal(const char *input) {
    char *endptr;
    strtol(input, &endptr, 16);
    return *endptr != '\0'; /* 0 for truly hex */
}

int str2hex_split(char *input, unsigned char **code, unsigned int *CodeSize) {
    unsigned int HEX_INT;
    char *token = strtok(input, " ");
    
    while (token) {
        if(is_hexadecimal(token)) goto RET_ERR;
        if (sscanf(token, "%X", &HEX_INT) == 1) {
            *code = (unsigned char *) realloc(*code, sizeof(unsigned char) * (*CodeSize + 1));
            if (!*code) { perror("realloc"); exit(1); }
            (*code)[*CodeSize] = (unsigned char) HEX_INT;
            (*CodeSize)++;
        } else {
            goto RET_ERR;
        }
        token = strtok(NULL, " ");
    }
    return 0;

RET_ERR:
    printf(YELLOW"InputError:"RESET" You are only allowed to enter hexadecimal numbers or 'RUN' and 'END'.\n");
    return 1;
}