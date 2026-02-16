#include<stdlib.h> /* system */

int zelemi_command_clr(int argc, char *opt) {
    if(argc==1) {
        system("clear");
    }
    return 0;
}
