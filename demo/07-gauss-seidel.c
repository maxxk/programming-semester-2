#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EPS 1e-16

typedef double (*matrix_formula)(int size, int row, int col);

double hilbert_element(int size, int row, int col) {
    return 1. / (row + col + 1.);
}

double matrix_element(int size, const double *matrix, int row, int col);
double *matrix_element_pointer(int size, double *matrix, int row, int col);
double matrix_fill_formula(int size, double *matrix, matrix_formula formula);
void print_matrix(int size, double *matrix);
void print_vector(int size, double *vector);

int lower_triangular_gausian(int size, double *matrix, double *vector);
void matrix_upper_triangle_multiply(int size, double *matrix, double *vector);
void matrix_multiply(int size, double *matrix, double *vector);
void vector_sub(int size, double *left_source, double *right_dest);
int gauss_seidel(int size, double *matrix, double *rhs, double *x);

double matrix_element(int size, const double *matrix, int row, int col) {
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

int lower_triangular_gausian(int size, double *matrix, double *vector) {
    for (int diag = 0; diag < size; diag++) {
        if (fabs(matrix_element(size, matrix, diag, diag)) < EPS) {
            return (diag+1);
        }

        vector[diag] /= matrix_element(size, matrix, diag, diag);

        for (int row = diag + 1; row < size; row++) {
            vector[row] -= vector[diag] * matrix_element(size, matrix, row, diag);
        }
    }
    return 0;
}

void vector_sub(int size, double *left_source, double *right_dest) {
    for (int i = 0; i < size; i++) {
        right_dest[i] = left_source[i] - right_dest[i];
    }
}

int gauss_seidel(int size, double *matrix, double *rhs, double *x) {
    int status;
    double *residual;

    residual = (double*)malloc(size*sizeof(double));
    
    memcpy(x, rhs, size * sizeof(double));
    if ((status = lower_triangular_gausian(size, matrix, x))) {
        return status;
    }

    while (1) {
        matrix_upper_triangle_multiply(size, matrix, x);
        vector_sub(size, rhs, x);
        if ((status = lower_triangular_gausian(size, matrix, x))) {
            return status;
        }
        print_vector(size, x);
        //getc(stdin);
    }
}

void matrix_upper_triangle_multiply(int size, double *matrix, double *vector) {
    double value;
    for (int row = 0; row < size; row++) {
        value = 0.;
        for (int col = row + 1; col < size; col++) {
            value += matrix_element(size, matrix, row, col) * vector[col];
        }
        vector[row] = value;
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

void print_vector(int n, double *vector) {
    for (int i = 0; i < n; i++) {
        printf("%.2f\t", vector[i]);
    }
    printf("\n");
}

int main(int argc, char **argv) {
    int n;
    double *matrix;
    double *right_side;
    double *x;

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
    x = (double*)malloc(n * sizeof(double));

    for (int i = 0; i < n; i++) {
        right_side[i] = 0;
    }
    right_side[2] = 1.;

    if (gauss_seidel(n, matrix, right_side, x)) {
        printf("Can't perform Gaussian elimination\n");
        return 2;
    }

    free(matrix);
    return 0;
}
