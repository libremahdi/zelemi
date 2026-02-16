#include <stdlib.h> /* system realloc */
#include <string.h>
#include "c_struct.h"
#include "errors.h"
#include "pgetopt_error_handle.h"

int zelemi_command_clr(int argc, char *opt, struct DATA_STRUCT *data_pack) {
    if(!opt) system("clear");
    else if(strcmp(opt, "BFR")==0) { data_pack->code_size=0; return 0; /* continue to loop */ }
    else if(strcmp(opt, "BFRCAPA")==0) {
        data_pack->code_size=0;
        data_pack->code_capa=1;
        data_pack->code = realloc(data_pack->code, 1); /* don't need to test return value */
        return 0; /* continue to loop */ 
    }
    else {
        zelemi_printerr_sys(ARGUMENT_ERROR_HEADER, ARGUMENT_ERROR, opt);
        return -3; /* Auto contrinue/exit */
    }
    return 0; /* continue to loop */
}
