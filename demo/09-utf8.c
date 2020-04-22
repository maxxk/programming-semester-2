#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "util.h"

// unsigned int чаще всего 4 байта (иногда 2 байта)
// uint32_t 
void print_unicode_2byte(uint32_t value) {
    if (value < 0x80) {
        putc(value, stdout);
        return;
    }

    if (value <= 0x7ff) {
        uint8_t lower = value & 0x3f; // младшие 6 бит
        uint8_t higher = value >> 6; // сдвинули биты на 6 вправо, затирая младшие биты старшими
        putc(higher | 0xc0, stdout);
        putc(lower | 0x80, stdout);
    }
}

int main(void) {
    char *c1 = "🇷 🇺 🇷🇺"; // 1 видимый знак, 2 "символа", 8 байт
    c1 = "🏴󠁧󠁢󠁳󠁣󠁴󠁿";
    int length = strlen(c1);
    printf("%d: ", length);
    for (int i = 0; i < length; i++) {
        printf("%02x ", (unsigned char)c1[i]);
    }
    printf("\n");
    
    putc(0x41, stdout); // LATIN CAPITAL ... A
    // 0x80 < 0x42b < 0x7ff
    print_binary(0x42b, 12); //  010000101011 ⟶ 1101 0000  1010 1011 
    // 8 = 1000 1001 A 1010 B 1011 C 1100 D 1101 E 1110 F 1111
    putc(0xD0, stdout);
    putc(0xAB, stdout);
    print_unicode_2byte(0x42b);
    return 0;
}
