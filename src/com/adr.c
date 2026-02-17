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

void get_register_X86_64() {
    unsigned long long RAX, RBX, RCX, RDX, RSI, RDI, RSP, RBP, R8, R9, R10, R11, R12, R13, R14, R15;
    __asm__ ("mov %%rax, %0" : "=r" (RAX));
    __asm__ ("mov %%rbx, %0" : "=r" (RBX));
    __asm__ ("mov %%rcx, %0" : "=r" (RCX));
    __asm__ ("mov %%rdx, %0" : "=r" (RDX));
    __asm__ ("mov %%rsi, %0" : "=r" (RSI));
    __asm__ ("mov %%rdi, %0" : "=r" (RDI));
    __asm__ ("mov %%rsp, %0" : "=r" (RSP));
    __asm__ ("mov %%rbp, %0" : "=r" (RBP));
    __asm__ ("mov %%r8,  %0" : "=r" (R8));
    __asm__ ("mov %%r9,  %0" : "=r" (R9));
    __asm__ ("mov %%r10, %0" : "=r"(R10));
    __asm__ ("mov %%r11, %0" : "=r"(R11));
    __asm__ ("mov %%r12, %0" : "=r"(R12));
    __asm__ ("mov %%r13, %0" : "=r"(R13));
    __asm__ ("mov %%r14, %0" : "=r"(R14));
    __asm__ ("mov %%r15, %0" : "=r"(R15));

    printf("   RAX=%llx\n   RBX=%llx\n", RAX, RBX);
    printf("   RCX=%llx\n   RDX=%llx\n", RCX, RDX);
    printf("   RSI=%llx\n   RDI=%llx\n", RSI, RDI);
    printf("   R8=%llx \n   R9=%llx \n",R8 , R9 );
    printf("   R10=%llx\n   R11=%llx\n",R10, R11);
    printf("   R12=%llx\n   R13=%llx\n",R12, R13);
    printf("   R14=%llx\n   R15=%llx\n",R14, R15);

    printf("   RSP=%llx\n",RSP);
    printf("   RBP=%llx\n", RBP);
    return;
}

int zelemi_command_adr(int argc, char *opt, struct DATA_STRUCT *data_pack) {
    if(!opt) {zelemi_printerr_sys(ARGUMENT_ERROR_HEADER, ADR_TAKES_ONE_ARG_ERROR); return -3;}
    
    if((strcmp(opt, "REG-X86_64")==0) || (strcmp(opt, "REG-AMD64")==0))
    { printf("Function Address: %p\n", (void*)get_register_X86_64); return 0; /* continue to loop */ }
    else {
        zelemi_printerr_sys(ARGUMENT_ERROR_HEADER, ARGUMENT_ERROR, opt);
        return -3; /* Auto contrinue/exit */
    }
    return 0; /* continue to loop */
}
