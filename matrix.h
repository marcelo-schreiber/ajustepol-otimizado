#include "interval_operations.h"
#include <math.h>
#include <float.h>
#include <stdlib.h>
#include <stdint.h>

/* Estrutura de dados de uma Matriz de intervalos */
typedef struct
{
  size_t size;
  Interval *data;
} Matrix;

/* Estrutura de dados de um vetor de intervalos */
typedef struct
{
  size_t size;
  Interval *data;
} Vector;

/* Estrutura de um ponto (x,y) */
typedef struct point
{
  double x;
  double y;
} point_t;

/* Estrutura de um array de pontos (x,y) */
typedef struct points
{
  point_t *points;
  long long int num_of_points;
} points_t;

/* eliminação de gauss */
void triangulate_matrix_by_gauss(Matrix *m, Vector *c);

/* faz retrossubstituição e retorna o vetor solução */
Vector *get_solution_by_substitution(Matrix m, Vector c);

/* Inicializa matriz de intervalos */
Matrix *initialize_matrix(long long int order);

/* Inicializa vector de intervalos */
Vector *initialize_vector(long long int order);

/* printa vector */
void print_vector(Vector v);

/* acha o maior numero da coluna */
size_t find_max(Matrix m, size_t i);

/* troca linha da matriz */
void switch_line(Matrix *m, Vector *c, size_t i, size_t max);

/* libera memoria */
void free_matrix(Matrix *A);
void free_vector(Vector *b);
