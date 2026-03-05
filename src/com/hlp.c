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

#include <stdio.h> /* vfprintf */
#include <string.h> /* strcmp */
#include <stdarg.h> /* va_list va_start va_end */
#include "c_struct.h"
#include "errors.h"
#include "zelemi_err.h"
#include "config.h"

int zelemi_printret(char *hint, ...) {
    va_list args;
    va_start(args, hint);
    vfprintf(stdout, hint, args);
    va_end(args);
    return 0;
}

int zelemi_command_hlp(int argc, char *opt, struct DATA_STRUCT *data_pack) {
    char flag=1; /* A byte for A Flag */

      if((!opt)||(strcmp(opt, "ADR")==0)) flag=zelemi_printret("\
ADR [fnc]         : It returns the address of a specific internal function based on its parameter.\n\
                    [REG] : prints the values of all global registers.\n");
      if((!opt)||(strcmp(opt, "LIC")==0)) flag=zelemi_printret("\
LIC -no argument- : prints the text and provisions of the software license.\n");
      if((!opt)||(strcmp(opt, "HLP")==0)) flag=zelemi_printret("\
HLP -no argument- : prints the help text.\n");
       if((!opt)||(strcmp(opt, "END")==0)) flag=zelemi_printret("\
END -no argument- : An interactive command used to exit the software.\n\
                    It does not affect the machine code, and the END \n\
                    instruction cannot be used within the machine code.\n");
        if((!opt)||(strcmp(opt, "CLR")==0)) flag=zelemi_printret("\
CLR [parameter]   : It clears a specific buffer or page based on the parameter.\n\
                    It cannot be used within machine code.\n\
                    [BFR]     : It clears the machine code buffer as if no machine\n\
                              code instructions have ever been entered. \n\
                              However, the buffer capacity does not change.\n\
                    [BFRCAPA] : Like the parameter BFR, it also clears the \n\
                                buffer capacity and frees the buffer in memory.\n\
                    -no-parameter- : Clear the Terminal Screen with Call system-function\n");
        if((!opt)||(strcmp(opt, "LDF")==0)) flag=zelemi_printret("\
LDF [File Addr]:    Load Machine opcodes from File, while the Zelemi is in Console mode.\n\
                    it can be used to save Call Point Machine Code (like func) in a file!\n");
        if((!opt)||(strcmp(opt, "NMB")==0)) flag=zelemi_printret("\
NMB [Number Base]:  Changes the base of the input number.. default is %d\n\
                    [2][BIN] [10][DEC] [8][OCT] [16][HEX]\n", DEFAULT_NMB_ARG_I);
        if((!opt)||(strcmp(opt, "RUN")==0)) flag=zelemi_printret("\
RUN -no argument- : It loads the machine code buffer into the executable space and then executes it.\n");
        
        if(flag) {
            zelemi_printerr_sys(ARGUMENT_ERROR_HEADER, ARGUMENT_ERROR, opt);
            return -3;
        }
        return 0;
}
