/* BSD 3-Clause License
 * 
 * Copyright (c) 2026, Mahdi Hosseini Asaad

 * Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:

 1.Redistributions of source code must retain the above copyright notice, this
    list of conditions and the following disclaimer.

 2.Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

 3.Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
   FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
   OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include<stdio.h> /* printf */
#include<pgetopt-4.3/pgetopt.h>
#include"pgetopt_error_handle.h"
#include"config.h"

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
    pinit_set_allowed_masters (init, masters_avl);

    usrerr error_ = pinit_parser(init, argc, argv);
    if (zelemi_error_parser(error_, argv)) goto EXIT;

    switch(pinit_get_master_id(init)) {
        case 1:
            // zelemi_run(
            //     /* argc= */ pinit_get_master_argc(init),
            //     /* argv= */ pinit_get_master_argv(init)
            // ); goto EXIT;
            break;
    }

    {   /* Isolating the environment */
        register int opt_id, i=0;
        while((opt_id=pclass_loop_get_opt_id(main, i))!=-1) {
            switch(opt_id) {
                case 1:
                    printf("%s\n", "BSD 3-Clause License\nCopyright (c) 2026, Mahdi Hosseini Asaad");
                    goto EXIT;
                case 2:
                    printf("%s\n", GET_VERSION);
                    goto EXIT;
            }
            ++i;
        }
    }
    
EXIT:
    pclass_free(main);
    pinit_free(init);
    return 0;
}