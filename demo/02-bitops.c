#include <stdio.h>
#include "util.h"

int main(void)
{
    // Для примера возьмём следующие числа:
    //   01100 
    //   01010
    // битовые операторы действуют на отдельные биты независимо.

    int i = 0xC;
    int j = 0xA;

    printf("Исходные значения:\n");
    print_bin_hex_dec("i", i, 5);
    print_bin_hex_dec("j:", j, 5);

    // i | j — побитовое «ИЛИ», побитовый максимум, OR
    print_bin_hex_dec("i | j", i | j, 5);
    // i & j — побитовое «И», побитовый минимум, AND
    print_bin_hex_dec("i & j", i & j, 5);
    // i ^ j — побитовое исключающее «ИЛИ», !=, сумма по модулю 2, XOR
    print_bin_hex_dec("i ^ j", i ^ j, 5);
    // обычная сумма использует перенос
    print_bin_hex_dec("i + j", i + j, 5);

    // ~i — побитовое обращение, «не»
    print_bin_hex_dec("i", i, 5);
    print_bin_hex_dec("~i", ~i, 5);

    // побитовые сдвиги эквивалентны умножению / делению на 2 в степени «количество бит сдвига» 
    print_bin_hex_dec("i >> 1", i >> 1, 5);
    print_bin_hex_dec("i >> 2", i >> 2, 5);
    print_bin_hex_dec("i << 1", i << 1, 5);
    print_bin_hex_dec("i << 2", i << 2, 5);

    // сравнение побитовых и логических операций
    print_bin_hex_dec("1", 1, 5);
    print_bin_hex_dec("3", 3, 5);
    print_bin_hex_dec("1 && 3", 1 && 3, 5);
    print_bin_hex_dec("1 & 3", 1 & 3, 5);
    print_bin_hex_dec("1 || 3", 1 || 3, 5);
    print_bin_hex_dec("1 | 3", 1 | 3, 5);

    print_bin_hex_dec("!0", !0, 5);
    print_bin_hex_dec("~0", ~0, 5);
    print_bin_hex_dec("!1", !1, 5);
    print_bin_hex_dec("~1", ~1, 5);

    // отрицательное двоичное число — дополнение до 2
    // Для положительного x, -x записывается как ~x + 1
    // Это позволяет избежать двойной записи для нуля
    // и использовать одну реализацию арифметических операций
    // для положительных и отрицательных чисел.
    
    // Разница между преобразованием типов (unsigned) и реинтерпретацией *(unsigned*)&
    // Преобразование типов в некоторых случаях меняет значение битов. Реинтерпретация позволяет посмотреть на значение (те же биты) как на значение другого типа. Для целых чисел без переполнения разницы не должно быть:

    print_bin_hex_dec("(unsigned char)-1", (unsigned char)-1, 5);
    i = -1; // мы можем брать указатели только на переменные. Где литералы находятся в памяти — некорректный вопрос.
    print_bin_hex_dec("*(unsigned char*)&", *(unsigned char*)&i, 5);


    return 0;
}
