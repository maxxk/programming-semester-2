#include <stdlib.h>

#define A(i, j) a[(i)*n+(j)]

double element(double *matrix, int size, int row, int column);
double element(double *matrix, int size, int row, int column)
{
    return matrix[size*row + column];
}

double* element_pointer(double *matrix, int size, int row, int column);
double* element_pointer(double *matrix, int size, int row, int column)
{
    return &matrix[size*row + column];
}

double element(int i, int j)
{
    return fabs(i - j);
}

int main(int argc, char **argv) {
    int n = 10;
    double matrix[1000][1000]; // это неправильно
    double matrix[1000*1000]; // это неправильно
    double matrix[4*4]; 

    // это неправильно
    double **matrix = malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        matrix[i] = malloc(n * sizeof(double));
    }
    
    matrix[i][j] // несколько обращений к памяти: указатель на строку matrix[i], указатель на элемент [j]

    double *matrix = malloc(n*n*sizeof(double));
    double *right_part = malloc(n*sizeof(double));
    short *row_indices = malloc(n * sizeof(short)); // < 32 000
    // O(n³)

    for (int i = 0; i < n; i++) { row_indices[i] = i; }
    matrix[row_indices[i]*n + column_indices[j]]

    tmp = row_indices[i];
    row_indices[i] = row_indices[k];
    row_indices[k] = tmp;

    // выбор главного элемента (неправильно): перезаписать элементы в матрице

    printf("%f\n", element(matrix, n, 3, 5));
    *element_pointer(matrix, n, 3, 5) = 10;
}
