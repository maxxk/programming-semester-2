#include <stdio.h>
#include "util.h"

int main(void)
{
    double d;
    unsigned long long d_bits;
    int sign;
    unsigned exp;
    unsigned long long frac;

    if (scanf("%lf", &d) != 1) {
        return 1;
    }

    d_bits = *(unsigned long long*)&d;
    sign = (d_bits >> 63) & 1;
    exp = (d_bits >> 52) & 0x7FF;
    frac = d_bits & 0xFFFFFFFFFFFFF;

    printf("Number:\t%f\n", d);
    printf("sign:\t%d (%c)\n", sign, sign ? '-' : '+');
    printf("exp:\t%d₁₀\t%x₁₆\t", exp, exp);
    print_binary(exp, 11);
    printf("₂\t(2 ** %d = %lld)\n", exp - 1023, 1ULL << (exp - 1023));
    printf("frac:\t1.");
    print_binary(frac, 52);
    printf("\t(%lld)\n", frac | (1ULL << 53)); 
    return 0;
}
