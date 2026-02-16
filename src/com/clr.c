#include <stdlib.h> /* system */
#include <string.h>
#include "c_struct.h"
#include "errors.h"
#include "pgetopt_error_handle.h"

int zelemi_command_clr(int argc, char *opt, struct DATA_STRUCT *data_pack) {
    if(!opt) system("clear");
    else if(strcmp(opt, "BFR")==0) { data_pack->code_size=1; return 0; /* continue to loop */ }
    else {
        zelemi_printerr_sys(ARGUMENT_ERROR_HEADER, ARGUMENT_ERROR, opt);
        return -3; /* Auto contrinue/exit */
    }
    return 0; /* continue to loop */
}
