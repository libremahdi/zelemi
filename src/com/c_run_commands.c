#include <stdlib.h> /* NULL */
#include <string.h> /* strcmp */
#include "c_struct.h"

struct FunctionBuffer commands[] = {
    {"RUN", zelemi_command_run},
    {"END", zelemi_command_end},
    {"CLR", zelemi_command_clr},
    {"ADR", zelemi_command_adr},
    {"HLP", zelemi_command_hlp},
    {"LIC", zelemi_command_lic},
    {NULL, NULL}
};

int c_run_commands(int argc, char *com, char *opt, struct DATA_STRUCT *data_pack) {
    register unsigned char in_1 = 0;
    while(commands[in_1].CommandName) {
        if(strcmp(com, commands[in_1].CommandName)==0) {
            return commands[in_1].fnc(argc, opt, data_pack);
        }
        ++in_1;
    }
    return -2;
}