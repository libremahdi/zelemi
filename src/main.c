#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <stdlib.h>
#include "load_com.h"
#include "mi_startup.h"
#include "colors.h"
// #include "pstring.h"

int main(void) {
    unsigned char *code = NULL;
    unsigned int CodeSize=0;
    char input[256];
    unsigned int HEX_INT=0;

    show_startup();

    while(1) {
        printf(PINK">> "RESET);
        if(fgets(input, sizeof(input), stdin) == NULL) {printf(YELLOW"InputError:"RESET" An error occurred in the input buffer.\n");}
        if(strcmp(input, "\n")==0) continue;
        input[strcspn(input, "\n")]=0;
        
        
        if(input[0] == ';') continue;
        if(strcmp(input, "RUN")==0) break;
        if(strcmp(input, "END")==0) goto Exit;
        if(strcmp(input, "HLP")==0) {load_hlp(); continue;}
        if(strcmp(input, "CPY")==0) {load_cpy(); continue;}
        if(strcmp(input, "CLR")==0) {load_clr(); continue;}
    
    
        if(sscanf(input, "%X", &HEX_INT)) {
            code = (unsigned char *) realloc (code, sizeof(char)*(CodeSize+1));
            if(!code){perror("realloc"); return 1;}
            code[CodeSize]=HEX_INT;
            ++CodeSize;
        } else {
            printf(YELLOW"InputError:"RESET" You are only allowed to enter hexadecimal numbers or 'RUN' and 'END'.\n");
        }
    };

    if(!CodeSize) {perror(YELLOW"EmptyBuffer"RED); return 1;}

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