#include <stdio.h>
#include <string.h>
 
int main(void)
{
  const char *str = "Try not. Do, or do not. There is no try.";
  char target = 'T';
  const char *result = str;
 
  while((result = strrchr(result, target)) != NULL) {
    printf("Found '%c' starting at '%s'\n", target, result);
    printf("Index of last occurence: %ld\n", result - str);
    ++result; // Increment result, otherwise we'll find target at the same location
  }
//   my_strrchr (не вызывая функций из string.h, только за счёт циклов)
//   (функция main должна тестировать вашу реализацию
//   на разных наборах входных данных (включая NULL и некорректные данные)
//   и сравнивать работу вашей реализации с исходной)
}
