#include <stdio.h> /* printf */
#include "c_struct.h"

int zelemi_command_hlp(int argc, char *opt, struct DATA_STRUCT *data_pack) {
    if(argc==1) {
        printf("Help DEMO Text : %s\n", opt);
    }
    return 0;
}
