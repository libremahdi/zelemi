#include <string.h> /* memmove sizeof */

void __attribute__((nonnull))
trim_start (char * const pp_str) {
    register unsigned int in=0;

    while ((pp_str[in]==' ') && (pp_str[in]!='\0')) {++in;} // first index after whitespaces
    if (!in) return;

    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wunsafe-buffer-usage"
    memmove(pp_str, pp_str+in, strlen(pp_str)-in+1);
    #pragma clang diagnostic pop
}

void __attribute__((nonnull))
trim_end(char * const pp_str) {
    size_t len = strlen(pp_str);
    register unsigned int in = 0;

    while (len > 0 && pp_str[len - 1 - in] == ' ') {++in;}

    if (in > 0) pp_str[len - in] = '\0';
}