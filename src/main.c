#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/utsname.h>

#define RED     "\033[31m"
#define YELLOW  "\033[33m"
#define PINK    "\033[35m"
#define RESET   "\033[0m"

void load_cpy();
void load_hlp();

int main(void) {
    unsigned char *code = NULL;
    unsigned int CodeSize=0;
    char input[256];
    unsigned int HEX_INT=0;

    struct utsname os_info;
    uname(&os_info);
    printf("Machine Interpreter 1.0 (main, %s %s) [%s (%s) for %s]\n", __DATE__, __TIME__, os_info.nodename, os_info.sysname, os_info.machine);
    printf("Type \"HLP\" or \"CPY\" for more information.\n");

    while(1) {
        printf(PINK">> "RESET);
        if(fgets(input, sizeof(input), stdin) == NULL) {printf("InputError: An error occurred in the input buffer.\n");}
        if(strcmp(input, "\n")==0) continue;
        input[strcspn(input, "\n")]=0;
        
        
        if(input[0] == ';') continue;
        if(strcmp(input, "RUN")==0) break;
        if(strcmp(input, "END")==0) goto Exit;
        if(strcmp(input, "HLP")==0) {load_hlp(); continue;}
        if(strcmp(input, "CPY")==0) {load_cpy(); continue;}
        
        if(sscanf(input, "%X", &HEX_INT)) {
            code = (unsigned char *) realloc (code, sizeof(char)*(CodeSize+1));
            if(!code){perror("realloc"); return 1;}
            code[CodeSize]=HEX_INT;
            ++CodeSize;
        } else {
            printf("InputError: You are only allowed to enter hexadecimal numbers or 'RUN' and 'END'.\n");
        }
    };

    if(!CodeSize) {perror("EmptyBuffer"); return 1;}

    void *mem = mmap(NULL, sizeof(code), PROT_READ | PROT_WRITE | PROT_EXEC,
                     MAP_ANON | MAP_PRIVATE, -1, 0);
    if (mem == MAP_FAILED) { perror("mmap"); return 1; }

    memcpy(mem, code, CodeSize);

    void (*fn)(void) = mem;
    fn();

    munmap(mem, sizeof(code));

Exit:
    free(code);
    return 0;
}