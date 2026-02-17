#include <stdlib.h> /* realloc */
#include <string.h> /* strtok strtol */
#include <stdio.h> /* sscanf perror */
#include "c_struct.h"
#include "errors.h"
#include "error_handle.h"

static int isn_hexadecimal(const char *input) {
    char *endptr;
    strtol(input, &endptr, 16);
    return *endptr != '\0'; /* 0 for truly hex */
}

int str2hex_split(char *input, struct DATA_STRUCT *data_pack) {
    unsigned int HEX_INT;
    char *token = strtok(input, " ");
    while (token) {
        if(isn_hexadecimal(token)) goto RET_ERR;
        if (sscanf(token, "%X", &HEX_INT) == 1) {
            if(data_pack->code_capa<=data_pack->code_size) {
                data_pack->code = (unsigned char *) realloc(data_pack->code, sizeof(unsigned char) * (data_pack->code_capa+1));
                if (!data_pack->code) { perror("realloc"); return 1; }
                (data_pack->code_capa)++;
            }
            (data_pack->code)[data_pack->code_size] = (unsigned char) HEX_INT;
            (data_pack->code_size)++;
        } else {
            goto RET_ERR;
        }
        token = strtok(NULL, " ");
        if(!token) break;
    }
    return 0;

RET_ERR:
    zelemi_printerr_sys(INPUT_ERROR_HEADER, LOAD_HEX_INPUT_ERROR, token);
    return 1;
}