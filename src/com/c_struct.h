#include <stdlib.h> /* size_t */
#pragma once

struct DATA_STRUCT {
    unsigned char *code; /* opcodes Buffer in Memory */
    size_t code_size; /* number of Buffer opcodes */
    size_t code_capa; /* number of Buffer opcodes */
};

struct FunctionBuffer {
    char *CommandName;
    int (*fnc)(int argc, char *opt, struct DATA_STRUCT *);
};

int c_run_commands(int, char *, char *, struct DATA_STRUCT *);

int zelemi_command_run(int argc, char *opt, struct DATA_STRUCT *);
int zelemi_command_clr(int argc, char *opt, struct DATA_STRUCT *);
int zelemi_command_adr(int argc, char *opt, struct DATA_STRUCT *);
int zelemi_command_hlp(int argc, char *opt, struct DATA_STRUCT *);
int zelemi_command_lic(int argc, char *opt, struct DATA_STRUCT *);
int zelemi_command_end(int argc, char *opt, struct DATA_STRUCT *);
