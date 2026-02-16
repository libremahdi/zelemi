#include "c_struct.h"

int zelemi_command_run(int argc, char *com, struct DATA_STRUCT *data_pack) {
    #include<stdio.h> /* printf */
    for (int i=0 ; i<data_pack->code_size ; ++i) {
        printf("%x\n", data_pack->code[i]);
    }
    return -1;
}
