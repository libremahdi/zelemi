#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <stdlib.h>
#include "load_com.h"
#include "mi_startup.h"
#include "colors.h"
// #include "pstring.h"

#define PROMPT ">>"

int main(int argc, char **argv) {
    unsigned char *code = NULL; /* opcodes in Memory */
    unsigned int CodeSize=0; /* opcodes size */
    char input[256]; /* input buffer*/
    unsigned int HEX_INT=0; /* input buffer to Hex buffer */
    FILE *inp_ptr;

    if(argc==1) { /* console */
        show_startup();
        inp_ptr=stdin;
    } else { /* file */
        inp_ptr=fopen(argv[1], "r");
        if(!inp_ptr) {
            printf(YELLOW"FileError:"RESET"Unable to open '%s'.", argv[1]);
            return 1;
        }
    }

    while(1) {
        if(argc==1) printf(PINK"%s "RESET, PROMPT);

        if(fgets(input, sizeof(input), inp_ptr) == NULL) {printf(YELLOW"InputError:"RESET" An error occurred in the input buffer.\n");}
        
        if(strcmp(input, "\n")==0) continue; /* ignore blank line */
        input[strcspn(input, "\n")]=0; /* Remove NUL */
        
        
        if(input[0] == ';') continue;
        if(strcmp(input, "RUN")==0) break;
        if(strcmp(input, "END")==0) goto Exit;
        if(strcmp(input, "HLP")==0) {load_hlp(); continue;}
        if(strcmp(input, "CPY")==0) {load_cpy(); continue;}
        if(strcmp(input, "CLR")==0) {load_clr(); continue;}

        if(sscanf(input, "%X", &HEX_INT) == 1) {
            code = (unsigned char *) realloc (code, sizeof(char)*(CodeSize+1));
            if(!code){perror("realloc"); return 1;}
            code[CodeSize]= (unsigned char) HEX_INT;
            ++CodeSize;
        } else {
            printf(YELLOW"InputError:"RESET" You are only allowed to enter hexadecimal numbers or 'RUN' and 'END'.\n");
        }
    };

    if(!CodeSize) {perror(YELLOW"EmptyBuffer"RED); return 1;}

    void *mem = mmap(NULL, CodeSize, PROT_READ | PROT_WRITE | PROT_EXEC,
                     MAP_ANON | MAP_PRIVATE, -1, 0);
    if (mem == MAP_FAILED) { perror("mmap"); return 1; }

    memcpy(mem, code, CodeSize);

    void (*fn)(void) = mem;
    fn();

    munmap(mem, CodeSize);

Exit:
    if(inp_ptr!=stdin) fclose(inp_ptr);
    free(code);
    return 0;
}