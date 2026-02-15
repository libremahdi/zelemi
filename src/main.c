/*
 *  Copyright (C) 2025-2026 Mahdi Hosseini Asaad
 *  For more information, please read LICENSE file.
 *
*/

#include <pgetopt-4.3/pgetopt.h>

int main(int argc, char **argv) {
    pinit *init = pinit_create(
"This is Zero Level Machine Interpreter.. \n\
For executing machine language codes.");

    pclass *main = pclass_create(init, "main");
    pinit_set_main_class(init, main);

    palw main_allowed_options[] = {
        { 1, "license" },
        { 2, "version" },
        { 2, "v" },
        EOL
    };
    pclass_set_allowed_options(main, main_allowed_options);
    
    palw masters_avl[] = {
        { 1, "run" },
        EOL
    };
    switch(pinit_get_master_id(init)) {
        case 1:
            // zelemi_run(
            //     /* argc= */ pinit_get_master_argc(init),
            //     /* argv= */ pinit_get_master_argv(init)
            // ); goto EXIT;
            break;
    }

    usrerr error_ = pinit_parser(init, argc, argv);
    if (usererror_parser (error_, argv)) goto EXIT;

    {   /* Isolating the environment */
        register int opt_id, i=0;
        while((opt_id=pclass_loop_get_opt_id(main, i))!=-1) {
            switch(opt_id) {
                case 1:
                    // license();
                    break;
                case 2:
                    // version();
                    break;
            }
            ++i;
        }
    }
    
EXIT:
    pclass_free(main);
    pinit_free(init);
    return 0;
}