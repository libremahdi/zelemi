/* BSD 3-Clause License
 * 
 * Copyright (c) 2026, Mahdi Hosseini Asaad

 * Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:

 1.Redistributions of source code must retain the above copyright notice, this
    list of conditions and the following disclaimer.

 2.Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

 3.Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
   FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
   OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

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

int zelemi_run_hex(char *input, struct DATA_STRUCT *data_pack) {
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