// С командной строки передаётся имя входного файла
// И последовательность инструкций вида A=5
// Написать программу, которая реализует инструкции препроцессора
// #if, #else, #endif в начале строки.
// +#define 
// 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IF 1
#define ELSE 2
#define ELSEIF 3
#define NORMAL 4
#define SKIP 5

// Параметры: массив пар (имя, значение)
struct name_value {
    const char* name;
    int value;
};
int preprocess(FILE *input, FILE *output, int param_count, const struct name_value params[param_count]);
int read_directive(FILE *input, FILE *output, int param_count, const struct name_value params[param_count]);
int handle_directive(int directive, int state, FILE *input, FILE *output, int param_count, const struct name_value params[param_count]);
// 0 - разобрали успешно
int parse_parameter(char *source, struct name_value *destination);

int parse_parameter(char *source, struct name_value *destination) {
    // source = "ABC\01234\0" ⇒ strndup(...)
    // "./a.out\0input.txt\0A=5\0BBB C=7"
    char *end;
    long value;
    char *eq = strchr(source, '=');
    const char *number = eq + 1;
    if (!eq) {
        printf("'=' not found\n");
        return 1;
    }
    *eq = '\0';
    value = strtol(number, &end, 10);
    if (*end != '\0' || end == number) {   // "ABC\0\0"
        printf("Can't read number %s %d\n", number, end - number);
        return 2;
    }
    destination->name = source;
    destination->value = (int)value;
    return 0;
}


int handle_directive(int directive, int state, FILE *input, FILE *output, int param_count, const struct name_value params[param_count])
{
    if (directive == IF) {
        // считать условие
        // проверить его корректность
        // вернуть NORMAL (если условие верно)
        // или SKIP (если условие неверно)
    } else if (directive == ELSE) {
        // до этого было тело оператора #if
        if (state == NORMAL) { // которое мы не пропускали
            return SKIP;
        } else if (state == SKIP) { // которое мы пропускали
            return NORMAL;
        }
    } else if (directive == ENDIF) {
        return NORMAL;
    }
}

int read_directive(FILE *input, FILE *output, int param_count, const struct name_value params[param_count]) {
    char buffer[6];
    int c = fgetc(input);
    if (c == EOF) {
        return 0;
    }
    if (c == '#') {
        if (!fgets(buffer, 6, input)) {
            return -1;
        }
        if (!strncmp(buffer, "if", strlen("if"))) {
            return IF;
        } else if (!strncmp(buffer, "else", strlen("else"))) {
            return ELSE;
        } else if (!strncmp(buffer, "endif", strlen("endif"))) {
            return ENDIF;
        } else {
            fputs(buffer, output);
            return 0;
        }
    } else {
        fputc(c, output);
    }
}

int preprocess(FILE *input, FILE *output, int param_count, const struct name_value params[param_count]) {
    // посимвольно считываем input, ищем участок "\n#"
    // пока участок не найден, переносим символы из input в output
    int c;
    int result;
    int state = NORMAL; // NORMAL, SKIP
    result = read_directive(input, output, param_count, params);
    if (result) {
        handle_directive(result, state, input, output, param_count, params);
    }
    while ((c = fgetc(input)) != EOF) {
        if (state == NORMAL) {
            fputc(c, output);
        }
        if (c == '\n') {
            read_directive(input, output, param_count, params);
            if (result) {
                state = handle_directive(result, input, output, param_count, params);
            }
        }
    }
}

int main(int argc, char *argv[argc]) {
    FILE *input;
    struct name_value *params;
    int param_count = 0;
    if (argc < 2) {
        printf("Usage: %s <filename> [A=5 ...]\n", argv[0]);
        return 1;
    }

    input = fopen(argv[1], "r");
    if (!input) {
        printf("Unable to open file %s\n", argv[1]);
        return 2;
    }

    params = malloc((argc-2) * sizeof(struct name_value));
    for (int i = 2; i < argc; i++) {
        if (parse_parameter(argv[i], &params[param_count])) {
            printf("Invalid argument: %s\n", argv[i]);
        } else {
            printf("Read: %s = %d\n", params[param_count].name, params[param_count].value);
            param_count += 1;
        }
    }

    preprocess(input, stdout, param_count, params);

    free(params);
    fclose(input);
    return 0;
}
