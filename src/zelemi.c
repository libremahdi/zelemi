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
#include "c_struct.h"
#include "pgetopt_error_handle.h"

int trim_start(char * const);
int trim_end(char * const);

int zelemi_run(int argc, char **argv) {
    struct DATA_STRUCT *data_pack=malloc(sizeof(struct DATA_STRUCT));
    
    data_pack->code=malloc(1);
    data_pack->code_size=1;
    data_pack->code_capa=1;
    
    char input[256]; /* User inputs is placed here. */
    FILE *current_fp; /* file-ptr or stdin */
    void *mem_opcode=NULL; /* Location of the opcodes that will be executed. */
    void (*fn)(void)=NULL; /* The opcodes will be executed in the form of a function. */
    int fork_pid=-1, status;
    
    if(!data_pack->code) { perror("malloc"); goto RET_1; }

    if(argc==1) { /* It runs in console mode and takes input from the user. */
        struct utsname os_info;
        if(uname(&os_info)) { perror("uname"); goto RET_1; }
        printf("%s %s (main, %s %s) [%s (%s) for %s]\n", INTR_NAME, INTR_VERSION, __DATE__, __TIME__, os_info.nodename, os_info.sysname, os_info.machine);
        printf(STARTUP_MESSAGE_HINT);
        current_fp=stdin;
    } else { /* It runs in file mode and reads data from a file. */
        if((!strchr(argv[1], '.'))||(strcmp(strchr(argv[1], '.'), ".mi")!=0))
        {zelemi_printerr_sys(FILE_NAME_ERROR_HEADER, FILE_NAME_ERROR); goto RET_1;}

        current_fp=fopen(argv[1], "r");
        if(!current_fp)
        {zelemi_printerr_sys(FILE_ERROR_HEADER, FILE_ERROR, argv[1]); goto RET_1;}
    }

    while(1) {
        if(argc==1) printf(PROMPT);

        if(!fgets(input, sizeof(input), current_fp)) {
            zelemi_printerr_sys(INPUT_ERROR_HEADER, INPUT_ERROR);
            if (argc==1) continue;
            goto RET_1;
        }

        input[strcspn(input, "\n")]=0; /* Remove NUL */
        if(strstr(input, ";")) *strstr(input, ";")='\0'; /* replaces comment characters with \0 to ignore comments anywhere in the line. */
        trim_start(input); trim_end(input);
        if(input[0]=='\0') continue; /* ignore blank line */

        char *command = strtok(input, " ");
        char *option_ = strtok(NULL , " ");
        switch(c_run_commands(argc, command, option_, data_pack)) { 
          /* 0: continue the loop
             1: exit with error
            -1: exit Normally
            -2: Command not find (goto the hex segment)
            -3: exit or continue Auto by Console/file mode
          */
          case -1: goto RET_0;
          case  1: goto RET_1;
          case -3: if(argc==1) continue; else goto RET_1;
        }
        /* It nullifies the effect of strtok. If option_ is NULL, 
           it means the command is a single part, and strtok has made no changes to the command.
        */ if(option_) command[strcspn(command, "\n")]=' ';
    }
  RET_0:
      free(data_pack);
      return 0;
  RET_1:
      free(data_pack);
      return 1;
}