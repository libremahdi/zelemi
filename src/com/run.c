#include <sys/mman.h> 
#include <stdio.h> /* perror */
#include <unistd.h> /* fork */
#include <sys/wait.h> /* waitpid */
#include <string.h> /* memcpy */
#include "c_struct.h"
#include "errors.h"
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
            printf("   exited normally with status: %d\n", exit_status);
        } else if (WIFSIGNALED(status)) {
            int sig = WTERMSIG(status);
            printf("   killed by signal: %d\n", sig);
        } else if (WIFSTOPPED(status)) {
            int sig = WSTOPSIG(status);
            printf("   stopped by signal: %d\n", sig);
        } else {
            printf("   terminated abnormally\n");
        }
        zelemi_command_clr(argc, "BFR", data_pack); /* clear buffer */
        return 0;
    }
    return -3;
}
