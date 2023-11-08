/*
 * Autores:
 * Marcelo Augusto Rissette Schreiber GRR20220063
 * Felipe Quaresma Vieira GRR20215516
 *
 * Data: 8/10/2023
 */

#include "matrix.h"

Matrix* initialize_matrix(long long int order) {
    Matrix *A = (Matrix *)malloc(sizeof(Matrix));
    A->size = order;
    A->data = (Interval **)malloc(A->size * sizeof(Interval *));

    for (long long int i = 0; i < A->size; i++)
    {
        A->data[i] = (Interval *)malloc(A->size * sizeof(Interval));
    }
    return A;
}

Vector* initialize_vector(long long int order) {
    Vector *b = (Vector *)malloc(sizeof(Vector));
    b->size = order;
    b->data = (Interval *)malloc(b->size * sizeof(Interval));
    return b;
}

size_t find_max(Matrix m, size_t i)
{
  size_t max = i;

  for (size_t j = i + 1; j < m.size; j++)
  {
    if (fabs(m.data[j][i].upper) > fabs(m.data[max][i].upper)) // get just the upper
    {
      max = j;
    }
  }

  return max;
}

void switch_line(Matrix *m, Vector *c, size_t i, size_t max)
{
  Interval *temp = m->data[i];
  m->data[i] = m->data[max];
  m->data[max] = temp;

  Interval t = c->data[i];
  c->data[i] = c->data[max];
  c->data[max] = t;
}

void triangulate_matrix_by_gauss(Matrix *m, Vector *c)
{
  for (size_t i = 0; i < m->size; i++)
  {
    size_t max = find_max(*m, i);

    if (max != i)
    { // switch line
      switch_line(m, c, i, max);
    }

    for (size_t j = i + 1; j < m->size; j++)
    {
      // Interval mult = m->data[j][i] / m->data[i][i];
      Interval mult = interval_div(m->data[j][i], m->data[i][i]);

      m->data[j][i].lower = 0.0; // [j][i] = 0
      m->data[j][i].upper = 0.0;

      for (size_t k = i + 1; k < m->size; k++)
      {
        // m->data[j][k] -= mult * m->data[i][k];
        m->data[j][k] = interval_sub(m->data[j][k], interval_mul(mult, m->data[i][k]));
      }

      // c->data[j] -= mult * c->data[i];
      c->data[j] = interval_sub(c->data[j], interval_mul(mult, c->data[i]));
    }
  }
}

void print_vector(Vector v)
{
    for (long long int i = 0; i < v.size; i++)
    {
        printf("[%1.8e,%1.8e] ", v.data[i].lower, v.data[i].upper);
    }
    printf("\n");
}

Vector *get_solution_by_substitution(Matrix m, Vector c)
{
  Vector *solution = initialize_vector(m.size);

  for (long long int i = m.size - 1; i >= 0; i--)
  {

    Interval sum = interval(0.0);

    for (size_t j = i + 1; j < m.size; j++)
      sum = interval_sum(sum, interval_mul(m.data[i][j], solution->data[j]));

    solution->data[i] = interval_div(interval_sub(c.data[i], sum), m.data[i][i]);
  }

  return solution;
}

void free_matrix(Matrix *A)
{
    for (long long int i = 0; i < A->size; i++)
    {
        free(A->data[i]);
    }
    free(A->data);
    free(A);
}

void free_vector(Vector *b)
{
    free(b->data);
    free(b);
}