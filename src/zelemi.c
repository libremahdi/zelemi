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

#include <stdlib.h> /* malloc */
#include <stdio.h> /* perror */
#include <string.h> /* strchr, strcmp */
#include <sys/utsname.h> /* uname utsname */
#include "config.h"
#include "errors.h"
#include "pgetopt_error_handle.h"

int trim_start(char * const);
int trim_end(char * const);

int zelemi_run(int argc, char **argv) {
    unsigned char *code = malloc(1); /* opcodes Buffer in Memory */
    unsigned int code_size = 1; /* number of Buffer opcodes */
    char input[256]; /* User inputs is placed here. */
    FILE *current_fp; /* file-ptr or stdin */
    void *mem_opcode=NULL; /* Location of the opcodes that will be executed. */
    void (*fn)(void)=NULL; /* The opcodes will be executed in the form of a function. */
    int fork_pid=-1, status;

    if(!code) { perror("malloc"); return 1; }

    if(argc==1) { /* It runs in console mode and takes input from the user. */
        struct utsname os_info;
        if(uname(&os_info)) { perror("uname"); return 1; }
        printf("%s %s (main, %s %s) [%s (%s) for %s]\n", INTR_NAME, INTR_VERSION, __DATE__, __TIME__, os_info.nodename, os_info.sysname, os_info.machine);
        printf(STARTUP_MESSAGE_HINT);
        current_fp=stdin;
    } else { /* It runs in file mode and reads data from a file. */
        if((!strchr(argv[1], '.'))||(strcmp(strchr(argv[1], '.'), ".mi")!=0))
        {zelemi_printerr_sys(FILE_NAME_ERROR_HEADER, FILE_NAME_ERROR); return 1;}

        current_fp=fopen(argv[1], "r");
        if(!current_fp)
        {zelemi_printerr_sys(FILE_ERROR_HEADER, FILE_ERROR, argv[1]); return 1;}
    }

    while(1) {
        if(argc==1) printf(PROMPT);

        if(!fgets(input, sizeof(input), current_fp)) {
            zelemi_printerr_sys(INPUT_ERROR_HEADER, INPUT_ERROR);
            if (argc==1) continue;
            return 1;
        }

        input[strcspn(input, "\n")]=0; /* Remove NUL */
        if(strstr(input, ";")) *strstr(input, ";")='\0'; /* replaces comment characters with \0 to ignore comments anywhere in the line. */
        trim_start(input);
        trim_end(input);
        if(input[0]=='\0') continue; /* ignore blank line */

    }
    return 0;
}