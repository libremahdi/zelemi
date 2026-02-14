#include<stdio.h>

void get_register(){
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
}