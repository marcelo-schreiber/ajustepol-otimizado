#include "matrix.h"

/* faz a triangularização de gauss e a retrosubstituição, retornando o vetor solução */
Vector *solve_system(Matrix *A, Vector *b);

/* A função é responsável pelo método dos mínimos quadrados, ela usa três loops aninhados para percorrer
a matriz A, cada membro da matriz é calculado usando a fórmula
interval_sum(A->data[i][j], interval_pow(interval(points->points[k].x), i + j));

Depois disso, dois fors alinhados preenchem o vetor b com a fórmula
interval_sum(b->data[i], interval_mul(interval_pow(interval(points->points[k].x), i), interval(points->points[k].y))); */
void generate_matrix(Matrix *A, Vector *b, const points_t *points, unsigned long long int order);

/* printa e calcula residuo */
void print_residue(const points_t *points, const Vector *b);
