#include <sys/utsname.h>
#include <stdio.h>
#include "mi_config.h"

void show_startup() {
    struct utsname os_info;
    uname(&os_info);
    printf("%s %s (main, %s %s) [%s (%s) for %s]\n", INTR_NAME, INTR_VERSION, __DATE__, __TIME__, os_info.nodename, os_info.sysname, os_info.machine);
    printf("Type \"HLP\" or \"CRT\" for more information.\n");
}

