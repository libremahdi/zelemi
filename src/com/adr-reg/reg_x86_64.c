#include <stdio.h> /* printf */

#define MOVREG(register) __asm__("mov %"#register", %0" : "=r" (register))

void reg_x86_64() {
    unsigned long long registers[16];
    const char *regs_x86_64[16] = {
        "rax", "rbx", "rcx", "rdx",
        "rsi", "rdi", "rsp", "rbp",
        "r8" , "r9" , "r10", "r11",
        "r12", "r13", "r14", "r15"
    };

    __asm__ ("mov %%rax, %0" : "=r" (registers[0]));
    __asm__ ("mov %%rbx, %0" : "=r" (registers[1]));
    __asm__ ("mov %%rcx, %0" : "=r" (registers[2]));
    __asm__ ("mov %%rdx, %0" : "=r" (registers[3]));
    __asm__ ("mov %%rsi, %0" : "=r" (registers[4]));
    __asm__ ("mov %%rdi, %0" : "=r" (registers[5]));
    __asm__ ("mov %%rsp, %0" : "=r" (registers[6]));
    __asm__ ("mov %%rbp, %0" : "=r" (registers[7]));
    __asm__ ("mov %%r8,  %0" : "=r" (registers[8]));
    __asm__ ("mov %%r9,  %0" : "=r" (registers[9]));
    __asm__ ("mov %%r10, %0" : "=r" (registers[10]));
    __asm__ ("mov %%r11, %0" : "=r" (registers[11]));
    __asm__ ("mov %%r12, %0" : "=r" (registers[12]));
    __asm__ ("mov %%r13, %0" : "=r" (registers[13]));
    __asm__ ("mov %%r14, %0" : "=r" (registers[14]));
    __asm__ ("mov %%r15, %0" : "=r" (registers[15]));

    printf("   RAX=%llx\n   RBX=%llx\n", registers[0] , registers[1]);
    printf("   RCX=%llx\n   RDX=%llx\n", registers[2] , registers[3]);
    printf("   RSI=%llx\n   RDI=%llx\n", registers[4] , registers[5]);
    printf("   R8=%llx \n   R9=%llx \n", registers[6] , registers[7] );
    printf("   R10=%llx\n   R11=%llx\n", registers[8] , registers[9]);
    printf("   R12=%llx\n   R13=%llx\n", registers[10], registers[11]);
    printf("   R14=%llx\n   R15=%llx\n", registers[12], registers[13]);

    printf("   RSP=%llx\n", registers[14]);
    printf("   RBP=%llx\n", registers[15]);
    return;
}
