#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int arr1[5] = { 1, 2, 3, 4, 5 };
    char *c1 = "12345678"; // \0
    char *c2 = "ABCDEFGH"; // ASCII
    char *test = malloc(32);
    char *test2 = test;
    int *arr2 = malloc(5 * sizeof(int));

    memset(test, 'O', 10);
    memset(test + 5, 'N', 3);

    memcpy(test, c1, 15);
    printf("Strlen before: %ld\n", strlen(test));
    test[8] = ' ';
    //printf("Strlen after: %ld\n", strlen(test));

    printf("strcmp(c1, test): %d %d\n", strcmp(c1, test), 'A' == 'A');

    if (strcmp(c1, test) == 0) {
        printf("Equal!\n");
    }

    memcpy(arr2, arr1, 6 * sizeof(int));
    for (int i = 0; i < 5; i++) {
        printf("%d ", arr2[i]);
    }
    printf("\n");

    // test = memchr(test, '5', 2);
    // test = 0x1234567;

    //strcpy(test, c1);
    strncpy(test, c1, 13);

    //strcat(test, c2);
    strncat(test, c2, 3);

    test2 = strdup(test);
    test2[3] = '#';

    printf("String: %s\n", test);
    printf("Test2: %s\n", test2);
    for (int i = 0; i < 32; i++) {
        printf("%x ", test[i]);
    }

    return 0;
}
