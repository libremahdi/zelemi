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

int trim_start(char * const);
int trim_end(char * const);
int zelemi_send(char *, struct DATA_STRUCT *);
int ignore_commands(char *);

int zelemi_command_lod(int argc, char *opt, struct DATA_STRUCT *data_pack) {
    FILE *load_fp=NULL;
    char input[256];
    // char flag; /* a Byte for flag */
    unsigned input_size;

    if(!opt)  {zelemi_printerr_sys(FILE_ERROR_HEADER, TAKES_ONE_ARG_ERROR, "LDF"); return -3;} 
    
    load_fp=fopen(opt, "r");
    if(!load_fp) {zelemi_printerr_sys(FILE_ERROR_HEADER, FILE_ERROR, opt); return -3;}

    while(1) {
        if((fgets(input, sizeof(input), load_fp)==NULL)&&(!feof(load_fp))) {
            zelemi_printerr_sys(INPUT_ERROR_HEADER, INPUT_ERROR);
            goto RET_3;
        } else if (feof(load_fp)) break;
        
        if(strstr(input, ";")) *strstr(input, ";")='\0'; /* replaces comment characters with \0 to ignore comments anywhere in the line. */
        input[strcspn(input, "\n")]=0; /* Remove NL */
        trim_start(input); trim_end(input);
        if(input[0]=='\0') continue; /* ignore blank line */
        
        #ifdef POINT_SUPPORT
        if(input[0]=='.') continue; /* ignore dot-commands */
        #endif

        input_size = strlen(input);
        char *command = strtok(input, " ");
    
        if(ignore_commands(command)) {
            input[strcspn(input, "\0")]=' '; /* Remove NUL */
            printf("; %s\n", input); // flag=1; 
            continue; 
        } else printf(GREEN"%s\n"RESET, input);

        input[strcspn(input, "\0")]=' '; /* Remove NUL */
        if(zelemi_send(input, data_pack)) goto RET_3;
    }
    // if(flag) zelemi_printerr_sys("Hint", COMMAND_LOAD_HINT);

RET_3:
    fclose(load_fp);
    return -3;
}