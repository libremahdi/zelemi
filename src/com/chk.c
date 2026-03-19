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

#include <string.h> /* strcmp */
#include "errors.h"
#include "c_struct.h"
#include "zelemi_err.h"
#include "config.h"

int zelemi_command_chk(int argc, const char *opt, struct DATA_STRUCT *data_pack) {
    if(!opt)  {zelemi_printerr_sys(ARGUMENT_ERROR_HEADER, TAKES_ONE_ARG_ERROR, "CHK"); return -3;} 
    else if((strcmp(opt, "X64")==0)||(strcmp(opt, "X86_64")==0)||(strcmp(opt, "AMD64")==0)) { 
        #ifdef X86_64
            return 0;
        #else
        zelemi_printerr_sys("CHK Signal", "Your Architecture is not '%s'", opt);
        return -3;
        #endif
    }
    else if((strcmp(opt, "POWERPC")==0)) { 
        #ifdef POWERPC
            return 0;
        #else
        zelemi_printerr_sys("CHK Signal", "Your Architecture is not '%s'", opt);
        return -3;
        #endif
    }
    else {zelemi_printerr_sys(ARGUMENT_ERROR_HEADER, ARGUMENT_ERROR, opt); return -3;} 
}
