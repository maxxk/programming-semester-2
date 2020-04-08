#include <stdio.h>
#include "util.h"

int main(void)
{
    for (int i = 0; i < 33; i++) {
        printf("%d\t%x\t", i, i);
        print_binary(i, 6);
        putchar('\n');
    }
    return 0;
}
