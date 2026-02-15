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

#include <pgetopt-4.3/pgetopt.h>
#include <stdio.h>
#include "colors.h" /* See config/colors.h */
#include "errors.h" /* See config/errors.h */

#define _without_error          0
#define _invalid_option         1
#define _key_without_value      2
#define _lack_of_class          3
#define _class_syntax_error     4
#define _invalid_value          5
#define _lack_of_master         6

static void zelemi_printerr_user (char *err, char *opt) {
    printf (RED"%s "RESET"%s\n%s\n", USER_ERR_HEADER, opt, err);
}

int __attribute__((nonnull))
zelemi_error_parser (usrerr _error, char **argv) {
    return  (_error.error == _invalid_option)
    ?   (zelemi_printerr_user (INVALID_OPTION_ERR, argv[_error.index]), 1):
            (_error.error == _key_without_value)  
    ?   (zelemi_printerr_user (KEY_WITHOUT_VALUE_ERR, argv[_error.index]), 1): 
            (_error.error == _lack_of_class)   
    ?   (zelemi_printerr_user (LACK_OF_CLASS_ERR, argv[_error.index]), 1): 
            (_error.error == _class_syntax_error)  
    ?   (zelemi_printerr_user (CLASS_SYNTAX_ERR, argv[_error.index]), 1):
            (_error.error == _invalid_value)
    ?   (zelemi_printerr_user (INVALID_VALUE_ERR, argv[_error.index]), 1):
            (_error.error == _lack_of_master)
    ?   (zelemi_printerr_user (LACK_OF_MASTER_ERR, argv[_error.index]), 1): 0;
}
