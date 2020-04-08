#include <stdio.h>
#include "util.h"
// maxim.krivchikov@gmail.com

// double t_abs(double d)
// int t_sign(double d)
// double add(double a, double b)

// 1.fff..f * 2 ** e + 1.gg..g * 2 ** h
// max(e, h) = M
// 1.ff...f >> (M - e)
// 1.g...g >> (M - h)
// 2 ** (M +/- ε) * 1.

#define SHIFT 1023

int log2_(long long l) {
    int result = 0;
    while (l) {
        result += 1;
        l >>= 1;
    }
    return result;
}

double add(double a, double b) {
    unsigned long long answer;
    long long frac;
    int sign = 0;
    unsigned long long ax = *(unsigned long long*)(&a);
    unsigned long long bx = *(unsigned long long*)(&b);
    int a_s = ax >> 63;
    int b_s = bx >> 63;
    int a_e = (ax & (~( 1ULL << 63 ))) >> 52;
    int b_e = (bx & (~( 1ULL << 63 ))) >> 52;
    long long a_f = ax & 0xFFFFFFFFFFFFF;
    long long b_f = bx & 0xFFFFFFFFFFFFF;

    if (!a_e && !a_f) { return b; }
    if (!b_e && !b_f) { return a; }

    a_f |= 1LL << 52;
    b_f |= 1LL << 52;

    printf("a = %d %d ", a_s, a_e);
    print_binary(a_f, 53);
    printf("\n");

    printf("b = %d %d ", b_s, b_e);
    print_binary(b_f, 53);
    printf("\n");
    
    int M = (a_e > b_e) ? a_e : b_e; // M - SHIFT
    a_f >>= M - a_e;
    b_f >>= M - b_e;

    if (a_s) { a_f = -a_f; }
    if (b_s) { b_f = -b_f; }

    frac = a_f + b_f;
    sign = frac < 0;
    if (frac < 0) { frac = -frac; }

    int N = log2_(frac);
    if (N < 53) {
        frac <<= 53 - N;
        M -= 53 - N;
    }
    if (N > 53) {
        frac >>= N - 53;
        M += N - 53;
    }

    frac &= 0x0FFFFFFFFFFFFF;
    answer = ((unsigned long long)frac) 
        | ((unsigned long long)M << 52) 
        | ((unsigned long long)sign << 63);

    return *(double*)&answer;
}

double t_abs(double d) {
    unsigned long long x = *(unsigned long long*)(&d);

    x = x & (~( 1ULL << 63 ));
    return *(double*)&x;
}

int t_sign(double d) {
    unsigned long long x = *(unsigned long long*)(&d);
    int sign = x >> 63;
    if (x & (~( 1ULL << 63 ))) {
        return sign ? -1 : 1; // условие ? истина : ложь
    } else {
        return 0;
    }
}



int main(void) {
    double a, b;
    while (1) {
        scanf("%lf %lf", &a, &b);
        printf("%f\n", add(a, b));
    }
    return 0;
}
