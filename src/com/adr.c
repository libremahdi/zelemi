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

#include <stdio.h> /* printf */
#include <string.h> /* strcmp */
#include "c_struct.h"
#include "c_struct.h"
#include "errors.h"
#include "error_handle.h"
#include "config.h"

void reg_x86_64();

#if defined(X86_64)
  #define REG_CALL reg_x86_64
#endif

int zelemi_command_adr(int argc, char *opt, struct DATA_STRUCT *data_pack) {
    if(!opt) {zelemi_printerr_sys(ARGUMENT_ERROR_HEADER, ADR_TAKES_ONE_ARG_ERROR); return -3;}
    
    if(strcmp(opt, "REG")==0)
    { printf("Function Address: %p\n", (void*)REG_CALL); return 0; /* continue to loop */ }
    else {
        zelemi_printerr_sys(ARGUMENT_ERROR_HEADER, ARGUMENT_ERROR, opt);
        return -3; /* Auto contrinue/exit */
    }
    return 0; /* continue to loop */
}
