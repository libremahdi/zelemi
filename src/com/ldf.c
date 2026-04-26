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

#include <stdio.h> /* fopen printf */
#include <string.h> /* strcspn strstr*/
#include "c_struct.h"
#include "errors.h"
#include "zelemi_err.h"
#include "colors.h"
#include "config.h"

int zelemi_send(const string *, struct DATA_STRUCT *);
int ignore_commands(const string *);

#define BUFFER_SIZE 256

int zelemi_command_lod(int argc, const char *opt, struct DATA_STRUCT *data_pack) {
    if(!opt)  {zelemi_printerr_sys(FILE_ERROR_HEADER, TAKES_ONE_ARG_ERROR, "LDF", "LDF"); return -3;} 

    FILE *load_fp=fopen(opt, "r");
    if(!load_fp) {zelemi_printerr_sys(FILE_ERROR_HEADER, FILE_ERROR, opt); return -3;}

    string *p_input = pstr_with_cap(BUFFER_SIZE); /* for pstr_gets_set */

    for(;;) {
        if (pstr_gets_set(p_input, load_fp)) {
            if (feof(load_fp)!=0) break;
            zelemi_printerr_sys(INPUT_ERROR_HEADER, INPUT_ERROR);
            goto RET_3;
        }
        {
            int i=pstr_contains(p_input, ";");
            if(i==0) continue;
            pstr_sept(p_input, 0, i);
        }
        pstr_trim(p_input);
        if(pstr_len(p_input)==0) continue;

        #ifdef POINT_SUPPORT
        if(pstr_at(p_input, 0)=='.') {
            printf("%s\n", pstr_peek(p_input));
            continue;
        }
        #endif

        /**************************/
        {
            string *command = pstr_isplit(p_input, 1);
            if(ignore_commands(command)) {
                printf(GREEN"; %s\n"RESET, pstr_peek(p_input));
                continue; 
            }
            pstr_free(command);
        }

        /**************************/

        printf("%s\n", pstr_peek(p_input));
        if (zelemi_send(p_input, data_pack)) goto RET_3;
    }
    fclose(load_fp);
    pstr_free(p_input);
    return 0;
RET_3:
    pstr_free(p_input);
    fclose(load_fp);
    return -3;
}