#include<stdio.h> /* printf */

int zelemi_command_hlp(int argc, char *opt) {
    if(argc==1) {
        printf("Help DEMO Text : %s\n", opt);
    }
    return 0;
}
