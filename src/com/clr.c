#include<stdlib.h> /* system */
#include<string.h>

int zelemi_command_clr(int argc, char *opt) {
    if((opt)&&(strcmp(opt, "BFR")==0)) {
        #include<stdio.h>
        printf("Clearing the buffer...\n");
        return 0;
    }
    if(argc==1) {system("clear");}
    return 0;
}
