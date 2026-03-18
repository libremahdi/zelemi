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
#include "zelemi_err.h"
#include "config.h"
#include "header.h"

static int zelemi_isn_hex(const string *, unsigned);

int zelemi_send(const string const *p_input, struct DATA_STRUCT *data_pack) {
    unsigned int HEX_INT, i=1;
    
    string *token = pstr_isplit(p_input, i);
    while (token!=NULL) {
        #ifdef POINT_SUPPORT /* Makes the structure dirty!! ( Like MS-DOS ) */
        if(pstr_at(token, 0)=='.') { /* Remove all dots from First of token */
            pstr_trim_ch(token, '.');
        }
        #endif

        if (zelemi_isn_hex(token, data_pack->i_number_base)) goto RET_ERR;
        if (sscanf(pstr_peek(token), data_pack->number_base, &HEX_INT) != EOF) {
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
        pstr_free(token);
        token = pstr_isplit(p_input, ++i);
    }
     return 0;

RET_ERR:
    zelemi_printerr_sys(INPUT_ERROR_HEADER, LOAD_BASE_INPUT_ERROR, pstr_peek(token));
    return 1;
}

static int zelemi_isn_hex(const string const *input, unsigned i_number_base) {
    char *endptr;
    strtol(pstr_peek(input), &endptr, i_number_base);
    return *endptr != '\0'; /* 0 for truly hex */
}