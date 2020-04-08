#include <stdio.h>
#include "util.h"

void print_binary(unsigned long long value, char length)
{
    for (int i = length-1; i >= 0; i-- ) {
        char c = (value >> i) & 1;
        putchar(c ? '1' : '0');
    }
}

void print_bin_hex_dec(const char *name, unsigned long long value, char length)
{
    printf("%s\t", name);
    print_binary(value, length);
    printf("\t0x%llx\t%lld\t", value, value);
    putchar('\n');
}
