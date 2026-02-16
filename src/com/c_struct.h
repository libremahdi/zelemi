#pragma once

struct FunctionBuffer {
    char *CommandName;
    int (*fnc)(int argc, char *opt);
};
int c_run_commands(int argc, char *com, char *opt);

int zelemi_command_run(int argc, char *opt);
int zelemi_command_clr(int argc, char *opt);
int zelemi_command_adr(int argc, char *opt);
int zelemi_command_hlp(int argc, char *opt);
int zelemi_command_lic(int argc, char *opt);
int zelemi_command_end(int argc, char *opt);
