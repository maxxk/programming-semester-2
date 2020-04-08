#ifndef _UTIL_H
#define _UTIL_H

// Вывести число в двоичной записи.
// value — значение, length — сколько бит выводим.
void print_binary(unsigned long long value, char length);

// Вывести число по основанию 2, 16, 10 и перейти на следующую строку.
void print_bin_hex_dec(const char *name, unsigned long long value, char length);

#endif
