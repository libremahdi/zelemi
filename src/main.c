#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h> /* fork */
#include <sys/wait.h> /* waitpid */
#include "colors.h"
#include "mi_string.h"

#define PROMPT ">>"

void show_startup();
void load_cpy();
void load_hlp();
void load_clr();
static void clear_buffer(unsigned char **code, unsigned int *CodeSize) {
    *CodeSize=1;
    free(*code);
    *code = malloc(1);
    if (!*code) { perror("malloc"); exit(1); }
}

int main(int argc, char **argv) {
    signal(SIGINT, SIG_IGN);
    unsigned char *code = malloc(1); /* opcodes in Memory */
    if (!code) { perror("malloc"); exit(1); }
    unsigned int CodeSize=1; /* opcodes size */
    char input[256]; /* input buffer*/
    unsigned int HEX_INT=0; /* input buffer to Hex buffer */
    FILE *inp_ptr;
    void *mem=NULL;
    void (*fn)(void)=NULL;
    pid_t fork_pid=-1;
    int status;

    if(argc==1) { /* console */
        show_startup();
        inp_ptr=stdin;
    } else { /* file */
        if((!strchr(argv[1], '.'))||(strcmp(strchr(argv[1], '.'), ".mi")!=0)) {
            printf(YELLOW"FileNameError:"RESET" Invalid file extension. The expected extension is '.mi'.\n");
            goto Exit_UNORM;
        }
        inp_ptr=fopen(argv[1], "r");
        if(!inp_ptr) {
            printf(YELLOW"FileError:"RESET"Unable to open '%s'.", argv[1]);
            goto Exit_UNORM;
        }
    }

    while(1) {
        if(argc==1) printf(PINK"%s "RESET, PROMPT);

        if(fgets(input, sizeof(input), inp_ptr) == NULL) {
            printf(YELLOW"InputError:"RESET" An error occurred in the input buffer.\n"); 
            if (argc==1) continue;
            goto Exit_UNORM;
        }
        
        input[strcspn(input, "\n")]=0; /* Remove NUL */
        if(strstr(input, ";")) *strstr(input, ";")='\0';
        trim_start(input);
        trim_end(input);

        if(input[0]=='\0') continue; /* ignore blank line */

        if      (strcmp(input, "END")==0) goto Exit;
        else if (strcmp(input, "HLP")==0) {load_hlp(); continue;}
        else if (strcmp(input, "CRT")==0) {load_cpy(); continue;}
        else if((strcmp(input, "CLR")==0)&&(argc==1)) {load_clr(); continue;}
        else if((strcmp(input, "CLRBFR")==0)&&(argc==1)) {clear_buffer(&code, &CodeSize); continue;}
        else if (strcmp(input, "RUN")==0) {
            if(argc==1) {
                if(!(CodeSize-1)) {perror(YELLOW"EmptyBuffer"RED); continue;}
                fork_pid = fork();
                if(fork_pid<0) {perror("fork"); goto Exit;}
            } else {
                fork_pid=0;
            }
            if(fork_pid==0) {
                mem = mmap(NULL, CodeSize, PROT_READ | PROT_WRITE | PROT_EXEC,
                                MAP_ANON | MAP_PRIVATE, -1, 0);
                if (mem == MAP_FAILED) { perror("mmap"); goto Exit_UNORM; }

                memcpy(mem, code, CodeSize);

                void (*fn)(void) = mem;

                fn();

                unsigned long my_rax;

                __asm__ (
                    "mov %%rax, %0\n\t"
                    : "=r" (my_rax)
                );

                printf("RAX: %016lx\n", my_rax);



                munmap(mem, CodeSize);
                goto Exit;
            } else {
                waitpid(-1, &status, 0);
                clear_buffer(&code, &CodeSize);
                if (WIFEXITED(status)) {
                    int exit_status = WEXITSTATUS(status);
                    printf(GREEN"   exited normally with status: %d\n"RESET, exit_status);
                } else if (WIFSIGNALED(status)) {
                    int sig = WTERMSIG(status);
                    printf(RED"   killed by signal: %d\n"RESET, sig);
                } else if (WIFSTOPPED(status)) {
                    int sig = WSTOPSIG(status);
                    printf(YELLOW"   stopped by signal: %d\n"RESET, sig);
                } else {
                    printf(YELLOW"   terminated abnormally\n"RESET);
                }
                continue;
            }

        };
        if(str2hex_split(input, &code, &CodeSize)) {
            if(argc==1) continue;
            goto Exit_UNORM;
        }
    };

Exit:
    if(inp_ptr!=stdin) fclose(inp_ptr);
    free(code);
    return 0;

Exit_UNORM:
    if(inp_ptr!=stdin) fclose(inp_ptr);
    free(code);
    return 1;

}