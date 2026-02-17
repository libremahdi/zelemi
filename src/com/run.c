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

#include <sys/mman.h> 
#include <stdio.h> /* perror */
#include <unistd.h> /* fork */
#include <sys/wait.h> /* waitpid */
#include <string.h> /* memcpy */
#include "c_struct.h"
#include "errors.h"
#include "colors.h"
#include "error_handle.h"

int zelemi_command_run(int argc, char *com, struct DATA_STRUCT *data_pack) {
    void *mem_opcode=NULL; /* Location of the opcodes that will be executed. */
    void (*fn)(void)=NULL; /* The opcodes will be executed in the form of a function. */
    int fork_pid=-1, status;

    if(data_pack->code_size==0) {
        zelemi_printerr_sys(EMPTY_BUFFER_HEADER, EMPTY_BUFFER_ERROR);
        return -3;
    }

    if(argc==1) {
        fork_pid = fork();
        if(fork_pid<0) {perror("fork"); return 1; /* exit with error */}
    } else fork_pid=0;

    if(fork_pid==0) { /* child */
        mem_opcode = mmap(NULL, data_pack->code_size+1, PROT_READ | PROT_WRITE | PROT_EXEC,
                        MAP_ANON | MAP_PRIVATE, -1, 0);
        if (mem_opcode == MAP_FAILED) { perror("mmap"); return 1; /* exit with error */ }

        memcpy(mem_opcode, data_pack->code, data_pack->code_size);
        void (*fn)(void) = mem_opcode;
        fn();
        munmap(mem_opcode, data_pack->code_size);
        return -1; /* exit normally */
    } else { /* mother */
        waitpid(-1, &status, 0);
        if (WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(status);
            printf(PINK"   exited normally with status: %d\n"RESET, exit_status);
        } else if (WIFSIGNALED(status)) {
            int sig = WTERMSIG(status);
            printf(PINK"   killed by signal: %d\n"RESET, sig);
        } else if (WIFSTOPPED(status)) {
            int sig = WSTOPSIG(status);
            printf(PINK"   stopped by signal: %d\n"RESET, sig);
        } else {
            printf(PINK"   terminated abnormally\n"RESET);
        }
        zelemi_command_clr(argc, "BFR", data_pack); /* clear buffer */
        return 0;
    }
    return -3;
}
