#include <stdio.h>
#include <stdlib.h>

typedef double (*matrix_formula)(int size, int row, int col);

double hilbert_element(int size, int row, int col) {
    return 1. / (row + col + 1.);
}

double matrix_element(int size, double *matrix, int row, int col);
double *matrix_element_pointer(int size, double *matrix, int row, int col);
double matrix_fill_formula(int size, double *matrix, matrix_formula formula);
void print_matrix(int size, double *matrix);

double matrix_element(int size, double *matrix, int row, int col) {
    return matrix[row * size + col];
}

double *matrix_element_pointer(int size, double *matrix, int row, int col) {
    return &matrix[row * size + col];
}

double matrix_fill_formula(int size, double *matrix, matrix_formula formula) {
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            *matrix_element_pointer(size, matrix, row, col) = formula(size, row, col);
        }
    }
}

void print_matrix(int n, double *matrix) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%.2f\t", matrix_element(n, matrix, i, j));
        }
        printf("\n");
    }
}

int main(int argc, char **argv) {
    int n;
    double *matrix;
    double *right_side;
    if (argc != 2) {
        printf("Usage: %s <matrix size>\n", argv[0]);
        return 1;
    }

    if (sscanf(argv[1], "%d", &n) != 1 || n <= 0) {
        printf("Invalid size: %s\n", argv[1]);
        return 2;
    }

    matrix = (double*)malloc(n*n*sizeof(double));
    matrix_fill_formula(n, matrix, hilbert_element);
    print_matrix(n, matrix);

    right_side = (double*)malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) {
        right_side[i] = 0;
    }
    right_side[4] = 1.;

    free(matrix);
    return 0;
}
