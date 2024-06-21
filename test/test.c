#include <stdio.h>
#include <string.h>

int     main(void)
{
    char *str;

    str = "conf";

    printf("res : %s\n", strrchr(str, '.'));
}

