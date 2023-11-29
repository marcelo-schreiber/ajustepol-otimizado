/*
 * Autores:
 * Marcelo Augusto Rissette Schreiber GRR20220063
 * Felipe Quaresma Vieira GRR20215516
 *
 * Data: 8/10/2023
 */

#include "matrix.h"
#include <string.h>

Matrix *initialize_matrix(long long int order)
{
  Matrix *A = (Matrix *)malloc(sizeof(Matrix));
  A->size = order;
  A->data = (Interval *)malloc(order * order * sizeof(Interval) + 1);

  return A;
}

Vector *initialize_vector(long long int order)
{
  Vector *b = (Vector *)malloc(sizeof(Vector));
  b->size = order;
  b->data = (Interval *)malloc(order * sizeof(Interval));

  return b;
}

size_t find_max(Matrix m, size_t i)
{
  size_t max = i;
  size_t m_size = m.size;
  for (size_t j = i + 1; j < m_size; ++j)
  {
    if (fabs(m.data[j * m_size + i].upper) > fabs(m.data[max * m_size + i].upper)) // get just the upper
    {
      max = j;
    }
  }

  return max;
}

void switch_line(Matrix *m, Vector *c, size_t i, size_t max)
{

  size_t m_size = m->size;

    Interval* temp = (Interval*)malloc(sizeof(Interval) * m_size);
    memcpy(temp, &(m->data[i * m_size]), sizeof(Interval) * m_size);
    memcpy(&(m->data[i * m_size]), &(m->data[max * m_size]), sizeof(Interval) * m_size);
    memcpy(&(m->data[max * m_size]), temp, sizeof(Interval) * m_size);
    // m->data[i * m_size + j] = m->data[max * m_size + j];
    // m->data[max * m_size + j] = t;
    free(temp);

  Interval t = c->data[i];
  c->data[i] = c->data[max];
  c->data[max] = t;
}

// void switch_line(Matrix *m, Vector *c, size_t i, size_t max)
// {
//   // Interval *temp = m->data[i];
//   // m->data[i] = m->data[max];
//   // m->data[max] = temp;

//   size_t m_size = m->size;

//   for (size_t j = 0; j < m_size; ++j)
//   {
//     Interval t = m->data[i * m_size + j];
//     m->data[i * m_size + j] = m->data[max * m_size + j];
//     m->data[max * m_size + j] = t;
//   }

//   Interval t = c->data[i];
//   c->data[i] = c->data[max];
//   c->data[max] = t;
// }

void triangulate_matrix_by_gauss(Matrix *m, Vector *c)
{
  size_t m_size = m->size;

  for (size_t i = 0; i < m_size; ++i)
  {
    size_t max = find_max(*m, i);

    if (max != i)
    { // switch line
      switch_line(m, c, i, max);
    }

    for (size_t j = i + 1; j < m_size; ++j)
    {
      // Interval mult = m->data[j][i] / m->data[i][i];
      Interval mult = interval_div(m->data[j * m_size + i], m->data[i * m_size + i]);

      m->data[j * m_size + i].lower = 0.0; // [j * m_size + i] = 0
      m->data[j * m_size + i].upper = 0.0;

      for (size_t k = i + 1; k < m_size; ++k)
      {
        // m->data[j * m_size + k] -= mult * m->data[i * m_size + k];
        m->data[j * m_size + k] = interval_sub(m->data[j * m_size + k], interval_mul(mult, m->data[i * m_size + k]));
      }

      // c->data[j] -= mult * c->data[i];
      c->data[j] = interval_sub(c->data[j], interval_mul(mult, c->data[i]));
    }
  }
}

void print_vector(Vector v)
{
  for (long long int i = 0; i < v.size; ++i)
  {
    printf("[%1.8e,%1.8e] ", v.data[i].lower, v.data[i].upper);
  }
  printf("\n");
}

Vector *get_solution_by_substitution(Matrix m, Vector c)
{
  size_t m_size = m.size;
  Vector *solution = initialize_vector(m_size);

  for (long long int i = m_size - 1; i >= 0; i--)
  {

    Interval sum = interval(0.0);

    for (size_t j = i + 1; j < m_size; ++j)
      sum = interval_sum(sum, interval_mul(m.data[i * m_size + j], solution->data[j]));

    solution->data[i] = interval_div(interval_sub(c.data[i], sum), m.data[i * m_size + i]);
  }

  return solution;
}

void free_matrix(Matrix *A)
{
  free(A->data);
  free(A);
}

void free_vector(Vector *b)
{
  free(b->data);
  free(b);
}